//#include 

#include <vector>
#include <opencv2/opencv.hpp>
#include <dirent.h>

namespace Fw
{


class ImagesKeeper
{
   public:
   ImagesKeeper(const std::string& pathToImages);
   ImagesKeeper() = delete;
   
   private:
      
   std::vector<cv::Mat> m_images;   
        
};


std::vector<std::string> extractJpgsFromPath (const std::string& folderPath)
{
	std::vector<std::string> listOfImagePaths;
	
	DIR *dir;
    struct dirent *ent;
	if ((dir = opendir ("c:\\src\\")) != NULL) 
	{
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) 
	  {
    	printf ("%s\n", ent->d_name);
	  }
  	  closedir (dir);
	} 
	else 
	{
 		/* could not open directory */
  		perror ("");
  		return EXIT_FAILURE;
	}
	
	



}


std::vector<cv::Mat> fillImageVectorFromPath( const std::string& path)
{
   using namespace cv;
   
   Mat image;
   
   image = imread(path);

}




} // End of Namespace Fw