#include <string>
#include <pthread.h>

class RootRunner{
    private:
        std::string target_ip;

    public:
        RootRunner(std::string ipAddr)
            : target_ip {ipAddr}{}

        int nmapRunner(){
        }
        int rpcRunner(){}
        int snmpRunner(){}
        int smbRunner(){}
        int webRunner(){}
        int kerberosRunner(){}
        int ldapRunner(){}
        int rdpRunner(){}
        int winrmRunner(){}

};