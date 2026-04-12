#include "executor.hpp"

class NmapRunner{
    std::string ipAddress;
    std::string data;
public:
    NmapRunner(std::string ipAddress) : ipAddress{ipAddress} {}

    int service_script_scan(){
        const char* params[]{"nmap", "-Pn", "-sC", "-sV", "-oA"};
        data.clear();
        
        return 0;
    }

    int udp_scan(){
        return 0;
    }

    int tcp_syn_scan(){
        return 0;
    }

    int tcp_connect_scan(){
        return 0;
    }

    int suggested_scan(){
        return 0;
    }



};