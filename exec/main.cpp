#include <iostream>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <lib_imageDatatypes.hpp>
#include <lib_dataImporter.hpp>
#include <lib_imageOperations.hpp>



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
	void (*foo)(cv::Mat&) = &createGrad;
	m_imageContainer[0].operate(foo);

	//demo
	Fw::showImage(m_imageContainer[0].getImage());

	return 0;
}
