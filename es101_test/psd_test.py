import spidev
import time

# SPI 설정
spi = spidev.SpiDev()
spi.open(0, 0)  # SPI0, CE0 사용
spi.max_speed_hz = 1000000  # 1MHz (MCP3208 사양 내에서 조정 가능)

def read_mcp3208(channel):
    if channel < 0 or channel > 7:
        raise ValueError("채널은 0에서 7 사이여야 합니다.")

    # MCP3208의 단일 채널 읽기 명령 구성
    command = 0b11 << 6  # 시작 비트(2비트) 및 단일/차동 비트(1비트)
    command |= (channel & 0b111) << 3  # 채널 선택 비트(3비트)
    tx_data = [command, 0, 0]
    rx_data = spi.xfer2(tx_data)

    # 수신된 데이터에서 12비트 ADC 값 추출
    adc_value = ((rx_data[0] & 0x01) << 11) | (rx_data[1] << 3) | (rx_data[2] >> 5)
    return adc_value & 0xFFF  # 12비트 값 반환

def voltage_to_distance(voltage):
    if voltage <= 0:
        return float('inf')  # 무한대 거리로 처리
    return 27.86 / (voltage - 0.1694)

def test_psd_sensor(channel=0, samples=10):
    try:
        print(f"PSD 센서 테스트 시작 (채널 {channel})")
        print("Ctrl+C로 종료")
        time.sleep(1)  # 센서 안정화를 위한 지연

        for i in range(samples):
            adc_value = read_mcp3208(channel)
            voltage = adc_value * 5.0 / 4095  # VREF를 5V로 가정
            distance = voltage_to_distance(voltage)
            print(f"샘플 {i+1}: ADC 값 = {adc_value}, 전압 = {voltage:.3f}V, 거리 = {distance:.2f}cm")
            time.sleep(0.5)

        print("초기 테스트 완료. 실시간 모드로 전환합니다.")

        while True:
            adc_value = read_mcp3208(channel)
            voltage = adc_value * 5.0 / 4095
            distance = voltage_to_distance(voltage)
            print(f"ADC 값 = {adc_value}, 전압 = {voltage:.3f}V, 거리 = {distance:.2f}cm", end='\r')
            time.sleep(0.1)

    except KeyboardInterrupt:
        print("\n테스트 종료.")
    finally:
        spi.close()

if __name__ == "__main__":
    # PSD 센서가 MCP3208의 CH0에 연결되어 있다고 가정
    test_psd_sensor(channel=0, samples=10)