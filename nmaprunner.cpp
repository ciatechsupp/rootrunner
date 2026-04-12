#include "executor.hpp"
#include "nmaprunner.hpp"

NmapRunner::NmapRunner(const std::string& ipAddress) : ipAddress{ipAddress}, data{} {};

int NmapRunner::service_script_scan(){
    const char* params[]{"nmap", "-Pn", "-sC", "-sV", "-oA", ipAddress.c_str(), nullptr};
    data.clear();
    int result = spawnProc(&data, params);
    return result;
}

int NmapRunner::udp_scan(){
    return 0;
}

int NmapRunner::simple_scan(){
    const char* params[]{"nmap", "-n", "-v", "-sT", "-A", ipAddress.c_str(), nullptr};
    data.clear();
    int result = spawnProc(&data, params);

    return result;
}

int NmapRunner::full_tcp_scan(){
    return 0;
}

int NmapRunner::suggested_scan(){
    return 0;
}