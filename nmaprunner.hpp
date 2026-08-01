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

std::string toString(NmapScanType type);

class NmapRunner {

  public:
    ScanResult run(const ScanJob& job);

  private:
    std::vector<std::string> buildArgs(
      const ScanJob& job
    );
};

#endif