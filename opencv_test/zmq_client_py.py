import random
import time

import zmq


def run_client():
    context = zmq.Context()

    # 서버에 연결할 REQ 소켓 생성
    print("서버에 연결 중...")
    socket = context.socket(zmq.REQ)
    ipc_path = "ipc:///tmp/zmq_ipc_test"
    socket.connect(ipc_path)
    print(f"ZMQ REQ 클라이언트가 {ipc_path}에 연결되었습니다...")

    request_count = 0
    try:
        while True:
            request_count += 1
            message = [random.randint(1, 100) for _ in range(1, 100)]
            message = " ".join(map(str, message))
            print(f"요청 전송: {message}")
            socket.send_string(message)

            # 서버로부터 응답 수신
            reply = socket.recv_string()
            print(f"응답 수신: {reply}")

            # 5초 대기
            print("다음 요청까지 5초 대기...\n")
            time.sleep(5)

    except KeyboardInterrupt:
        print("\n클라이언트 종료 중...")
    finally:
        socket.close()
        context.term()
        print("클라이언트가 종료되었습니다.")


if __name__ == "__main__":
    run_client()
