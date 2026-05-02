#include <filesystem>
#include <vector>
#include <map>
//#include <sys/stat.h>

//Scan name: scan result



bool fileExists(const std::string& path){
    return std::filesystem::exists(path);
}

// bool fileExists(const char* path){
//     struct stat *buffer;
//     return stat(path, buffer) == 0;
// }

// Testing out iterators
            // try {
            //     std::ofstream outFile(fileName);

            //     if (!outFile.is_open()){
            //         std::cerr << "Error: Could not open file for writing." << std::endl;
            //         return 1;
            //     }
            //     for (auto outerIt = scanResults.begin(); outerIt != scanResults.end(); ++outerIt){
            //         outFile << outerIt->first << " Scans" << std::endl;
            //         outFile << "-----------------------\n" << std::endl;
            //         for (auto innerIt = outerIt->second.begin(); innerIt != outerIt->second.end(); ++innerIt){
            //             outFile << innerIt->first << " Scan Results" << std::endl;
            //             outFile << "[-------------]" << std::endl;
            //             outFile << innerIt->second << std::endl;
            //         }
            //  }
            //  outFile.close();
            // } catch ( const std::exception& e){
            //     std::cout << "A standard exception was caught, with message: '" << e.what() << "'\n";
            // }