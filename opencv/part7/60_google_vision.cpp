#include "opencv2/opencv.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace cv;
using namespace cv::dnn;
using namespace std;

String folderPath = "/home/aa/kuBig2025/opencv/part7/";

int main()
{
    vector<String> files;
    files.push_back("beagle.jpg");
    files.push_back("cup.jpg");
    files.push_back("pineapple.jpg");
    files.push_back("scooter.jpg");
    files.push_back("space_shuttle.jpg");

    vector<Mat> imgs;
    for (auto &f : files)
        imgs.push_back(imread(folderPath + f));

    Net net = readNet(
        "/home/aa/kuBig2025/opencv/part7/bvlc_googlenet.caffemodel",
        "/home/aa/kuBig2025/opencv/part7/deploy.prototxt");

    return 0;
}