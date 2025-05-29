# OpenCV 교육 과정

---

## 2025-05-27

---

- 1교시
  - OpenCV 소개
  - OpenCV의 역사 및 발전 과정
  - OpenCV의 주요 기능 및 활용 분야
- 2교시
  - 프로젝트에서의 활용 형태 및 예시
  - OpenCV 설치 및 환경 설정
  - 이미지 처리 - 빛, 양자화, 샘플링
  - 기본적인 이미지 처리 기법 소개 - imread, imshow, namedWindow, waitKey
- 3교시
  - openCV 의 옵션 flags
    - ENUM class 를 활용한 `int flag` ( ex imread IMREAD_COLOR  IMREAD_GRAYSCALE )
    - Vector 형식의 `vector<int> flags` ( ex: imwrite jpeg_quality )
  - OpenCV의 이미지 입출력 - imwrite jpeg
- 4교시
  - 기본 클래스 Point_<> 클래스
  - 기본 클래스 Size_<> 클래스
- 5교시
  - 기본 클래스 Rect_<> 클래스
  - 기본 클래스 Scalar_<> 클래스
  - InputArray, OutputArray, InputOutputArray
- 6교시
  - Mat 클래스
    - Mat 클래스의 생성자
    - Mat 클래스의 속성 (rows, cols, channels, type)
    - Mat 클래스의 데이터 접근 (at, ptr)
    - Mat 클래스의 복사 및 할당
- 7교시
  - Mat 클래스의 연산
    - Mat 클래스의 연산자 오버로딩
    - Mat 클래스의 기본 연산 (덧셈, 뺄셈, 곱셈, 나눗셈)
    - Mat 클래스의 비교 연산
- 8교시
  - 간단한 video 처리
    - VideoCapture, VideoWriter
    - imshow, waitKey
    - 동영상 재생 및 저장
  - 정리

---

## 2025-05-28

---

- 1교시
  - 복습
  - Video 처리 - 에러 처리, release, 동영상 저장(VideoWriter), fourcc
- 2교시
  - drawing
    - 선 (line), 원(circle), 사각형(rectangle), 타원(ellipse)
- 3교시
  - 글자 (putText)
  - 한글글자 (freetype) - 래퍼함수 작성
- 4교시
  - 마우스 이벤트(setMouseCallback)
    - 마우스 이벤트의 종류 및 처리 방법
    - 마우스 이벤트를 선 그리기
- 5교시
  - 트랙바 (trackbar)
    - 트랙바의 생성 및 사용법
    - 트랙바를 이용한 이미지 필터링
- 6교시
  - 파일저장 fileStorage
    - XML, YAML 파일 저장
    - FileStorage 클래스의 사용법
- 7교시
  - 웹캠 abko 설정
  - 캠-사각형 그리기 코드 작성
- 8교시
  - 일경험 안내
  - 정리
