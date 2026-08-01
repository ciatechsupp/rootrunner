#include "nmaprunner.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

class RootRunner {
private:
  std::string targetIp;
  std::vector<ScanJob> jobs;
  ScanResults scanResults;
  NmapRunner runner;

public:
  RootRunner(std::string ipAddr) : targetIp{ipAddr} {
    jobs = {
      {"Nmap", NmapScanType::Simple, targetIp},
      {"Nmap", NmapScanType::FullTCP, targetIp},
      {"Nmap", NmapScanType::UDP, targetIp},
      {"Nmap", NmapScanType::ServiceScript, targetIp},
      {"Nmap", NmapScanType::Vuln, targetIp}
    };  
  }

  int addScanResult(const std::string &scanType,
                    const ScanResult &scanResult) {
    scanResults[scanType] = scanResult;
    return 0;
  }

  const std::string &getScanResult(const std::string &scanType) {
    return scanResults[scanType].stdoutData;
  }

  int writeStatusLog(const std::string &fileName) {
    try {
      std::ofstream outFile(fileName);

      if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return 1;
      }

      for (const auto &scan : scanResults) {
        const std::string &scanType = scan.first;
        const auto &scanResultData = scan.second;

        outFile << scanResultData.job.tool << "->" << scanType << " Scan" << std::endl;
        outFile << "----------------------\n" << std::endl;
        outFile << "Scan Results" << std::endl;
        outFile << "[----------------------]" << std::endl;
        outFile << scanResultData.stdoutData << std::endl;
      }
      outFile.close();
    } catch (const std::exception &e) {
      std::cout << "A standard exception was caught, with message: '"
                << e.what() << "'\n";
    }
    return 0;
  }

  int run() {

    std::vector<std::thread> threads;
    std::vector<ScanResult> results(jobs.size());

    for (size_t i = 0; i < jobs.size(); ++i){
      threads.emplace_back([&, i]{
        std::cout << "Starting " << toString(jobs[i].type) << " on " << jobs[i].target << std::endl;
        results[i] = runner.run(jobs[i]);
      });
    }

    for (auto& t : threads){
      t.join();
    }

    for (const auto& result : results){
      addScanResult(
        toString(result.job.type),
        result
      );
    }

    // for (const auto& job : jobs){
    //   ScanResult result = runner.run(job);
    //   addScanResult(
    //     toString(job.type),
    //     result
    //   );
    // }

    std::string outputFileName = targetIp + "_output.txt";

    writeStatusLog(outputFileName);

    // std::string data;
    // nmapInstance.simple_scan(data);
    // addScanResult("Nmap", "nmap_simple_scan", data);
    // data.clear();
    // nmapInstance.full_tcp_scan(data);
    // addScanResult("Nmap", "nmap_full_tcp_scan", data);
    // data.clear();
    // nmapInstance.vuln_scan(data);
    // addScanResult("Nmap", "nmap_vuln_scan", data);
    // data.clear();
    // nmapInstance.udp_scan(data);
    // addScanResult("Nmap", "nmap_udp_scan", data);
    // data.clear();
    // nmapInstance.service_script_scan(data);
    // addScanResult("Nmap", "nmap_service_script_scan", data);
    // data.clear();
    // writeStatusLog(targetIp);
    // return 0;

    return 0;
  }

  // int nmapRunner(){
  // }
  // int rpcRunner(){}
  // int snmpRunner(){}
  // int smbRunner(){}
  // int webRunner(){}
  // int kerberosRunner(){}
  // int ldapRunner(){}
  // int rdpRunner(){}
  // int winrmRunner(){}
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <targets_file>" << std::endl;
    return 1;
  }

  std::ifstream targetsFile(argv[1]);
  if (!targetsFile.is_open()) {
    std::cerr << "Error: Could not open " << argv[1] << std::endl;
    return 1;
  }

  std::string ip;
  while (std::getline(targetsFile, ip)) {
    if (ip.empty())
      continue;

    RootRunner r(ip);
    r.run();
  }

  return 0;
}