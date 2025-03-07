#include "ConverterJSON.h"
#include "SearchServer.h"
#include "InvertedIndex.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ConverterJSON json;
    InvertedIndex invertedIndex;
    SearchServer search_server(invertedIndex);

    vector<string> files = json.getFiles();
    invertedIndex.UpdateDocumentBase(files);

    vector<string> requests = json.GetRequests();
    search_server.search(requests);

    return 0;
}