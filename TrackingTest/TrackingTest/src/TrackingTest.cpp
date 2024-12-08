
#include <iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include"findLightBar.h"
#include"findNum_cascade.h"

using namespace std;
using namespace cv;

void MYshow(string imgname, Mat img)
{
	Mat imgResized;
	resize(img, imgResized, Size(), 1.5, 1.5);
	cv::imshow(imgname, imgResized);
}


void findHSV(VideoCapture video)
{
	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;
	namedWindow("HSVtrackbars", (640, 2560));
	createTrackbar("hmin", "HSVtrackbars", &hmin, 179);
	createTrackbar("hmax", "HSVtrackbars", &hmax, 179);
	createTrackbar("smin", "HSVtrackbars", &smin, 255);
	createTrackbar("smax", "HSVtrackbars", &smax, 255);
	createTrackbar("vmin", "HSVtrackbars", &vmin, 255);
	createTrackbar("vmax", "HSVtrackbars", &vmax, 255);

	Mat cam0, camHSV, mask;

	while (true)
	{
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		video >> cam0;
		cvtColor(cam0, camHSV, COLOR_BGR2HSV);
		inRange(camHSV, lower, upper, mask);
		MYshow("mask", mask);
		MYshow("cam", cam0);
		cv::waitKey(int(float(1 / video.get(5)) * 1000));
	}
}



int main()
{
	string path1 = "/home/ooofieee/下载/TrackingTest/TrackingTest/src/resources/test1.avi";
	string path2 = "/home/ooofieee/下载/TrackingTest/TrackingTest/src/resources/test2.mp4";
	string path3 = "/home/ooofieee/下载/TrackingTest/TrackingTest/src/resources/test3.mp4";
	
	int mode = 2;
	
	VideoCapture video(path3);

	ArmorDetector test;
	
	test.findLightBar(video, mode);

	//findHSV(video1);
	
	//findNum_cascade(video1);

	return 0;
}
