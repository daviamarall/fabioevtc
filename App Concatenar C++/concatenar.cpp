#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file1("/workspaces/fabioevtc/App Concatenar C++/file1.txt");
    std::ifstream file2("/workspaces/fabioevtc/App Concatenar C++/file2.txt");
    std::ofstream outputFile("/workspaces/fabioevtc/App Concatenar C++/OutputFile.txt");

    if (!file1.is_open() || !file2.is_open() || !outputFile.is_open()) {
        std::cerr << "Failed to open one or more files." << std::endl;
        return EXIT_FAILURE;
    }

    std::string line1, line2;
    while (std::getline(file1, line1) && std::getline(file2, line2)) {
        outputFile << line1 << " " << line2 << "\n";
    }

    file1.close();
    file2.close();
    outputFile.close();

    std::cout << "Files concatenated successfully!" << std::endl;
    return 0;
}
