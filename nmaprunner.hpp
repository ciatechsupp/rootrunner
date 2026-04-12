#ifndef NMAPRUNNER_HPP
#define NMAPRUNNER_HPP
#include <string>
#include "executor.hpp"

class NmapRunner{
    const std::string& ipAddress;
    std::string data;

    public:
        NmapRunner(const std::string& ipAddress);
        int service_script_scan();
        int udp_scan();
        int simple_scan();
        int full_tcp_scan();
        int suggested_scan();
};

#endif