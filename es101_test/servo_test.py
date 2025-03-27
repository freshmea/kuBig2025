# Servo Motor Test Code
# sudo pip3 install adafruit-circuitpython-pca9685
# sudo pip3 install adafruit-circuitpython-servokit

import time

import adafruit_pca9685
import board
import busio
from adafruit_servokit import ServoKit

# I2C 버스 초기화
i2c = busio.I2C(board.SCL, board.SDA)

# PCA9685 초기화 (주소 0x5e)
pca = adafruit_pca9685.PCA9685(i2c, address=0x5e)

# 주파수 설정 (50Hz)
pca.frequency = 50

# ServoKit 초기화 (16채널, 주소 0x5e)
kit = ServoKit(channels=16, i2c=i2c, address=0x5e)

# 서보 채널 설정
# Servo1: CH5 (R48), Servo2: CH4 (R50)
servo1 = kit.servo[3]  # CH5
servo2 = kit.servo[4]  # CH4

# 서보 각도 범위 설정 (0~180도)
servo1.set_pulse_width_range(500, 2500)  # 0.5ms ~ 2.5ms
servo2.set_pulse_width_range(500, 2500)  # 0.5ms ~ 2.5ms

# 테스트 함수
def test_servo():
    print("Servo 테스트 시작: Servo1(CH5), Servo2(CH4)")

    # 초기 위치: 180도
    print("Servo1, Servo2를 180도로 설정...")
    servo1.angle = 180
    servo2.angle = 180
    time.sleep(1)

    # 180도에서 0도까지 이동
    print("180도에서 0도까지 이동...")
    for angle in range(180, -1, -1):  # 180도에서 0도까지 1도씩 감소
        servo1.angle = angle
        servo2.angle = angle
        time.sleep(0.02)  # 부드러운 이동을 위해 20ms 대기

    # 0도에서 180도로 이동
    print("0도에서 180도로 이동...")
    for angle in range(0, 181, 1):  # 0도에서 180도까지 1도씩 증가
        servo1.angle = angle
        servo2.angle = angle
        time.sleep(0.02)

    # 테스트 완료 후 서보 비활성화 (토크 해제)
    print("테스트 완료, 서보 비활성화")
    servo1.angle = None  # PWM 신호 끄기
    servo2.angle = None  # PWM 신호 끄기

# 메인 실행
if __name__ == "__main__":
    try:
        test_servo()
    except KeyboardInterrupt:
        print("\n테스트 중단")
        servo1.angle = None
        servo2.angle = None
    except Exception as e:
        print(f"에러 발생: {e}")
        servo1.angle = None
        servo2.angle = None