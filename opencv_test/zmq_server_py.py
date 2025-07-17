import errno
import os
import time

os.environ["CUDA_VISIBLE_DEVICES"] = "-1"  # CUDA 장치를 보이지 않게 설정
import tensorflow as tf
from tensorflow.keras.preprocessing.sequence import pad_sequences

# TensorFlow가 CPU만 사용하도록 명시적으로 설정
# 이 코드는 TensorFlow 관련 작업(예: 모델 로딩) 전에 호출되어야 합니다.
try:
    print(f"Initializing TensorFlow. Version: {tf.__version__}")  # TensorFlow 버전 출력
    physical_devices = tf.config.list_physical_devices("GPU")
    if physical_devices:
        tf.config.set_visible_devices([], "GPU")
        logical_devices = tf.config.list_logical_devices("GPU")
        print(
            f"Num GPUs Available: {len(physical_devices)}, After hiding: {len(logical_devices)}"
        )
    else:
        print("No GPU devices found. Running on CPU.")
except Exception as e:
    print(f"GPU 설정 중 오류 발생 (무시하고 CPU로 진행): {e}")

import zmq

IPC_FILE_PATH = "/tmp/zmq_ipc_test"
MODEL_PATH = "/home/aa/kuBig2025/opencv_test/best-embedding-model.h5"


def run_server():
    ipc_uri_path = f"ipc://{IPC_FILE_PATH}"
    raw_ipc_file_path = IPC_FILE_PATH  # os.unlink용 실제 파일 경로

    context = zmq.Context()
    socket = context.socket(zmq.REP)

    # 서버 시작 전 기존 IPC 파일 삭제 시도
    if os.path.exists(raw_ipc_file_path):
        try:
            os.unlink(raw_ipc_file_path)
            print(f"기존 IPC 파일 '{raw_ipc_file_path}'을(를) 삭제했습니다.")
        except OSError as e:
            error_message = (
                os.strerror(e.errno) if e.errno is not None else "알 수 없는 OS 오류"
            )
            print(
                f"경고: 기존 IPC 파일 '{raw_ipc_file_path}' 삭제 시도 중 오류 발생: {error_message}"
            )
            if e.errno == errno.EACCES:
                print(
                    f"오류: IPC 파일 '{raw_ipc_file_path}' 삭제 권한이 없습니다. 파일 권한을 확인하거나 수동으로 삭제하세요."
                )
                return 1

    # TensorFlow 모델 로드
    model = None
    try:
        print(
            f"TensorFlow 모델 로딩 시도: {MODEL_PATH} (using tf.keras.models.load_model)"
        )
        # tf.keras.models를 사용하여 모델 로드 시도
        model = tf.keras.models.load_model(MODEL_PATH)

        print(f"TensorFlow 모델 '{MODEL_PATH}'을(를) 성공적으로 로드했습니다.")
        model.summary()  # 모델 구조 출력 (선택 사항)
    except AttributeError as ae:
        # tf.keras 접근 관련 AttributeError를 구체적으로 확인
        if "keras" in str(ae).lower() and "tensorflow" in str(ae).lower():
            print(
                f"오류: 'tensorflow' 모듈에서 'keras' 속성을 찾을 수 없습니다. TensorFlow 버전: {tf.__version__}"
            )
            print("TensorFlow 설치가 올바르지 않거나, 환경에 문제가 있을 수 있습니다.")
            print("TensorFlow 2.x 버전이 올바르게 설치되었는지 확인해주세요.")
            print(f"원래 오류 메시지: {ae}")
        else:
            print(f"모델 로딩 중 AttributeError 발생: {ae}")
        print("모델 없이 서버를 계속 진행합니다.")
    except Exception as e:
        print(f"TensorFlow 모델 로딩 중 예기치 않은 오류 발생: {e}")
        print(f"현재 TensorFlow 버전: {tf.__version__}")
        print("모델 없이 서버를 계속 진행합니다.")

    try:
        socket.bind(ipc_uri_path)
        print(f"ZMQ REP 서버가 {ipc_uri_path}에 바인딩되었습니다.")

        while True:
            try:
                message = socket.recv_string()
                print(f"메시지 수신: {message}")

                # 실제 모델 예측 로직 (model이 정상적으로 로드된 경우)
                if model:
                    message = message.split()  # 메시지를 단어 단위로 분할
                    message = [int(word) for word in message if word.isdigit()]
                    val_seq = pad_sequences([message], maxlen=100)
                    result = model.predict(val_seq)
                    reply_str = f"모델 응답: {message}에 대한 처리 결과 (Python CPU server, 모델 로드됨)"
                else:
                    reply_str = f"모델 없음: {message}에 대한 기본 응답 (Python CPU server, 모델 로드 실패 또는 없음)"

                time.sleep(0.1)  # 응답 전송 전 약간의 지연 (디버깅/테스트용)

                socket.send_string(str(result))
                print(f"응답 전송: {result}")

            except zmq.Again:  # 현재 블로킹 소켓에서는 발생하지 않아야 함
                print("메시지 수신 대기 중 (논블로킹, 현재는 발생하지 않아야 함)")
                time.sleep(0.1)
                continue
            except zmq.ZMQError as e:
                if e.errno == zmq.ETERM:
                    print("컨텍스트 종료로 인해 수신 중단.")
                    break
                else:
                    print(
                        f"메시지 수신/송신 중 ZMQ 오류 발생: {e} (오류 코드: {e.errno})"
                    )
                    break

    except zmq.ZMQError as e:
        print(f"치명적 오류: ZeroMQ 예외 발생!")
        print(f"오류 메시지: {e}")
        print(f"ZeroMQ 오류 코드: {e.errno}")
        if e.errno == zmq.EADDRINUSE:
            print(
                f"상세: 주소 '{ipc_uri_path}'가 이미 사용 중입니다. IPC 파일 '{raw_ipc_file_path}'이(가) 다른 프로세스에 의해 사용 중이거나, 이전 실행에서 남은 파일일 수 있습니다."
            )
            print(
                f"조치 제안: 다른 프로세스가 해당 IPC 파일을 사용하고 있지 않은지 확인하거나, '{raw_ipc_file_path}' 파일을 수동으로 삭제한 후 다시 시도해 보세요."
            )
        elif e.errno == errno.EACCES:
            print(
                f"상세: IPC 파일 '{raw_ipc_file_path}'에 대한 접근 권한이 없습니다. 파일 권한을 확인하세요."
            )
        return 1
    except KeyboardInterrupt:
        print("\n사용자에 의해 서버가 중지되었습니다 (Ctrl+C).")
    finally:
        print("서버 리소스 정리 중...")
        socket.close()
        context.term()
        print("ZMQ 소켓 및 컨텍스트가 성공적으로 종료되었습니다.")
        # 애플리케이션 종료 시 IPC 파일 정리 (선택 사항, 주의 필요)
        # if os.path.exists(raw_ipc_file_path):
        #     try:
        #         os.unlink(raw_ipc_file_path)
        #         print(f"종료 시 IPC 파일 '{raw_ipc_file_path}'을(를) 삭제했습니다.")
        #     except OSError as e:
        #         error_message = os.strerror(e.errno) if e.errno is not None else "알 수 없는 OS 오류"
        #         print(f"종료 시 IPC 파일 '{raw_ipc_file_path}' 삭제 실패: {error_message}")
    return 0


if __name__ == "__main__":
    exit_code = run_server()
    if exit_code == 0:
        print("Python ZMQ REP 서버가 성공적으로 종료되었습니다.")
    else:
        print(f"Python ZMQ REP 서버가 오류 코드 {exit_code}(으)로 종료되었습니다.")
    exit(exit_code)
