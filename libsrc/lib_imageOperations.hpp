#ifndef fw_imageOperations_hpp
#define fw_imageOperations_hpp

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

extern const int g_gaussianBlurSetting;

namespace Fw {

static void showImage(cv::Mat const & image) {
	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image", image);
	cv::waitKey(0);
}

static cv::Mat readImage(const std::string& pathToImage) {
	return cv::imread(pathToImage);
}

static bool isDayImage(cv::Mat& image) {
	//todo: to be implemented
	return true;
}

static void createGrad(cv::Mat& image) {
	using namespace cv;
	const int scale = 1;
	const int delta = g_gaussianBlurSetting;
	/// Generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	int ddepth = CV_16S;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(image, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(image, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, image);

}

static void convertToGray(cv::Mat& image) {
	cv::cvtColor(image, image, CV_BGR2GRAY);
}

static void runDifferenceOfGradients(cv::Mat& currentImage,
		cv::Mat& previousImage) {
	cv::Mat result;
	cv::absdiff(previousImage, currentImage, result);
	cv::medianBlur(result, result, 9);
	cv::threshold(result, result, 30, 255, cv::THRESH_BINARY);
	int dilation_size = 4;
	cv::Mat element = cv::getStructuringElement(0,
			cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
			cv::Point(dilation_size, dilation_size));
	cv::Mat element2 = cv::getStructuringElement(0,
			cv::Size(4 * dilation_size + 1, 4 * dilation_size + 1),
			cv::Point(2 * dilation_size, 2 * dilation_size));
	cv::medianBlur(result, result, 7);
	cv::erode(result, result, element2);
	cv::medianBlur(result, result, 7);
	cv::dilate(result, result, element);
	currentImage = result;
}

} // end of namespace Fw

#endif /* fw_imageOperations_hpp */
