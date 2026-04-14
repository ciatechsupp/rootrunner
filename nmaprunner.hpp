#ifndef NMAPRUNNER_HPP
#define NMAPRUNNER_HPP
#include <string>
#include <unordered_map>
#include "executor.hpp"


class NmapRunner{
    const std::string& ipAddress;
    std::string data;

    public:
        NmapRunner(const std::string& ipAddress);
        int service_script_scan(std::string& data);
        int udp_scan(std::string& data);
        int simple_scan(std::string& data);
        int full_tcp_scan(std::string& data);
        int vuln_scan(std::string& data);
};

#endif