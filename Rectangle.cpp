#include "Rectangle.h"
#include <sstream>

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

bool Rectangle::isWithinCircle(double cx, double cy, double r) const {
	if ((cx - x) * (cx - x) + (cy - y) * (cy - y) > r * r) {
		return 0;
	}
	if ((cx - (x + width)) * (cx - (x + width)) + (cy - y) * (cy - y) > r * r) {
		return 0;
	}
	if ((cx - x) * (cx - x) + (cy - (y + height)) * (cy - (y + height)) > r * r) {
		return 0;
	}
	if ((cx - (x + width)) * (cx - (x + width)) + (cy - (y + height)) * (cy - (y + height)) > r * r) {
		return 0;
	}
	return 1;
}

bool Rectangle::isWithinRectangle(double x, double y, double width, double height) const {
	if (this->x < x || this->y < y) {
		return 0;
	}
	if (this->x + this->width > x + width || this->y + this->height > y + height) {
		return 0;
	}
	return 1;
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