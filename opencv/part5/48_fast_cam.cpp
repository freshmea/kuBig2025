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
    Ptr<Feature2D> feature = ORB::create();
    vector<KeyPoint> keypoints;
    // vector<Point2f> corners;
    Mat img, gray_img, desc;
    while (true)
    {
        cap >> img;
        cvtColor(img, gray_img, COLOR_BGR2GRAY);
        // FAST(gray_img, keypoints, 60, true);
        // goodFeaturesToTrack(gray_img, corners, 1000, 0.01, 10);
        // feature->detect(img, keypoints);
        // feature->compute(img, keypoints, dst);
        feature->detectAndCompute(img, noArray(), keypoints, desc);
        drawKeypoints(img, keypoints, img, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        // for (auto &k : keypoints)
        // {
        //     circle(img, Point(cvRound(k.pt.x), cvRound(k.pt.y)), 5, red, 2);
        // }
        // for (auto &p : corners)
        // {
        //     circle(img, Point(p.x, p.y), 5, red, 2);
        // }

        imshow("img", img);
        if (waitKey(33) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}
