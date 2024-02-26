#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class MatColorDemo {
public:
	void bgr2rgb(Mat& image);
	void color_range_demo(Mat& image);
};