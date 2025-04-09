#include <iostream>
#include "InvertedIndex.h"
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <algorithm>
#include <mutex>

using namespace std;

void InvertedIndex::UpdateDocumentBase(const vector<string> &input_docs) {
    docs.clear();
    freq_dictionary.clear();
    vector<string> words;
    stringstream buffer;
    docs = input_docs;
    mutex mtx;
    std::vector<std::thread> threads;
    size_t num_threads = std::thread::hardware_concurrency();
    size_t docs_per_thread = docs.size() / num_threads;
    threads.reserve(num_threads);
    for (int i = 0; i < num_threads; i++) {
        size_t start = i * docs_per_thread;
        size_t end = (i == num_threads - 1) ? docs.size() : (i + 1) * docs_per_thread;
        threads.emplace_back([this, start, end, &mtx]() {
            for( size_t doc_id = start; doc_id < end; ++doc_id ) {
                string text = docs[doc_id];
                stringstream ss(text);
                string word;
                while(ss >> word) {
                    mtx.lock();
                    transform(word.begin(), word.end(), word.begin(), ::tolower);
                    auto it = freq_dictionary.find(word);
                    if(it == freq_dictionary.end()) {
                        freq_dictionary[word].push_back({doc_id, 1});
                    }else {
                        bool found = false;
                        for(auto& entry : it->second) {
                            if(entry.doc_id == doc_id) {
                                found = true;
                                entry.count++;
                                break;
                            }
                        }
                        if(!found) {
                            it->second.push_back({doc_id, 1});
                        }
                    }
                    mtx.unlock();
                }
            }
        });
    }
    for(auto& thread : threads) {
        thread.join();
    }
}
vector<Entry> InvertedIndex::GetWordCount(const string &word) {
    auto it = freq_dictionary.find(word);
    if(it == freq_dictionary.end()) {
        return {};
    }
    return it->second;
}









