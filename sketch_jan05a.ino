#include <Wire.h>
#include <BluetoothSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include <NewPingESP8266.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
BluetoothSerial SerialBT;

#define SENSOR_PIN 19
#define trig_pin 32
#define echo_pin 33
#define maximum_distance 200

NewPingESP8266 sonar(trig_pin, echo_pin, maximum_distance);

int state = digitalRead(SENSOR_PIN);
int pos0 = 150;
int pos180 = 520;
int buzzer = 18;
int distance = 100;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(115200);
  SerialBT.begin("Scion V1 Robot");
  Serial.println("Scion V1 Robot.");
  pwm.begin();
  pwm.setPWMFreq(50);
  digitalWrite(buzzer, HIGH);
  delay(1000);
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
  delay(200);
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 180);
  setServo(5, 180);
  delay(200);
}

void Backward() {
  setServo(0, 120);
  setServo(1, 60);
  setServo(2, 110);
  setServo(3, 70);
  setServo(4, 180);
  setServo(5, 180);
  delay(200);
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 180);
  setServo(5, 180);
  delay(200);
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
  setServo(4, 180);
  setServo(5, 90);
  delay(200);
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 180);
  setServo(5, 90);
  delay(200);
}

void Right() {
  setServo(0, 120);
  setServo(1, 120);
  setServo(2, 110);
  setServo(3, 110);
  setServo(4, 90);
  setServo(5, 180);
  delay(200);
  setServo(0, 90);
  setServo(1, 90);
  setServo(2, 90);
  setServo(3, 90);
  setServo(4, 90);
  setServo(5, 180);
  delay(200);   
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

void Semi_auto2() {
   setServo(0, 60);
  setServo(1, 120);
  setServo(2, 70);
  setServo(3, 110);
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
  if (SerialBT.available() > 0) {
    char value = SerialBT.read();
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
   else if(state == HIGH) {
    Semi_auto2();
   }
  }
  
