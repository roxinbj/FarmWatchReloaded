/*
 * lib_poi.hpp
 *
 *  Created on: 2 Sep 2018
 *      Author: Bjoern
 */

#ifndef lib_poi_hpp
#define lib_poi_hpp

#include <opencv2/opencv.hpp>
#include <iostream>
#include <lib_imageDatatypes.hpp>

namespace Fw
{

class Poi
{
public:



private:
cv::Point m_topLeft;
cv::Point m_bottomRight;
Label m_label;


};



} // namespace Fw

#endif /* lib_poi_hpp */
