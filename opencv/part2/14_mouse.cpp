#include </home/aa/kuBig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2025/opencv/data/";

void on_mouse(int event, int x, int y, int flags, void *);

int main()
{
    Mat img = imread(folderPath + "lenna.bmp");
    namedWindow("img");
    setMouseCallback("img", on_mouse);
    auto i = getTickCount();
    int keycode;
    while (true)
    {
        cout << "keycode: " << keycode << endl;
        cout << "i: " << i << endl;
        cout << "fps: " << getTickFrequency() / (getTickCount() - i) << endl;
        i = getTickCount();
        imshow("img", img);
        keycode = waitKey(33);
    }
    destroyAllWindows();
    return 0;
}

void on_mouse(int event, int x, int y, int flags, void *)
{
    switch (event)
    {
    case EVENT_LBUTTONDOWN:
        cout << "마우스 왼쪽 버튼이 눌렸다!" << endl;
        break;
    default:
        cout << "마우스 이벤트!!" << endl;
        break;
    }
}
