#include "Rectangle.h"
#include "Utils.h"
#include <ostream>
#include <istream>

Rectangle::Rectangle(double x, double y, double width, double height, const std::string& fill) :
	x(x), y(y), width(width), height(height), fill(fill) {
}

void Rectangle::translate(double dx, double dy) {
	x += dx;
	y += dy;
}

void Rectangle::print(std::ostream& os) const {
	os << "rectangle " << x << " " << y << " " << width << " " << height << " " << fill;
}

//Проверява дали четирите точки са вътре в кръга. Ако е така то цялата фигура е там.
bool Rectangle::isWithinCircle(double cx, double cy, double r) const {
	if ((cx - x) * (cx - x) + (cy - y) * (cy - y) > r * r) {
		return false;
	}
	if ((cx - (x + width)) * (cx - (x + width)) + (cy - y) * (cy - y) > r * r) {
		return false;
	}
	if ((cx - x) * (cx - x) + (cy - (y + height)) * (cy - (y + height)) > r * r) {
		return false;
	}
	if ((cx - (x + width)) * (cx - (x + width)) + (cy - (y + height)) * (cy - (y + height)) > r * r) {
		return false;
	}
	return true;
}

//Проверява дали четирите точки са вътре в правоъгълника. Ако е така то цялата фигура е там.
bool Rectangle::isWithinRectangle(double x, double y, double width, double height) const {
	if (this->x < x || this->y < y) {
		return false;
	}
	if (this->x + this->width > x + width || this->y + this->height > y + height) {
		return false;
	}
	return true;
}

std::string Rectangle::serializeSVG() const {
	return "<rect x=\"" +
		std::to_string(x) +
		"\" y=\"" +
		std::to_string(y) +
		"\" width=\"" +
		std::to_string(width) +
		"\" height=\"" +
		std::to_string(height) +
		"\" fill=\"" +
		fill +
		"\" />\n";
}

Figure* Rectangle::clone() const {
	return new Rectangle(*this);
}

std::string Rectangle::type() const {
	return "rectangle";
}
// От другите функции имаме гаранция, че ще има затварящ />
// Ако стойността е невалидна std::stod ще хвърли expetion, които 
// ше бъде хванат.
Rectangle Rectangle::deserialize(std::istream& is) {
	std::string token;

	double x = 0, y = 0, width = 0, height = 0;
	std::string fill = "none";

	while (is >> token) {

		if (token.find("x=") != std::string::npos) {
			x = std::stod(extractToken(token));
		}
		else if (token.find("y=") != std::string::npos) {
			y = std::stod(extractToken(token));
		}
		else if (token.find("width=") != std::string::npos) {
			width = std::stod(extractToken(token));
		}
		else if (token.find("height=") != std::string::npos) {
			height = std::stod(extractToken(token));
		}
		else if (token.find("fill=") != std::string::npos) {
			fill = extractToken(token);
		}
		if (token.find("/>") != std::string::npos) {
			break;
		}
	}
	return Rectangle(x, y, width, height, fill);
}