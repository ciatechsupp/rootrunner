#include <fcntl.h>
#include <unistd.h>

int run_initial_scan(){
//Command: nmap -Pn -sC -sV -oA [NAME_FOR_SCAN_FILES]
    int pipefd[2];
    pipe(pipefd);
}