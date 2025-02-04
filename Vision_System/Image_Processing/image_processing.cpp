#include "image_processing.h"

Mat image_processing::Target_detect_processing(Mat img)
{
    // 进行高斯模糊处理
    Mat blur;
    GaussianBlur(img, blur, Size(5, 5), 0, 0);
    // hsv颜色筛选
    Mat hsv;
    cvtColor(blur, hsv, COLOR_RGB2HSV);
    Mat mask;
    Scalar lower(Color[0], Color[1], Color[2]);
    Scalar upper(Color[3], Color[4], Color[5]);
    inRange(hsv, lower, upper, mask);
    // 形态学操作
    Mat morph;
    Mat kernal = getStructuringElement(MORPH_ELLIPSE, Size(30, 30));
    // morphologyEx(mask, morph, MORPH_CLOSE, kernal);
    dilate(mask, morph, kernal, Point(-1, -1), 1);
    return morph;
}

vector<Point3f> image_processing::Target_Positioning(Mat process, Mat img)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(process, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Point2f> centers;
    vector<float> radius;
    vector<Point3f> C;

    for (int i = 0; i < contours.size(); i++)
    {
        // double peri=arcLength(contours[i],true);
        // approxPolyDP(contours[i],conPoly[i],0.02*peri,true);
        Point2f center;
        float R;
        minEnclosingCircle(contours[i], center, R);
        if(R>50 && R<400)
        {
            centers.push_back(center);
            radius.push_back(R);
            circle(img, center, R, Scalar(0, 255, 0), 5);
            circle(img, center, 8, Scalar(0, 0, 0), -1);
        }
    }
    // cout<<centers.size();
    for (int j = 0; j < radius.size(); j++)
    {
        float x = centers[j].x;
        float y = centers[j].y;
        C.push_back(Point3f(x, y, radius[j]));
    }
    return C;
}