// 파일 경로: /home/aa/kuBig2025/opencv_test/zmq_1.cpp
#include <cerrno> // errno 사용을 위해 추가 (unlink 오류 확인용)
#include <iostream>
#include <string>   // std::string 사용을 위해 추가
#include <unistd.h> // unlink 함수 사용을 위해 추가
#include <zmq.hpp>  // C++ 바인딩 사용
using namespace std;
int main(void)
{
    // ZeroMQ 컨텍스트 생성
    zmq::context_t context(1);

    // REP 소켓 생성 (서버)
    zmq::socket_t responder(context, zmq::socket_type::rep); // C++ 스타일 소켓 타입 지정

    const char *ipc_uri_path = "ipc:///tmp/zmq_ipc_test"; // ZeroMQ 바인딩용 경로
    const char *raw_ipc_file_path = "/tmp/zmq_ipc_test";  // unlink용 실제 파일 경로
    // // bind 호출 전에 기존 IPC 파일 삭제 시도
    if (unlink(raw_ipc_file_path) == 0)
    {
        cout << "경고: 기존 IPC 파일 '" << raw_ipc_file_path << "'이(가) 삭제되었습니다." << endl;
    }
    else if (errno != ENOENT) // ENOENT는 파일이 없음을 의미
    {
        perror("경고: 기존 IPC 파일 삭제 시도 중 오류 발생");
        // 이 경우 bind가 실패할 가능성이 있음
        return 1; // 오류 발생 시 프로그램 종료
    }

    try
    {
        // 소켓을 IPC 경로에 바인딩
        responder.bind(ipc_uri_path);
        // 이 메시지가 출력되어야 정상적으로 바인딩 된 것임
        cout << "ZMQ REP 서버가 " << ipc_uri_path << "에 바인딩되었습니다." << endl;
        while (true)
        {
            // 클라이언트로부터 메시지 수신
            zmq::message_t request;
            zmq::recv_result_t result = responder.recv(request, zmq::recv_flags::none);

            if (result && result.value() > 0)
            {
                std::string received_msg = request.to_string();
                cout << "메시지 수신: " << received_msg << endl;
                // '작업' 수행
                sleep(1); // 작업 수행

                // 클라이언트에 응답 전송
                std::string reply_str = "World";
                zmq::message_t reply(reply_str.begin(), reply_str.end());
                responder.send(reply, zmq::send_flags::none);
                cout << "응답 전송: " << reply_str << endl;
            }
            else
            {
                cerr << "메시지 수신 실패 또는 빈 메시지." << endl;
                if (zmq_errno() == ETERM)
                {
                    cerr << "컨텍스트 종료로 인해 수신 중단." << endl;
                    break;
                }
                sleep(1);
            }
        }
    }
    catch (const zmq::error_t &e)
    {
        cerr << "치명적 오류: ZeroMQ 예외 발생!" << endl;
        cerr << "오류 메시지: " << e.what() << endl;
        cerr << "ZeroMQ 오류 코드: " << e.num() << endl;
        if (e.num() == EADDRINUSE)
        {
            cerr << "상세: 주소 '" << ipc_uri_path << "'가 이미 사용 중입니다. IPC 파일 '" << raw_ipc_file_path << "'이(가) 다른 프로세스에 의해 사용 중이거나, 이전 실행에서 남은 파일일 수 있습니다." << endl;
            cerr << "조치 제안: 다른 프로세스가 해당 IPC 파일을 사용하고 있지 않은지 확인하거나, '" << raw_ipc_file_path << "' 파일을 수동으로 삭제한 후 다시 시도해 보세요." << endl;
        }
        else if (e.num() == EACCES)
        {
            cerr << "상세: IPC 파일 '" << raw_ipc_file_path << "'에 대한 접근 권한이 없습니다. 파일 권한을 확인하세요." << endl;
        }
        // 여기에 다른 특정 ZMQ 오류 코드에 대한 처리를 추가할 수 있습니다.
        return 1;
    }
    catch (const std::exception &e)
    {
        cerr << "치명적 오류: 일반 C++ 예외 발생!" << endl;
        cerr << "오류 메시지: " << e.what() << endl;
        return 1;
    }

    return 0;
}