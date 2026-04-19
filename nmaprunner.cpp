#include <iostream>
#include "executor.hpp"
#include "nmaprunner.hpp"

NmapRunner::NmapRunner(const std::string& ipAddress) : ipAddress{ipAddress} {};

int NmapRunner::service_script_scan(std::string& data){
    const char* params[]{"nmap", "-Pn", "-n", "-sC", "-sV", ipAddress.c_str(), nullptr};
    int result = spawnProc(&data, params);
    if(result != 0){
        std::cout << "There was a failure spawning a process for service script scan" << std::endl;
    }
    return result;
}

int NmapRunner::udp_scan(std::string& data){
    const char* params[]{"nmap", "-Pn", "-n", "-sUV", "-A", ipAddress.c_str(), nullptr};
    int result = spawnProc(&data, params);
    if(result != 0){
        std::cout << "There was a failure spawning a process for UDP scan" << std::endl;
    }
    return 0;
}

int NmapRunner::simple_scan(std::string& data){
    const char* params[]{"nmap", "-Pn", "-n", "-v", "-sT", "-A", ipAddress.c_str(), nullptr};
    int result = spawnProc(&data, params);
    if(result != 0){
        std::cout << "There was a failure spawning a process for simple scan" << std::endl;
    }
    return result;
}

int NmapRunner::full_tcp_scan(std::string& data){
    const char* params[]{"nmap", "-Pn", "-n", "-v", "-sT", "-p-", ipAddress.c_str(), nullptr};
    int result = spawnProc(&data, params);
    if(result != 0){
        std::cout << "There was a failure spawning a process for full tcp scan" << std::endl;
    }
    return result;
}

int NmapRunner::vuln_scan(std::string& data){
    const char* params[]{"nmap", "-Pn", "-n", "--script=vuln", "-sT", "-A", ipAddress.c_str(), nullptr};
    int result = spawnProc(&data, params);
    if(result != 0){
        std::cout << "There was a failure spawning a process for vuln scan" << std::endl;
    }
    return result;
}

// int NmapRunner::suggested_scans(){
//     try{

//     } catch ( const std::exception& e){
//         std::cout << "A standard exception was caught, with message: '" << e.what() << "'\n";
//     }


//     return 0;
// }