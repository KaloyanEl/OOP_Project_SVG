#include "Figures.h"
#include<vector>
#include<string>
#include<iostream>


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

void Figures::erase(size_t ind) {

	if (ind == 0 || ind > figures.size()) {
		std::cout << "No such index\n";
		return;
	}
	ind--;
	delete figures[ind];
	figures.erase(figures.begin() + ind);
}

void Figures::translate(size_t ind, double x, double y) {
	if (ind == 0 || ind > figures.size()) {
		std::cout << "No such index\n";
		return;
	}
	ind--;
	figures[ind]->translate(x, y);
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