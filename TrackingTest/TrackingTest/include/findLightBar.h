#pragma once

#include <iostream>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


class ArmorDetector
{
public:

    void findLightBar(VideoCapture video, int mode);

};
