void PIVOT_DEGREES(int DEGREES, int MOTOR, int SPEED);
void DRIVE_STRAIGHT(int LEFT_MOTOR1, int RIGHT_MOTOR1, int SPEED, float TIME);
void SPIN_DEGREES(float degrees, int speed);
void FREEZE_ALL();
void SQUARE_UP_ON_BLACK(int right_sensor, int left_sensor, int threshold, int speed);
void SQUARE_UP_ON_WHITE(int right_sensor, int left_sensor, int threshold, int speed);
void STEPPER_SERVO(int servo, int speed, int end_position);
void ARM_DOWN(int motor);
void PUT_BARREL_ON_POLE(int motor);