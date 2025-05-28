#include </home/aa/kuBig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2025/opencv/data/";

int main()
{
    Mat img = imread(folderPath + "lenna.bmp");
    namedWindow("img");
    auto i = getTickCount();
    int keycode;
    while (true)
    {
        keycode = waitKey(10);
        cout << "keycode: " << keycode << endl;
        cout << "i: " << i << endl;
        cout << "fps: " << getTickFrequency() / (getTickCount() - i) << endl;

        if (keycode == 'v' || keycode == 'V')
        {
            img = ~img;
            imshow("img", img);
        }
        if (keycode == 27)
            break;
        i = getTickCount();
    }
    destroyAllWindows();
    return 0;
}
