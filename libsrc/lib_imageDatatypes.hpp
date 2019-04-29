//#include

#include <opencv2/opencv.hpp>
#include <iostream>

#include "lib_imageOperations.hpp"

namespace Fw
{

enum class Label

{
	Leopard,
	Oryx,
	Guinea,
	Unknown
};

class Date
{
  public:
	std::string getDate()
	{
		return std::string(
			std::to_string(m_day) + "." + std::to_string(m_month) + "." + std::to_string(m_year));
	}

	friend std::ostream &operator<<(std::ostream &os, const Date &obj)
	{
		// write obj to stream
		os << std::to_string(obj.m_day) << "." << std::to_string(obj.m_month)
		   << "." << std::to_string(obj.m_year);
		return os;
	}

  private:
	int m_day{1};
	int m_month{1};
	int m_year{2000};
};

class Time
{
  public:
	std::string getTime()
	{
		return std::string(
			std::to_string(m_hour) + ":" + std::to_string(m_minutes));
	}

	friend std::ostream &operator<<(std::ostream &os, const Time &obj)
	{
		// write obj to stream
		os << std::to_string(obj.m_hour) << ":"
		   << std::to_string(obj.m_minutes);
		return os;
	}

  private:
	int m_minutes{00};
	int m_hour{12};
};

class Poi
{
  public:
  private:
	cv::Point m_topLeft;
	cv::Point m_bottomRight;
	Label m_label;
};

class ImageContainer
{
	typedef void (*imageOperation)(cv::Mat &);

  public:
	ImageContainer(const std::string &pathToImage) : m_pathToImage(pathToImage), m_image(Fw::readImage(pathToImage))
	{
	}

	cv::Mat getOriginal()
	{
		return readImage(m_pathToImage);
	}

	// used to perform transformations on image
	cv::Mat &getImage()
	{
		if (!m_image.data)
		{
			std::cout << "No image data to give \n";
			exit(0);
		}
		return m_image;
	}

	Date const &getDate()
	{
		return m_date;
	}
	Time const &getTime()
	{
		return m_time;
	}
	std::string const &getVenue()
	{
		return m_venue;
	}

	cv::Mat &getAnalysedImageRef()
	{
		return m_analysedImage;
	}

	// perform operations on image
	void operate(imageOperation foo)
	{
		foo(m_image);
	}

	friend std::ostream &operator<<(std::ostream &os,
									const ImageContainer &obj)
	{
		// write obj to stream
		os << "to be implemented";
		return os;
	}

  private:
	cv::Mat m_image;
	cv::Mat m_analysedImage;
	Fw::Label m_label{Fw::Label::Unknown};
	Fw::Date m_date{};
	Fw::Time m_time{};
	std::string m_venue{};
	bool isDayImage{true};
	const std::string m_pathToImage;
};

} // End of Namespace Fw
