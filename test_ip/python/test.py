# import time


# def main():
#     while True:
#         print("hi, hellow")
#         time.sleep(1)

# main()

import sys


def foo():
    frame = sys._getframe()
    a = 13
    b = sys.path[0]
    c = lambda x : x*x
    print("foo() frame name:", frame.f_code.co_name)
    print(frame.f_locals.items())

frame = sys._getframe()
print("module-level frame name:", frame.f_code.co_name)
print(__name__)
print(frame.f_globals.items())

foo()
