#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
Ticker encoder_ticker;
PwmOut pin5(D5), pin6(D6);
DigitalIn encoder(D11);
volatile int steps;
volatile int last;

BBCar car(pin5, pin6, servo_ticker);
void encoder_control() {
   int value = encoder;
   if (!last && value) steps++;
   last = value;
}

int main()
{
    double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table0[] = {-15.785, -15.307, -14.190, -11.002, -4.863, 0.000, 6.617, 11.878, 14.589, 15.705, 16.104};
    double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
    double speed_table1[] = {-22.640, -23.598, -24.315, -24.395, -11.081, 0.000, 15.705, 23.199, 22.960, 23.359, 22.003};

    car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

    car.goStraightCalib(15);
    encoder_ticker.attach(&encoder_control, 10ms);
    steps = 0;
    last = 0;
    while(steps*6.5*3.14/32 < 30) {
        printf("encoder = %d\r\n", steps); 
        ThisThread::sleep_for(100ms);
    }
    car.turn(15, -1);
    while(steps*6.5*3.14/32 < 9) {
        ThisThread::sleep_for(100ms);
    }
    car.stop();
    return 0;
}
