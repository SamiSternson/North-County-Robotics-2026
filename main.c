#include <kipr/wombat.h>
#include "movement.h"
#include "sensors.h"
int LM = 1;
int RM = 0;
int LS = 1;
int RS =0;
int ARM_MOTOR=3;
int THRESH=1310;
void DRIVE_TO_DRUMS();
void COLLECT_DRUMS();
int main()
{
        wait_for_light(5);
    double start_time=seconds();
   OPEN_CAMERA();
    DRIVE_TO_DRUMS();
    COLLECT_DRUMS();
    //SPIN_DEGREES(90, 1500);
    //PIVOT_DEGREES(90, LM, 300);
     printf("Total Time: %f", seconds()-start_time);//just a debug feature.
    camera_close();
    return 0;
}
void DRIVE_TO_DRUMS()//DRIVING IN MY CAR RIGHT TO THE DRUMS...
{

    double time = seconds();
    SQUARE_UP_ON_BLACK(0,1, THRESH, 1500);
    SQUARE_UP_ON_WHITE(0,1, THRESH, 1500);
    SQUARE_UP_ON_BLACK(0,1, THRESH, 1500);
    SQUARE_UP_ON_WHITE(0,1, THRESH, 1500);
    DRIVE_STRAIGHT(1,0,1500, 2);
    mav(RM, 300);
    mav(LM, 300);
    msleep(200);
   DRIVE_STRAIGHT(1,0,-100, 0.5);
    ARM_DOWN(3);   
   
    
}
void COLLECT_DRUMS()
{
 int color=-1;
    while (color<0)
    {
     color=CHECK_BARREL_COLOR();
    }
    PUT_BARREL_ON_POLE(3);
}
