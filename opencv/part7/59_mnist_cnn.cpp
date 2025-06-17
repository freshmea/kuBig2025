#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <unistd.h>
#include <zmq.hpp>

using namespace std;
using namespace zmq;
using namespace cv;
using namespace cv::dnn;

void on_mouse(int event, int x, int y, int flags, void *userdata);

int main()
{
    context_t context(1);
    socket_t requester(context, socket_type::req);
    const char *ipc_file_path = "/tmp/zmq_server";
    requester.connect("ipc://" + string(ipc_file_path));
    cout << "클라이언트가 IPC 소켓에 연결되었습니다: " << ipc_file_path << endl;
    int request_count = 0;
    Mat img = Mat::zeros(400, 400, CV_8UC1);
    imshow("img", img);
    setMouseCallback("img", on_mouse, (void *)&img);
    waitKey(1000);
    while (true)
    {
        string request_str = "클라이언트에서 간다~ " + to_string(request_count++);
        message_t request_msg(request_str.begin(), request_str.end());
        // recv_result_t result = requester.send(request_msg, send_flags::none);
        // message_t reply_msg;
        // recv_result_t reply_result = requester.recv(reply_msg, recv_flags::none);

        // if (reply_result && reply_result.value() > 0)
        // {
        //     string reply_str = reply_msg.to_string();
        //     cout << "서버로부터 받은 메시지: " << reply_str << endl;
        // }
        // else
        // {
        //     cerr << "서버로부터 응답을 받지 못했습니다." << endl;
        // }
        waitKey(30);
    }
    return 0;
}

void on_mouse(int event, int x, int y, int flags, void *userdata)
{
    Mat &img = *(Mat *)userdata;
    static Point ptPrev = Point(-1, -1);
    static bool isDrawing = false;
    if (event == EVENT_LBUTTONDOWN)
    {
        ptPrev = Point(x, y);
        isDrawing = true;
    }
    else if (event == EVENT_LBUTTONUP)
    {
        ptPrev = Point(-1, -1);
        isDrawing = false;
    }
    else if (event == EVENT_MOUSEMOVE && ptPrev.x >= 0 && ptPrev.y >= 0 && isDrawing)
    {
        line(img, ptPrev, Point(x, y), Scalar(255), 30, LINE_AA, 0);
        ptPrev = Point(x, y);
        imshow("img", img);
    }
}