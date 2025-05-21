---
title: 고대_빅데이터사물인터넷 과정 강의 계획서
date: 2025-05-07
category: 파이썬 프로그래밍
tags: [파이썬, 프로그래밍, 모듈, 가상환경, 객체지향]
---

# 「고대_빅데이터사물인터넷 과정」 강의 계획서

## 회차별 강의 계획

### 5월 7일 (수) - 파이썬 기초

| 차시                | 강의 내용                                                                                                                                                                  |
| ------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1차시 (09:00~09:50) | 파이썬 언어 설명, 특징 (인터프리터, 동적 타이핑, 객체지향, 플랫폼 독립)                                                                                                    |
| 2차시 (10:00~10:50) | 파이썬 주의사항 (indentation, 대소문자 구분, 주석)                                                                                                                         |
| 3차시 (11:00~11:50) | pythonInterpreter, pythonInterpreter2 작성, 타입 (int, float, str, list)                                                                                                   |
| 4차시 (12:00~12:50) | python frame (sys._getframe, PyFrameObject), 객체 (PyObject, PyTypeObject, PyCodeObject), frame.f_back, f_code, f_locals, f_globals, locals(), globals(), vars()           |
| 5차시 (14:00~14:50) | string 클래스, 연산자 (+, *, -, /, %, //, **, in, not in)                                                                                                                  |
| 6차시 (15:00~15:50) | input 함수 (return str), indentation, 스트링 정의 ("", '', """ """, ''' ''')                                                                                               |
| 7차시 (16:00~16:50) | 스트링 클래스 메소드 (find, rfind, index, rindex, count, replace, split, join, strip, lstrip, rstrip, upper, lower, title, capitalize, isalpha, isdigit, isalnum, isspace) |
| 8차시 (17:00~17:50) | 과제 (구구단 출력, 섭씨->화씨 변환, 단어 카운트), 정리                                                                                                                     |

### 5월 8일 (목) - 제어 흐름과 모듈

| 차시                | 강의 내용                                                                                      |
| ------------------- | ---------------------------------------------------------------------------------------------- |
| 1차시 (09:00~09:50) | 복습, 3D 프린터 사용법 (bambu studio)                                                          |
| 2차시 (10:00~10:50) | 제어 흐름 (if-else, elif), import (module, package, library), 환경변수 (env, PATH, PYTHONPATH) |
| 3차시 (11:00~11:50) | datetime 모듈, 과제 (오전오후, 계절 출력)                                                      |
| 4차시 (12:00~12:50) | 리스트, list 메소드 (append, extend, insert, remove, pop, index, count, sort, reverse)         |
| 5차시 (14:00~14:50) | range, for문, tuple, enumerate 예제                                                            |
| 6차시 (15:00~15:50) | 동적 로딩 (dlopen, dlsym, dlclose), dlMain.c, plugin.c 작성                                    |
| 7차시 (16:00~16:50) | mymodule.c 작성                                                                                |
| 8차시 (17:00~17:50) | setup.py 작성 및 패키지 설치, 정리                                                             |

### 5월 9일 (금) - 함수와 데이터 구조

| 차시                | 강의 내용                                                                                 |
| ------------------- | ----------------------------------------------------------------------------------------- |
| 1차시 (09:00~09:50) | 복습, dictionary (key, value, pop, update, items, keys, values)                           |
| 2차시 (10:00~10:50) | while문 (break, continue), time 모듈 (sleep, time, localtime, strftime)                   |
| 3차시 (11:00~11:50) | list comprehension, min, max, sum                                                         |
| 4차시 (12:00~12:50) | 함수 argument (default, keyword, positional, variable-length), return, packing, unpacking |
| 5차시 (14:00~14:50) | 재귀함수, lru_cache, cache                                                                |
| 6차시 (15:00~15:50) | 일경험 프로그램, 함수 객체, static 변수, lambda 함수                                      |
| 7차시 (16:00~16:50) | lambda 함수 예제, 파일 처리 (open, read, write, close)                                    |
| 8차시 (17:00~17:50) | with open, fd 확인 및 print 파일 처리 (file 옵션), 정리                                   |

### 5월 12일 (월) - 모듈과 패키지 관리

| 차시                | 강의 내용                                                                                                                                                                                                                                                                                                                                                                      |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| 1차시 (09:00~09:50) | 복습, generator (yield, next, send)                                                                                                                                                                                                                                                                                                                                            |
| 2차시 (10:00~10:50) | iterator (__iter__, __next__), 에러 처리 (try, except, finally, raise), Exception/MinusError 클래스, 사용자 정의 예외                                                                                                                                                                                                                                                          |
| 3차시 (11:00~11:50) | random 모듈 (random, randint, choice, shuffle, sample, uniform, randrange)                                                                                                                                                                                                                                                                                                     |
| 4차시 (12:00~12:50) | random 균등/정규 분포 (matplotlib)                                                                                                                                                                                                                                                                                                                                             |
| 5차시 (14:00~14:50) | 내부 모듈 (os, sys, time, math, urllib, argparse, beautifulsoup)                                                                                                                                                                                                                                                                                                               |
| 6차시 (15:00~15:50) | 외부 모듈 (웹: flask, django, gradio, fastapi, dash, streamlit; 빅데이터: numpy, pandas, matplotlib, seaborn; AI: scikit-learn, tensorflow, keras, pytorch; 게임: pygame; GUI: tkinter, PyQt, wxPython, openCV; DB: sqlite3, mysql-connector-python; 네트워크: socket, twisted, asyncio; 테스트: unittest, pytest; 문서화: sphinx, pydoc; 패키지 관리: pip, conda, poetry, uv) |
| 7차시 (16:00~16:50) | setuptools 패키지 작성 및 설치, uv_test 패키지 작성 및 설치                                                                                                                                                                                                                                                                                                                    |
| 8차시 (17:00~17:50) | 패키지 심화 (가상환경, docker, uv, venv, poetry, conda), 정리                                                                                                                                                                                                                                                                                                                  |

### 5월 13일 (화) - 가상환경과 컨테이너

| 차시                | 강의 내용                                                                                                                                                                |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| 1차시 (09:00~09:50) | 복습, 가상 환경 설명                                                                                                                                                     |
| 2차시 (10:00~10:50) | venv 실습 (path 관리), myenv 실습 (pip, PATH 환경 변수 확인)                                                                                                             |
| 3차시 (11:00~11:50) | miniconda 실습 (conda, pip, venv), myconda 실습, poetry 실습 (poetry add, remove, update, build, publish, run python), CI/CD (github actions, travis, circleci, jenkins) |
| 4차시 (12:00~12:50) | docker 실습, VsCode dev container                                                                                                                                        |
| 5차시 (14:00~14:50) | dockerfile 작성, flask 예제                                                                                                                                              |
| 6차시 (15:00~15:50) | docker-compose 실습, app.py 작성                                                                                                                                         |
| 7차시 (16:00~16:50) | docker-compose 파일 작성 (flask)                                                                                                                                         |
| 8차시 (17:00~17:50) | dict class student 작성, 정리                                                                                                                                            |

### 5월 14일 (수) - 객체지향 프로그래밍

| 차시                | 강의 내용                                                                                                                                                                                 |
| ------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1차시 (09:00~09:50) | 복습, 클래스, student class 작성                                                                                                                                                          |
| 2차시 (10:00~10:50) | student class 메소드, __init__, __new__ (singleton 패턴), pickle 객체 직렬화, 데이터 파일 저장/읽기                                                                                       |
| 3차시 (11:00~11:50) | special method (dunder), operator overloading (__str__, __repr__, __add__, __sub__, __mul__, __truediv__, __floordiv__, __mod__, __pow__, __lt__, __le__, __eq__, __ne__, __gt__, __ge__) |
| 4차시 (12:00~12:50) | 소멸자 (__del__), 클래스 상속, super(), mro()                                                                                                                                             |
| 5차시 (14:00~14:50) | dataclass 실습 (list, dict, default_factory 초기화)                                                                                                                                       |
| 6차시 (15:00~15:50) | meta-programming (__getattr__, __setattr__, __delattr__, __call__, __getitem__, __setitem__, __delitem__), setattr 예제                                                                   |
| 7차시 (16:00~16:50) | 래퍼함수, 데코레이터 실습, time check 데코레이터                                                                                                                                          |
| 8차시 (17:00~17:50) | threading 실습, 정리                                                                                                                                                                      |

### 5월 15일 (목) - 비동기 프로그래밍

| 차시                | 강의 내용                   |
| ------------------- | --------------------------- |
| 1차시 (09:00~09:50) | 복습, asyncio, async, await |
| 2차시 (10:00~10:50) | -                           |
| 3차시 (11:00~11:50) | -                           |
| 4차시 (12:00~12:50) | -                           |
| 5차시 (14:00~14:50) | -                           |
| 6차시 (15:00~15:50) | -                           |
| 7차시 (16:00~16:50) | -                           |
| 8차시 (17:00~17:50) | 정리                        |