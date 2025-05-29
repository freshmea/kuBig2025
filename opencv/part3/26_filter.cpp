// ls /dev/vi*
// v4l2-ctl --list-devices
// v4l2-ctl -d /dev/video0 --list-formats-ext
// sudo usermod -aG video $USER

#include </home/aa/kuBig2025/opencv/part2/color.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

String folderPath = "/home/aa/kuBig2025/opencv/data/";

int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cerr << "동영상 파일이 없습니다!" << endl;
    }
    cout << "Frame width: " << cvRound(cap.get(CAP_PROP_FRAME_WIDTH)) << endl;
    cout << "Frame height: " << cvRound(cap.get(CAP_PROP_FRAME_HEIGHT)) << endl;
    auto fps = cap.get(CAP_PROP_FPS);
    cout << "fps : " << cvRound(fps) << endl;

    Mat frame;
    Mat filter_frame;

    float data[] = {-1, -1, 0, -1, 0, 1, 0, 1, 1};
    Mat emboss(3, 3, CV_32FC1, data);

    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break; // 마지막 프레임 처리
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        filter2D(frame, filter_frame, -1, emboss, Point(-1, -1), 0, BORDER_REPLICATE);
        imshow("frame", filter_frame);
        if (waitKey(1000 / fps) == 27) // fps 조절 숫자.
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
