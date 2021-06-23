#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial pc(USBTX, USBRX);
BufferedSerial uart(D1, D0);

BBCar car(pin5, pin6, servo_ticker);

int main() {
    uart.set_baud(9600);
    char buf[256], outbuf[256];
    FILE *devin = fdopen(&uart, "r");
    FILE *devout = fdopen(&uart, "w");
    while (1) {
        memset(buf, 0, 256);
        for( int i = 0; ; i++ ) {
            char recv = fgetc(devin);
            buf[i] = fputc(recv, devout);
            if(recv == '\n') {
                printf("\r\n");
                break;
            }
        }
        printf("%s\n",buf);
        RPC::call(buf, outbuf);
    }
}
