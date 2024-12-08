#include"cascadeThreadPool.h"

void num1cascadeFunc(CascadeClassifier num1cascade, Mat imgGray, vector<Rect> &num1)
{
	num1cascade.detectMultiScale(imgGray, num1, 1.1, 5);
}

void num2cascadeFunc(CascadeClassifier num2cascade, Mat imgGray, vector<Rect> &num2)
{
	num2cascade.detectMultiScale(imgGray, num2, 1.1, 5);
}

void num3cascadeFunc(CascadeClassifier num3cascade, Mat imgGray, vector<Rect> &num3)
{
	num3cascade.detectMultiScale(imgGray, num3, 1.1, 5);
}

void num4cascadeFunc(CascadeClassifier num4cascade, Mat imgGray, vector<Rect> &num4)
{
	num4cascade.detectMultiScale(imgGray, num4, 1.1, 5);
}