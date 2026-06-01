#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "Figures.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "SvgFun.h"
#include "SvgParser.h"



bool saveToFile(const std::string& fileName, const std::string& unrecognizedInfoUp, const std::string& unrecognizedInfoDown, const Figures& figuresFile) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        return false;
    }
    file << unrecognizedInfoUp;
    file << figuresFile.serializeSVG();
    file << unrecognizedInfoDown;
    return true;
}

int main() {

    Figures figuresFile = Figures();
    std::string unrecognizedInfoDown;
    std::string unrecognizedInfoUp;

    std::string fileName;
    bool isFileOpen = false;
    while (true) {
        std::cout << ">";

        std::string commandLine;
        std::getline(std::cin, commandLine);

        std::stringstream ss(commandLine);

        std::string command;
        if (!(ss >> command)) {
            continue;
        }

        if (command == "open") {

            std::string newFileName;
            std::getline(ss, newFileName);

            while (!newFileName.empty() && newFileName[0] == ' ') {
                newFileName.erase(0, 1);
            }

            if (newFileName.empty()) {
                std::cout << "Error: No file name specified!\n";
                continue;
            }



            if (!deserialize(newFileName, unrecognizedInfoUp, unrecognizedInfoDown, figuresFile)) {

                std::cout << "Error: " << newFileName << " is invalid SVG or cannot be opened!" << "\n";
                return 1;
            }
            fileName = newFileName;
            isFileOpen = true;
            std::cout << "Successfully opened " << fileName << "\n";
        }
        else if (command == "exit") {
            std::cout << "Exiting the program...";
            return 0;
        }

        else if (command == "help") {
            std::cout << "The following commands are supported:\n"
                << "  open <file>      opens <file>\n"
                << "  close            closes currently opened file\n"
                << "  save             saves the currently open file\n"
                << "  saveas <file>    saves the currently open file in <file>\n"
                << "  print            prints the loaded figures\n"
                << "  create <fig>     creates a new figure\n"
                << "  erase <idx>      erases figure at index\n"
                << "  translate        translates figures\n"
                << "  within <fig>     checks if figures are within an area\n"
                << "  help             prints this information\n"
                << "  exit             exits the program\n";
            continue;
        }
        else if (!isFileOpen) {
            std::cout << "No file is currently open. Use open <file> \n";
            continue;
        }
        else if (command == "print") {
            figuresFile.print(std::cout);
        }
        else if (command == "create") {

            std::string typeFig;
            ss >> typeFig;
            if (typeFig == "rectangle") {
                double x, y, width, height;
                std::string fill;
                if (ss >> x >> y >> width >> height >> fill) {
                    figuresFile.create(Rectangle(x, y, width, height, fill));
                    std::cout << "Successfully created rectangle!\n";
                }
                else {
                    std::cout << "Invalid parameters for rectangle\n";
                }
            }
            else if (typeFig == "circle") {
                double x, y, radius;
                std::string fill;
                if (ss >> x >> y >> radius >> fill) {
                    figuresFile.create(Circle(x, y, radius, fill));
                    std::cout << "Successfully created circle!\n";
                }
                else {
                    std::cout << "Invalid parameters for circle\n";
                }
            }
            else if (typeFig == "line") {
                double x1, y1, x2, y2;
                if (ss >> x1 >> y1 >> x2 >> y2) {
                    figuresFile.create(Line(x1, y1, x2, y2));
                    std::cout << "Successfully created line!\n";

                }
                else {
                    std::cout << "Invalid parameters for line\n";
                }
            }
            else {
                std::cout << "Unknown figure type: " << typeFig << "\n";
            }
        }
        else if (command == "erase") {
            size_t ind;
            if (!(ss >> ind)) {
                std::cout << "Error: No index provided.\n";
            }
            else if (figuresFile.erase(ind)) {
                std::cout << "Successfully erased figure " << ind << "\n";
            }
            else {
                std::cout << "Error: Invalid index provided.\n";
            }
        }
        else if (command == "within") {
            std::string specifier;
            ss >> specifier;
            if (specifier == "rectangle") {
                double x, y, width, height;
                if (ss >> x >> y >> width >> height) {
                    figuresFile.isWithinRectangle(x, y, width, height);
                }
                else {
                    std::cout << "Invalid parameters.\n";
                }
            }
            else if (specifier == "circle") {
                double x, y, radius;
                if (ss >> x >> y >> radius) {
                    figuresFile.isWithinCircle(x, y, radius);
                }
                else {
                    std::cout << "Invalid parameters.\n";
                }
            }
            else {
                std::cout << "No such option for figure for method within\n";
            }

        }
        else if (command == "translate") {
            std::string token;
            int ind = 0;
            double horizontal = 0, vertical = 0;

            try {
                while (ss >> token)
                {
                    if (token[0] == '-' || std::isdigit(token[0]))
                    {
                        ind = std::stoi(token);
                    }
                    else if (token.find("horizontal=") != std::string::npos)
                    {
                        horizontal = std::stod(token.substr(11));
                    }
                    else if (token.find("vertical=") != std::string::npos)
                    {
                        vertical = std::stod(token.substr(9));
                    }
                }
            }
            catch (const std::exception& e) {
                std::cout << "Invalid parameters for translate\n";
                continue;
            }

            if (ind == 0) {
                figuresFile.translate(horizontal, vertical);
                std::cout << "Translated all figures\n";
            }
            else {
                figuresFile.translate(ind, horizontal, vertical);
                std::cout << "Translated figure " << ind << "\n";
            }
        }
        else if (command == "save") {
            if (saveToFile(fileName, unrecognizedInfoUp, unrecognizedInfoDown, figuresFile)) {
                std::cout << "Successfully saved " << fileName << "\n";
            }

        }
        else if (command == "saveas") {
            std::string newFile, fileDirect = "";
            if (!(ss >> newFile)) {
                std::cout << "No file name specified for saveas\n";
                continue;
            }
            if (newFile[0] != '\"') {
                if (!saveToFile(newFile, unrecognizedInfoUp, unrecognizedInfoDown, figuresFile)) {
                    std::cout << "Error: Could not open file " << newFile << " for writing.\n";
                }
                else {
                    std::cout << "Successfully saved " << newFile << "\n";
                }
            }
            else {
                fileDirect = "";
                getline(ss, fileDirect);
                newFile = newFile + fileDirect;
                newFile = extractToken(newFile);
                if (!saveToFile(newFile, unrecognizedInfoUp, unrecognizedInfoDown, figuresFile)) {
                    std::cout << "Error: Could not open file " << newFile << " for writing.\n";
                }
                else {
                    std::cout << "Successfully saved " << newFile << "\n";
                }
            }
        }
        else if (command == "close") {
            fileName.clear();
            figuresFile.clear();
            isFileOpen = false;
            unrecognizedInfoUp.clear();
            unrecognizedInfoDown.clear();
            std::cout << "Successfully closed file.\n";
        }
        else {
            std::cout << "Unknown command! Type 'help' to see available commands.\n";
        }
    }

    return 0;
}

