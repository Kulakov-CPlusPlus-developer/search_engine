#include "SearchServer.h"

#include <algorithm>
#include <string>
#include <sstream>
#include "Checks.h"
#include "InvertedIndex.h"
#include <set>
#include <vector>
#include "ConverterJSON.h"

vector<vector<RelativeIndex>> SearchServer::search(const vector<string>& queries_input) {
    vector<vector<RelativeIndex>> results;
    ConverterJSON convert;
    vector<vector<std::pair<int, float>>>answers;

    for (auto& query : queries_input) {
        stringstream ss(query);
        string word;
        vector<string> query_words;
        vector<string> unique_query_words;
        while(ss >> word) {
            query_words.push_back(word);
        }
        for(auto& word1 : query_words) {
            int count = 0;
            for(auto& word2 : query_words) {
                if(word1 == word2) {
                    count++;
                    if(count == 1) {
                        unique_query_words.push_back(word1);
                    }
                }
            }
        }
        vector<string> sorted_query = sorting_queries(unique_query_words,_index);
        set<size_t> doc_ids;
        for(auto& word3 : sorted_query) {
            for(auto& entry : _index.GetWordCount(word3)) {
                doc_ids.emplace(entry.doc_id);
            }
        }
        vector<Entry> entries;
        bool checkingWords = false;
        for(auto& entry : _index.GetWordCount(sorted_query[0])) {
            entries.push_back(entry);
        }
        vector<Entry> entries_copy = entries;
        for(auto& word3 : sorted_query) {
            if(!entries_copy.empty()) {
                for(auto& entry : entries_copy) {
                    bool found = false;
                    for(auto& entry2 : _index.GetWordCount(word3)) {
                        if(entry.doc_id == entry2.doc_id) {
                            found = true;
                        }
                    }
                    if(!found) {erase(entries_copy, entry);}
                }
            }
        }
        if(!entries_copy.empty()) {
            vector<RelativeIndex> relative_indices;
            map<size_t, size_t> doc_id_absolut_rel;
            for(auto& id : doc_ids) {
                size_t absolute_relevance = 0;
                for(auto& query_word : sorted_query) {
                    for(auto& entry2 : _index.GetWordCount(query_word)) {
                        if(id == entry2.doc_id) {
                            absolute_relevance += entry2.count;
                        }
                    }
                }
                doc_id_absolut_rel[id] = absolute_relevance;
            }

            size_t max_absolute_rel = 0;
            for(auto& [doc_id, absolute_relevance] : doc_id_absolut_rel) {
                max_absolute_rel = max(max_absolute_rel, absolute_relevance);
            }
            for(auto& [doc_id, absolute_relevance] : doc_id_absolut_rel) {
                float relative_relevance;
                if(max_absolute_rel > 0) {
                    relative_relevance = (float)absolute_relevance / (float)max_absolute_rel;
                }
                else {
                    relative_relevance = 0.0f;
                }


                relative_indices.push_back({doc_id, relative_relevance});
            }

            sort(relative_indices.begin(), relative_indices.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
                if(a.rank > b.rank) {
                    return a.rank > b.rank;
                }else if(a.rank < b.rank) {
                    return a.rank > b.rank;
                }else if(a.rank == b.rank) {
                    return a.doc_id < b.doc_id;
                }
            });
            int count = convert.GetResponsesLimit();
            while(relative_indices.size() > count) {
                relative_indices.pop_back();
            }
            results.push_back(relative_indices);
            for(auto& buffer1 : results) {
                for(auto& buffer2 : buffer1) {
                    answers.push_back({pair<int, float>(buffer2.doc_id, buffer2.rank)});
                }
            }
        }
    }

    convert.putAnswers(answers);
    return results;
}
