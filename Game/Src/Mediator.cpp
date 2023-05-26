#include "../Include/Mediator.hpp"

std::string FileName;
std::string MapFile;
std::string StatusFile;
std::string ActionsFile;
size_t TimeLimit{5};

namespace mediator {
    int checkGivenData(int argc, char* argv[]) {
        // Check the number of arguments
        if (argc < 4 || argc > 5) {
            std::cout << "Please provide three arguments." << std::endl;
            return 1; // Return an error code indicating invalid argument count
        }

        FileName = argv[0];
        MapFile = argv[1];
        StatusFile = argv[2];
        ActionsFile = argv[3];

        if (argc == 5) {
            TimeLimit = std::stoull(argv[4]);
        }

        // Extract the file content from command-line arguments
        // Read the content of file1
        std::ifstream file1_stream(MapFile);
        std::string file1_content((std::istreambuf_iterator<char>(file1_stream)),
                                  std::istreambuf_iterator<char>());

        // Check if the file content meets the requirements
        if (file1_content.length() < 2 ||
            std::find(file1_content.begin(), file1_content.end(), '1') == file1_content.end() ||
            std::find(file1_content.begin(), file1_content.end(), '2') == file1_content.end()||
            std::find(file1_content.begin(), file1_content.end(), 'B') != file1_content.end()) {
            std::cout << "The map does not meet the requirements." << std::endl;
            return 1; // Return an error code indicating invalid map
        }

        return 0; // Return success code indicating valid data
    }
}
