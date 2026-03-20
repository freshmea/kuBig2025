# bowlingRay

`bowlingRay`는 기존 `c_example/bowling`의 볼링 점수 계산 규칙을 유지하면서, 입력과 화면 표시를 `raylib` 기반 GUI로 옮긴 예제입니다.

이 문서는 아래 내용을 설명합니다.

- 프로젝트 목적
- 필요한 시스템 라이브러리와 폰트 설치 방법
- 폴더 및 파일 구성
- CMake 구성 방식
- 빌드 및 실행 방법
- 화면 동작 방식
- 문제 해결 방법

## 1. 개요

기존 `c_example/bowling`은 콘솔에서 동작하는 볼링 게임입니다. `bowlingRay`는 같은 점수 규칙을 사용하지만 다음 부분이 다릅니다.

- 점수판을 GUI로 표시합니다.
- 마우스로 쓰러뜨린 핀 수를 선택합니다.
- 한글 UI를 위해 시스템 한글 폰트를 직접 로드합니다.
- 데이터베이스 저장 기능은 포함하지 않고 게임 플레이와 시각화에 집중합니다.

핵심 목표는 `raylib`를 이용해 C 기반 GUI 프로그램을 가장 단순한 구조로 만드는 것입니다.

## 2. 시스템 요구 사항

Linux 환경을 기준으로 작성되었습니다.

필수 요소는 다음과 같습니다.

- GCC 또는 Clang 같은 C 컴파일러
- CMake 3.10 이상
- `make`
- OpenGL 및 X11 계열 런타임 라이브러리
- `raylib` 개발 라이브러리
- 한글 표시를 위한 시스템 폰트

현재 `bowlingRay`는 `raylib` 헤더와 라이브러리가 시스템 전역 경로에 설치되어 있다고 가정합니다.

찾는 경로는 다음과 같습니다.

- 헤더: `/usr/local/include` 또는 `/usr/include`
- 라이브러리: `/usr/local/lib` 또는 `/usr/lib`

## 3. raylib 설치 방법

이 저장소 작업 기준으로는 Ubuntu 패키지 저장소에서 원하는 `raylib` 개발 패키지를 바로 찾기 어려울 수 있습니다. 그래서 소스 설치 방식을 사용했습니다.

### 3.1 소스 코드 받기

```bash
git clone --depth 1 https://github.com/raysan5/raylib.git /tmp/raylib
```

### 3.2 raylib 빌드

이 환경에서는 `src/Makefile` 기반 설치를 사용했습니다.

```bash
cd /tmp/raylib/src
make PLATFORM=PLATFORM_DESKTOP -j"$(nproc)"
```

### 3.3 시스템 전역 설치

```bash
cd /tmp/raylib/src
sudo make PLATFORM=PLATFORM_DESKTOP install
```

설치가 끝나면 보통 다음 파일이 생성됩니다.

- `/usr/local/include/raylib.h`
- `/usr/local/include/raymath.h`
- `/usr/local/include/rlgl.h`
- `/usr/local/lib/libraylib.a`

### 3.4 설치 확인

```bash
ls -l /usr/local/include/raylib.h
ls -l /usr/local/lib/libraylib.a
```

## 4. 한글 폰트 설치 및 사용 방식

`raylib` 기본 폰트는 ASCII 위주라서 한글이 깨질 수 있습니다. 그래서 `bowlingRay`는 실행 시 시스템 한글 폰트를 직접 로드합니다.

코드에서 우선적으로 확인하는 폰트 경로는 다음과 같습니다.

- `/usr/share/fonts/truetype/nanum/NanumGothic.ttf`
- `/usr/share/fonts/truetype/nanum/NanumBarunGothic.ttf`
- `/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc`
- `/usr/share/fonts/opentype/noto/NotoSansCJK-Bold.ttc`

Ubuntu 계열에서는 보통 아래 패키지로 해결됩니다.

```bash
sudo apt update
sudo apt install fonts-nanum fonts-noto-cjk
```

설치 확인 예시는 다음과 같습니다.

```bash
fc-list :lang=ko file family | head
```

## 5. 폴더 구성

`bowlingRay` 폴더 구조는 다음과 같습니다.

```text
c_example/bowlingRay/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── board.h
│   └── bowling.h
└── src/
    ├── board.c
    ├── bowling.c
    └── main.c
```

각 파일의 역할은 다음과 같습니다.

### `include/bowling.h`

- 점수 구조체 `Score`
- 게임 상태 구조체 `BowlingGame`
- 점수 계산 및 진행 함수 선언

### `include/board.h`

- 화면 그리기 함수 선언
- 폰트 리소스 초기화 및 해제 함수 선언
- 버튼 hit-test 함수 선언

### `src/bowling.c`

- 점수 초기화
- 스트라이크, 스페어, 10프레임 보너스를 포함한 누적 점수 계산
- 현재 프레임과 투구 진행 상태 관리

### `src/board.c`

- raylib 기반 화면 렌더링
- 점수판, 레인, 버튼, 종료 화면 출력
- 한글 폰트 로딩 및 텍스트 렌더링 처리

### `src/main.c`

- 애플리케이션 진입점
- 이름 입력 화면, 플레이 화면, 종료 화면 전환
- 마우스 입력 처리

### `CMakeLists.txt`

- `bowlingRay` 실행 파일 타깃 정의
- 시스템 전역에 설치된 `raylib` 라이브러리 검색
- 헤더 포함 경로와 링크 라이브러리 지정

## 6. CMake 구성 설명

현재 `c_example/bowlingRay/CMakeLists.txt`는 다음 방식으로 동작합니다.

1. `find_library()`로 `raylib` 또는 `libraylib` 이름의 라이브러리를 찾습니다.
2. `include`, `/usr/local/include`, `/usr/include`를 include path에 넣습니다.
3. `raylib` 외에 Linux 데스크톱 링크에 필요한 기본 시스템 라이브러리를 함께 연결합니다.

현재 링크 항목은 다음과 같습니다.

- `GL`
- `m`
- `pthread`
- `dl`
- `rt`
- `X11`
- `c`

이 구성은 현재 Linux 데스크톱 환경에서 정적 `libraylib.a`를 링크하기 위한 설정입니다.

## 7. 루트 프로젝트와의 연결 방식

루트 `CMakeLists.txt`에서는 아래처럼 `bowlingRay`를 하위 프로젝트로 추가합니다.

```cmake
add_subdirectory(c_example/bowlingRay)
```

즉, 전체 프로젝트를 한 번에 빌드하면 `bowlingRay` 타깃도 함께 생성됩니다.

## 8. 빌드 방법

저장소 루트에서 이미 `build` 디렉터리를 사용 중이라면 전체 프로젝트 빌드로 충분합니다.

```bash
cd /home/aa/kuBig2025
cmake -S . -B build
cmake --build build
```

`bowlingRay`만 빌드하고 싶다면 다음처럼 타깃을 지정할 수 있습니다.

```bash
cd /home/aa/kuBig2025
cmake --build build --target bowlingRay
```

빌드가 끝나면 실행 파일은 보통 다음 위치에 생성됩니다.

```text
build/c_example/bowlingRay/bowlingRay
```

## 9. 실행 방법

```bash
cd /home/aa/kuBig2025/build/c_example/bowlingRay
./bowlingRay
```

실행 후 동작은 다음 순서입니다.

1. 이름 입력 화면이 표시됩니다.
2. 플레이어 이름을 입력하고 게임을 시작합니다.
3. 각 투구마다 쓰러뜨린 핀 수를 버튼으로 선택합니다.
4. 점수판이 프레임별로 갱신됩니다.
5. 게임 종료 후 최종 점수가 표시됩니다.
6. 다시 시작 버튼으로 새 게임을 시작할 수 있습니다.

## 10. 입력 방법

### 이름 입력 화면

- 키보드로 이름 입력
- `Backspace`로 삭제
- `Enter` 또는 시작 버튼 클릭으로 게임 시작

### 플레이 화면

- 마우스로 핀 수 버튼 클릭
- 현재 프레임과 투구 상태에 따라 선택 가능한 최대 핀 수가 자동 제한됨

### 종료 화면

- 다시 시작 버튼 클릭
- 또는 `Enter` 입력으로 첫 화면 복귀

## 11. 점수 로직 설명

점수 계산은 기존 `c_example/bowling` 로직을 기준으로 유지했습니다.

- 1~9프레임: 일반 볼링 규칙 적용
- 스트라이크: 다음 두 투구를 보너스로 합산
- 스페어: 다음 한 투구를 보너스로 합산
- 10프레임: 스트라이크 또는 스페어 시 보너스 투구 허용

`src/bowling.c`가 이 규칙을 담당합니다.

## 12. 시스템 구성 파일 사용 방법

이 프로젝트에서 실제로 중요한 시스템 구성 요소는 아래 세 가지입니다.

### A. 시스템 라이브러리 경로

`raylib`는 시스템 전역에 설치되어 있어야 하며, CMake는 아래 경로에서 라이브러리를 검색합니다.

- `/usr/local/lib`
- `/usr/lib`

헤더는 아래 경로를 검색합니다.

- `/usr/local/include`
- `/usr/include`

### B. 시스템 폰트 경로

한글 표시를 위해 아래 경로 중 하나에 한글 폰트가 있어야 합니다.

- `/usr/share/fonts/truetype/nanum/NanumGothic.ttf`
- `/usr/share/fonts/truetype/nanum/NanumBarunGothic.ttf`
- `/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc`
- `/usr/share/fonts/opentype/noto/NotoSansCJK-Bold.ttc`

### C. 루트 CMake 구성

루트 프로젝트에서 `add_subdirectory(c_example/bowlingRay)`가 활성화되어 있어야 전체 빌드에 포함됩니다.

## 13. 자주 발생하는 문제와 해결 방법

### 문제 1. `raylib.h: No such file or directory`

원인:
`raylib` 헤더가 시스템에 설치되지 않았거나 설치 경로가 다릅니다.

해결:

- `/usr/local/include/raylib.h` 존재 여부 확인
- `raylib`를 다시 설치
- 필요하면 `c_example/bowlingRay/CMakeLists.txt`의 include path 수정

### 문제 2. `libraylib.a` 또는 `raylib` 라이브러리를 찾지 못함

원인:
라이브러리 경로가 현재 CMake 검색 경로와 다릅니다.

해결:

- `/usr/local/lib/libraylib.a` 확인
- 다른 경로에 설치했다면 `find_library()` 검색 경로 수정

### 문제 3. 한글이 깨져 보임

원인:
한글 지원 폰트가 설치되지 않았거나 폰트 경로가 다릅니다.

해결:

- `fonts-nanum`, `fonts-noto-cjk` 설치
- `fc-list :lang=ko`로 폰트 존재 확인
- `src/board.c`의 폰트 경로 목록 수정

### 문제 4. VS Code에서 빨간 밑줄이 보이는데 실제 빌드는 성공함

원인:
에디터의 정적 분석기가 시스템 헤더 경로를 아직 모를 수 있습니다.

해결:

- `compile_commands.json`이 생성되도록 CMake 구성 사용
- VS Code C/C++ 설정 또는 CMake Tools 구성을 통해 include 경로 동기화

## 14. 확장 아이디어

현재 버전은 가장 단순한 GUI 예제입니다. 다음 확장이 가능합니다.

- 애니메이션 추가
- 효과음 추가
- DB 저장 기능 통합
- 플레이 기록 저장 및 불러오기
- 키보드 조작 추가

## 15. 요약

`bowlingRay`를 사용하려면 아래 세 가지가 핵심입니다.

1. `raylib`를 시스템 전역에 설치한다.
2. 한글 폰트를 시스템에 설치한다.
3. 루트 프로젝트에서 CMake 빌드를 수행한다.

이 세 가지가 준비되면 `build/c_example/bowlingRay/bowlingRay` 실행 파일로 바로 GUI 볼링 예제를 실행할 수 있습니다.
