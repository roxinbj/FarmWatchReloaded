#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <lib_imageDatatypes.hpp>
#include <lib_dataImporter.hpp>
#include <lib_imageOperations.hpp>
#include "fw_filtering.hpp"

extern const int g_gaussianBlurSetting(0);

int main(int argc, char** argv) {

	// set path to Images
	const std::string m_pathToImagesFolder {
			Fw::FileReader("../imagesPath.txt").getContent()[0] };
	const std::vector<std::string> m_imageNames { Fw::FolderReader {
			m_pathToImagesFolder }.getContent() };

	// set up ImageContainer Vector
	std::vector<Fw::ImageContainer> m_imageContainer;
	for (int i = 0; i < m_imageNames.size(); ++i) {
		const std::string path { m_pathToImagesFolder + "/" + m_imageNames[i] };
		m_imageContainer.push_back(Fw::ImageContainer(path));
	}

	// perform operations on images before analysis
	std::for_each(m_imageContainer.begin(), m_imageContainer.end(),
			[](Fw::ImageContainer &n) {Fw::applyImageFiltersAlgorithms(n.getImage());});

	// run delta analysis
	Fw::ImageContainer* current { nullptr };
	Fw::ImageContainer* previous { nullptr };
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
		Fw::runImageDeltaAnalysis(current->getImage(), previous->getImage());
	}

	//demo
	Fw::showImage(m_imageContainer[4].getOriginal());
	Fw::showImage(m_imageContainer[4].getImage());

	return 0;
}
