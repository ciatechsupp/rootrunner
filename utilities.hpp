#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::string> ScanResult;
typedef std::map<std::string, ScanResult> ScanResults;

struct ServiceInfo {
  int port;
  std::string name;
  std::string protocol;
};

struct HttpInfo {
  std::string server;
  std::string title;
  std::string method;
};

struct SmbInfo {
  std::vector<std::string> shares;
};

bool fileExists(const std::string &path);

#endif