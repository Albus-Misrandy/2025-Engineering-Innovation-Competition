#include "QRcode.h"

QRCodeDetector QRCode;


string QRcode_Detecting(Mat img)
{
    string QRcode_Info;
    QRcode_Info = QRCode.detectAndDecode(img);
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
