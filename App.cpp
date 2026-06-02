#include "App.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <istream>
#include <sstream>
#include <ostream>
#include "Figures.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Utils.h"



int App::open(const std::string& newFileName) {

    int result = deserialize(newFileName);

    if (result == 0) {
        fileName = newFileName;
        isFileOpen = true;
    }

    return result;
}
// Намира първото срещане на фигура на реда, като връща npos, ако такова няма
size_t App::firstPosFigure(const std::string& line) {

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

int App::deserialize(const std::string& newFileName) {

    std::ifstream file(newFileName);

    // 0 - успешно протичане
    // 1 - грешка при създаване и отваряне
    // 2 - файлът е невалиден 

    if (!file.is_open()) {
        // Това ще създаде празен файл
        //С някакъв default XML отгоре на файла
        std::ofstream out(newFileName);
        if (!out.is_open()) { //Файлът не може да бъде отворен или името е невалидно и не мода да бъде съзададен 
            return 1;
        }

        reset();

        unrecognizedInfoUp = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
            "<svg xmlns = \"http://www.w3.org/2000/svg\">\n";
        unrecognizedInfoDown = "</svg>\n";

        return 0;
    }

    /*
    Иначе, ако има файл го разделяме на части горе,фигури,долу.
    Това разделение е спрямо </svg>. Тоест неразпознатите фигури
    отиват в up.
    */

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::string line;
    std::string figuresContent = "";
    reset();

    size_t svgOpen = content.find("<svg");
    if (svgOpen == std::string::npos) {
        return 2;
    }

    size_t svgOpenEnd = content.find(">", svgOpen);
    if (svgOpenEnd == std::string::npos) {
        return 2;
    }

    unrecognizedInfoUp = content.substr(0, svgOpenEnd + 1);

    size_t svgClose = content.find("</svg>");
    if (svgClose == std::string::npos) {
        return 2;
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
                    return 2;
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

    // Проверка за проблеми във файла 
    // exeption ще дойде от stod, ако има грешна стойност
    normalize(figuresContent);
    try {
        std::stringstream figureInfo(figuresContent);
        figuresFile.deserialize(figureInfo);
    }
    catch (...) {
        return 2;
    }
    return 0;
}

void App::close() {
    reset();
}

void App::reset() {
    figuresFile.clear();
    unrecognizedInfoDown.clear();
    unrecognizedInfoUp.clear();
    isFileOpen = false;
    fileName.clear();
}

std::string App::getFileName() const {
    return fileName;
}

bool App::saveTo(const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        return false;
    }
    file << unrecognizedInfoUp;
    file << figuresFile.serializeSVG();
    file << unrecognizedInfoDown;
    return true;
}

bool App::hasOpenedFile() const {
    return isFileOpen;
}

// Препращащи функции
void App::print(std::ostream& os) const {
    figuresFile.print(os);
}

void App::create(const Figure& other) {
    figuresFile.create(other);
}

bool App::erase(size_t ind) {
    return figuresFile.erase(ind);
}

bool App::translate(size_t ind, double dx, double dy) {
    return figuresFile.translate(ind, dx, dy);
}

void App::translate(double dx, double dy) {
    return figuresFile.translate(dx, dy);
}

void App::isWithinCircle(double x, double y, double r) const {
    figuresFile.isWithinCircle(x, y, r);
}

void App::isWithinRectangle(double x, double y, double width, double height) const {
    figuresFile.isWithinRectangle(x, y, width, height);
}