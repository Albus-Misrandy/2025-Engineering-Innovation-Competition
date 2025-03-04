#include <iostream>
#include "Image_Processing/image_processing.h"
#include "Socket_transmit/socket_transmit.h"
#include "QRcode_Target/QRcode.h"
#include "Serial_Port/uart_setting.h"

using namespace std;

int main()
{
    string path = "/home/albus/2025-Engineering-Innovation-Competition/Vision_System/picture_and_video/Target_test.mp4";
    // VideoCapture cap1(path);
    // Mat img = imread(path);
    // QRcode_Detecting(img);

    VideoCapture cap1(0);
    VideoCapture cap2(path);
    image_processing Img_Processor;
    uart_port Serial;
    socket_transmission Image_transmitter;
    vector<int> num;
    Mat mv1, mv2;
    // Serial.uart_setting_init();
    // int socket_checking = Image_transmitter.socket_check();
    // int socket_isInit = Image_transmitter.socket_init();
    // int client_isConnected = Image_transmitter.check_client();
    // if (!cap.isOpened()) {
    //     cerr << "无法打开摄像头！" << endl;
    //     return -1;
    // }
    while (true)
    {
        cap1.read(mv1);
        cap2.read(mv2);
        Mat pre = Img_Processor.QRcode_Processing(mv1);
        string range = QRcode_Detecting(mv1, pre);
        if(!range.empty())
        {
            int isQRcode = 1;
            Serial.uart_send_int(isQRcode);
            // cout<<range<<endl;
            num = extractDigits(range);
            cout<<num.size()<<endl;
            Serial.uart_send_int_vector(num);
                // vector<int> Color_select = Img_Processor.Select_Color(num[i]);
                // Mat process_img = Img_Processor.Target_detect_processing(mv2, Color_select);
                // vector<Point3f> Targets = Img_Processor.Target_Positioning(process_img, mv2);
        // Image_transmitter.wifi_transmit_image(mv);
        // Image_transmitter.double_data_transmit(6.89);
        }
        imshow("QRcode", mv1);
        waitKey(1);
    }

}