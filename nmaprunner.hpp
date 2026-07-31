#ifndef NMAPRUNNER_HPP
#define NMAPRUNNER_HPP
#include "executor.hpp"
#include <string>
#include <map>
#include <chrono>

constexpr size_t MAX_NMAP_ARGS = 16;

enum class NmapScanType{
  Simple,
  FullTCP,
  UDP,
  ServiceScript,
  Vuln
};

struct ScanJob
{
  std::string tool;
  NmapScanType type;
  std::string target;
};

struct ScanResult
{
  ScanJob job;

  int exitCode;

  std::string stdoutData;

  std::chrono::system_clock::time_point start;
  std::chrono::system_clock::time_point end;
};

typedef std::map<std::string, ScanResult> ScanResults;

class NmapRunner {

  public:
    ScanResult run(const ScanJob& job);

  private:
    std::vector<std::string> buildArgs(
      const ScanJob& job
    );
    // NmapRunner(const std::string &ipAddress);
    // int service_script_scan(std::string &data);
    // int udp_scan(std::string &data);
    // int simple_scan(std::string &data);
    // int full_tcp_scan(std::string &data);
    // int vuln_scan(std::string &data);

  // private:
  //   template <std::size_t N>
  //   int executeScan(std::string &data, const char *(&params)[N]) {
  //     int result = spawnProc(&data, params);
  //     if (result != 0) {
  //       std::cout << "There was a failure spawning a process for nmap scan"
  //                 << std::endl;
  //     }
  //     return result;
  //   }
};

#endif