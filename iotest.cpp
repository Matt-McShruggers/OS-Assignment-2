#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

int main(){
    std::ifstream inputFile;
    inputFile.open("malloc-input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
        return 1;
    }

    std::ofstream outputFile;
    outputFile.open("malloc-output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "No se pudo abrir el archivo de entrada." << std::endl;
        return 1;
    }

    std::vector<std::string> inputFileContent;
    std::string line;
    int currentLine = 0;
    while (std::getline(inputFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        inputFileContent.push_back(line);
    }

	for (int i = 0; i < inputFileContent.size(); i++){
		std::cout << inputFileContent[i] << std::endl;
	}

    inputFile.close();
    outputFile.close();
	return 0;
}