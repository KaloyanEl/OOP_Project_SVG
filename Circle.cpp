#include <string>
#include <ostream>
#include "Circle.h"
#include "SvgFun.h"

Circle::Circle(double cx, double cy, double radius, const std::string& fill) :
	cx(cx), cy(cy), radius(radius), fill(fill) {
}

void Circle::translate(double x, double y) {
	cx += x;
	cy += y;
}

void Circle::print(std::ostream& os) const {
	os << "circle " << cx << " " << cy << " " << radius << " " << fill;
}

bool Circle::isWithinCircle(double x, double y, double r) const {
	if (r < radius) {
		return false;
	}

	double distanceSq = (cx - x) * (cx - x) + (cy - y) * (cy - y);
	double maxDistanceSq = (r - radius) * (r - radius);

	if (distanceSq > maxDistanceSq) {
		return false;
	}
	return true;
}

bool Circle::isWithinRectangle(double x, double y, double width, double height) const {
	if (cx - radius < x) {
		return false;
	}
	if (cx + radius > x + width) {
		return false;
	}
	if (cy - radius < y) {
		return false;
	}
	if (cy + radius > y + height) {
		return false;
	}
	return true;
}

std::string Circle::serializeSVG() const {
	return "<circle cx=\"" +
		std::to_string(cx) +
		"\" cy=\"" +
		std::to_string(cy) +
		"\" r=\"" +
		std::to_string(radius) +
		"\" fill=\"" +
		fill +
		"\" />\n";
}

Figure* Circle::clone() const {
	return new Circle(*this);
}

std::string Circle::type() const {
	return "circle";
}

Circle Circle::deserialize(std::istream& is) {
	std::string token;

	double cx = 0, cy = 0, radius = 0;
	std::string fill = "none";

	while (is >> token) {

		if (token.find("cx=") != std::string::npos) {
			cx = std::stod(extractToken(token));
		}
		else if (token.find("cy=") != std::string::npos) {
			cy = std::stod(extractToken(token));
		}
		else if (token.find("r=") != std::string::npos) {
			radius = std::stod(extractToken(token));
		}
		else if (token.find("fill=") != std::string::npos) {
			fill = extractToken(token);
		}
		if (token.find("/>") != std::string::npos) {
			break;
		}
	}

	return Circle(cx, cy, radius, fill);
}