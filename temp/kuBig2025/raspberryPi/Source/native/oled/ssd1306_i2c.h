#ifndef SSD1306_I2C_H
#define SSD1306_I2C_H

int ssd1306I2CSetup(unsigned char i2cAddr);

void sendCommand(int fd, unsigned char command);
void sendData(int fd, unsigned char data);

void displayOn(int fd);  
void displayOff(int fd);
void clearDisplay(int fd); 
void draw(int x,int y,unsigned char ascii);
void draw_line(int x ,int y,unsigned char ascii_str[16]);
void updateDisplay(int fd);

#define SSD1306_DISPLAYON 0xAF
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_MULTIPLEX_RATIO 0xA8

#define SSD1306_CONTROL_REG 0x00  
#define SSD1306_DATA_REG 0x40

#endif
