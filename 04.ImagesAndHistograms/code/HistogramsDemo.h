#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class HistogramDemo {
public:
	void displayHist(Mat& image);
	void stasticInfo(Mat& image);
	void cmpHist(Mat& img1, Mat& img2);
	void global_eq(Mat& image);
	void local_eq(Mat& image);
	void backProjectionHistogram(Mat& image, Mat& tpl);
};