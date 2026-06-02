#pragma once
#include <string>
#include <ostream>
#include <istream>
#include "Figures.h"


struct App {
public:
	std::string getFileName() const;

	int deserialize(const std::string& newFileName);

	int open(const std::string& fileName);

	bool saveTo(const std::string& fileName);

	void close();

	bool hasOpenedFile() const;

	size_t firstPosFigure(const std::string& line);


	// Препращащи функции
	void print(std::ostream& os) const;

	void create(const Figure& other);

	bool erase(size_t ind);

	bool translate(size_t ind, double dx, double dy);

	void translate(double dx, double dy);

	void isWithinCircle(double x, double y, double r) const;

	void isWithinRectangle(double x, double y, double width, double height) const;

private:
	Figures figuresFile;
	std::string unrecognizedInfoUp;
	std::string unrecognizedInfoDown;
	std::string fileName;
	bool isFileOpen = false;

	void reset();
};
