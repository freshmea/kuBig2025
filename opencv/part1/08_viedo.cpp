#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // 디버깅 로그 활성화
    setenv("OPENCV_LOG_LEVEL", "DEBUG", 1);

    // GStreamer 파이프라인
    VideoCapture cap("v4l2src device=/dev/video0 ! image/jpeg,width=1280,height=720,framerate=30/1 ! jpegdec ! videoconvert ! appsink", cv::CAP_GSTREAMER);
    if (!cap.isOpened())
    {
        cerr << "카메라를 열 수 없습니다!" << endl;
        return -1;
    }

    // 설정값 확인
    cout << "Frame width: " << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "Frame height: " << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
    double fps = cap.get(CAP_PROP_FPS);
    cout << "FPS: " << fps << endl;

    Mat frame;
    while (true)
    {
        cap >> frame;
        if (frame.empty() || frame.cols != 1280 || frame.rows != 720)
        {
            cerr << "잘못된 프레임: " << frame.cols << "x" << frame.rows << endl;
            continue;
        }

        imshow("frame", frame);
        if (waitKey(1000 / (fps > 0 ? fps : 30)) == 27) // ESC 키로 종료
            break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}