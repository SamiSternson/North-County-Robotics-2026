#include "movement.h"
#include <kipr/wombat.h>
#include <math.h>
#include <stdlib.h>
double AVERAGE= -5.301245; //Ticks/Degrees
double SPIN_AVERAGE = -5.991245;
int RIGHT_MOTOR=0;
int LEFT_MOTOR=1;
int grabber_servo=3;
int grabber_servo_closed=1785;
int grabber_servo_open=650;
void PIVOT_DEGREES(int DEGREES, int MOTOR, int SPEED) //create a function called turn degrees with the argument of how many degrees u want to turn and which motor to turn in
{
    double ANGLE=0;
    double SECONDS_START= 0;
    double SECONDS_END =0;
    gyro_calibrate();
    if(MOTOR == RIGHT_MOTOR)//is the right motor being used?
    {
        while (ANGLE < DEGREES) 
        { 

            SECONDS_START=seconds();
            mav(MOTOR,SPEED);//pivot
            SECONDS_END= seconds() - SECONDS_START;//count how many seconds that was 
            ANGLE += (gyro_z()*SECONDS_END)/AVERAGE;//adjust our angle based on that
            printf("ANGLE:%f\n", ANGLE);//just a debug feature (:


        }
    }
    else if(MOTOR == LEFT_MOTOR)//or is the left?
    {
        while (ANGLE < DEGREES) //bassically does the same thing as above
        { 

            SECONDS_START=seconds();
            mav(MOTOR,SPEED);
            SECONDS_END= seconds() - SECONDS_START; 
            ANGLE += (gyro_z()*SECONDS_END)/(AVERAGE*-1);
            printf("ANGLE:%f\n", ANGLE);


        }
    }
    freeze(MOTOR);
    //while (ANGLE = DEGREES) stop robot
}
void SPIN_DEGREES(float degrees, int speed)//same thing as pivot BUT WITH SPINNING... Note: This for some reason has a different average.
{
    double angle = 0;
    gyro_calibrate();
    double start_time = seconds();
    double duration;
    while (abs(angle)<abs(degrees))
    {
        start_time=seconds();
        mav(RIGHT_MOTOR, speed);
        mav(LEFT_MOTOR, -speed);
        duration=seconds();
        angle+=(gyro_z()/SPIN_AVERAGE)*(duration-start_time);
    }
    FREEZE_ALL();
}
void DRIVE_STRAIGHT(int LEFT_MOTOR1, int RIGHT_MOTOR1, int SPEED, float TIME)//TO DRIVE STRAIGHT...
{
    double ANGLE = 0;
    double LEFT_MOTOR_SPEED = SPEED;
    double RIGHT_MOTOR_SPEED = SPEED;
    gyro_calibrate();
    double START_TIME = seconds();
    while(seconds()-START_TIME<TIME)
    {
        double SECONDS_START1=seconds();
        mav(LEFT_MOTOR1, LEFT_MOTOR_SPEED);
        mav(RIGHT_MOTOR1, RIGHT_MOTOR_SPEED);
        double END_TIME1 = seconds() - SECONDS_START1;
        ANGLE += (gyro_z()*END_TIME1)/(AVERAGE);// get the ANGLE in DEGREES
        if(ANGLE>2)//check if ANGLE is off by more than 2 DEGREES
        {
            //adjust SPEED for each MOTOR accordingly
            LEFT_MOTOR_SPEED += 100;
            RIGHT_MOTOR_SPEED -= 100;
        }
        else if(ANGLE<-2) //same process as above
        {
            LEFT_MOTOR_SPEED -= 100;
            RIGHT_MOTOR_SPEED += 100;
        }
        else //set SPEED back to NORMAL once there is NO ERROR
        {
            RIGHT_MOTOR_SPEED = SPEED;
            LEFT_MOTOR_SPEED = SPEED;
        }
    }
    FREEZE_ALL();
}
void FREEZE_ALL()//this just freezes all the motors, saves us time by not having to type out all freezes.
{
    freeze(0);
    freeze(1);
    freeze(2);
    freeze(3);
    msleep(10);
}
void SQUARE_UP_ON_BLACK(int right_sensor, int left_sensor, int threshold, int speed)//squares up on black.
{
    while (analog(right_sensor)<threshold || analog(left_sensor)<threshold)
    {
        if (analog(right_sensor)>threshold && analog(left_sensor)<threshold)
        {
            mav(RIGHT_MOTOR, -speed);
            mav(LEFT_MOTOR, speed);
        } 
        else if (analog(right_sensor)<threshold && analog(left_sensor)>threshold)
        {
            mav(RIGHT_MOTOR, speed);
            mav(LEFT_MOTOR, -speed);
        }
        else
        {
            mav(RIGHT_MOTOR, speed);
            mav(LEFT_MOTOR, speed);
        }
    }
    FREEZE_ALL();
}
void SQUARE_UP_ON_WHITE(int right_sensor, int left_sensor, int threshold, int speed)//squares up on white
{
    while (analog(right_sensor)>threshold || analog(left_sensor)>threshold)
    {
        if (analog(right_sensor)<threshold && analog(left_sensor)>threshold)
        {
            mav(RIGHT_MOTOR, -speed);
            mav(LEFT_MOTOR, speed);
        } 
        else if (analog(right_sensor)>threshold && analog(left_sensor)<threshold)
        {
            mav(RIGHT_MOTOR, speed);
            mav(LEFT_MOTOR, -speed);
        }
        else
        {
            mav(RIGHT_MOTOR, speed);
            mav(LEFT_MOTOR, speed);
        }
    }
    FREEZE_ALL();
}
void PUT_BARREL_ON_POLE(int motor)// puts a drum onto our pole storage system.
{
    int almost_there_motor_ticks=1250;
    cmpc(motor);
    int motor_position=0;
    STEPPER_SERVO(grabber_servo, 50, grabber_servo_closed);
    while(motor_position<almost_there_motor_ticks)
    {
        mav(motor, 500);
        motor_position=gmpc(motor);
    }
    ao();

    STEPPER_SERVO(grabber_servo,  30,grabber_servo_open);   
}
void ARM_DOWN(int motor)// puts the grabbing arm down.
{
    int motor_ticks=-1400;
    cmpc(motor);
    int motor_position=0;
    while(motor_position>motor_ticks)
    {
        mav(motor, -900);
        motor_position=gmpc(motor);
    }


}
void STEPPER_SERVO(int servo, int speed, int end_position)// just  a stepper servo.
{
    enable_servo(servo);
    int servo_position=get_servo_position(servo);
    if ((end_position-servo_position)>0)
    {
        while (end_position>=servo_position)
        {
            set_servo_position(servo, servo_position+speed);
            servo_position+=speed;
            msleep(15);
        }
    }
    else
    {
        while (end_position<=servo_position)
        {
            set_servo_position(servo, servo_position-speed);
            servo_position-=speed;
            msleep(15);
        }
    }

    disable_servos();
    printf("hiiii");
}
