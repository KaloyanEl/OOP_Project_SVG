#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "SvgParser.h"
#include "Figures.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "SvgFun.h"

size_t firstPosFigure(const std::string& line) {

    size_t rectPos = line.find("<rect");
    size_t circPos = line.find("<circle");
    size_t linePos = line.find("<line");
    size_t firstPos = std::string::npos;
    if (rectPos != std::string::npos) {
        firstPos = (firstPos == std::string::npos) ? rectPos : std::min(firstPos, rectPos);
    }
    if (circPos != std::string::npos) {
        firstPos = (firstPos == std::string::npos) ? circPos : std::min(firstPos, circPos);
    }
    if (linePos != std::string::npos) {
        firstPos = (firstPos == std::string::npos) ? linePos : std::min(firstPos, linePos);
    }

    return firstPos;
}

bool deserialize(const std::string& fileName, std::string& unrecognizedInfoUp, std::string& unrecognizedInfoDown, Figures& figuresFile) {

    std::ifstream file(fileName);

    if (!file.is_open()) {
        // Това ще създаде празен файл
        //С някакъв default XML отгоре на файла
        unrecognizedInfoUp = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
            "<svg xmlns = \"http://www.w3.org/2000/svg\">\n";
        unrecognizedInfoDown = "</svg>\n";
        std::ofstream out(fileName);
        return true;
    }
    //Иначе, ако има файл го разделяма на части горе,фигури,долу
    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    std::string line;
    std::string figuresContent = "";
    unrecognizedInfoUp = "";
    unrecognizedInfoDown = "";
    figuresFile.clear();

    size_t svgOpen = content.find("<svg");
    if (svgOpen == std::string::npos) {
        return false;
    }

    size_t svgOpenEnd = content.find(">", svgOpen);
    if (svgOpenEnd == std::string::npos) {
        return false;
    }

    unrecognizedInfoUp = content.substr(0, svgOpenEnd + 1);

    size_t svgClose = content.find("</svg>");
    if (svgClose == std::string::npos) {
        return false;
    }

    unrecognizedInfoDown = content.substr(svgClose);

    std::string insideSvg = content.substr(svgOpenEnd + 1, svgClose - (svgOpenEnd + 1));


    std::stringstream ss(insideSvg);

    while (std::getline(ss, line)) {

        while (!line.empty()) {

            size_t firstPos = firstPosFigure(line);

            if (firstPos == std::string::npos) {
                unrecognizedInfoUp += line + "\n";
                line.clear();
                break;
            }

            if (firstPos != 0) {
                unrecognizedInfoUp += line.substr(0, firstPos);
                line = line.substr(firstPos);
            }

            size_t closePos = line.find("/>");
            while (closePos == std::string::npos) {
                figuresContent += line + "\n";
                if (!std::getline(ss, line)) {
                    return false;
                }

                closePos = line.find("/>");
            }

            figuresContent += line.substr(0, closePos + 2);
            line = line.substr(closePos + 2);

            if (line.empty()) {
                figuresContent += "\n";
            }
            else {
                figuresContent += " ";
            }
        }
    }

    try {
        std::stringstream figureInfo(figuresContent);
        figuresFile.deserialize(figureInfo);
    }
    catch (const std::exception& e) {
        return false;
    }
    return true;
}