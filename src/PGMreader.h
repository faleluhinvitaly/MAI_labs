/*
 * PGMreader.h
 *
 *  Created on: Oct 21, 2025
 *      Author: cyberdemon
 */

#ifndef PGMREADER_H_
#define PGMREADER_H_

#include "vector"
#include <string>

struct pgmimage {
	int width;
	int height;
	int maxvalue;
	std::vector<std::vector<unsigned char>> data;
	pgmimage() :
		width(0), height(0), maxvalue(255) {}

	pgmimage(const pgmimage &other) :
		width(other.width),
		height(other.height),
		maxvalue(other.maxvalue),
		data(other.data) {}

	pgmimage &operator=(const pgmimage &other) {
		if (this != &other) {
			width = other.width;
			height = other.height;
			maxvalue = other.maxvalue;
			data = other.data;
		}
		return *this;
	}
};

class PGMreader {

public:
	pgmimage image;
	PGMreader(const std::string &filename);
	PGMreader(pgmimage input);
	void save(const std::string &filename);
	virtual ~PGMreader();
};

#endif /* PGMREADER_H_ */
