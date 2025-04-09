#ifndef CONVERTERJSON_H
#define CONVERTERJSON_H
#include <vector>
#include <string>
#include <nlohmann/json.hpp>


class ConverterJSON
{
public:
    ConverterJSON ();
    ~ConverterJSON ();

    std::vector<std::string> getFiles();
    int  GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> &answers);



private:
    nlohmann::json configData;

};


#endif //CONVERTERJSON_H
