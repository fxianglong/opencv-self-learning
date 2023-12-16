#include "matdemo.h"
std::string root_dir = "E:/Code/coding/Allopencv/opencv-self-learning/02.MatAndPixelOperations/resource/";

//创建mat对象的方式
void MatDemo::mat_opt() {
	// 创建Mat对象 m1，大小为 4x4，数据类型为 CV_8UC1（8位无符号整数，单通道），初始化值为 Scalar(255)
	Mat m1(4, 4, CV_8UC1, Scalar(255));
	imshow("m1", m1); // 显示m1
	std::cout << "m1:" << m1 << std::endl; // 打印m1的内容

	// 创建Mat对象 m2，大小为 4x4，数据类型为 CV_8UC3（8位无符号整数，三通道彩色图像），初始化值为 Scalar(0, 0, 255)
	Mat m2(Size(4, 4), CV_8UC3, Scalar(0, 0, 255));
	std::cout << "m2:\n" << m2 << std::endl; // 打印m2的内容
	imshow("m2", m2); // 显示m2

	// 创建Mat对象 m3，大小为 4x4，数据类型为 CV_8UC3，初始化值为 Scalar::all(255)
	Mat m3(Size(4, 4), CV_8UC3, Scalar::all(255));
	std::cout << "m3:\n" << m3 << std::endl; // 打印m3的内容
	imshow("m3", m3); // 显示m3

	// 创建Mat对象 m4，大小为 4x4，数据类型为 CV_8UC3，初始化为全零
	Mat m4 = Mat::zeros(Size(4, 4), CV_8UC3);
	std::cout << "m4:\n" << m4 << std::endl; // 打印m4的内容
	imshow("m4", m4); // 显示m4

	// 创建Mat对象 m5，大小为 4x4，数据类型为 CV_8UC3，初始化为全一
	Mat m5 = Mat::ones(Size(4, 4), CV_8UC3);
	std::cout << "m5:\n" << m5 << std::endl; // 打印m5的内容
	imshow("m5", m5); // 显示m5

	// 克隆 Mat 对象 m4 到 m6
	Mat m6 = m4.clone();
	std::cout << "m6:\n" << m6 << std::endl; // 打印m6的内容
	imshow("m6", m6); // 显示m6

	// 将 m2 复制到 m7
	Mat m7;
	m2.copyTo(m7);
	std::cout << "m7:\n" << m7 << std::endl; // 打印m7的内容
	imshow("m7", m7); // 显示m7

	// 使用C++11的初始化列表创建 Mat 对象 m8，大小为 3x3，数据类型为 double
	Mat m8 = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	std::cout << "m8:\n" << m8 << std::endl; // 打印m8的内容
	imshow("m8", m8); // 显示m8
}

void MatDemo::pixel_visit() {
	// 读取图像
	Mat src = imread(root_dir + "lovely-girl.jpg");
	int w = src.cols; // 图像宽度
	int h = src.rows; // 图像高度
	int cn = src.channels(); // 通道数（彩色图像为3）

	// 生成查找表，将每个像素值映射到离散的16的倍数
	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(16 * (i / 16));

	double t1 = getTickCount();
	imshow("lovely-girl", src); // 显示处理结果
	// 方法1：使用at方法访问像素
	/*
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w * cn; col++) {
			int pv = src.at<uchar>(row, col);
			src.at<uchar>(row, col) = table[pv];
		}
	}
	*/

	// 方法2：使用指针访问像素
	/*
	uchar* currentRow;
	for (int row = 0; row < h; row++) {
		currentRow = src.ptr<uchar>(row);
		for (int col = 0; col < w * cn; col++) {
			src.at<uchar>(row, col) = table[currentRow[col]];
		}
	}
	*/

	// 方法3：使用迭代器访问像素
	/*
	switch (cn) {
		case 1: {
			MatIterator_<uchar> it, end;
			for (it = src.begin<uchar>(), end = src.end<uchar>(); it != end; ++it)
				*it = table[*it];
			break;
		}
		case 3: {
			MatIterator_<Vec3b> it, end;
			for (it = src.begin<Vec3b>(), end = src.end<Vec3b>(); it != end; ++it) {
				(*it)[0] = table[(*it)[0]];
				(*it)[1] = table[(*it)[1]];
				(*it)[2] = table[(*it)[2]];
			}
		}
	}
	*/

	// 方法4：使用data指针访问像素
	uchar* image_data = src.data;
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w * cn; col++) {
			*image_data = table[*image_data];
			image_data++;
		}
	}

	double t2 = getTickCount();
	double t = ((t2 - t1) / getTickFrequency()) * 1000; // 计算执行时间
	ostringstream ss;
	ss << "Execute time: " << std::fixed << std::setprecision(2) << t << " ms ";
	std::cout << ss.str() << std::endl;

	imshow("result", src); // 显示处理结果
}

//图像加减乘除操作
void MatDemo::suanshu_demo() {
	// 读取两张图像
	Mat src1 = imread(root_dir + "WindowsLogo.jpg");
	Mat src2 = imread(root_dir + "LinuxLogo.jpg");

	// 定义用于存储运算结果的 Mat 对象
	Mat add_result, sub_result, mul_result, div_result;

	// 使用add函数进行图像相加
	add(src1, src2, add_result);

	// 使用subtract函数进行图像相减
	subtract(src1, src2, sub_result);

	// 使用multiply函数进行图像相乘
	multiply(src1, src2, mul_result);

	// 使用divide函数进行图像相除
	divide(src1, src2, div_result);

	// 显示各个运算结果
	imshow("add_result", add_result); // 显示图像相加的结果
	imshow("sub_result", sub_result); // 显示图像相减的结果
	imshow("mul_result", mul_result); // 显示图像相乘的结果
	imshow("div_result", div_result); // 显示图像相除的结果
}

//图像位运算操作
void MatDemo::bitwise_demo() {
	// 读取两张图像
	Mat src1 = imread(root_dir + "WindowsLogo.jpg");
	Mat src2 = imread(root_dir + "LinuxLogo.jpg");

	// 定义用于存储位运算结果的 Mat 对象
	Mat invert_result, and_result, or_result, xor_result;

	// 使用bitwise_not进行图像取反操作
	bitwise_not(src1, invert_result);

	// 使用bitwise_and进行图像的逐位与操作
	bitwise_and(src1, src2, and_result);

	// 使用bitwise_or进行图像的逐位或操作
	bitwise_or(src1, src2, or_result);

	// 使用bitwise_xor进行图像的逐位异或操作
	bitwise_xor(src1, src2, xor_result);

	// 显示各个位运算的结果
	imshow("invert_result", invert_result); // 显示图像取反的结果
	imshow("and_result", and_result); // 显示图像逐位与的结果
	imshow("or_result", or_result); // 显示图像逐位或的结果
	imshow("xor_result", xor_result); // 显示图像逐位异或的结果
}

void MatDemo::type_convert(Mat& image) {
	Mat f;
	// 将输入图像的像素值转换为32位浮点数类型（CV_32F）
	image.convertTo(f, CV_32F);
	// 对转换后的图像进行归一化，将像素值范围缩放到 [0, 1] 区间
	f = f / 255.0;
	// 显示转换后的图像
	imshow("f32", f);
}

void MatDemo::adjust_contrast(Mat& image) {
	// 创建与输入图像相同大小的全零图像 constant_img，并设置其通道值为 (0.8, 0.8, 0.8)
	Mat constant_img = Mat::zeros(image.size(), CV_32FC3);
	constant_img.setTo(Scalar(0.8, 0.8, 0.8));

	Mat lowContrastMat, highContrastMat;

	// 降低对比度：将图像与常量图像逐元素相乘
	multiply(image, constant_img, lowContrastMat, 1.0, CV_8U);

	// 增加对比度：将图像与常量图像逐元素相除
	divide(image, constant_img, highContrastMat, 1.0, CV_8U);

	// 显示调整后的图像
	imshow("lowContrastMat", lowContrastMat); // 低对比度图像
	imshow("highContrastMat", highContrastMat); // 高对比度图像
}


void MatDemo::adjust_light(Mat& image) {
	// 创建与输入图像相同大小的全零图像 constant_img，并设置其通道值为 (50, 50, 50)
	Mat constant_img = Mat::zeros(image.size(), image.type());
	constant_img.setTo(Scalar(50, 50, 50));

	Mat darkMat, lightMat;

	// 增加亮度：将图像与常量图像逐元素相加
	add(image, constant_img, lightMat);

	// 降低亮度：将图像与常量图像逐元素相减
	subtract(image, constant_img, darkMat);

	// 显示调整后的图像
	imshow("lightMat", lightMat); // 增加亮度后的图像
	imshow("darkMat", darkMat);   // 降低亮度后的图像
}


void MatDemo::channels_demo(Mat& image) {
	// 分离通道
	std::vector<Mat> mv;
	split(image, mv);

	// 逐通道取反
	for (size_t t = 0; t < mv.size(); t++) {
		bitwise_not(mv[t], mv[t]);
	}

	// 合并通道
	Mat dst;
	merge(mv, dst);
	imshow("merge channels", dst); // 显示合并后的图像

	// 通过 mixChannels 函数进行通道混合
	int from_to[] = { 0, 2, 1, 1, 2, 0 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);

	imshow("mix channels", dst); // 显示混合后的图像
}


int main() {
	//读取源文件
	Mat src = imread(root_dir + "baboon.jpg");
	imshow("input", src);
	//获取通道数
	int cn = src.channels();
	printf("image channels : %d \n", cn);
	Mat gray;
	//将源文件转为灰度图
	cvtColor(src, gray, COLOR_BGR2GRAY);
	cn = gray.channels();
	imshow("gray", gray);
	printf("gray channels : %d \n", cn);

	MatDemo md;
	//md.mat_opt();
	md.pixel_visit();
	md.suanshu_demo();
	md.bitwise_demo();
	md.type_convert(src);
	md.adjust_contrast(src);
	md.adjust_light(src);
	md.channels_demo(src);
	md.pixel_visit();
	waitKey(0);
	return 0;
}