#include "nmaprunner.hpp"
#include <iostream>

NmapRunner::NmapRunner(const std::string &ipAddress) : ipAddress{ipAddress} {};

int NmapRunner::service_script_scan(std::string &data) {
  const char *params[]{"nmap", "-Pn", "-n", "-sC", "-sV", ipAddress.c_str(),
                       nullptr};
  return executeScan(data, params);
}

int NmapRunner::udp_scan(std::string &data) {
  const char *params[]{"nmap", "-Pn", "-n", "-sUV", "-A", ipAddress.c_str(),
                       nullptr};
  return executeScan(data, params);
}

int NmapRunner::simple_scan(std::string &data) {
  const char *params[]{
      "nmap", "-Pn", "-n", "-v", "-sT", "-A", ipAddress.c_str(), nullptr};
  return executeScan(data, params);
}

int NmapRunner::full_tcp_scan(std::string &data) {
  const char *params[]{
      "nmap", "-Pn", "-n", "-v", "-sT", "-p-", ipAddress.c_str(), nullptr};
  return executeScan(data, params);
}

int NmapRunner::vuln_scan(std::string &data) {
  const char *params[]{
      "nmap", "-Pn", "-n", "--script=vuln", "-sT", "-A", ipAddress.c_str(),
      nullptr};
  return executeScan(data, params);
}