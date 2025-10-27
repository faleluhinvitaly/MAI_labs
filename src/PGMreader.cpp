/*
 * PGMreader.cpp
 *
 *  Created on: Oct 21, 2025
 *      Author: cyberdemon
 */

#include "PGMreader.h"
#include <fstream>
#include <string>

PGMreader::PGMreader(const std::string &filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("Cannot open file: " + filename);
	}
	std::string magic;
	file >> magic;
	if (magic != "P5") {
		throw std::runtime_error("Invalid PGM format. Expected P5, got: " +
								 magic);
	}

	file >> image.width;
	file >> image.height;
	file >> image.maxvalue;
	file.get();

	image.data.resize(image.height, std::vector<unsigned char>(image.width));

	for (int y = 0; y < image.height; y++) {
		for (int x = 0; x < image.width; x++) {
			unsigned char pixel;
			file.read(reinterpret_cast<char *>(&pixel), 1);
			image.data[y][x] = pixel;
		}
	}

	file.close();
}

PGMreader::PGMreader(pgmimage input) {
	image = input;
}

void PGMreader::save(const std::string &filename) {
	std::ofstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("Cannot create file: " + filename);
	}
	file << "P5\n";
	file << image.width << " " << image.height << "\n";
	file << image.maxvalue << "\n";

	for (int y = 0; y < image.height; y++) {
		for (int x = 0; x < image.width; x++) {
			file.write(reinterpret_cast<const char *>(&image.data[y][x]), 1);
		}
	}
	file.close();
}

PGMreader::~PGMreader() {
	// TODO Auto-generated destructor stub
}
