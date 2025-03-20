#ifndef UART1_H_
#define UART1_H_

void uart0Init(void);
void uart0Transmit(char data);
unsigned char uart0Receive(void);
void uart0PrintString(char *str);
void uart0Print1ByteNumber(unsigned char n);

#endif // UART1_h_