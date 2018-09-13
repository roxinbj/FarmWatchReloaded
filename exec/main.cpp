#include <iostream>
#include <stdio.h>
#include <boost/filesystem.hpp>

#include <opencv2/opencv.hpp>
#include <lib_imageDatatypes.hpp>
#include <lib_dataImporter.hpp>
#include <lib_imageOperations.hpp>
#include "fw_filtering.hpp"

extern const int g_gaussianBlurSetting(0);

static constexpr bool g_saveOutput { true };
static constexpr bool g_showImages { true };
static constexpr bool g_showPrefilteredImage { false };
static constexpr bool g_showOutput { true };

int main(int argc, char** argv) {
	// --------------------------------
	// ---  set up local variables ----
	// --------------------------------
	// ImageContainer
	std::vector<Fw::ImageContainer> m_imageContainer;
	// Pointer to ImageContainer
	Fw::ImageContainer* current { nullptr };
	Fw::ImageContainer* previous { nullptr };

	// set path to Images
	const std::string m_pathToImagesFolder {
			Fw::FileReader("../imagesPath.txt").getContent()[0] };
	const std::vector<std::string> m_imageNames { Fw::FolderReader {
			m_pathToImagesFolder }.getContent() };

	// set up ImageContainer Vector
	for (int i = 0; i < m_imageNames.size(); ++i) {
		const std::string path { m_pathToImagesFolder + "/" + m_imageNames[i] };
		m_imageContainer.push_back(Fw::ImageContainer(path));
	}

	// perform operations on images before analysis
	std::for_each(m_imageContainer.begin(), m_imageContainer.end(),
			[](Fw::ImageContainer &n) {Fw::applyImageFiltersAlgorithms(n.getImage());});

	// run delta analysis
	for (int i = 0; i < m_imageContainer.size(); ++i) {
		// assign pointers to imageContainer
		if (i == 0) {
			current = &m_imageContainer[0];
			previous = &m_imageContainer[1];
		} else {
			current = &m_imageContainer[i];
			previous = &m_imageContainer[i - 1];
		}
		// run algorithms
		Fw::runImageDeltaAnalysis(current->getImage(), previous->getImage(),
				current->getAnalysedImageRef());
		//Fw::drawContours(current->getAnalysedImageRef());
		Fw::drawCircle(current->getAnalysedImageRef());


		// print
		if (g_showImages) {
			Fw::showImage(m_imageContainer[i].getOriginal());
		}
		if (g_showPrefilteredImage) {
			Fw::showImage(m_imageContainer[i].getImage());
		}
		if (g_showOutput) {
			Fw::showImage(m_imageContainer[i].getAnalysedImageRef());
		}
	}

	if (g_saveOutput) {

		const std::string m_pathToOutputFolder { Fw::FileReader(
				"../outputPath.txt").getContent()[0] };
		//save images to file
		boost::filesystem::path dir(m_pathToOutputFolder + "/output");
		if (boost::filesystem::create_directory(dir)) {
			std::cout << "Success" << "\n";

		}
		for (int i = 0; i < m_imageContainer.size(); ++i) {
			std::string pathForResultImage = m_pathToOutputFolder + "/output";//+ m_imageNames[i];
			Fw::saveImage(m_imageContainer[i].getAnalysedImageRef(),
					pathForResultImage, m_imageNames[i]);
		}

	}

	//demo

	return 0;
}

