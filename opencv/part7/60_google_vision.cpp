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
    // 그림 파일 가지고 오기
    vector<String> files;
    files.push_back("beagle.jpg");
    files.push_back("cup.jpg");
    files.push_back("pineapple.jpg");
    files.push_back("scooter.jpg");
    files.push_back("space_shuttle.jpg");

    vector<Mat> imgs;
    for (auto &f : files)
        imgs.push_back(imread(folderPath + f));

    // 모델 파일 로드
    Net net = readNet(
        folderPath + "bvlc_googlenet.caffemodel",
        folderPath + "deploy.prototxt");

    ifstream fp(folderPath + "classification_classes_ILSVRC2012.txt");

    // 클래스 정보 로드
    vector<String> classNames;
    String name;
    while (!fp.eof())
    {
        getline(fp, name);
        if (name.length())
            classNames.push_back(name);
    }

    // 추론
    int i = 0;
    for (auto &img : imgs)
    {
        Mat inputBlob = blobFromImage(img, 1, Size(224, 224), Scalar(104, 117, 123));
        net.setInput(inputBlob, "data");
        Mat prob = net.forward(); // 실제 연산라인.

        double maxVal;
        Point maxLoc;
        minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);
        String str = format("%s (%4.2lf%%)", classNames[maxLoc.x].c_str(), maxVal * 100);
        putText(img, str, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255), 2);
        imshow("img" + to_string(++i), img);
    }
    waitKey();

    return 0;
}