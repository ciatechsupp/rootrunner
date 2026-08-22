#include "executor.hpp"
#include <cerrno>

extern char **environ;

static std::string resolveExecutable(const std::string& name) {
  if (name.find('/') != std::string::npos) {
    return access(name.c_str(), X_OK) == 0 ? name : std::string();
  }

  const char *pathEnv = getenv("PATH");
  std::string pathList = pathEnv ? pathEnv : "/usr/local/bin:/usr/bin:/bin";

  size_t start = 0;
  while (start <= pathList.size()) {
    size_t end = pathList.find(':', start);
    std::string dir = pathList.substr(
        start, end == std::string::npos ? std::string::npos : end - start);
    if (dir.empty()) {
      dir = ".";
    }

    std::string candidate = dir + "/" + name;
    if (access(candidate.c_str(), X_OK) == 0) {
      return candidate;
    }

    if (end == std::string::npos) {
      break;
    }
    start = end + 1;
  }

  return std::string();
}

int spawnProc(std::string& stdoutData, const std::vector<std::string> args) {
  if (args.empty()) {
    logError("spawnProc: no command provided");
    return -1;
  }

  int pipefd[2];
  if (pipe(pipefd) == -1) {
    perror("pipe");
    return -1;
  }

  std::string executable = resolveExecutable(args.front());
  if (executable.empty()) {
    logError("spawnProc: executable not found: " + args.front());
    close(pipefd[0]);
    close(pipefd[1]);
    return -1;
  }

  std::vector<char*> argv;
  argv.reserve(args.size() + 1);
  for (const auto& arg : args) {
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  argv.push_back(nullptr);

  pid_t cpid = fork();
  if (cpid == -1) {
    perror("fork");
    close(pipefd[0]);
    close(pipefd[1]);
    return -1;
  }

  if (cpid == 0) {
    close(pipefd[0]);

    if (dup2(pipefd[1], STDOUT_FILENO) == -1 ||
        dup2(pipefd[1], STDERR_FILENO) == -1) {
      _exit(127);
    }

    close(pipefd[1]);

    execve(executable.c_str(), argv.data(), environ);

    _exit(127);
  }

  close(pipefd[1]);

  char buffer[4096];
  ssize_t count;

  while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
    stdoutData.append(buffer, count);
  }

  close(pipefd[0]);

  while (waitpid(cpid, nullptr, 0) == -1 && errno == EINTR) {
  }

  return 0;
}
