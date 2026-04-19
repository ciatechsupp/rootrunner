#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string>
#include <vector>

template<std::size_t N>
int spawnProc(std::string *output, const char* (&args)[N]){
//Command: nmap -Pn -sC -sV -oA [NAME_FOR_SCAN_FILES]
// fork a new process, set nmap and cli args for new process, run process, catch output via pipe
    int pipefd[2];
    pid_t cpid;
    //pipe(pipefd);

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

        //C version, assuming upAddress is a std::string
        // const char* args[] = {
        //     "nmap",
        //     "-Pn",
        //     "-sC",
        //     "-sV",
        //     ipAddress.c_str(), // user input string
        //     nullptr
        // };

        //std::vector<std::string> argStrings{args...};
        std::vector<char*> argv;

        for (std::size_t i = 0; i < N; ++i){
            argv.push_back(const_cast<char*>(args[i]));
        }
        argv.push_back(nullptr);

        // execvp("nmap", const_cast<char* const*>(args));

        execvp(args[0], argv.data());

        //C++ version
        // std::vector<std::string> argStrings{"nmap", "-Pn", "-sC", "-sV", ipAddress};
        // std::vector<char*> argss;
        // for (auto &s: argStrings) argss.push_back(s.data());
        // argss.push_back(nullptr);

        // execvp("nmap", argss.data());

        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[1]);

        char buffer[4096];
        ssize_t count;
        //std::string output;

        while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0){
            output->append(buffer, count);
        }

        close(pipefd[0]);

        waitpid(cpid, nullptr, 0);

        // int fd = open("nmap_initial_scan_output.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);
        // if (fd == -1){
        //     perror("Couldn't open output file for nmap log");
        //     exit(EXIT_FAILURE);
        // }
    
        // if (write(fd, output.data(), output.size()) == -1){
        //     perror("Couldn't write nmap log data to output file");
        //     exit(EXIT_FAILURE);
        // };

        // close(fd);

        return 0;

    }


}
#endif