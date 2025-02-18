#include <iostream>
#include "Image_Processing/image_processing.h"
#include "Socket_transmit/socket_transmit.h"
#include "QRcode_Target/QRcode.h"

using namespace std;

int main()
{
    // string path = "/home/albus/2025-Engineering-Innovation-Competition/Vision_System/picture_and_video/QRcode.png";
    // // VideoCapture cap1(path);
    // Mat img = imread(path);
    // image_processing Img_Processor;

    // // Mat process_img = Img_Processor.Target_detect_processing(img);
    // // vector<Point3f> Targets = Img_Processor.Target_Positioning(process_img, img);

    // QRcode_Detecting(img);

    // // cout<<"Targets:"<<Targets<<endl;
    // // imshow("img", process_img);
    // imshow("Img", img);
    // waitKey(0);
    // return 0;

    VideoCapture cap1(0);
    image_processing Img_Processor;
    socket_transmission Image_transmitter;
    string range;
    // int socket_checking = Image_transmitter.socket_check();
    // int socket_isInit = Image_transmitter.socket_init();
    // int client_isConnected = Image_transmitter.check_client();
    // if (!cap.isOpened()) {
    //     cerr << "无法打开摄像头！" << endl;
    //     return -1;
    // }
    while (true)
    {
        Mat mv;
        cap1.read(mv);

        Mat pre = Img_Processor.QRcode_Processing(mv);
        range = QRcode_Detecting(pre);
        if(!range.empty())
        {
            // cout<<range<<endl;
            vector<int> num = extractDigits(range);
            // cout<<num[0]<<endl;
        }
        // Image_transmitter.wifi_transmit_image(mv);
        // Image_transmitter.double_data_transmit(6.89);

        imshow("camera", mv);
        waitKey(1);
    }
    
}