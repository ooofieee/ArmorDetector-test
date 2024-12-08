#include"findNum_cascade.h"
#include"cascadeThreadPool.h"
#include<thread>



void NumDetector::findNum_cascade(CascadeClassifier num1cascade, CascadeClassifier num2cascade, CascadeClassifier num3cascade, CascadeClassifier num4cascade,Mat imgCrop, Mat imgGray, Mat &frame,Point2f topLeft, Point2f bottomRight, Point2f &topLeft_record, Point2f &bottomRight_record, int gap)
{
	if (imgCrop.empty())
	{
		cout << "unvalid"<<endl;
	}
	else
	{

	
		cvtColor(imgCrop, imgGray, COLOR_BGR2GRAY);

		vector<Rect> num1;
		vector<Rect> num2;
		vector<Rect> num3;
		vector<Rect> num4;

		thread t1(num1cascadeFunc, num1cascade, imgGray, std::ref(num1));
		thread t2(num2cascadeFunc, num2cascade, imgGray, std::ref(num2));
		thread t3(num3cascadeFunc, num3cascade, imgGray, std::ref(num3));
		thread t4(num4cascadeFunc, num4cascade, imgGray, std::ref(num4));

		t1.join(); t2.join(); t3.join(); t4.join();

		vector<vector<Rect>> num = { num1,num2,num3,num4 };
	
		for (int i = 0; i<4;i++)
		{
			cout << num[i].size()<<endl;
		}

		if (num1.size() != 0 || num2.size() != 0 || num3.size() != 0 || num4.size() != 0)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j<num[i].size();j++)
				{
					float areaNum = num[i][j].width * num[i][j].height;
					float areaImg = imgCrop.cols * imgCrop.rows;
					if (areaNum / areaImg > 0.3)
					{
						topLeft_record = topLeft + Point2f(0, gap / 2);
						bottomRight_record = bottomRight - Point2f(0,gap/2);	
						cout <<"fuck the WORLD!!!"<<endl;
						rectangle(frame, topLeft_record, bottomRight_record, Scalar(0, 255, 0), 2);
						putText(frame, to_string(i+1), topLeft_record, FONT_HERSHEY_PLAIN, 2, Scalar(0, 255, 0), 2);
					}
				}

			}
		}
	}

}