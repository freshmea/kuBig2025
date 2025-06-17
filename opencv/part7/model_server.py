import os
import time

import cv2
import numpy as np
import tensorflow as tf
import zmq

IPC_FILE_PATH = "/tmp/zmq_server"


def main():
    # model 로드
    model = tf.keras.models.load_model(
        "/home/aa/kuBig2025/opencv/part7/best-cnn-model.h5"
    )
    print("모델이 성공적으로 로드되었습니다.")
    if not model:
        print("모델 로드에 실패했습니다. 서버를 종료합니다.")
        return
    print(f"모델 구조: {model.summary()}")
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    os.unlink(IPC_FILE_PATH) if os.path.exists(IPC_FILE_PATH) else None
    socket.bind(f"ipc://{IPC_FILE_PATH}")
    print(f"ZMQ REP 서버가 {IPC_FILE_PATH}에 바인딩되었습니다")

    try:
        while True:
            message = socket.recv()
            image = cv2.imdecode(np.frombuffer(message, np.uint8), cv2.IMREAD_GRAYSCALE)
            result = model.predict(image.reshape(-1, 28, 28, 1))
            print(f"예측 결과: {result}")
            socket.send_string(f"예측 결과: {result}")
    except KeyboardInterrupt:
        print("서버를 종료합니다.")
    finally:
        socket.close()
        context.term()
        os.unlink(IPC_FILE_PATH)


if __name__ == "__main__":
    main()
