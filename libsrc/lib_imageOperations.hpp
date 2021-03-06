
#ifndef fw_imageOperations_hpp
#define fw_imageOperations_hpp

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

extern const int g_gaussianBlurSetting;

namespace Fw
{


static void showImage(cv::Mat& image) {
	cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display Image", image);
	cv::waitKey(0);
}

static cv::Mat readImage(const std::string& pathToImage) {
	return cv::imread(pathToImage);
}

static void createGrad(cv::Mat& image)
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
    Sobel( image, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );

    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( image, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );

    /// Total Gradient (approximate)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, image );

}

} // end of namespace Fw

#endif /* fw_imageOperations_hpp */
