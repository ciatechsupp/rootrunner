#include <string>
#include <pthread.h>
#include "nmaprunner.hpp"

class RootRunner{
    private:
        std::string target_ip;

    public:
        RootRunner(std::string ipAddr)
            : target_ip {ipAddr}{
                run_initial_scan(ipAddr);
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