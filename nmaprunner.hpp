#ifndef NMAPRUNNER_HPP
#define NMAPRUNNER_HPP
#include "executor.hpp"
#include <string>

class NmapRunner {
  const std::string ipAddress;

public:
  NmapRunner(const std::string &ipAddress);
  int service_script_scan(std::string &data);
  int udp_scan(std::string &data);
  int simple_scan(std::string &data);
  int full_tcp_scan(std::string &data);
  int vuln_scan(std::string &data);

private:
  template <std::size_t N>
  int executeScan(std::string &data, const char *(&params)[N]) {
    int result = spawnProc(&data, params);
    if (result != 0) {
      std::cout << "There was a failure spawning a process for nmap scan"
                << std::endl;
    }
    return result;
  }
};

#endif