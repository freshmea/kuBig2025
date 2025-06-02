#include </home/aa/kuBig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2025/opencv/data/";

int main()
{
    VideoCapture cap(0);
    vector<KeyPoint> keypoints;
    Mat img, gray_img;
    while (true)
    {
        cap >> img;
        cvtColor(img, gray_img, COLOR_BGR2GRAY);
        FAST(gray_img, keypoints, 60, true);
        for (auto &k : keypoints)
        {
            circle(img, Point(cvRound(k.pt.x), cvRound(k.pt.y)), 5, red, 2);
        }

        imshow("img", img);
        if (waitKey(33) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}
