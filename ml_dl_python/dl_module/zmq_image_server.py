import os

import cv2
import numpy as np
import zmq

IPC_FILE_PATH = "/tmp/zmq_server"


def main():
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    os.unlink(IPC_FILE_PATH) if os.path.exists(IPC_FILE_PATH) else None
    socket.bind(f"ipc://{IPC_FILE_PATH}")
    print(f"ZMQ REP 서버가 {IPC_FILE_PATH}에 바인딩되었습니다")

    try:
        while True:
            # 이미지 수신
            message = socket.recv()
            image = cv2.imdecode(np.frombuffer(message, np.uint8), cv2.IMREAD_COLOR)
            cv2.imshow("Received Image", image)

            socket.send_string(f"예측 결과: 이미지 수신 완료")
            cv2.waitKey(1)
    except KeyboardInterrupt:
        print("서버를 종료합니다.")
    finally:
        socket.close()
        context.term()
        os.unlink(IPC_FILE_PATH)


if __name__ == "__main__":
    main()
