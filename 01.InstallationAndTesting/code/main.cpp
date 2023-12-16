#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
string rootdir = "E:/Code/coding/Allopencv/opencv-self-learning/01.InstallationAndTesting/resource/";
void video_demo();
int main(int argc, char** argv) {
	//image_demo()
	video_demo();
	return 0;
}
//图片测试
void image_demo() {
	Mat image = imread(rootdir + "lena.jpg", IMREAD_UNCHANGED);
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", image);
	waitKey(0);
	destroyAllWindows();
}
//视频测试
void video_demo() {
	VideoCapture capture;
	capture.open(rootdir + "vtest.avi", CAP_FFMPEG);
	int height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int width = capture.get(CAP_PROP_FRAME_WIDTH);
	double fps = capture.get(CAP_PROP_FPS);
	double count = capture.get(CAP_PROP_FRAME_COUNT);
	printf("height: %d, width: %d, fps: %.2f, count: %.2f \n", height, width, fps, count);

	VideoWriter writer( rootdir + "output.avi", capture.get(CAP_PROP_FOURCC), fps, Size(width, height));
	Mat frame;
	while (true) {
		bool ret = capture.read(frame);
		if (!ret) break;
		imshow("frame", frame);
		writer.write(frame);
		char c = waitKey(1);
		if (c == 27) {
			break;
		}
	}
	capture.release();
	writer.release();
	waitKey(0);
	destroyAllWindows();
	return;
}