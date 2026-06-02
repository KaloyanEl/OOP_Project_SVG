#pragma once
#include <string>
#include <ostream>

/*
Абстарктен базов клас за фигурите от SVG.
Общ интерфайс, който има виртуален деструктор,
за да гарантира гладкото освобождаване на
паметта
*/

class Figure {
public:
	virtual void translate(double x, double y) = 0;

	virtual void print(std::ostream& os) const = 0;

	virtual bool isWithinCircle(double x, double y, double r) const = 0;

	virtual bool isWithinRectangle(double x, double y, double width, double height) const = 0;

	virtual std::string serializeSVG() const = 0;

	virtual Figure* clone() const = 0;

	virtual ~Figure() = default;

	virtual std::string type() const = 0;

};