#include <string>
#include <vector>
#include <unordered_map>
#include <pthread.h>
#include "nmaprunner.hpp"

//Scan name: scan result
using ScanResult = std::unordered_map<std::string, std::string>;
using ScanResults = std::unordered_map<std::string, ScanResult>;

class RootRunner{
    private:
        std::string targetIp;
        ScanResults scanResults;
        NmapRunner nmapInstance;

    public:
        RootRunner(std::string ipAddr)
            : targetIp {ipAddr},
            nmapInstance {targetIp} {
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