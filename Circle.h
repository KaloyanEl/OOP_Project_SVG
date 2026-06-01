#pragma once
#include "Figure.h"
#include <string>
#include <ostream>
#include <istream>


class Circle : public Figure {
public:
	Circle(double cx, double cy, double radius, const std::string& fill);

	void translate(double x, double y) override;

	void print(std::ostream& os) const override;

	bool isWithinCircle(double x, double y, double r) const override;

	bool isWithinRectangle(double x, double y, double width, double height) const override;

	std::string serializeSVG() const override;

	Figure* clone() const override;

	std::string type() const override;

	static Circle deserialize(std::istream& is);
private:
	double cx, cy, radius;
	std::string fill;
};