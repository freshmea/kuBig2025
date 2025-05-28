#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); // V4L2 백엔드 사용
    if (!cap.isOpened())
    {
        cerr << "카메라를 열 수 없습니다! V4L2 백엔드 실패" << endl;
    }

    // YUYV 포맷 및 해상도 설정
    // cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc('Y', 'U', 'Y', 'V'));
    // cap.set(CAP_PROP_FRAME_WIDTH, 640);
    // cap.set(CAP_PROP_FRAME_HEIGHT, 480);
    // cap.set(CAP_PROP_FPS, 30);
    // cap.set(CAP_PROP_BUFFERSIZE, 1);

    // 설정값 확인
    cout << "Frame width: " << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << "Frame height: " << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
    double fps = cap.get(CAP_PROP_FPS);
    cout << "FPS: " << fps << endl;
    cout << "FourCC: " << cap.get(CAP_PROP_FOURCC) << endl;

    Mat frame;
    int frame_count = 0;
    while (frame_count < 100) // 최대 100프레임 시도
    {
        // if (!cap.read(frame))
        // {
        //     cerr << "프레임 읽기 실패!" << endl;
        //     continue;
        // }
        // if (frame.empty() || frame.cols != 640 || frame.rows != 480)
        // {
        //     cerr << "잘못된 프레임: " << frame.cols << "x" << frame.rows << endl;
        //     continue;
        // }
        cap >> frame;

        imshow("frame", frame);
        if (waitKey(1000 / (fps > 0 ? fps : 30)) == 27) // ESC 키로 종료
            break;

        frame_count++;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}