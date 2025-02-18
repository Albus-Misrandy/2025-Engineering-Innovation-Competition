#ifndef __QRCODE_H__
#define __QRCODE_H__

#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/objdetect.hpp>

using namespace std;
using namespace cv;

string QRcode_Detecting(Mat img);
vector<int> extractDigits(string& input);

#endif
