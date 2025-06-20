# DL - 딥러닝

---

## 2025-06-13

---

- 1교시
  - 복습
  - 퍼셉트론과 신경세포
  - 딥러닝의 정의
- 2교시
  - tensorflow 소개
  - keras 소개
  - loss function - cost function
- 3교시
  - 순전파와 역전파
  - optimizer - adam, sgd, rmsprop
- 4교시
  - 정리

---

## 2025-06-16

---

- 1교시
  - 복습
  - dropout
- 2교시
  - checkpoint_cb 을 이용한 모델 저장
  - EarlyStopping 을 이용한 조기 종료
- 3교시
  - CNN - Convolutional Neural Network 설명
    - Convolutional Layer
    - Pooling Layer
- 4교시
  - argmax 함수 이용한 결론 만들기
  - 함수 API 를 이용한 중간 weights 값 분석
- 5교시
  - Conv2D, MaxPooling2D 을 이용한 이미지 분류
- 6교시
  - RNN 설명
  - RNN - IMDB 데이터 분석
  - RNN - one-hot encoding 으로 처리 메모리 초과로 200개로 낮춤
- 7교시
  - RNN - embedding 으로 처리
- 8교시
  - LSTM 설명 - Long Short Term Memory
    - LSTM의 구조 - forget gate, input gate, output gate
    - LSTM의 작동 원리 - 셀 상태와 은닉 상태
  - 정리

---

## 2025-06-17

---

- 1교시
  - 복습
  - LSTM 실습
- 2교시
  - custom LSTM 구현
    - LSTMCell 클래스 작성
    - LSTM 모델 작성
    - LSTM 모델 학습 및 평가
  - Bi-directional LSTM 설명
- 3교시
  - 분산 처리 모델 실습(zmq 사용)
    - zmq_server.py 작성 -> tensorflow 모델을 서버로 실행
    - zmq_client.py 작성
    - zmq_image_server.py 작성
    - zmq_image_client.py 작성
- 4교시
  - 분산 처리 모델 실습(zmq 사용)
    - zmq_server.cpp 작성
    - zmq_client.cpp 작성
- 5교시
  - GRU - Gated Recurrent Unit
    - GRU의 구조 - reset gate, update gate
    - GRU의 작동 원리 - 셀 상태와 은닉 상태
    - 실습
- 6교시
  - rnn 에서의 dropout 적용 방법 - GRU
  - rnn 두 개의 층 적용 방법
- 7교시
  - OpenCV 에서 tensorflow 사용법
  - 숫자 인식 모델 훈련
- 8교시
  - zmq + openCV + tensorflow 예제
  - 정리

---

## 2025-06-18

---

- 1교시
  - 복습
  - OpenCV classification - googlenet
- 2교시
  - OpenCV ssd classification - ssd face detection
- 3교시
  - Yolo 설명
    - YOLO의 구조 - Backbone, Neck, Head
    - YOLO의 작동 원리 - Anchor Box, Non-Maximum Suppression
- 4교시
  - YOLOv5 실습
    - python3 detect.py --source 0
    - coco 데이터넷 80개 클래스 설명
- 5교시
  - YOLOv5 커스터마이징
    - 커스터마이징을 위한 데이터 준비
      - 데이터셋 구성 - 이미지와 라벨 파일
      - 라벨링 도구 소개 - LabelImg, Roboflow
    - 커스터마이징을 위한 환경 설정
      - YOLOv5 설치 및 의존성 설치
      - 커스터마이징을 위한 config 파일 수정
  - [모델 학습](https://github.com/ultralytics/yolov5/wiki/Train-Custom-Data)
- 6교시
  - DQN의 하이퍼파라미터 튜닝
- 7교시
  - DQN의 확장
    - Double DQN
    - Dueling DQN
- 8교시
  - DQN의 응용
    - Atari 게임에서의 DQN 적용
    - DQN의 한계와 개선 방안
  - 정리

---

## 2025-06-19

---

- 1교시
  - 복습
  - 프로젝트
- 2교시
  - 프로젝트
- 3교시
  - 프로젝트
- 4교시
  - 프로젝트
- 5교시
  - 생성형 모델 AE - Autoencoder
    - AE의 구조 - Encoder, Decoder
    - AE의 작동 원리 - 재구성 손실
- 6교시
  - VAE - Variational Autoencoder
    - VAE의 구조 - Encoder, Decoder, Latent Space
    - VAE의 작동 원리 - 재구성 손실과 KL 발산
- 7교시
  - tensorboardX 설치 및 사용법
  - tensorboardX 를 이용한 모델 시각화
- 8교시
  - 정리

---

## 2025-06-20

---

- 1교시
  - 복습
  - 인공지능 적용 실습 - 바이브 코딩
- 2교시
  - VsCode 세팅
- 3교시
  - 자동완성 가이드 설정
- 4교시
  - 커밋메세지 가이드 설정
- 5교시
  - copilot 사용법
- 6교시
  - agent 사용법
- 7교시
  - mcp 사용법
- 8교시
  - agent + mcp 사용법
  - 정리
