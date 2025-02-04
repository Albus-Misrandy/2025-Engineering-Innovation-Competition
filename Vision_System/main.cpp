#include <iostream>
#include "Image_Processing/image_processing.h"

using namespace std;

int main()
{
    string path = "/home/albus/2025-Engineering-Innovation-Competition/Vision_System/picture_and_video/Target.png";
    // VideoCapture cap1(path);
    Mat img = imread(path);
    image_processing Img_Processor;
    Mat process_img = Img_Processor.Target_detect_processing(img);
    vector<Point3f> Targets = Img_Processor.Target_Positioning(process_img, img);
    cout<<"Targets:"<<Targets<<endl;
    imshow("img", process_img);
    imshow("Img", img);
    waitKey(0);
    return 0;
}