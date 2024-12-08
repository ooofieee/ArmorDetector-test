#pragma once

#include <iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>

using namespace std;
using namespace cv;

class NumDetector
{
public:
    void findNum_cascade(CascadeClassifier num1cascade, CascadeClassifier num2cascade, CascadeClassifier num3cascade, CascadeClassifier num4cascade,Mat imgCrop, Mat imgGray, Mat &frame,Point2f topLeft, Point2f bottomRight, Point2f &topLeft_record, Point2f &bottomRight_record,int gap);
};

