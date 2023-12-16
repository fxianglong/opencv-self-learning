#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;
using namespace cv;

class MatDemo
{
public:
	void mat_opt();
	void pixel_visit();
	void suanshu_demo();
	void bitwise_demo();
	void type_convert(Mat& image);
	void adjust_contrast(Mat& image);
	void adjust_light(Mat& image);
	void channels_demo(Mat& image);
};
