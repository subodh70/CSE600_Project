#include <iostream>
#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;

void listDirectoryContents(const fs::path& directoryPath) {
    std::cout << "Contents of directory: " << directoryPath << std::endl;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        std::cout << entry.path().filename() << std::endl;
    }
}

int main() {
    try {
        // Display the current working directory
        std::cout << "Current working directory: " << fs::current_path() << std::endl;

        // Ask the user to enter a new directory path
        std::cout << "Enter the new directory path: ";
        std::string userInput;
        std::getline(std::cin, userInput);

        // Check if the directory exists
        fs::path newDirectoryPath(userInput);
        if (fs::exists(newDirectoryPath) && fs::is_directory(newDirectoryPath)) {
            // Change the current working directory
            fs::current_path(newDirectoryPath);

            // Display the updated current working directory
            std::cout << "Updated working directory: " << fs::current_path() << std::endl;

            // List the contents of the updated directory
            listDirectoryContents(fs::current_path());
        } else {
            std::cerr << "Error: The specified directory does not exist." << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Error code: " << e.code() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
