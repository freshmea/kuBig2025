#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2025/opencv/data/";

int main()
{
    Point_<int> p1(1, 2);
    cout << p1 << endl;
    cout << "x :" << p1.x << "y :" << p1.y << endl;

    Point p2(3, 4);
    Point2f p3(3.12, 4.23);
    Point2d p4(1.1, 2.2);
    cout << p2 << p3 << p4 << endl;

    return 0;
}