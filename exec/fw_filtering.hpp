/*
 * fw_filtering.hpp
 *
 *  Created on: 2 Sep 2018
 *      Author: Bjoern
 */

#ifndef fw_filtering_hpp
#define fw_filtering_hpp

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Fw {

static void applyImageFiltersAlgorithms(cv::Mat& image) {
	// todo: to be pimped
	//image preperation
	Fw::convertToGray(image);
	//cv::GaussianBlur( image, image, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );
}

static void runImageDeltaAnalysis(cv::Mat& mainImage, cv::Mat& referenceImage, cv::Mat& resultImage) {
	Fw::runDifferenceOfGradients(mainImage,referenceImage, resultImage);
}

}

#endif /* fw_filtering_hpp */
