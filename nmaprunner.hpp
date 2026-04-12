#ifndef NMAPRUNNER_HPP
#define NMAPRUNNER_HPP
#include <string>

class NmapRunner{
    std::string_view ipAddress;
    std::string data;

    public:
        NmapRunner(std::string_view ipAddress){};
        int service_script_scan(){};
        int udp_scan(){};
        int tcp_syn_scan(){};
        int tcp_connect_scan(){};
        int suggested_scan(){};
};

#endif