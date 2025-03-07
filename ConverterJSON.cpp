#include "ConverterJSON.h"
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <exception>
#include "Exceptions.h"
#include "Checks.h"
using namespace std;

ConverterJSON::ConverterJSON(){};
ConverterJSON::~ConverterJSON(){};

vector<string> ConverterJSON::getFiles () {
  cout << "Loading config file..." << std::endl;
  ifstream configFile("config.json");
  if(checkingFilesIsOpen(configFile)) {
    if(configFile.is_open()) {
      try{
        nlohmann::json config;
        configFile >> config;
        configFile.close();
        if(config["config"].is_null()) {throw NoSuchConfig();}
        cout << "Loaded config file." << endl;
        cout << config["name"] << endl;
        cout << config["version"] << endl;
        configData = config;
      }catch (NoSuchConfig& e) {
        cerr << e.what() << endl;
      }
    }
  }
  vector<string> path;
  vector<string> files;
  try {
    if(configData.contains("files") && configData["files"].is_array()) {
      for(auto& file : configData["files"]) {
        if(file.is_string()) {
          path.push_back(file);

        }else {
          cout << "File not string" << endl;
        }
      }
    }else {
      throw NoSuchFile();
    }
  }catch(NoSuchFile& e) {
    cerr << e.what() << endl;
  }

  ifstream file;
  for(auto& _path : path) {
    file.open(_path);
    if(!file.is_open()) {
      cerr << "File not open!" << endl;
    }else {
      stringstream buffer;
      buffer << file.rdbuf();
      if(checkingFiles(buffer)) {
        string content = buffer.str();
        files.push_back(content);
      }
    }
    file.close();
  }
  return files;
}

int ConverterJSON::GetResponsesLimit () {
  if(configData.contains("responseLimit")) {
    return configData["max_responses"].get<int>();
  } else {
    return 5;
  }
}

vector<string> ConverterJSON::GetRequests() {
  vector<string> requests;
  ifstream fileRequests("requests.json");
  checkingFilesIsOpen(fileRequests);
  nlohmann::json _requests;
  fileRequests >> _requests;
  fileRequests.close();
  try {
    if(_requests.contains("requests") && _requests["requests"].is_array()) {
      if(checkingRequests(_requests)) {
        for(auto& request : _requests["requests"]) {
          requests.push_back(request);
        }
      }
      return requests;
    }else {
      throw NoSuchRequests();
    }
  }catch(NoSuchRequests& e) {
    cerr << e.what() << endl;
    return requests;
  }
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>>answers) {
  nlohmann::json answersJson;
  nlohmann::json answersObject;
  int requestIndex = 1;
  for(auto& answer : answers) {
    string requestID = "request" + to_string(requestIndex);
    nlohmann::json requestObject;

    if(answer.empty()) {
      requestObject["relevance"] = {};
      requestObject["result"] = "false";
    }else {
      nlohmann::json relevanceArray;
      for(auto& result : answer) {
        nlohmann::json resultObject;
        resultObject["docid"] = result.first;
        resultObject["rank"] = result.second;
        relevanceArray.push_back(resultObject);
      }
      requestObject["relevance"] = relevanceArray;
      requestObject["result"] = "true";
    }
    answersObject[requestID] = requestObject;
    requestIndex++;
  }
  answersJson["answers"] = answersObject;

  std::ofstream outputFile("answers.json");
  outputFile << answersJson.dump(4);
  outputFile.close();
}









