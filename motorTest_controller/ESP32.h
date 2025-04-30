//outputs for motor 1 (front right)
#define M1_1 27  
#define M1_2 13

//outputs for motor 2 (back right)
#define M2_1 4
#define M2_2 2

//outputs for motor 3 (back left)
#define M3_1 17
#define M3_2 12

//outputs for motor 4 (front left)
#define M4_1 15
#define M4_2 14

//needed for pwm signals
#define TIMER_BIT   8
#define BASE_FREQ   5000

//LEDs
#define LED_COUNT 4
#define LED_PIN 16

//servos
#define SERVO_1 26
#define SERVO_2 25
#define SERVO_3 33
#define SERVO_4 32

#define initPos_1 90
#define initPos_2 90
#define initPos_3 90
#define initPos_4 90

int rightX, rightY;
int leftX, leftY;
unsigned long timer;
bool led;