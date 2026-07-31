#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <string>
#include <vector>


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

std::string toString(NmapScanType type){
  switch(type)
  {
    case NmapScanType::Simple: return "Simple";
    case NmapScanType::FullTCP: return "FullTCP";
    case NmapScanType::UDP: return "UDP";
    case NmapScanType::ServiceScript: return "ServiceScript";
    case NmapScanType::Vuln: return "Vuln";
  }
  return "Unknown";
}

bool fileExists(const std::string &path);

#endif