#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string_view>



int run_initial_scan(std::string_view ipAddress){
//Command: nmap -Pn -sC -sV -oA [NAME_FOR_SCAN_FILES]
// fork a new process, set nmap and cli args for new process, run process, catch output via pipe
    int pipefd[2];
    pid_t cpid;
    //pipe(pipefd);
    char buf;

    if (pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0){
        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);

        close(pipefd[1]);

        execvp("nmap", (char*[]){, "-Pn", "-sC", "-sV", nullptr});

        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[1]);

        char buffer[4096];
        ssize_t count;
        std::string output;

        while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0){
            output.append(buffer, count);
        }

        close(pipefd[0]);

        waitpid(cpid, nullptr, 0);

        int fd = open("nmap_initial_scan_output.txt", O_CREAT | O_TRUNC | O_WRONLY, 06400);
        write(fd, output.data(), output.size());
        close(fd);

    }


}