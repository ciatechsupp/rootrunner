#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

int spawnProc(std::string& stdoutData, const std::vector<std::string> args);

#endif