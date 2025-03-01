#include "QRcode.h"

QRCodeDetector QRCode;


string QRcode_Detecting(Mat img, Mat pre)
{
    vector<Point2f> QRcode_2d_Points;
    string QRcode_Info;
    QRcode_Info = QRCode.detectAndDecode(pre, QRcode_2d_Points);
    if(QRcode_2d_Points.size() == 4)
    {
        for (int i = 0; i < 4; i++)
        {
            line(img, QRcode_2d_Points[i], QRcode_2d_Points[(i+1)%4], Scalar(0, 255, 0), 4);
        }
    }
    return QRcode_Info;
}

vector<int> extractDigits(string& input) {
    vector<int> digits;
    
    for (char ch : input) {
        if (isdigit(ch)) {
            digits.push_back(ch - '0');  // 将字符转换为整数
        }
    }

    return digits;
}
