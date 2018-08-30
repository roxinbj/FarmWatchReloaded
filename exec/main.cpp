#include <iostream>
#include <opencv2/opencv.hpp>
#include <lib_imageDatatypes.hpp>
#include <lib_dataImporter.hpp>
#include <stdio.h>


int main(int argc, char** argv )
{
	Fw::FileReader fileReader{"../imagesPath.txt"};
	std::vector<std::string> myVector = fileReader.getContent();
    Fw::FolderReader folderReader{myVector[0]};

	for(auto item : folderReader.getContent())
	{
		std::cout << "Zeile: " << item << "\n";
	}

	using namespace cv;
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    waitKey(0);

    return 0;
}
