#include "MatColorDemo.h"

std::string root_dir = "E:/Code/coding/Allopencv/opencv-self-learning/03.MatColor/resource/";

void MatColorDemo::bgr2rgb(Mat& image) {
	Mat dst;
	// 使用 cvtColor 函数将输入图像从BGR颜色空间转换为RGB颜色空间
	cvtColor(image, dst, COLOR_BGR2RGB);
	// 显示转换后的图像
	imshow("result", dst);
}

void MatColorDemo::color_range_demo(Mat& image) {
	// BGR to HSV 转换
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	imshow("hsv", hsv);

	// BGR to RGB 转换
	Mat rgb;
	cvtColor(image, rgb, COLOR_BGR2RGB);
	imshow("rgb", rgb);

	// BGR to LAB 转换
	Mat lab;
	cvtColor(image, lab, COLOR_BGR2Lab);
	imshow("lab", lab);

	// 在HSV颜色空间中提取指定颜色范围的掩膜
	Mat mask;
	inRange(hsv, Scalar(35, 43, 46), Scalar(99, 255, 255), mask);
	imshow("mask", mask);

	// 对掩膜取反，然后逐元素与原图像相与，实现颜色提取
	Mat dst;
	bitwise_not(mask, mask);
	bitwise_and(image, image, dst, mask);
	imshow("dst", dst);
}


int main(int argc, char** argv) {
	// 读取图像
	Mat src = imread(root_dir + "baboon.jpg");
	// 显示原始图像
	imshow("baboon", src);
	// 创建 MatColorDemo 类的实例
	MatColorDemo cs;
	// 调用 bgr2rgb 函数进行RGB颜色空间转换，并显示结果
	cs.bgr2rgb(src);
	// 读取另一张图像
	Mat src1 = imread(root_dir + "green.jpg");
	// 显示新的输入图像
	imshow("green", src1);
	// 调用 color_range_demo 函数进行颜色范围操作，并显示结果
	cs.color_range_demo(src1);
	// 等待用户按键
	waitKey(0);

	return 0;
}