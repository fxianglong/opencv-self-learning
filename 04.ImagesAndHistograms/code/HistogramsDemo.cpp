#include "HistogramsDemo.h"

std::string root_dir = "E:/Code/coding/Allopencv/opencv-self-learning/04.ImagesAndHistograms/resource/";

int main() {
	//Mat src = imread(rootdir + "lena.jpg");
	//Mat src2 = imread(rootdir + "ela_original.jpg");
	Mat image = imread(root_dir + "fruits.jpg");
	// Mat tpl = imread(rootdir + "tpl.png");
	imshow("input", image);
	HistogramDemo hd;
	// hd.displayHist(src);
	hd.global_eq(image);
	waitKey(0);
	return 0;
}