#include <iostream>
#include <string>
#include <unistd.h>
#include <zmq.hpp>

using namespace std;
using namespace zmq;

int main()
{
    context_t context(1);
    socket_t responder(context, socket_type::rep);
    const char *ipc_file_path = "/tmp/zmq_server";
    if (unlink(ipc_file_path) == -1 && errno != ENOENT)
    {
        cerr << "에러 IPC 파일 삭제: " << strerror(errno) << endl;
        return 1;
    }
    responder.bind("ipc://" + string(ipc_file_path));
    cout << "서버가 IPC 소켓에 바인딩되었습니다: " << ipc_file_path << endl;
    while (true)
    {
        message_t request;
        recv_result_t result = responder.recv(request, recv_flags::none);
        if (result && result.value() > 0)
        {
            string received_msg = request.to_string();
            cout << "받은 메시지: " << received_msg << endl;
            string reply_msg = "메시지 수신됨: " + received_msg; // echo 메시지
            responder.send(message_t(reply_msg), send_flags::none);
        }
    }
    return 0;
}