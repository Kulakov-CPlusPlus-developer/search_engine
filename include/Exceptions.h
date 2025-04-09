#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class NoSuchFile : public std::exception {
public:
  const char* what() const noexcept override {
    return "No such file or directory";
  }
};
  class NoSuchConfig : public std::exception {
public:
  const char* what() const noexcept override {
    return "'config' no such in file";
  }
};
class NoSuchFiles : public std::exception {
public:
  const char* what() const noexcept override {
    return "'files' no such in file";
  }
};
class NoSuchRequests : public std::exception {
public:
  const char* what() const noexcept override {
    return "Requests not found";
  }
};

#endif //EXCEPTIONS_H
