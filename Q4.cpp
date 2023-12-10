#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;


// Abstract base class for all commands
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() {}
};

// CdCommand class
class CdCommand : public Command {
public:
    CdCommand(const std::vector<std::string>& args) : arguments(args) {}

    void execute() override {
        // Implement cd command logic
        std::cout << "Executing cd command with options: ";
        for (const auto& arg : arguments) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<std::string> arguments;
};

// MvCommand class
class MvCommand : public Command {
public:
    MvCommand(const std::vector<std::string>& args) : arguments(args) {}

    void execute() override {
        // Implement mv command logic
        std::cout << "Executing mv command with options: ";
        for (const auto& arg : arguments) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;

        // Implement recursive functionality
        for (const auto& arg : arguments) {
            for (const auto& file : fs::recursive_directory_iterator(arg)) {
                std::cout << "Moving file: " << file.path() << std::endl;
                // Actual move logic goes here
            }
        }
    }

private:
    std::vector<std::string> arguments;
};

// RmCommand class
class RmCommand : public Command {
public:
    RmCommand(const std::vector<std::string>& args) : arguments(args) {}

    void execute() override {
        // Implement rm command logic
        std::cout << "Executing rm command with options: ";
        for (const auto& arg : arguments) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;

        // Implement recursive functionality
        for (const auto& arg : arguments) {
            for (const auto& file : fs::recursive_directory_iterator(arg)) {
                std::cout << "Removing file: " << file.path() << std::endl;
                // Actual remove logic goes here
            }
        }
    }

private:
    std::vector<std::string> arguments;
};

// LsCommand class
class LsCommand : public Command {
public:
    LsCommand(const std::vector<std::string>& args) : arguments(args) {}

    void execute() override {
        // Implement ls command logic
        std::cout << "Executing ls command with options: ";
        for (const auto& arg : arguments) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;

        // Implement wildcard functionality
        for (const auto& arg : arguments) {
            for (const auto& entry : fs::directory_iterator(arg)) {
                std::cout << "File: " << entry.path() << std::endl;
            }
        }
    }

private:
    std::vector<std::string> arguments;
};

// CpCommand class
class CpCommand : public Command {
public:
    CpCommand(const std::vector<std::string>& args) : arguments(args) {}

    void execute() override {
        // Implement cp command logic
        std::cout << "Executing cp command with options: ";
        for (const auto& arg : arguments) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;

        // Implement recursive functionality
        for (const auto& arg : arguments) {
            for (const auto& file : fs::recursive_directory_iterator(arg)) {
                std::cout << "Copying file: " << file.path() << std::endl;
                // Actual copy logic goes here
            }
        }
    }

private:
    std::vector<std::string> arguments;
};

// Shell class to handle user input
class Shell {
public:
    void run(Command* command) {
        command->execute();
    }
};

int main() {
    // Example usage with menu system
    Shell shell;

    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Cd\n";
        std::cout << "2. Mv\n";
        std::cout << "3. Rm\n";
        std::cout << "4. Ls\n";
        std::cout << "5. Cp\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string dir;
                std::cout << "Enter directory: ";
                std::cin >> dir;
                CdCommand cdCommand({dir});
                shell.run(&cdCommand);
                break;
            }
            case 2: {
                std::string source, destination;
                std::cout << "Enter source directory: ";
                std::cin >> source;
                std::cout << "Enter destination directory: ";
                std::cin >> destination;
                MvCommand mvCommand({source, destination});
                shell.run(&mvCommand);
                break;
            }
            case 3: {
                std::string target;
                std::cout << "Enter target directory: ";
                std::cin >> target;
                RmCommand rmCommand({target});
                shell.run(&rmCommand);
                break;
            }
            case 4: {
                std::string pattern;
                std::cout << "Enter wildcard pattern: ";
                std::cin >> pattern;
                LsCommand lsCommand({pattern});
                shell.run(&lsCommand);
                break;
            }
            case 5: {
                std::string source, destination;
                std::cout << "Enter source directory: ";
                std::cin >> source;
                std::cout << "Enter destination directory: ";
                std::cin >> destination;
                CpCommand cpCommand({source, destination});
                shell.run(&cpCommand);
                break;
            }
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
