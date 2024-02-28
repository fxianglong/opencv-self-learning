#include "Binary_ops.h"

std::string root_dir = "E:/Code/coding/Allopencv/opencv-self-learning/06.BinaryOps/resource/";

void plotHistogram(const Mat& image) {
	// 计算直方图
	Mat hist;
	int histSize = 256; // 直方图中的条目数
	float range[] = { 0, 256 }; // 像素值范围
	const float* histRange = { range };
	calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange, true, false);

	// 绘制直方图
	int hist_w = 512, hist_h = 400;
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	// 归一化直方图数据
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// 绘制直方图条形图
	for (int i = 1; i < histSize; i++) {
		line(histImage, Point(i - 1, hist_h - cvRound(hist.at<float>(i - 1))),
			Point(i, hist_h - cvRound(hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	imshow("Histogram", histImage);
	waitKey(0);
}

void BinaryDemo::binary_methods_demo(Mat& image) {
	Mat binary;
	threshold(image, binary, 127, 255, THRESH_BINARY);
	imshow("二值化", binary);
	threshold(image, binary, 127, 255, THRESH_BINARY_INV);
	imshow("二值化反", binary);
	threshold(image, binary, 127, 255, THRESH_TRUNC);
	imshow("阈值截断", binary);
	threshold(image, binary, 127, 255, THRESH_TOZERO);
	imshow("阈值取零", binary);
	threshold(image, binary, 127, 255, THRESH_TOZERO_INV);
	imshow("阈值取零反", binary);
}

void BinaryDemo::global_binary_demo(Mat& image) {
	//大律法
	Mat gray, binary;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	plotHistogram(gray);
	double t = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	std::cout << "threashold value:" << t << std::endl;
	imshow("OTSU二值化", binary);
	//三角法
	t = threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_TRIANGLE);
	std::cout << "threashold value:" << t << std::endl;
	imshow("TRIANGLE二值化", binary);
}

void BinaryDemo::ada_binary_demo(Mat& image) {
	Mat gray, binary;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 25, 10);
	imshow("均值模糊自适应", binary);

	adaptiveThreshold(gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 25, 10);
	imshow("高斯模糊自适应", binary);
}

void BinaryDemo::noise_and_binary(Mat& image) {
	Mat binary;
	threshold(image, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("二值化", binary);

	Mat denoise_img;
	GaussianBlur(image, denoise_img, Size(5, 5), 0, 0);
	threshold(denoise_img, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("高斯模糊处理+二值化", binary);

	bilateralFilter(image, denoise_img, 0, 100, 10);
	threshold(denoise_img, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("高斯双边模糊处理+二值化", binary);
}

void BinaryDemo::inrange_binary(Mat& image) {
	Mat hsv, mask;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(20, 43, 46), Scalar(23, 255, 255), mask);
	imshow("区域掩膜", mask);

	Mat result;
	bitwise_and(image, image, result, mask);
	imshow("区域提取", result);
}

void BinaryDemo::inrange_binary_copy(Mat& image) {
	Mat hsv, mask;
	// 定义灰度阈值范围
	int lowerThreshold = 127;
	int upperThreshold = 255;
	inRange(image, lowerThreshold, upperThreshold, mask);
	imshow("区域掩膜1", mask);

	Mat result;
	bitwise_and(image, image, result, mask);
	imshow("区域提取1", result);
}
int main() {
	Mat image = imread(root_dir + "bee.png");
	imshow("bee", image);
	Mat image1 = imread(root_dir + "coins.jpg", cv::IMREAD_GRAYSCALE);
	imshow("coins", image1);
	BinaryDemo binary_ops;
	binary_ops.inrange_binary(image);
	binary_ops.inrange_binary_copy(image1);
	waitKey(0);
	return 0;
}