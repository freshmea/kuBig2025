# TCPIP

---

## 2025-05-07

---

- 1교시
  - 파이썬 언어 설명
  - 특징 : 인터프리터 언어, 동적 타이핑, 객체 지향 언어, 플랫폼 독립적 언어
  - 장점 : 간결한 문법, 다양한 라이브러리 지원, 커뮤니티가 활발함
- 2교시
  - 파이썬 주의 사항 : indentation, 대소문자 구분, 주석
- 3교시
  - pythonInterpreter 작성, pythonInterpreter2 작성
  - type : int , float, str, list
- 4교시
  - 
- 5교시
  - mqueeue 예제 작성
  - server, client 코드
- 6교시
  - tcp server, tcp client 예제 작성
- 7교시
  - ninja 설정 하는 방법
- 8교시
  - ss -tulpn -socket statictics
  - 옵션 설명

---

## 2025-04-29

---

- 1교시
  - 복습
  - inet_addr 함수 설명
  - inet_pton 함수 설명(iton 함수 사라짐. ipv4, ipv6 모두 지원)
  - inet_ntoa 함수 실습
- 2교시
  - echo_server 예제 작성
- 3교시
  - echo_client 예제 작성
- 4교시
  - 수신된 메시지의 전체 길이를 보장하도록 수정(server, client)
- 5교시
  - ninja 설정
  - op_server 예제 작성
- 6교시
  - op_client 예제 작성
- 7교시
  - udp 설명
  - uecho_server 예제 작성
  - uecho_client 예제 작성
- 8교시
  - boundhost 예제 작성(경계가 존재 한다는 예시)
  - 정리

---

## 2025-04-30

---

- 1교시
  - 복습
  - file_server 작성 - 우아한 종료 halfclose
- 2교시
  - file_client 작성
- 3교시
  - info.c 작성 다양한 내부 변수 확인 버퍼크기 및 큐 사이즈
- 4교시
  - DNS 설명
  - gethostbyname, getaddrinfo 설명
- 5교시
  - zombie 프로세스 설명
  - fork 예제 작성 zombie 프로세스
- 6교시
  - wait, waitpid 설명 - 좀비 프로세스 해결
  - signal 설명 - ipc 폴더에 sigal.c 작성, sigaction.c 작성(인텔리센스 인식 오류 해결)
- 7교시
  - 멀티 프로세서 코드 작성 forck, waitpid, signal -> echo_mpserver.c
  - echo_mpclient.c 작성
- 8교시
  - select_pipe 예제 작성
  - 정리

---

## 2025-05-01

---

- 1교시
  - 복습
  - select_pipe 예제 디버깅
- 2교시
  - select_pipe 예제 -배열과 함수 사용
- 3교시
  - 멀티플렉싱 echo_server 작성(select)
- 4교시
  - 멀티플렉싱 echo_client 작성(select)
- 5교시
  - 다양한 입출력함수 설명 send, recv, readv, writev
  - 멀티 캐스팅
    - 학생 절반이 메세지를 받지 못함(아마도 방확벽 때문인듯)
- 6교시
  - 소켓과 표준입출력 fileno, fdopen, 이중 버퍼 문제 fflush
  - 브로드캐스팅(한명 빼고 다 받음)
- 7교시
  - epoll 설명
  - epoll 예제 작성 (pipe 서버)
- 8교시
  - select_pipe 예제 작성
  - 정리
  - redis, mqtt, http, https, websocket, grpc, rest, GraphQL, WebRTC, CoAP, kafka

---

## 2025-05-02

---

- 1교시
  - 복습
  - echo epollserver 디버깅- fd 설정 오류
- 2교시
  - 쓰레드 설명!
  - thread_test.c 작성
- 3교시
  - thread_test2.c 작성
- 4교시
  - chat_srv.c 작성
- 6교시
  - multithread echo_server 작성
  - multithread echo_client 작성
- 7교시
  - multithread echo_server 작성 수정 - 구조체 추가
  - 2차 프로젝트, 파이널 프로젝트 팀 구성
- 8교시
  - 시험
