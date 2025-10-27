/*
 * Filter.cpp
 *
 *  Created on: Oct 21, 2025
 *      Author: cyberdemon
 */

#include "Filter.h"
#include "PGMreader.h"
#include <algorithm>
#include <random>
#include <stdexcept>
#include <vector>

pgmimage Filter::movavr(pgmimage image, const int window) {
	const int offset = window / 2;

	if (window > image.height || window > image.width) {
		throw std::invalid_argument("window size too big");
	}

	std::vector<std::vector<int>> horizontalSums(
		image.height, std::vector<int>(image.width, 0));

	for (int y = 0; y < image.height; y++) {
		int sum = 0;

		for (int x = 0; x < window; x++) {
			sum += image.data[y][x];
		}
		horizontalSums[y][offset] = sum;
		for (int x = window; x < image.width; x++) {
			sum = sum - image.data[y][x - window] + image.data[y][x];
			horizontalSums[y][x - offset] = sum;
		}
	}

	const int windowArea = window * window;

	for (int x = offset; x < image.width - offset; x++) {
		int sum = 0;
		for (int y = 0; y < window; y++) {
			sum += horizontalSums[y][x];
		}
		image.data[offset][x] = sum / windowArea;

		for (int y = window; y < image.height; y++) {
			sum = sum - horizontalSums[y - window][x] + horizontalSums[y][x];
			image.data[y - offset][x] = sum / windowArea;
		}
	}

	return image;
}
pgmimage Filter::runavr(pgmimage image, double alpha) {

	std::vector<std::vector<double>> temp(image.height,
										  std::vector<double>(image.width));

	for (int y = 0; y < image.height; y++) {
		temp[y][0] = image.data[y][0];
		for (int x = 1; x < image.width; x++) {
			temp[y][x] =
				alpha * image.data[y][x] + (1 - alpha) * temp[y][x - 1];
		}
	}

	for (int y = 0; y < image.height; y++) {
		for (int x = 0; x < image.width; x++) {
			image.data[y][x] = static_cast<unsigned char>(std::max(
				0, std::min(image.maxvalue, static_cast<int>(temp[y][x]))));
		}
	}

	return image;
}

pgmimage Filter::medium(const pgmimage &image, int window) {
	window = (window % 2 == 0) ? window - 1 : window;
	window = std::max(3, window);
	pgmimage result = image;
	const int offset = window / 2;
	std::vector<int> arr(window * window);
	auto middle = arr.begin() + arr.size() / 2;
	for (int centerX = offset; centerX < image.width - offset; centerX++) {
		for (int centerY = offset; centerY < image.height - offset; centerY++) {

			for (int y = centerY - offset, i = 0; y <= centerY + offset; y++) {
				for (int x = centerX - offset; x <= centerX + offset;
					 x++, i++) {
					arr[i] = image.data[y][x];
				}
			}

			std::nth_element(arr.begin(), middle, arr.end());
			result.data[centerY][centerX] = *middle;
		}
	}
	return result;
}

pgmimage Filter::SaltPepperNoise(const pgmimage &image,
								 double noiseProbability) {
	pgmimage result = image;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> probDist(0.0, 1.0);

	for (int y = 0; y < image.height; y++) {
		for (int x = 0; x < image.width; x++) {
			double r = probDist(gen);

			if (r < noiseProbability / 2.0) {
				result.data[y][x] = 0;
			} else if (r < noiseProbability) {
				result.data[y][x] = image.maxvalue;
			}
		}
	}
	return result;
}
pgmimage Filter::BlockNoise(const pgmimage &image, int blockSize,
							double intensity) {
	pgmimage result = image;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> variationDist(1.0 - intensity,
												   1.0 + intensity);

	for (int blockY = 0; blockY < image.height; blockY += blockSize) {
		for (int blockX = 0; blockX < image.width; blockX += blockSize) {
			double blockFactor = variationDist(gen);

			for (int y = blockY; y < std::min(blockY + blockSize, image.height);
				 y++) {
				for (int x = blockX;
					 x < std::min(blockX + blockSize, image.width); x++) {
					int newValue =
						static_cast<int>(image.data[y][x] * blockFactor);
					result.data[y][x] = static_cast<unsigned char>(
						std::max(0, std::min(image.maxvalue, newValue)));
				}
			}
		}
	}
	return result;
}

// 7. Полосовой шум
pgmimage Filter::StripingNoise(const pgmimage &image, int stripeWidth,
							   double intensity, bool vertical = false) {
	pgmimage result = image;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> stripeDist(-intensity, intensity);

	if (vertical) {
		for (int x = 0; x < image.width; x += stripeWidth) {
			double stripeVariation = stripeDist(gen) * image.maxvalue;

			for (int stripeX = x;
				 stripeX < std::min(x + stripeWidth, image.width); stripeX++) {
				for (int y = 0; y < image.height; y++) {
					int newValue = image.data[y][stripeX] +
								   static_cast<int>(stripeVariation);
					result.data[y][stripeX] = static_cast<unsigned char>(
						std::max(0, std::min(image.maxvalue, newValue)));
				}
			}
		}
	} else {
		for (int y = 0; y < image.height; y += stripeWidth) {
			double stripeVariation = stripeDist(gen) * image.maxvalue;

			for (int stripeY = y;
				 stripeY < std::min(y + stripeWidth, image.height); stripeY++) {
				for (int x = 0; x < image.width; x++) {
					int newValue = image.data[stripeY][x] +
								   static_cast<int>(stripeVariation);
					result.data[stripeY][x] = static_cast<unsigned char>(
						std::max(0, std::min(image.maxvalue, newValue)));
				}
			}
		}
	}
	return result;
}
pgmimage Filter::SpeckleNoise(const pgmimage &image, double variance) {
	pgmimage result = image;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::normal_distribution<> normalDist(1.0, variance);

	for (int y = 0; y < image.height; y++) {
		for (int x = 0; x < image.width; x++) {
			double speckleFactor = normalDist(gen);
			int newValue = static_cast<int>(image.data[y][x] * speckleFactor);
			result.data[y][x] = static_cast<unsigned char>(
				std::max(0, std::min(image.maxvalue, newValue)));
		}
	}
	return result;
}

pgmimage Filter::BrightnessDependentNoise(const pgmimage &image,
										  double baseSigma, double darkBoost) {
	pgmimage result = image;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::normal_distribution<> normalDist(0.0, 1.0);

	for (int y = 0; y < image.height; y++) {
		for (int x = 0; x < image.width; x++) {
			double brightness =
				static_cast<double>(image.data[y][x]) / image.maxvalue;
			double effectiveSigma =
				baseSigma * (1.0 + darkBoost * (1.0 - brightness));

			double noise = normalDist(gen) * effectiveSigma;
			int newValue = image.data[y][x] + static_cast<int>(noise);
			result.data[y][x] = static_cast<unsigned char>(
				std::max(0, std::min(image.maxvalue, newValue)));
		}
	}
	return result;
}

double Filter::compareImages(const pgmimage &original,
							 const pgmimage &filtered) {
	if (original.width != filtered.width ||
		original.height != filtered.height) {
		throw std::invalid_argument(
			"Image dimensions must match for comparison");
	}

	int correctPixels = 0;
	int totalPixels = original.width * original.height;

	const int tolerance = 5;

	for (int y = 0; y < original.height; y++) {
		for (int x = 0; x < original.width; x++) {
			int originalValue = original.data[y][x];
			int filteredValue = filtered.data[y][x];

			if (std::abs(originalValue - filteredValue) <= tolerance) {
				correctPixels++;
			}
		}
	}

	return (static_cast<double>(correctPixels) / totalPixels) * 100.0;
}
