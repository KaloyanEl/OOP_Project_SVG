#pragma once
#include "Figure.h"
#include <string>
#include <ostream>
#include <istream>
/*
Клас, представящ геометричната фигура правоъгълник (Rectangle)
*/
class Rectangle : public Figure {
public:
	Rectangle(double x, double y, double width, double height, const std::string& fill);

	void translate(double dx, double dy) override;

	void print(std::ostream& os) const override;

	bool isWithinCircle(double x, double y, double r) const override;

	bool isWithinRectangle(double x, double y, double width, double height) const override;

	std::string serializeSVG() const override;

	Figure* clone() const override;

	std::string type() const override;

	static Rectangle deserialize(std::istream& is);
private:
	double x, y, width, height; // кординати на единия връх и далжините на страните
	std::string fill; // цвят
};