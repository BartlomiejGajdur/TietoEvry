#include "../Include/Mediator.hpp"

 std::string file0_content;
 std::string file1_content;
 std::string file2_content;
 std::string file3_content;

namespace mediator {
    int checkGivenData(int argc, char* argv[]) {
        // Check the number of arguments
        if (argc != 4) {
            std::cout << "Please provide three arguments." << std::endl;
            return 1; // Return an error code indicating invalid argument count
        }

        // Extract the file content from command-line arguments
        file0_content = argv[0];
        file1_content = argv[1];
        file2_content = argv[2];
        file3_content = argv[3];

        // Read the content of file1
        std::ifstream file1_stream(file1_content);
        std::string file1_content((std::istreambuf_iterator<char>(file1_stream)),
                                  std::istreambuf_iterator<char>());

        // Check if the file content meets the requirements
        if (file1_content.length() < 2 ||
            std::find(file1_content.begin(), file1_content.end(), '1') == file1_content.end() ||
            std::find(file1_content.begin(), file1_content.end(), '2') == file1_content.end()) {
            std::cout << "The map does not meet the requirements." << std::endl;
            return 1; // Return an error code indicating invalid map
        }

        return 0; // Return success code indicating valid data
    }
}
