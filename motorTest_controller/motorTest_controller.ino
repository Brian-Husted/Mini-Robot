#include <Ps3Controller.h>
#include <Adafruit_NeoPixel.h>
#include <ESP32Servo.h>
#include <ESP32.h>

//create servo objects
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
//argument 1 = Number of pixels
//argument 2 = Pin number
//argument 3 = NEO_GRB Pixels are wired for GRB bitstream + NEO_KHZ800  800 KHz bitstream


void setup(){
  Serial.begin(115200);

  //initilize bluetooth connection
  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.attachOnDisconnect(onDisconnect);
  Ps3.begin("20:00:00:00:34:14");  //modify to match MAC address on controller

  //initilize LEDs
  pixels.begin();
  pixels.show();
  pixels.setBrightness(20);

  //initilize motors
  Motor_Setup();

  //initilize servos
  Servo_Setup();

  Serial.println("Ready."); 
}

void loop(){
  //Motor_Test();  //call to test motor position and direction

  if(!Ps3.isConnected()){
    if ((millis() - timer) > 50 && !led){
      pixels.setPixelColor(0, 255, 0, 0);
      pixels.setPixelColor(1, 255, 0, 0);
      pixels.setPixelColor(2, 255, 0, 0);
      pixels.setPixelColor(3, 255, 0, 0);
      pixels.show();
      led = true;
      timer = millis();
    }
    else if((millis() - timer) > 50 && led){
      pixels.clear();
      pixels.show();
      timer = millis();
      led = false;
    }
    return;
  }
}