#include"findLightBar.h"
#include"findNum_cascade.h"
#include<thread>

void MYshow2(string imgname, Mat img)
{
	Mat imgResized;
	resize(img, imgResized, Size(), 0.5, 0.5);
	cv::imshow(imgname, imgResized);
}



void ArmorDetector::findLightBar(VideoCapture video, int mode)
{

	Mat frame, frameHSV, maskBlur, maskHSV, maskCanny, maskDilHSV, dst, imgCrop;
	Mat imgGray, imgHSV;

	vector<vector<int>> LightBarHSV = { { 0,179,0,255,250,255 } ,{0,164,0,61,245,255}, {0,179,0,255,236,255} };
	int hmin = LightBarHSV[mode][0], smin = LightBarHSV[mode][2], vmin = LightBarHSV[mode][4];
	int hmax = LightBarHSV[mode][1], smax = LightBarHSV[mode][3], vmax = LightBarHSV[mode][5];
	Scalar lowerHSV(hmin, smin, vmin);
	Scalar upperHSV(hmax, smax, vmax);
	Mat kernelHSV = getStructuringElement(MORPH_RECT, Size(5, 5));

	vector<vector<Point>> contoursHSV;
	vector<Vec4i> hierarchy;


	int ret = 0;
	int standard = 3;
	int num = 0;

	Point2f topLeft,topLeft_record, bottomRight, bottomRight_record, center;
	double gap,  averageHeight;

	CascadeClassifier numCascade[4];

	numCascade[0].load("/home/ooofieee/下载/TrackingTest/TrackingTest/src/resources/num1cascade.xml");
	numCascade[1].load("/home/ooofieee/下载/TrackingTest/TrackingTest/src/resources/num2cascade.xml");
	numCascade[2].load("/home/ooofieee/下载/TrackingTest/TrackingTest/src/resources/cascade.xml");
	numCascade[3].load("/home/ooofieee/下载/TrackingTest/TrackingTest/src/resources/num4cascade.xml");

	NumDetector test;

	while (1)
	{

		video >> frame;

		


		if (frame.empty())
		{
			cout << "video done" << endl;
			video.release();
			break;
		}
		ret++;
		if (ret % standard == 0)
		{


			cvtColor(frame, frameHSV, COLOR_BGR2HSV);
			inRange(frameHSV, lowerHSV, upperHSV, maskHSV);
			GaussianBlur(maskHSV, maskBlur, Size(7, 7), 0);
			Canny(maskHSV, maskCanny, 25, 75, 3);
			dilate(maskCanny, maskDilHSV, kernelHSV);



			findContours(maskDilHSV, contoursHSV, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			vector<RotatedRect> boundRect(contoursHSV.size());
			int noise = 0;

			for (int i = 0; i < contoursHSV.size(); i++)
			{
				/*drawContours(frame, contoursHSV, i, Scalar(255,255,255), 2);*/

				if (contoursHSV[i].size() >= 6)
				{
					boundRect[i] = fitEllipse(contoursHSV[i]);
				}
				else
				{
					noise++;
				}
			}


	

			for (int i = 0; i < boundRect.size() - noise; i++)
			{
				if (boundRect[i].size.height > boundRect[i].size.width)
				{
					for (int j = i + 1; j < boundRect.size() - noise; j++)
					{
						if (boundRect[j].size.height > boundRect[j].size.width)
						{
							averageHeight = (boundRect[i].size.height + boundRect[j].size.height) / 2;
							gap = boundRect[i].center.x - boundRect[j].center.x;
							center = (boundRect[i].center + boundRect[j].center) / 2;
							topLeft = center - Point2f(gap / 2, gap );
							bottomRight = center + Point2f(gap / 2, gap );

							if (topLeft.y >= 0 && topLeft.x >= 0 && topLeft.y <= frame.rows && topLeft.x <= frame.cols && bottomRight.y <= frame.rows && bottomRight.x <= frame.cols && bottomRight.y >= 0 && bottomRight.x > 0)
							{
								if (boundRect[i].center.y / boundRect[j].center.y < 1.3 && boundRect[i].center.y / boundRect[j].center.y > 0.7)//���ĵ�yֵ�ж�
								{
									if ((boundRect[i].size.height / boundRect[j].size.height < 1.3 && boundRect[i].size.height / boundRect[j].size.height > 0.7) || (boundRect[i].size.width / boundRect[j].size.width < 1.3 && boundRect[i].size.width / boundRect[j].size.width > 0.7))//���������ж�
									{
										Rect roi(topLeft, bottomRight);
										imgCrop = frame(roi);
									
										test.findNum_cascade(numCascade[0], numCascade[1], numCascade[2], numCascade[3], imgCrop, imgGray, frame, topLeft, bottomRight,topLeft_record,bottomRight_record, gap);
									}
								}
							}
						}
					}
				}
			}
		}

		// rectangle(frame, topLeft_record, bottomRight_record, Scalar(0, 255, 0), 2);
		// putText(frame, to_string(result), topLeft_record, FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 2);

		MYshow2("video", frame);
		//cv::imshow("videoPreProcessed-HSV", maskHSV);
		//cv::imshow("videoPreProcessed-BGR", maskBGR);
		cv::waitKey(1);
	}






}
