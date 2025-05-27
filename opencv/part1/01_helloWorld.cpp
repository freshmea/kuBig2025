#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2025/opencv/data/";

int main()
{
    cout << "hello, world" << endl;

    Mat img = imread(folderPath + "lenna.bmp");
    if (img.empty())
    {
        cerr << "이미지 불러오기 실패!! ";
        return -1;
    }

    // cout << img << endl;
    namedWindow("lenna", WINDOW_AUTOSIZE);
    Size size(640, 480);
    resizeWindow("lenna", size);

    imshow("lenna", img);
    waitKey();

    return 0;
}