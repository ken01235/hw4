#include"mbed.h"

BufferedSerial pc(USBTX,USBRX);
BufferedSerial uart(D1,D0);

int main()
{
    uart.set_baud(9600);
    while(1){
        if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            string text;
            text = pc.write(recv, sizeof(recv));
            for (int i = 0; i < sizeof(recv); ++i) {
                //printf("%c", text[i]);
            }
        }
    }
    
}
