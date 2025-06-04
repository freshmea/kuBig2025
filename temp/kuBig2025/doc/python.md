# PYTHON

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
  - python frame 설명: sys._getframe -> C언어의 PyFrameObject
  - python 의 객체 :
    - PyObject : 모든 객체의 기본 클래스
    - PyFrameObject : 함수 호출 시 생성되는 객체
    - PyTypeObject : 객체의 타입을 정의하는 구조체
    - PyCodeObject : 바이트코드를 저장하는 구조체
  - frame.f_back, f_code, f_locals, f_globals
  - locals() : 현재 지역변수
  - globals() : 현재 전역변수
  - vars() : 현재 전역변수 + 지역변수
- 5교시
  - string class 설명
  - 연산자 : +, *, -, /, %, //, **, in, not in
- 6교시
  - input 함수 설명 -> return str class!
  - indentation 주의 : C 언어의 블럭 {} 역할
  - 스트링 정의 "", '', """ """, ''' ''' 차이점
- 7교시
  - 스트링 클래스 메소드 :
    - find, rfind, index, rindex, count, replace
    - split, join, strip, lstrip, rstrip
    - upper, lower, title, capitalize
    - isalpha, isdigit, isalnum, isspace
- 8교시
  - 과제:
    - 파이썬으로 구구단 출력하기 2단 -> 9단
    - 섭씨->화씨 변환 프로그램 input -> casting -> 연산 -> 출력
    - 문자열을 입력 받아서 단어를 카운트 해서 결과를 출력하세요
  - 정리

---

## 2025-05-08

---

- 1교시
  - 복습
  - 3D 프린터 사용법 설명(bambu studio)
- 2교시
  - 제어 흐름 설명 if - else, elif
  - import 설명 - module(.py), package(폴더), library(.so, .pyi)
  - 환경변수 env, PATH, PYTHONPATH
- 3교시
  - datetime 모듈
  - 과제 - 오전오후, 계절 출력
- 4교시
  - 리스트 설명
  - list 메소드 : append, extend, insert, remove, pop, index, count, sort, reverse
- 5교시
  - range 설명, for문 설명, tuple 설명
  - enumerate 예시.
- 6교시
  - 동적 로딩 dynamic loading 설명
  - dlMain.c, plugin.c 작성
  - dlopen, dlsym, dlclose 설명
- 7교시
  - mymodule.c 작성
- 8교시
  - setup.py 작성 및 패키지 설치
  - 정리

---

## 2025-05-09

---

- 1교시
  - 복습
  - dictionary 설명 - key, value, pop, update, items, keys, values
- 2교시
  - while문 설명 - break, continue
  - time 모듈 - sleep, time, localtime, strftime
- 3교시
  - list comprehension 설명
  - nim, max, sum 설명
- 4교시
  - 함수의 argument 설명 - default, keyword, positional, variable-length
  - return 설명
  - packing, unpacking 설명
- 5교시
  - 재귀함수
  - lru_cache, cache 설명
- 6교시
  - 일경험 프로그램 설명
  - 파이썬에서의 함수 객체, static 처럼 변수 쓰기
  - lambda 함수 설명
- 7교시
  - 람다 함수 예제
  - 파일 처리, open, read, write, close
- 8교시
  - with open 설명
  - fd 확인 및 print를 이용해서 파일 처리 (file 옵션)
  - 정리

---

## 2025-05-12

---

- 1교시
  - 복습
  - generator 설명 - yield, next, send
- 2교시
  - iterator 설명 - __iter__, __next__
  - 에러 처리 - try, except, finally, raise
  - Exception class, MinusError class 작성
  - 사용자 정의 예외 처리 방법 설명
- 3교시
  - random 모듈 설명 - random, randint, choice, shuffle, sample, uniform, randrange
- 4교시
  - random 의 균등 분포, 정규 분포 설명 (matplotlib)
- 5교시
  - 내부 모듈 설명 - os, sys, time, math, urllib - (argparse, beatifulsoup)
- 6교시
  - 외부 모듈 설명
    - 웹 : flask, django, gradio, fastapi, dash, streamlit
    - 빅데이터 : numpy, pandas, matplotlib, seaborn
    - AI : scikit-learn, tensorflow, keras, pytorch
    - 게임 : pygame
    - GUI : tkinter, PyQt, wxPython, openCV
    - DB : sqlite3, mysql-connector-python
    - 네트워크 : socket, twisted, asyncio
    - 테스트 : unittest, pytest
    - 문서화 : sphinx, pydoc
    - 패키지 관리 : pip, conda, poetry, uv
- 7교시
  - setuptools 패키지 작성 및 설치
  - uv_test 패키지 작성 및 설치
- 8교시
  - 패키지 심화 설명 - 가상환경, docker, uv, venv, poetry, conda
  - 정리

---

## 2025-05-13

---

- 1교시
  - 복습
  - 가상 환경 설명
- 2교시
  - venv 설명 및 실습 - path 관리 하는 기본적인 도구
  - myenv 실습 - pip 및 PATH 환경 변수 확인
- 3교시
  - miniconda 설명 및 실습 - conda, pip, venv
  - myconda 실습 - conda 및 PATH 환경 변수 확인
  - poetry 설명 및 실습 - 패키지 관리 도구
    - activate 할 필요 없음 ( poetry shell -> 실습 안됨...)
    - lock 파일로 패키지 버전 관리
    - 폴더 별 pyproject.toml 로 관리
    - poetry add, remove, update, build, publish
    - poetry run python
  - CI/CD 설명 - github actions, travis, circleci, jenkins
- 4교시
  - docker 설명 및 실습 - 컨테이너 관리 도구
  - VsCode dev container 설명 및 실습
- 5교시
  - dockerfile 작성 및 실습
  - flask 예제
- 6교시
  - docker-compose 설명 및 실습
  - app.py 작성
- 7교시
  - docker-compose 파일 작성 및 실습 - flask
- 8교시
  - dict class student 작성
  - 정리

---

## 2025-05-14

---

- 1교시
  - 복습
  - 클래스 설명
  - student class 작성
- 2교시
  - student class 메소드 작성
  - 생성자 __init__ 설명 및 __new__ 설명 - singleton 패턴 실습
  - 데이터 파일저장과 읽기로 student class 수정
  - pickle 을 이용한 객체 직렬화 설명
- 3교시
  - special method 설명(dunder method)
  - operator overloading 설명
  - __str__, __repr__, __add__, __sub__, __mul__, __truediv__, __floordiv__, __mod__, __pow__
  - __lt__, __le__, __eq__, __ne__, __gt__, __ge__
- 4교시
  - 소멸자 __del__ 설명
  - 클래스 상속
  - super() 설명
  - mro() 설명
- 5교시
  - dataclass 설명
  - dataclass 실습, list, dict, default_factory 사용하여 초기화
- 6교시
  - meta-programming 설명
  - __getattr__, __setattr__, __delattr__, __call__, __getitem__, __setitem__, __delitem__
  - setattr 예제
- 7교시
  - 래퍼함수 작성
  - 데코레이터 만들기 실습
  - time check 데코레이터 실습
- 8교시
  - threading 실습
  - 정리

---

## 2025-05-15

---

- 1교시
  - 복습
  - asyncio 설명
  - async, await 설명
- 2교시
  - a
- 3교시
  - a
- 4교시
  - a
- 5교시
  - a
- 6교시
  - a
- 7교시
  - a
- 8교시
  - 정리
