#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

inline std::mutex g_outputMutex;

inline void logMessage(const std::string& message) {
  std::lock_guard<std::mutex> lock(g_outputMutex);
  std::cout << message << std::endl;
}

inline void logError(const std::string& message) {
  std::lock_guard<std::mutex> lock(g_outputMutex);
  std::cerr << message << std::endl;
}

int spawnProc(std::string& stdoutData, const std::vector<std::string> args);

#endif