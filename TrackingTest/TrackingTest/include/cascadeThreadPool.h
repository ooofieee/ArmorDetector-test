#pragma once

#include <iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<functional>

using namespace std;
using namespace cv;

void num1cascadeFunc(CascadeClassifier num1cascade, Mat imgGray, vector<Rect>& num1);

void num2cascadeFunc(CascadeClassifier num2cascade,  Mat imgGray, vector<Rect>& num2);

void num3cascadeFunc(CascadeClassifier num3cascade, Mat imgGray, vector<Rect>& num3);

void num4cascadeFunc(CascadeClassifier num4cascade, Mat imgGray, vector<Rect>& num4);