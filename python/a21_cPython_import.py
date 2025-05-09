# python3 setup.py build
# sudo python3 setup.py install
# (option) 지우는 코드 sudo pip uninstall mymodule
# 실행
# (option) 개발 폴더에 .so 파일 옮기기 -> /root 가 아닌곳에서도 실행 됨
import mymodule

# from mymodule import Hello

# Hello("aa")
h = mymodule.Hello("sukil")
mymodule.print_hello()
print(h.greet())
