#include <iostream>
#include "executor.hpp"
#include "nmaprunner.hpp"

NmapRunner::NmapRunner(const std::string& ipAddress) : ipAddress{ipAddress}, data{} {};

int NmapRunner::service_script_scan(){
    const char* params[]{"nmap", "-Pn", "-n", "-sC", "-sV", "-oA", ipAddress.c_str(), nullptr};
    data.clear();
    int result = spawnProc(&data, params);
    return result;
}

int NmapRunner::udp_scan(){
    const char* params[]{"nmap", "-Pn", "-n", "-sUV", "-A", ipAddress.c_str(), nullptr};
    return 0;
}

int NmapRunner::simple_scan(){
    const char* params[]{"nmap", "-Pn", "-n", "-v", "-sT", "-A", ipAddress.c_str(), nullptr};
    data.clear();
    int result = spawnProc(&data, params);

    return result;
}

int NmapRunner::full_tcp_scan(){
    const char* params[]{"nmap", "-Pn", "-n", "-v", "-sT", "-p-", ipAddress.c_str(), nullptr};
    data.clear();
    int result = spawnProc(&data, params);

    return result;
}

int NmapRunner::vuln_scan(){
    const char* params[]{"nmap", "-Pn", "-n", "--script=vuln", "-sT", "-A", ipAddress.c_str(), nullptr};
    data.clear();
    int result = spawnProc(&data, params);

    return result;
}


int NmapRunner::suggested_scans(){
    try{
        simple_scan();
        full_tcp_scan();
        vuln_scan();
        udp_scan();
        service_script_scan();
    } catch ( const std::exception& e){
        std::cout << "A standard exception was caught, with message: '" << e.what() << "'\n";
    }


    return 0;
}