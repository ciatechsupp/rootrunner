#include "nmaprunner.hpp"

ScanResult NmapRunner::run(const ScanJob& job){
    
    ScanResult newScanResult;
    newScanResult.job = job;

    std::vector<std::string> args = buildArgs(job);

    int exitCode = spawnProc(newScanResult.stdoutData, args);
    if (exitCode != 0) {
    logMessage("There was a failure spawning a process for nmap scan");
    }
    newScanResult.exitCode = exitCode;
    logMessage("Finished " + toString(job.type) + " on " + job.target + " with exit code:" + std::to_string(newScanResult.exitCode));
    return newScanResult;
};

std::vector<std::string> NmapRunner::buildArgs(
    const ScanJob& job){

    std::vector<std::string> args;
    args.push_back("nmap");

    switch(job.type){
        case NmapScanType::Simple:
            args.push_back("-Pn");
            args.push_back("-n");
            args.push_back("-v");
            args.push_back("-sT");
            args.push_back("-A");
            break;
        case NmapScanType::FullTCP:
            args.push_back("-Pn");
            args.push_back("-n");
            args.push_back("-v");
            args.push_back("-sT");
            args.push_back("-p-");
            args.push_back("-T5");
            break;
        case NmapScanType::UDP:
            args.push_back("-Pn");
            args.push_back("-n");
            args.push_back("-sUV");
            args.push_back("-p 53,67,68,69,123,137,138,161,162,500,514");
            args.push_back("-A");
            break;
        case NmapScanType::ServiceScript:
            args.push_back("-Pn");
            args.push_back("-n");
            args.push_back("-sC");
            args.push_back("-sV");
            break;
        case NmapScanType::Vuln:
            args.push_back("-Pn");
            args.push_back("-n");
            args.push_back("--script=vuln");
            args.push_back("-sT");
            args.push_back("-A");
            break;
    }

    args.push_back(job.target);

    return args;
}

std::string toString(NmapScanType type){
  switch(type)
  {
    case NmapScanType::Simple: return "Simple";
    case NmapScanType::FullTCP: return "FullTCP";
    case NmapScanType::UDP: return "UDP";
    case NmapScanType::ServiceScript: return "ServiceScript";
    case NmapScanType::Vuln: return "Vuln";
  }
  return "Unknown";
}