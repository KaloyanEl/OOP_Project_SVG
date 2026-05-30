#pragma once
#include "Figure.h"

class Line : public Figure {
public:
	Line(double x1, double y1, double x2, double y2);


	void translate(double x, double y) override;

	void print(std::ostream& os) const override;

	bool isWithinCircle(double x, double y, double r) const override;

	bool isWithinRectangle(double x, double y, double width, double height) const override;

	std::string serializeSVG() const override;

	Figure* clone() const override;

	std::string type() const override;


private:
	double x1, y1, x2, y2;

};