#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <NewPing.h> 
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define trig_pin A1
#define echo_pin A2
#define maximum_distance 200

int pos0 = 150;
int pos180 = 520;
int buzzer =13;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance);

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
  digitalWrite(buzzer, HIGH);
  delay(1800);
  idle_pos();
  distance = sonar.ping_cm();
  delay(30);
  distance = sonar.ping_cm();
  delay(30);
  distance = sonar.ping_cm();
  delay(30);
  distance = sonar.ping_cm();
  delay(30);
}

void setServo(int servo, int angle) {
  int duty;
  duty = map(angle, 0, 180, pos0, pos180);
  pwm.setPWM(servo, 0, duty);
}

void idle_pos(){
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 180);
  setServo(5, 180);
}

void Forward() {
  setServo(0, 60);
  setServo(1, 120);
  setServo(2, 70);
  setServo(3, 110);
  setServo(4, 180);
  setServo(5, 180);
  delay(180);
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 180);
  setServo(5, 180);
  delay(180);
}

void Backward() {
  setServo(0, 120);
  setServo(1, 60);
  setServo(2, 110);
  setServo(3, 70);
  setServo(4, 180);
  setServo(5, 180);
  delay(180);
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 180);
  setServo(5, 180);
  delay(180);
}

void Stop() {
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 180);
  setServo(5, 180);  
}

void Left() {
  setServo(0, 60);
  setServo(1, 60);
  setServo(2, 70);
  setServo(3, 70);
  setServo(4, 90);
  setServo(5, 180);
  delay(180);
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 90);
  setServo(5, 180);
  delay(180);
}

void Right() {
  setServo(0, 120);
  setServo(1, 120);
  setServo(2, 110);
  setServo(3, 110);
  setServo(4, 180);
  setServo(5, 90);
  delay(180);
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 180);
  setServo(5, 90);
  delay(180);   
}

void Hands_up() {
  setServo(4, 0);
  setServo(5, 0);
}

void hand_dance() {
  setServo(4, 180);
  setServo(5 ,0);
  delay(350);
  setServo(4, 0);
  setServo(5, 180);
  delay(350);
  setServo(4, 90);
  setServo(5, 90);
  delay(350);
  setServo(4, 180);
  setServo(5, 180);
  delay(350);
  setServo(4, 0);
  setServo(5, 0);
  delay(350);
  setServo(4, 0);
  setServo(5 ,180);
  delay(350);
  setServo(4, 180);
  setServo(5, 0);
  delay(350);
  setServo(4, 90);
  setServo(5, 90);
  delay(350);
  setServo(4, 180);
  setServo(5, 180);
  delay(350);  
}

void Small_stop() {
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 180);
  setServo(5, 180);
  delay(1500);  
}

void Semi_auto() {
  setServo(0, 120);
  setServo(1, 60);
  setServo(2, 110);
  setServo(3, 70);
  setServo(4, 160);
  setServo(5, 160);
  digitalWrite(buzzer, HIGH);
  delay(300);
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 160);
  setServo(5, 160);
  digitalWrite(buzzer, LOW);
  delay(300);
}

void loop() {
  distance = sonar.ping_cm();
  delay(30);
  Serial.println(sonar.ping_cm());
   if (Serial.available() > 0) {
    char value = Serial.read();
    Serial.println(value);

    if (value == 'U') {
      Forward();
    } 
    else if (value == 'D') {
      Backward();
    } 
    else if (value == 'S') {
      Stop();
    }
    else if(value == 'L'){
      Right();
    }
    else if(value == 'R'){
      Left();
    }
    else if(value == '1'){
      Hands_up();

    }
    else if(value == '2'){
      idle_pos();

    }
    else if(value == '3') {
      hand_dance();

    }
    else if(value == '4') {
      Small_stop();

    }
  }
  else if(distance <= 7) {
    Semi_auto();

    }
  }
