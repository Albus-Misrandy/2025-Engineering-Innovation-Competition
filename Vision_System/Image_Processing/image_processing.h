#ifndef __IMAGE_PROCESSING_H__
#define __IMAGE_PROCESSING_H__

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class image_processing
{
    public:
    Mat CameraMatrix_s = (Mat_<double>(3, 3) <<745.1853243, 0., 323.83757136, 
    0., 735.15100849, 262.06579804, 0., 0., 1.);
    Mat distCoeffs_s = (Mat_<double>(1, 5) <<0., 0., 0., 0., 0.);
    Mat CameraMatrix_b = (Mat_<double>(3, 3) <<689.07684858, 0., 348.51495497,
    0., 689.82665381, 235.22890803, 0., 0., 1.);
    Mat distCoeffs_b = (Mat_<double>(1, 5) <<-0.1560279, -0.57875817, -0.00208722, -0.00096998, 0.91006794);
    vector<int> Color_red = {92,36,135,165,245,255};
    vector<int> Color_green = {30,22,130,91,178,255};
    vector<int> Color_blue = {0,21,65,24,255,255};

    vector<int> Select_Color(int num);
    Mat Target_detect_processing(Mat img, vector<int> Color);
    Mat QRcode_Processing(Mat img);
    vector<Point3f> Target_Positioning(Mat process, Mat img);
};

#endif