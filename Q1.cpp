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
        if (arguments.size() > 0) {
            fs::current_path(arguments[0]);
            std::cout << "Changed directory to: " << fs::current_path() << std::endl;
        } else {
            std::cout << "Usage: cd <directory>" << std::endl;
        }
    }

private:
    std::vector<std::string> arguments;
};

// MvCommand class
class MvCommand : public Command {
public:
    MvCommand(const std::vector<std::string>& args) : arguments(args) {}

    void execute() override {
        if (arguments.size() == 2) {
            try {
                fs::rename(arguments[0], arguments[1]);
                std::cout << "Moved: " << arguments[0] << " to " << arguments[1] << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error moving file: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Usage: mv <source> <destination>" << std::endl;
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
        for (const auto& arg : arguments) {
            try {
                fs::remove_all(arg);
                std::cout << "Removed: " << arg << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error removing file/directory: " << e.what() << std::endl;
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
        for (const auto& arg : arguments) {
            try {
                if (fs::is_directory(arg)) {
                    for (const auto& entry : fs::directory_iterator(arg)) {
                        std::cout << "File: " << entry.path() << std::endl;
                    }
                } else {
                    std::cout << "Directory not found: " << arg << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Error listing directory: " << e.what() << std::endl;
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
        if (arguments.size() == 2) {
            try {
                fs::copy(arguments[0], arguments[1], fs::copy_options::recursive);
                std::cout << "Copied: " << arguments[0] << " to " << arguments[1] << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error copying file/directory: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Usage: cp <source> <destination>" << std::endl;
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
                std::string path;
                std::cout << "Enter directory to list: ";
                std::cin >> path;
                LsCommand lsCommand({path});
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