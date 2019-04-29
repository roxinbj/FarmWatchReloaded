#ifndef fw_imageOperations_hpp
#define fw_imageOperations_hpp

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

extern const int g_gaussianBlurSetting;

namespace Fw
{

static void showImage(cv::Mat const &image)
{
	cv::namedWindow("Display Image", cv::WINDOW_NORMAL);
	cv::imshow("Display Image", image);
	cv::waitKey(0);
}

static cv::Mat readImage(const std::string &pathToImage)
{
	cv::Mat mat = cv::imread(pathToImage);
	if (mat.rows > 768 || mat.cols > 1024)
	{
		cv::resize(mat, mat, cv::Size(1024, 768));
	}
	return mat;
}

static bool isDayImage(cv::Mat &image)
{
	//todo: to be implemented
	return true;
}

static void saveImage(const cv::Mat &image, const std::string &path,
					  const std::string &name)
{
	std::string pathName{path + "/" + name};
	cv::imwrite(pathName, image);
}

static void createGrad(cv::Mat &image)
{
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

static void convertToGray(cv::Mat &image)
{
	cv::cvtColor(image, image, CV_BGR2GRAY);
}

static void drawContours(cv::Mat &image)
{
	using namespace cv;
	std::vector<std::vector<Point>> iContours;
	std::vector<Vec4i> iHierarchy;
	std::vector<Rect> iBoundingRect;
	findContours(image, iContours, iHierarchy, CV_RETR_EXTERNAL,
				 CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	for (int i = 0; i < iContours.size(); i++)
	{
		// Create Bounding Boxes
		std::vector<Point> contours_poly;
		//approxPolyDP(Mat(iContours[i]), contours_poly, 3, true);
		Rect rect = boundingRect(Mat(iContours[i]));
		drawContours(image,
					 std::vector<std::vector<Point>>(1, iContours.at(i)), 0,
					 Scalar(255, 0, 255), 1, 8);
		rectangle(image, rect.tl(), rect.br(), Scalar(255, 0, 255), 1, 8, 0);
	}
}

static void drawCircle(cv::Mat &image)
{
	using namespace cv;
	std::vector<std::vector<Point>> iContours;
	std::vector<Vec4i> iHierarchy;
	std::vector<Rect> iBoundingRect;
	findContours(image, iContours, iHierarchy, CV_RETR_EXTERNAL,
				 CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	for (int i = 0; i < iContours.size(); i++)
	{
		// Create Bounding Boxes

		Point2f center;
		float radius;

		minEnclosingCircle(iContours[i], center, radius);
		circle(image, center, static_cast<int>(radius), Scalar(255, 0, 255), 1);
	}
}

static void runDifferenceOfGradients(cv::Mat &currentImage,
									 cv::Mat &previousImage, cv::Mat &result)
{

	using namespace cv;
	cv::compare(previousImage, currentImage, result, cv::CmpTypes::CMP_GT);

	//cv::medianBlur(result, result, 9);
	//cv::threshold(result, result, 30, 255, cv::THRESH_BINARY);
	int dilation_size = 3;
	int erode_size = 1;
	cv::Mat dilateElement = cv::getStructuringElement(0,
													  cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
													  cv::Point(dilation_size, dilation_size));
	cv::Mat erodeElement = cv::getStructuringElement(0,
													 cv::Size(4 * erode_size + 1, 4 * erode_size + 1),
													 cv::Point(2 * erode_size, 2 * erode_size));
	//cv::medianBlur(result, result, 7);
	cv::erode(result, result, erodeElement);
	//cv::medianBlur(result, result, 7);
	cv::dilate(result, result, dilateElement);
}

} // end of namespace Fw

#endif /* fw_imageOperations_hpp */
