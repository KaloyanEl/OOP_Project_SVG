#pragma once
#include<ostream>
#include<vector>
#include<string>

#include "Figure.h"
class Figures {
public:
	Figures();

	Figures(const std::vector<Figure*>& figures);

	Figures(const Figures& other);

	Figures& operator=(const Figures& other);

	~Figures();

	void print(std::ostream& os) const;

	void create(const Figure& other);

	void erase(size_t ind);

	void translate(size_t ind, double x, double y);

	void translate(double x, double y);

	void isWithinCircle(double x, double y, double r) const;

	void isWithinRectangle(double x, double y, double width, double height) const;

	std::string serializeSVG() const;

	void clear();

private:
	std::vector<Figure*> figures;

};