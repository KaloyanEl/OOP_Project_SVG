#include "Figures.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include<vector>
#include<string>
#include<iostream>
#include<istream>


Figures::Figures() {}

Figures::Figures(const std::vector<Figure*>& figures) {
	for (size_t i = 0;i < figures.size();i++) {
		this->figures.push_back(figures[i]->clone());
	}
}

Figures::Figures(const Figures& other) {
	for (size_t i = 0;i < other.figures.size();i++) {
		figures.push_back(other.figures[i]->clone());
	}
}

Figures& Figures::operator=(const Figures& other) {
	if (&other == this) {
		return *this;
	}
	for (size_t i = 0;i < figures.size();i++) {
		delete figures[i];
	}
	figures.clear();
	for (size_t i = 0;i < other.figures.size();i++) {
		figures.push_back(other.figures[i]->clone());
	}
	return *this;
}

Figures::~Figures() {
	clear();
}

void Figures::print(std::ostream& os) const {
	for (size_t i = 0;i < figures.size();i++) {
		os << i + 1 << ". ";
		figures[i]->print(os);
		os << "\n";
	}
	os << "\n";
}

void Figures::create(const Figure& other) {
	figures.push_back(other.clone());
}
// Функцията е булева, за да връща информация за валидността на индекса
bool Figures::erase(size_t ind) {

	if (ind == 0 || ind > figures.size()) {
		//Няма такъв индекс
		return false;
	}
	ind--;
	delete figures[ind];
	figures.erase(figures.begin() + ind);
	return true;
}
// Функцията е булева, за да връща информация за валидността на индекса
bool Figures::translate(size_t ind, double dx, double dy) {
	if (ind == 0 || ind > figures.size()) {
		return false;
	}
	ind--;
	figures[ind]->translate(dx, dy);
	return true;
}

void Figures::translate(double x, double y) {
	for (size_t i = 0;i < figures.size();i++) {
		figures[i]->translate(x, y);
	}
}

void Figures::isWithinCircle(double x, double y, double r) const {

	bool any = false;
	for (size_t i = 0;i < figures.size();i++) {

		if (figures[i]->isWithinCircle(x, y, r)) {
			std::cout << i + 1 << ". ";
			figures[i]->print(std::cout);
			any = true;
			std::cout << "\n";
		}
	}
	if (!any) {
		std::cout << "No figures are located within circle " << x << " " << y << " " << r << "\n";
	}

}

void Figures::isWithinRectangle(double x, double y, double width, double height) const {
	bool any = false;
	for (size_t i = 0;i < figures.size();i++) {

		if (figures[i]->isWithinRectangle(x, y, width, height)) {
			std::cout << i + 1 << ". ";
			figures[i]->print(std::cout);
			any = true;
			std::cout << "\n";
		}
	}
	if (!any) {
		std::cout << "No figures are located within rectangle " << x << " " << y << " " << width << " " << height << "\n";
	}
}

std::string  Figures::serializeSVG() const {
	std::string result;
	for (size_t i = 0;i < figures.size();i++) {
		result += figures[i]->serializeSVG();
	}
	return result;
}

void Figures::clear() {
	for (size_t i = 0;i < figures.size();i++) {
		delete figures[i];
	}
	figures.clear();
}

// Чете от вече обработен поток, който садържа само фигури от проекта.
// Всяко от виканията на статичните методи ще завърши точно след като прочете затварящ />
void Figures::deserialize(std::istream& in) {
	clear();

	std::string token;
	while (in >> token) {

		if (token == "<rect") {
			create(Rectangle::deserialize(in));
		}
		else if (token == "<circle") {
			create(Circle::deserialize(in));
		}
		else if (token == "<line") {
			create(Line::deserialize(in));
		}
	}

}