#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class BinaryDemo {
public:
	void binary_methods_demo(Mat& image);
	void global_binary_demo(Mat& image);
	void ada_binary_demo(Mat& image);
	void noise_and_binary(Mat& image);
	void inrange_binary(Mat& image);
	void inrange_binary_copy(Mat& image);

};