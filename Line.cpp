#include "Line.h"
#include "Figure.h"
#include "Utils.h"
#include <istream>
#include <ostream>

Line::Line(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}


void Line::translate(double dx, double dy) {
	x1 += dx;
	y1 += dy;
	x2 += dx;
	y2 += dy;
}

void Line::print(std::ostream& os) const {
	os << "line " << x1 << " " << y1 << " " << x2 << " " << y2;
}
// Проверява дали двете точки са в кръга. Ако е така то цялата фигура е там.
bool Line::isWithinCircle(double x, double y, double r) const {
	if ((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y) > r * r) {
		return false;
	}
	if ((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y) > r * r) {
		return false;
	}
	return true;
}

// Проверява дали двете точки са в правоъгълника. Ако е така то цялата фигура е там.
bool Line::isWithinRectangle(double x, double y, double width, double height) const {
	if (x1<x || x1>x + width) {
		return false;
	}
	if (y1<y || y1>y + height) {
		return false;
	}

	if (x2<x || x2>x + width) {
		return false;
	}
	if (y2<y || y2>y + height) {
		return false;
	}
	return true;
}
std::string Line::serializeSVG() const {
	return "<line x1=\"" +
		std::to_string(x1) +
		"\" y1=\"" +
		std::to_string(y1) +
		"\" x2=\"" +
		std::to_string(x2) +
		"\" y2=\"" +
		std::to_string(y2) +
		"\" />\n";
}
Figure* Line::clone() const {
	return new Line(*this);
}


std::string Line::type() const {
	return "line";
}


// От другите функции имаме гаранция, че ще има затварящ />
// Ако стойността е невалидна std::stod ще хвърли expetion, които 
// ше бъде хванат.
Line Line::deserialize(std::istream& is) {

	std::string token;

	double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	while (is >> token) {

		if (token.find("x1=") != std::string::npos) {
			x1 = std::stod(extractToken(token));
		}
		else if (token.find("y1=") != std::string::npos) {
			y1 = std::stod(extractToken(token));
		}
		else if (token.find("x2=") != std::string::npos) {
			x2 = std::stod(extractToken(token));
		}
		else if (token.find("y2=") != std::string::npos) {
			y2 = std::stod(extractToken(token));
		}
		if (token.find("/>") != std::string::npos) {
			break;
		}
	}

	return Line(x1, y1, x2, y2);
}