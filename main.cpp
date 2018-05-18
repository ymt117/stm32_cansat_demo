#include "mbed.h"
#include "lis3mdl.h"
#include "LPS25H.h"
#include "GPS.h"
#include "motor.h"
#include "DaydreamCafe.h"

#define mC 261.626
#define mD 293.665
#define mE 329.628
#define mF 349.228
#define mG 391.995
#define mA 440.000
#define mB 493.883

#define PI 3.14159265
//#define DEBUG

GPS             gps(PA_9, PA_10);           // tx, rx
Serial          pc(PA_2, PA_3);             // tx, rx
LIS3MDL         compass(PB_7, PB_6);        // sda, scl
I2C             i2c(PB_7, PB_6);
LPS25H          pressure(i2c, 0xBA);
Motor           motor(PF_0, PF_1, PA_8, PB_1);
PwmOut          beep(PA_12);
DigitalIn       sw1(PA_4);
DigitalOut      leds[] = {
                    DigitalOut (PA_5),
                    DigitalOut (PA_6),
                    DigitalOut (PA_7),
                    DigitalOut (PB_0)
                };
Ticker ticker;
Timer  timer;

// CanSat state transition
enum myStatus{
    INIT,       // 0
    MUSIC,
    MOVE,
    CALIBRATE
};
// Set the status of CanSat
myStatus s = INIT;

// gloval variable
float   mx_max, mx_min, my_max, my_min;
float   direction;

void play_DaydreamCafe(){
    
    for (int i=0; i<sizeof(mm)/sizeof(float); i++) {
        if(mm[i] == Ky){
            wait(0.2f);
        }
        else if(mm[i] == mSi*4 || mm[i] == mMi*2 || mm[i] == mSo*2){
            leds[rand()%4] = 1;
            beep.period((double)1.0/mm[i]);
            beep.write(0.1f);
            if(mm[i+1] == No){
                wait(0.2f);
                i++;
            }
            else wait(0.1f);
            for(int j=0; j<4; j++) leds[j] = 0;
        }
        else{
            leds[rand()%4] = 1;
            beep.period((double)1.0/mm[i]);
            beep.write(0.2f);
            if(mm[i+1] == No){
                wait(0.4f);
                i++;
            }
            else wait(0.2f);
            for(int j=0; j<4; j++) leds[j] = 0;
        }
        beep.write(0.0f);
    }
}

void play_music(int n){
    float mm1[]={mC*2,mD*2,mE*2,mF*2,mG*2,mA*2,mB*2,mC*4};
    float mm2[]={mC*4,mB*2,mA*2,mG*2,mF*2,mE*2,mD*2,mC*2};
    if(n > 0){
        for(int i=0; i<sizeof(mm1)/sizeof(float); i++){
            leds[i%4] = 1;
            beep.period((double)1.0/mm1[i]);
            beep.write(0.2f);
            wait(0.2f);
            beep.write(0.0f);
            leds[i%4] = 0;
        }
    }
    else{
        for(int i=0; i<sizeof(mm2)/sizeof(float); i++){
            leds[i%4] = 1;
            beep.period((double)1.0/mm2[i]);
            beep.write(0.2f);
            wait(0.2f);
            beep.write(0.0f);
            leds[i%4] = 0;
        }
    }
}

void do_exit(){
    if(!sw1.read()){
        motor.stop();
        play_music(-1);
        exit(0);
    }
}

void mode_select(){
    int i=0;
    leds[i] = 1;
    timer.start();
    while(timer.read() < 5){
        if(!sw1.read()){
            wait(0.1);
            beep.period((double)1.0/(mC*2));
            beep.write(0.2f);
            wait(0.2f);
            beep.write(0.0f);
            timer.reset();
            for(int j=0; j<3; j++) leds[j]=0;
            i++;
            if(i%4 != 3) leds[i%4]=1;
            if(i%4 == 0) s=MOVE;
            else if(i%4 == 1) s=MUSIC;
            else if(i%4 == 2) s=CALIBRATE;
            else s=MOVE;
        }
    }
    if(i == 0) s=MOVE;
    timer.stop();
    for(int k=0; k<7; k++){
        leds[i%4] = 1;
        wait(0.1f);
        leds[i%4] = 0;
        wait(0.1f);
    }
}

void init(){
    // Set the baud rate of TWE-Lite
    pc.baud(9600);
    pc.printf("Hello my CanSat!\r\n");
    
    // Performance at startup
    play_music(1);
    sw1.mode(PullUp);
    
    // Select mode according to the state of the switch
    wait(0.5);
    mode_select();
    
    // Start Timer interrupt
    wait(0.5);
    ticker.attach(&do_exit, 1.0);
}

void demo_run(){
    motor.forward();   wait(2);
    motor.stop();      wait(2);
    motor.right();     wait(1);
    motor.stop();      wait(2);
    motor.left();      wait(1);
    motor.stop();      wait(2);
    motor.turnRight(); wait(2);
    motor.stop();      wait(5);
}

float calc_direction(){
    // Calculate the direction of the goal use geomagnetic sensor
    float mx_center = (mx_max + mx_min) / 2;
    float my_center = (my_max + my_min) / 2;
    compass.readMag();
    float theta = (int)(atan2(compass.my-my_center, compass.mx-mx_center)*(180/PI));
    return theta;
}

void set_direction(){
    // stop interrupt func
    ticker.detach();
    leds[3] = 1;
    
    wait(0.5);
    while(sw1.read()){
        direction = calc_direction();
    }
    for(int i=0; i<7; i++){
        leds[3] = 1;
        wait(0.1f);
        leds[3] = 0;
        wait(0.1f);
    }
    
    // restart interrupt func
    ticker.attach(&do_exit, 1.0);
}

void move_direction(){
    float theta = calc_direction();
    if(abs(theta - direction) < 15){
        motor.forward();
    }
    else{
        motor.stop();
    }
}

void calibrate(){
    // Calibrate the sensor value of the geomagnetic sensor
    // Get value of the standard geomagnetic sensor
    compass.readMag();
    mx_max = mx_min = compass.mx;
    my_max = my_min = compass.my;
    
    // To turn at that place
    motor.turnRight();
            
    // Update max and min values
    timer.reset();
    timer.start();
    while(timer.read() < 5){
        compass.readMag();
        if(compass.mx > mx_max){
            mx_max = compass.mx;
        }
        if(compass.mx < mx_min){
            mx_min = compass.mx;
        }
        if(compass.my > my_max){
            my_max = compass.my;
        }
        if(compass.my < my_min){
            my_min = compass.my;
        }
    }
    timer.stop();
    timer.reset();
    motor.stop();
    wait(3);
    
    // You set direction
    set_direction();
}

int main() {
    
    while(1){
        if(s == INIT){
            init();
        }
        if(s == MUSIC){
            play_DaydreamCafe();
        }
        if(s == MOVE){
            leds[1] = 1;
            demo_run();
        }
        if(s == CALIBRATE){
            leds[2] = 1;
            calibrate();
            while(1){
                move_direction();
            }
        }
    }
}
