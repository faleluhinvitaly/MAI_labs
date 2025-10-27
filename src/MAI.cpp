//============================================================================
// Name        : MAI.cpp
// Author      : Faleluhin Vitaly
// Version     :
// Copyright   : no copyright
// Description :
//============================================================================

#include "Filter.h"
#include "PGMreader.h"
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "you should put image path"
				  << std::endl;
		return 1;
	}
	PGMreader reader(argv[1]);
	pgmimage original =reader.image;

	// Вектор шумов: имя + функция
	std::vector<
		std::pair<std::string, std::function<pgmimage(const pgmimage &)>>>
		noises = {{"SaltPepper",
				   [](const pgmimage &img) {
					   return Filter::SaltPepperNoise(img, 0.05);
				   }},
				  {"Block",
				   [](const pgmimage &img) {
					   return Filter::BlockNoise(img, 8, 0.3);
				   }},
				  {"StripingHorizontal",
				   [](const pgmimage &img) {
					   return Filter::StripingNoise(img, 5, 0.2, false);
				   }},
				  {"StripingVertical",
				   [](const pgmimage &img) {
					   return Filter::StripingNoise(img, 5, 0.2, true);
				   }},
				  {"Speckle",
				   [](const pgmimage &img) {
					   return Filter::SpeckleNoise(img, 0.1);
				   }},
				  {"BrightnessDependent", [](const pgmimage &img) {
					   return Filter::BrightnessDependentNoise(img, 0.3, 2.0);
				   }}};

	// Вектор фильтров: имя + функция
	std::vector<
		std::pair<std::string, std::function<pgmimage(const pgmimage &)>>>
		filters = {
			{"MovingAverage",
			 [](const pgmimage &img) { return Filter::movavr(img, 3); }},
			{"RunningAverage",
			 [](const pgmimage &img) { return Filter::runavr(img, 0.9); }},
			{"Median",
			 [](const pgmimage &img) { return Filter::medium(img, 3); }}};

	std::cout << "=== Testing All Noise and Filter Combinations ==="
			  << std::endl;

	for (const auto &noise : noises) {
		std::cout << "\n--- " << noise.first << " Noise ---" << std::endl;

		pgmimage noisy = noise.second(original);
		PGMreader noisy_saver(noisy);
		noisy_saver.save(noise.first + ".pgm");

		for (const auto &filter : filters) {
			pgmimage filtered = filter.second(noisy);

			double score = Filter::compareImages(original, filtered);
			std::cout << filter.first << ": " << score << "%" << std::endl;
		}
	}

	std::cout << "\nProcessing completed! Check the generated PGM files."
			  << std::endl;


return 0;
}