#ifndef _SERIAL_H_
#define _SERIAL_H_

void init_serial(void);
void init_baudrate(void);
void enable_eusart(void);
void UART_Write(char data);
char UART_Read(void);

#endif
