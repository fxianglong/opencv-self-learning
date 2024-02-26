#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class ConvolutionDemo {
public:
	void custom_filter_demo(Mat &image);
	void conv_demo(Mat& image);
	void gaussian_blur_demo(Mat& image);
	void median_blur_demo(Mat& image);
	void blur_demo(Mat& image);
	void gradient_demo(Mat& image);
	void edge_demo(Mat& image);
	void epf_demo(Mat& image);
	void denoise_demo(Mat& image);
	void sharpen_demo(Mat& image);
};