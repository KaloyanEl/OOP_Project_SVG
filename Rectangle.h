#pragma once
#include "Figure.h"
#include<string>
#include<ostream>


class Rectangle : public Figure {
public:

	Rectangle(double x, double y, double width, double height, const std::string& fill);


	void translate(double x, double y) override;

	void print(std::ostream& os) const override;

	bool isWithinCircle(double x, double y, double r) const override;

	bool isWithinRectangle(double x, double y, double width, double height) const override;

	std::string serializeSVG() const override;

	Figure* clone() const override;

	std::string type() const override;


private:
	double x, y, width, height;
	std::string fill;


};