#pragma once
#include<ostream>
#include<istream>
#include<vector>
#include<string>

#include "Figure.h"
// Полиморфен списък подържащ актуалните фигури

class Figures {
public:
	Figures();

	Figures(const std::vector<Figure*>& figures);

	Figures(const Figures& other);

	Figures& operator=(const Figures& other);

	~Figures();

	void print(std::ostream& os) const;

	void create(const Figure& other);

	bool erase(size_t ind);

	bool translate(size_t ind, double dx, double dy);

	void translate(double dx, double dy);

	void isWithinCircle(double x, double y, double r) const;

	void isWithinRectangle(double x, double y, double width, double height) const;

	void deserialize(std::istream& in);

	std::string serializeSVG() const;

	void clear();

private:
	std::vector<Figure*> figures;

};