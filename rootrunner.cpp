#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <exception>
#include "nmaprunner.hpp"

//Scan name: scan result
using ScanResult = std::map<std::string, std::string>;
using ScanResults = std::map<std::string, ScanResult>;

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

            try {
                
                std::ofstream outFile("output.txt");

                if (!outFile.is_open()){
                    std::cerr << "Error: Could not open file for writing." << std::endl;
                    return 1;
                }
                for (auto outerIt = scanResults.begin(); outerIt != scanResults.end(); ++outerIt){
                    outFile << outerIt->first << " Scans" << std::endl;
                    outFile << "-----------------------\n" << std::endl;
                    for (auto innerIt = outerIt->second.begin(); innerIt != outerIt->second.end(); ++innerIt){
                        outFile << innerIt->first << " Scan Results" << std::endl;
                        outFile << "[-------------]" << std::endl;
                        outFile << innerIt->second << std::endl;
                    }
             }
             outFile.close();
            } catch ( const std::exception& e){
                std::cout << "A standard exception was caught, with message: '" << e.what() << "'\n";
            }

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