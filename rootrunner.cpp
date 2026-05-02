#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <exception>
#include "nmaprunner.hpp"
#include "utilities.hpp"

class RootRunner{
    private:
        std::string targetIp;
        ScanResults scanResults;
        NmapRunner nmapInstance;

    public:
        RootRunner(std::string ipAddr)
            : targetIp {ipAddr},
            nmapInstance {targetIp}{
                run_initial_scan();
            }

        int addScanResult(const std::string& scanType, const std::string& scanName, const std::string& scanOutput){
            scanResults[scanType][scanName] = scanOutput;
            return 0;
        }

        const std::string& getScanResult(const std::string& scanType, const std::string& scanName){
            return scanResults[scanType][scanName];
        }

        int writeStatusLog(const std::string& logData, const char* fileName){
            try {
                if (fileExists(fileName)){
                    std::ofstream outFile(fileName);

                    if (!outFile.is_open()){
                        std::cerr << "Error: Could not open file for writing." << std::endl;
                    }

                    for (const auto& outerScanResult : scanResults){
                        const std::string& scanProvider = outerScanResult.first;
                        const auto& scanData = outerScanResult.second;

                        outFile << scanProvider << " Scans" << std::endl;
                        outFile << "----------------------\n" << std::endl;
                        for (const auto& scanResult : scanData){
                            const std::string& specificScan = scanResult.first;
                            const std::string& specificScanData = scanResult.second;
                            
                            outFile << specificScan << " Scan Results" << std::endl;
                            outFile << "[--------------]" << std::endl;
                            outFile << specificScanData << std::endl;
                        }
                    }
                    outFile.close();
                } 
            } catch ( const std::exception& e){
                std::cout << "A standard exception was caught, with message: '" << e.what() << "'\n";
            }
        }

        int run_initial_scan(){
            std::string data;

            nmapInstance.simple_scan(data);
            addScanResult("Nmap","nmap_simple_scan", data);
            data.clear();
            nmapInstance.full_tcp_scan(data);
            addScanResult("Nmap", "nmap_full_tcp_scan", data);
            data.clear();
            nmapInstance.vuln_scan(data);
            addScanResult("Nmap", "nmap_vuln_scan", data);
            data.clear();
            nmapInstance.udp_scan(data);
            addScanResult("Nmap", "nmap_udp_scan", data);
            data.clear();
            nmapInstance.service_script_scan(data);
            addScanResult("Nmap","nmap_service_script_scan", data);
            data.clear();



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

int main(){
    RootRunner r("127.0.0.1");
}