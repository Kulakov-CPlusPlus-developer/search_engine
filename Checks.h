#ifndef CHECKS_H
#define CHECKS_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "InvertedIndex.h"
#include "nlohmann/json.hpp"
#include "Exceptions.h"
#include "SearchServer.h"
#include <algorithm>


using namespace std;

inline bool checkingFiles (stringstream &buffer) {
  int maxLength = 100;
  bool correctWord = true;
  int count = 0;
  string word;
  while(buffer >> word) {
    count++;
    if(word.length() > maxLength) {
      cerr << "Uncorrected word!" << endl;
      correctWord = false;
      break;
    }
  }
  if(count > 1000 && !correctWord) {
    cerr << "Too many words!" << endl;
    return false;
  }else return true;
}

inline bool checkingRequests (nlohmann::json &requests) {
  int countRequest = 0;
  int countWords = 0;
  for(auto& request : requests["requests"]) {
    if(request.is_string()) {
      countRequest++;
      stringstream buffer;
      buffer << request;
      string word;
      while(buffer >> word) {
        countWords++;
      }
    }else cerr << "Invalid request!" << endl;
  }
  if(countRequest > 1000 && countWords >= 1 && countWords <=10) {
    return true;
  }else return false;
}
inline bool checkingFilesIsOpen(std::ifstream& fileRequests) {
  try {
    fileRequests.open("requests.json");
    if (!fileRequests.is_open()) {
      throw NoSuchFile();
    }
    return true;
  } catch (NoSuchFile& e) {
    cerr << e.what() << endl;
    return false;
  }
}
inline vector<string> sorting_queries(vector<string>& words, InvertedIndex& index) {
  vector<string> result;
  vector<pair<string,size_t>> queryResult;

  for(auto& word : words) {
    size_t result_count = 0;
    for(auto& _word : index.GetWordCount(word)) {
      result_count += _word.count;
    }
    queryResult.emplace_back(make_pair(word, result_count));
  }
  sort(queryResult.begin(), queryResult.end(), [](const auto& a, const auto& b) {
    return a.second < b.second;
  });
  for(auto& word : queryResult) {
    result.push_back(word.first);
  }
  return result;
}




#endif //CHECKS_H
