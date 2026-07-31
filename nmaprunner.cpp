#include "nmaprunner.hpp"
#include <iostream>

ScanResult NmapRunner::run(const ScanJob& job){
    
    ScanResult newScanResult;
    newScanResult.job = job;

    std::vector<std::string> args = buildArgs(job);

    int exitCode = spawnProc(newScanResult.stdoutData, args);
    if (exitCode != 0) {
    std::cout << "There was a failure spawning a process for nmap scan"<< std::endl;
    }
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
            break;
        case NmapScanType::UDP:
            args.push_back("-Pn");
            args.push_back("-n");
            args.push_back("-sUV");
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