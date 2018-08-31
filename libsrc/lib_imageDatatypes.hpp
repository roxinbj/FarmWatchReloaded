//#include 

#include <opencv2/opencv.hpp>
#include <iostream>

namespace Fw {

static void showImage(cv::Mat& image) {
	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image", image);
	cv::waitKey(0);
}

static cv::Mat readImage(const std::string& pathToImage)
{
	return cv::imread(pathToImage);
}


class ImageContainer {
	typedef void (*imageOperation)(cv::Mat&);

public:
	ImageContainer(const std::string& pathToImage) : m_image(readImage(pathToImage)){
	}

	cv::Mat& getImage() {
		if (!m_image.data) {
			std::cout << "No image data to give \n";
			exit(0);
		}
		return m_image;
	}

	// perform operations on image
	void operate(imageOperation foo)
	{
	   	foo(m_image);
	}

private:

	cv::Mat m_image;

};

} // End of Namespace Fw
