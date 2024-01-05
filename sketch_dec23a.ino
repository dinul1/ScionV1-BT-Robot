#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String command;

const char* ssid = "Scion V1";
ESP8266WebServer Server(80);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


#define SENSOR_PIN 15
#define maximum_distance 400

int pos0 = 150;
int pos180 = 520;
int buzzer =14;
int distance = 100;

void setup() {
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  pwm.begin();
  pwm.setPWMFreq(50);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  idle_pos();

WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
     Server.on ( "/", HTTP_handleRoot );
     Server.onNotFound ( HTTP_handleRoot );
     Server.begin();    
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

void Semi_auto1() {
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
  setServo(5, 180);
  digitalWrite(buzzer, LOW);
  delay(300);
}

 void loop() {
  int state = digitalRead(SENSOR_PIN);
  Server.handleClient();
    
      command = Server.arg("State");
      if (command == "F") Forward();
      else if (command == "B") Backward();
      else if (command == "L") Right();
      else if (command == "R") Left();
      else if (command == "S") Stop();
      else if (command == "I") hand_dance();
      else if (command == "G") Hands_up();
      else if (command == "J") idle_pos();
      else if (command == "H") Small_stop();
      else if(state == HIGH) Semi_auto2();
  
}

void HTTP_handleRoot(void) {

if( Server.hasArg("State") ){
       Serial.println(Server.arg("State"));
  }
  Server.send ( 200, "text/html", "" );
  delay(1);
}
