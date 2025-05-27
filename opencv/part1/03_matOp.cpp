#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2025/opencv/data/";

int main()
{
    Mat img;
    Mat img2(100, 200, CV_8UC1);
    Mat img3(100, 200, CV_8UC3, Scalar(0, 0, 255)); // 빨간색  rgb X  bgr O

    // imshow("img", img);
    imshow("img2", img2);
    imshow("img3", img3);
    waitKey();
    return 0;
}
