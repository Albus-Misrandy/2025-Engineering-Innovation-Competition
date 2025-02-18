#ifndef __IMAGE_PROCESSING_H__
#define __IMAGE_PROCESSING_H__

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class image_processing
{
    public:
    Mat CameraMatrix = (Mat_<double>(3, 3) <<745.1853243, 0., 323.83757136, 
    0., 735.15100849, 262.06579804, 0., 0., 1.);
    Mat distCoeffs = (Mat_<double>(1, 5) <<0., 0., 0., 0., 0.);
    vector<int> Color = {0,19,10,179,255,241};

    Mat Target_detect_processing(Mat img);
    Mat QRcode_Processing(Mat img);
    vector<Point3f> Target_Positioning(Mat process, Mat img);
};

#endif