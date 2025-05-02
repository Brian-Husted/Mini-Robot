void onConnect(){
  Serial.println("Connected.");
  pixels.setPixelColor(0, 0, 0, 255);
  pixels.setPixelColor(1, 0, 0, 255);
  pixels.setPixelColor(2, 0, 0, 255);
  pixels.setPixelColor(3, 0, 0, 255);
  pixels.show();
}

void onDisconnect(){
  Serial.println("Disconnected.");

  //stop motors
  Front_Right(0);
  Back_Right(0);
  Back_Left(0);
  Front_Left(0);
}

void notify(){
  // Get Joystick values
  rightX = (Ps3.data.analog.stick.rx);
  rightY = (Ps3.data.analog.stick.ry);
  leftX = (Ps3.data.analog.stick.lx);
  leftY = -(Ps3.data.analog.stick.ly);

  //scale stick inputs
  rightX = scale(rightX);
  rightY = scale(rightY);
  leftX = scale(leftX);
  leftY = scale(leftY);

  //combine values for each motor power
  Front_Right(leftY - leftX - rightX);
  Back_Right(leftX + leftY - rightX);
  Back_Left(leftY - leftX + rightX);
  Front_Left(leftX + leftY + rightX);

  //buttons
  if( Ps3.event.button_down.l1 ){  //left bumper pressed
    servo_1.write(0);
  }
  if( Ps3.event.button_down.r1 ){  //right bumper pressed
    servo_1.write(180);
  }
}

void Motor_Test(){  //testing motor connections and directions
  Serial.println("Starting Front Right (motor 1) forward...");
  Front_Right(200);
  delay(5000);
  Serial.println("Stop");
  Front_Right(0);
  delay(5000);
  Serial.println("Starting Front Right (motor 1) reverse...");
  Front_Right(-200);
  delay(5000);
  Serial.println("Stop");
  Front_Right(0);
  delay(5000);

  Serial.println("Starting Back Right (motor 2) forward...");
  Back_Right(200);
  delay(5000);
  Serial.println("Stop");
  Back_Right(0);
  delay(5000);
  Serial.println("Starting Back Right (motor 2) reverse...");
  Back_Right(-200);
  delay(5000);
  Serial.println("Stop");
  Back_Right(0);
  delay(5000);

  Serial.println("Starting Back Left (motor 3) forward...");
  Back_Left(200);
  delay(5000);
  Serial.println("Stop");
  Back_Left(0);
  delay(5000);
  Serial.println("Starting Back Left (motor 3) reverse...");
  Back_Left(-200);
  delay(5000);
  Serial.println("Stop");
  Back_Left(0);
  delay(5000);

  Serial.println("Starting Front Left (motor 4) forward...");
  Front_Left(200);
  delay(5000);
  Serial.println("Stop");
  Front_Left(0);
  delay(5000);
  Serial.println("Starting Front Left (motor 4) reverse...");
  Front_Left(-200);
  delay(5000);
  Serial.println("Stop");
  Front_Left(0);
  delay(5000);
}

void Front_Right(float speed){ //front right control (Motor 1)
  if(speed > 0){  //forward
    speed = constrain(speed, 0, 255);
    ledcWrite(M1_1, speed);
    ledcWrite(M1_2, 0);
  }
  else if(speed < 0){  //reverse
    speed = abs(speed);
    speed = constrain(speed, 0, 255);
    ledcWrite(M1_1, 0);
    ledcWrite(M1_2, speed);
  }
  else{  //stop
    ledcWrite(M1_1, 0);
    ledcWrite(M1_2, 0);
  }
}

void Back_Right(float speed){ //back right control (Motor 2)
  if(speed > 0){  //forward
    speed = constrain(speed, 0, 255);
    ledcWrite(M2_1, speed);
    ledcWrite(M2_2, 0);
  }
  else if(speed < 0){  //reverse
    speed = abs(speed);
    speed = constrain(speed, 0, 255);
    ledcWrite(M2_1, 0);
    ledcWrite(M2_2, speed);
  }
  else{  //stop
    ledcWrite(M2_1, 0);
    ledcWrite(M2_2, 0);
  }
}

void Back_Left(float speed){ //back left control (Motor 3)
  if(speed > 0){  //forward
    speed = constrain(speed, 0, 255);
    ledcWrite(M3_1, speed);
    ledcWrite(M3_2, 0);
  }
  else if(speed < 0){  //reverse
    speed = abs(speed);
    speed = constrain(speed, 0, 255);
    ledcWrite(M3_1, 0);
    ledcWrite(M3_2, speed);
  }
  else{  //stop
    ledcWrite(M3_1, 0);
    ledcWrite(M3_2, 0);
  }
}

void Front_Left(float speed){ //front left control (Motor 4)
  if(speed > 0){  //forward
    speed = constrain(speed, 0, 255);
    ledcWrite(M4_1, speed);
    ledcWrite(M4_2, 0);
  }
  else if(speed < 0){  //reverse
    speed = abs(speed);
    speed = constrain(speed, 0, 255);
    ledcWrite(M4_1, 0);
    ledcWrite(M4_2, speed);
  }
  else{  //stop
    ledcWrite(M4_1, 0);
    ledcWrite(M4_2, 0);
  }
}

void Motor_Setup(){  //setup for motor pins
  ledcAttach(M1_1, BASE_FREQ, TIMER_BIT);
  ledcAttach(M1_2, BASE_FREQ, TIMER_BIT);

  ledcAttach(M2_1, BASE_FREQ, TIMER_BIT);
  ledcAttach(M2_2, BASE_FREQ, TIMER_BIT);

  ledcAttach(M3_1, BASE_FREQ, TIMER_BIT);
  ledcAttach(M3_2, BASE_FREQ, TIMER_BIT);

  ledcAttach(M4_1, BASE_FREQ, TIMER_BIT);
  ledcAttach(M4_2, BASE_FREQ, TIMER_BIT);

  Front_Right(0);
  Back_Right(0);
  Back_Left(0);
  Front_Left(0);
}

float scale(int value){  //scale for joystick inputs
  //joystick values range from -128 to 128
  //motor control values range from -255 to 255
  //parabolic control with a center dead zone of +/- 5
  if (value < -5){ 
    return -1 * (0.02 * sq(value));  //maintain sign
  }
  else if (value > 5){
    return 0.02 * sq(value);
  }
  else{
    return 0;
  }
}

void Servo_Setup(){  //attach and initilize servos
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  
  //set servo pwm frequency
  servo_1.setPeriodHertz(50);    // standard 50 hz servo
  servo_2.setPeriodHertz(50);
  servo_3.setPeriodHertz(50);
  servo_4.setPeriodHertz(50);

  // attach servo to the assigned pin
  servo_1.attach(SERVO_1, 650, 2600);  //min/max us signals
  servo_2.attach(SERVO_2, 650, 2600);
  servo_3.attach(SERVO_3, 650, 2600);
  servo_4.attach(SERVO_4, 650, 2600);

  //initialize the servo to starting position
  servo_1.write(initPos_1);
  servo_2.write(initPos_2);
  servo_3.write(initPos_3);
  servo_4.write(initPos_4);
}