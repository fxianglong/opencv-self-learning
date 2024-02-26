#include "Convolution_ops.h"
std::string root_dir = "E:/Code/coding/Allopencv/opencv-self-learning/05.convolutions/resource/";

void ConvolutionDemo::conv_demo(Mat& image) {
	int w = image.cols;
	int h = image.rows;
	Mat result = image.clone();
	for (int i = 1; i < h - 1; i++) {
		for (int j = 1; j < w - 1; j++) {
			int sum_b = image.at<Vec3b>(i - 1, j - 1)[0] + image.at<Vec3b>(i, j - 1)[0] + image.at<Vec3b>(i + 1, j - 1)[0]
				+ image.at<Vec3b>(i - 1, j)[0] + image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j + 1)[0]
				+ image.at<Vec3b>(i - 1, j + 1)[0] + image.at<Vec3b>(i, j + 1)[0] + image.at<Vec3b>(i + 1, j + 1)[0];
			int sum_g = image.at<Vec3b>(i - 1, j - 1)[1] + image.at<Vec3b>(i, j - 1)[1] + image.at<Vec3b>(i + 1, j - 1)[1]
				+ image.at<Vec3b>(i - 1, j)[1] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j + 1)[1]
				+ image.at<Vec3b>(i - 1, j + 1)[1] + image.at<Vec3b>(i, j + 1)[1] + image.at<Vec3b>(i + 1, j + 1)[1];
			int sum_r = image.at<Vec3b>(i - 1, j - 1)[2] + image.at<Vec3b>(i, j - 1)[2] + image.at<Vec3b>(i + 1, j - 1)[2]
				+ image.at<Vec3b>(i - 1, j)[2] + image.at<Vec3b>(i, j)[2] + image.at<Vec3b>(i, j + 1)[2]
				+ image.at<Vec3b>(i - 1, j + 1)[2] + image.at<Vec3b>(i, j + 1)[2] + image.at<Vec3b>(i + 1, j + 1)[2];
			result.at<Vec3b>(i, j) = Vec3b(sum_b / 9, sum_g / 9, sum_r / 9);
		}
	}
	imshow("卷积演示", result);
}
void ConvolutionDemo::blur_demo(Mat& image) {
	Mat result7x7;
	Mat result15x15;
	Mat result10x15;
	Mat result4x4;
	blur(image, result7x7, Size(7,7), Point(-1, -1), BORDER_DEFAULT);
	blur(image, result15x15, Size(15,15), Point(-1, -1), BORDER_DEFAULT);
	blur(image, result10x15, Size(10,15), Point(-1, -1), BORDER_DEFAULT);
	blur(image, result4x4, Size(4,4), Point(-1, -1), BORDER_DEFAULT);
	imshow("7x7", result7x7);
	imshow("15x15", result15x15);
	imshow("10x15", result10x15);
	imshow("4x4", result4x4);

}

void ConvolutionDemo::gaussian_blur_demo(Mat& image) {
	Mat result_size10x10;
	Mat result_sigma15;
	Mat result_sigma1;
	GaussianBlur(image, result_size10x10, Size(11, 11), 0, 0, BORDER_DEFAULT);
	GaussianBlur(image, result_sigma15, Size(0, 0), 15, 0, BORDER_DEFAULT);
	GaussianBlur(image, result_sigma1, Size(0, 0), 1, 0, BORDER_DEFAULT);
	imshow("result_size10x10", result_size10x10);
	imshow("result_sigma15", result_sigma15);
	imshow("result_sigma1", result_sigma1);
}

void ConvolutionDemo::median_blur_demo(Mat& image) {
	Mat result_median_demo;
	medianBlur(image, result_median_demo, 3);
	imshow("result_median_demo", result_median_demo);
}
void ConvolutionDemo::custom_filter_demo(Mat& image) {
	Mat k1 = Mat::ones(Size(25, 25), CV_32FC1);
	k1 = k1 / (25 * 25);
	std::cout << k1 << std::endl;
	Mat result25x25;
	filter2D(image, result25x25, -1, k1, Point(-1, -1), 0, BORDER_DEFAULT);
	imshow("自定义，模糊-25x25", result25x25);

	Mat k2 = Mat::ones(Size(25, 1), CV_32FC1);
	k2 = k2 / (25 * 1);
	std::cout << k2 << std::endl;
	Mat result25x1;
	filter2D(image, result25x1, -1, k2, Point(-1, -1), 0, BORDER_DEFAULT);
	imshow("自定义模糊-25x1", result25x1);

	Mat k3 = Mat::ones(Size(1, 25), CV_32FC1);
	k3 = k3 / (1*25);
	std::cout << k3 << std::endl;
	Mat result1x25;
	filter2D(image, result1x25, -1, k3, Point(-1, -1), 0, BORDER_DEFAULT);
	imshow("自定义模糊-1x25", result1x25);

	Mat k4 = Mat::eye(Size(25, 25), CV_32FC1);
	k4 = k4 / (25);
	std::cout << k4 << std::endl;
	Mat result25;
	filter2D(image, result25, -1, k4, Point(-1, -1), 4);
	imshow("自定义对角线模糊", result25);
}
void ConvolutionDemo::gradient_demo(Mat& image) {
	Mat gradx, grady;
	Sobel(image, gradx, CV_32F, 1, 0);
	Sobel(image, grady, CV_32F, 0, 1);
	imshow("gradx", gradx);
	imshow("grady", grady);
	normalize(gradx, gradx, 0, 1.0, NORM_MINMAX);
	normalize(grady, grady, 0, 1.0, NORM_MINMAX);
	imshow("梯度X轴方向", gradx);
	imshow("梯度Y轴方向", grady);

	Scharr(image, gradx, CV_32F, 1, 0);
	Scharr(image, grady, CV_32F, 0, 1);
	normalize(gradx, gradx, 0, 1.0, NORM_MINMAX);
	normalize(grady, grady, 0, 1.0, NORM_MINMAX);

	imshow("scharr-X轴方向", gradx);
	imshow("scharr-Y轴方向", grady);
}
void ConvolutionDemo::edge_demo(Mat& image) {
	Mat edge;
	int low_T = 150;
	Canny(image, edge, low_T, low_T * 2, 3, false);
	imshow("bianyuan", edge);
	Mat color_edge;
	bitwise_and(image, image, color_edge, edge);
	imshow("caisebianyuan", color_edge);
}

void ConvolutionDemo::denoise_demo(Mat& image) {
	RNG rng(12345);
	int h = image.rows;
	int w = image.cols;
	int nums = 10000;
	Mat jynoise_img = image.clone();
	for (int i = 0; i < nums; i++) {
		int x = rng.uniform(0, w);
		int y = rng.uniform(0, h);
		if (i % 2 == 1) {
			jynoise_img.at<Vec3b>(y, x) = Vec3b(255, 255, 255);
		}
		else {
			jynoise_img.at<Vec3b>(y, x) = Vec3b(0, 0, 0);
		}
	}
	imshow("椒盐噪声", jynoise_img);

	Mat noise = Mat::zeros(image.size(), image.type());
	randn(noise, (15, 15, 15), (30, 30, 30));
	Mat des;
	add(image, noise, des);
	imshow("高斯噪音", des);

	Mat median_denoise, mean_denoise;
	medianBlur(jynoise_img, median_denoise, 5);
	blur(jynoise_img, mean_denoise, Size(5, 5));
	imshow("中值去噪-5x5", median_denoise);
	imshow("均值去噪-5x5", mean_denoise);
}

void ConvolutionDemo::epf_demo(Mat& image) {
	Mat denoise_img, cartoon;
	bilateralFilter(image, denoise_img, 7, 80, 10);
	bilateralFilter(image, cartoon, 0, 150, 10);
	imshow("去噪效果", denoise_img);
	imshow("卡通效果", cartoon);
}

void ConvolutionDemo::sharpen_demo(Mat& image) {
	Mat lap_img, sharpen_img;
	Laplacian(image, lap_img, CV_32F, 3, 1.0, 0.0, 4);
	imshow("拉普拉斯0", lap_img);
	normalize(lap_img, lap_img, 0, 1.0, NORM_MINMAX);
	imshow("拉普拉斯", lap_img);

	Mat k = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(image, sharpen_img, -1, k, Point(-1, -1), 0, 4);
	imshow("锐化", sharpen_img);

	Mat gray;
	int h = image.rows;
	int w = image.cols;
	float sum = 0;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	for (int i = 1; i < h - 1; i++) {
		for (int j = 1; j < w - 1; j++) {
			int dx = gray.at<uchar>(i, j) * 2 - gray.at<uchar>(i, j + 1) - gray.at<uchar>(i, j - 1);
			int dy = gray.at<uchar>(i, j) * 2 - gray.at<uchar>(i+1, j) - gray.at<uchar>(i-1, j);
			sum += (abs(dx) + abs(dy));
		}
	}
	printf("Lapalcian ML sum: %.2f", sum);
}
int main() {
	Mat image = imread(root_dir + "bee.png");
	imshow("bee", image);
	ConvolutionDemo conv_ops;
	conv_ops.sharpen_demo(image);
	waitKey(0);
	return 0;
}