#include "Line.h"
#include "Figure.h"
#include "SvgFun.h"
#include <istream>
#include <ostream>

Line::Line(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}


void Line::translate(double x, double y) {
	x1 += x;
	y1 += y;
	x2 += x;
	y2 += y;
}

void Line::print(std::ostream& os) const {
	os << "line " << x1 << " " << y1 << " " << x2 << " " << y2;
}

bool Line::isWithinCircle(double x, double y, double r) const {
	if ((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y) > r * r) {
		return 0;
	}
	if ((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y) > r * r) {
		return 0;
	}
	return 1;
}

bool Line::isWithinRectangle(double x, double y, double width, double height) const {
	if (x1<x || x1>x + width) {
		return 0;
	}
	if (y1<y || y1>y + height) {
		return 0;
	}

	if (x2<x || x2>x + width) {
		return 0;
	}
	if (y2<y || y2>y + height) {
		return 0;
	}
	return 1;
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