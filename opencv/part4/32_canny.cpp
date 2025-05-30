#include </home/aa/kuBig2025/opencv/part2/color.hpp>
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "lenna.bmp", IMREAD_GRAYSCALE);
    Mat edge;
    int low_v, high_v;
    namedWindow("img1");
    createTrackbar("lowedge", "img1", &low_v, 255);
    createTrackbar("highedge", "img1", &high_v, 255);

    // vector img show 코드
    while (true)
    {
        Canny(img, edge, low_v, high_v);
        imshow("img1", edge);
        waitKey(33);
    }
    destroyAllWindows();
    return 0;
}
