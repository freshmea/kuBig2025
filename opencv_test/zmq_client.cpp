// 파일 경로: /home/aa/kuBig2025/opencv_test/zmq_2.cpp
#include <iostream>
#include <string> // std::string 사용을 위해 추가
#include <unistd.h>
#include <vector>  // zmq::message_t 생성 시 사용 가능
#include <zmq.hpp> // C++ 바인딩 사용

int main(void)
{
    // ZeroMQ 컨텍스트 생성
    zmq::context_t context(1);

    // REQ 소켓 생성 (클라이언트)
    zmq::socket_t requester(context, zmq::socket_type::req); // C++ 스타일 소켓 타입 지정

    const char *ipc_path = "ipc:///tmp/zmq_ipc_test"; // 서버의 IPC 경로 (한 번만 정의)

    try
    {
        // 서버에 연결
        requester.connect(ipc_path);
        std::cout << "ZMQ REQ 클라이언트가 " << ipc_path << "에 연결되었습니다..." << std::endl;

        int request_count = 0;

        while (true) // C++에서는 true 사용이 일반적
        {
            // 요청 메시지 생성
            std::string request_str = "Hello from client (요청 " + std::to_string(++request_count) + ")";
            zmq::message_t request_msg(request_str.begin(), request_str.end());

            std::cout << "요청 전송: " << request_str << std::endl;
            requester.send(request_msg, zmq::send_flags::none);

            // 응답 수신
            zmq::message_t reply_msg;
            zmq::recv_result_t result = requester.recv(reply_msg, zmq::recv_flags::none);

            if (result && result.value() > 0)
            {
                std::string reply_str = reply_msg.to_string();
                std::cout << "응답 수신: " << reply_str << std::endl;
            }
            else
            {
                std::cerr << "응답 수신 실패 또는 빈 메시지." << std::endl;
                if (zmq_errno() == ETERM)
                { // 컨텍스트가 종료된 경우
                    std::cerr << "컨텍스트 종료로 인해 수신 중단." << std::endl;
                    break;
                }
                // 간단한 재시도 전 대기 또는 다른 오류 처리
                sleep(1); // 잠시 대기 후 계속
                continue;
            }

            // 5초 대기
            std::cout << "다음 요청까지 5초 대기..." << std::endl
                      << std::endl;
            sleep(5);
        }
    }
    catch (const zmq::error_t &e)
    {
        // ZeroMQ 관련 예외 처리
        std::cerr << "ZeroMQ 오류 발생: " << e.what() << " (오류 코드: " << e.num() << ")" << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        // 기타 표준 예외 처리
        std::cerr << "일반 오류 발생: " << e.what() << std::endl;
        return 1;
    }

    // zmq::socket_t 와 zmq::context_t 는 RAII를 따르므로,
    // main 함수 종료 시 자동으로 소멸자에서 close 및 destroy가 호출됩니다.
    return 0;
}
