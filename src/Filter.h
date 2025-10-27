/*
 * Filter.h
 *
 *  Created on: Oct 21, 2025
 *      Author: cyberdemon
 */

#ifndef FILTER_H_
#define FILTER_H_

#include "PGMreader.h"
#include "vector"

class Filter {
public:
	static pgmimage movavr(pgmimage image, int window);
	static pgmimage runavr(pgmimage image, double alpha);
	static pgmimage medium(const pgmimage &image, int window);

	static pgmimage SaltPepperNoise(const pgmimage &image, double noiseProbability);
	static pgmimage BlockNoise(const pgmimage &image, int blockSize, double intensity);
	static pgmimage StripingNoise(const pgmimage &image, int stripeWidth, double intensity, bool vertical);
	static pgmimage SpeckleNoise(const pgmimage &image, double variance);
	static pgmimage BrightnessDependentNoise(const pgmimage &image, double baseSigma, double darkBoost);

	static double compareImages(const pgmimage& original, const pgmimage& filtered);
};

#endif /* FILTER_H_ */
