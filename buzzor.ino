#include"pitches.h"
const int motor_A1 = 5;
const int motor_A2 = 6;
const int motor_B1 = 9;
const int motor_B2 = 10;
const int IR_R = A1;
const int IR_M = A3;
const int IR_L = A5;
const int trigPin = 2;
const int echoPin = 3;
const int buzzer = 8;
int IR_L_data;
int IR_M_data;
int IR_R_data;

void setup() {
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
  pinMode(IR_L, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_R, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  Serial.print("Start");
  delay(1000);
}

void loop() {
  // 초음파 센서로 거리 측정
  IR_L_data = digitalRead(IR_L);
  IR_M_data = digitalRead(IR_M);
  IR_R_data = digitalRead(IR_R);
  Serial.print(IR_L_data);
  Serial.print("-");
  Serial.print(IR_M_data);
  Serial.print("-");
  Serial.println(IR_R_data);
  long duration, cm_distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm_distance = duration / 29 / 2;

   if (cm_distance <= 20) {  // 장애물이 20cm 이내에 있을 경우
    digitalWrite(buzzer, HIGH);  // 피에조 부저 울림
    delay(1000);
    digitalWrite(buzzer, LOW); 
    delay(1000);
  } 
  if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    Serial.println("직진");
    forward();
  }
  else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    Serial.println("좌회전 ");
    left();
  }
  else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    Serial.println("우회전");
    right();
  }
  else if (IR_L_data == 1  and IR_R_data == 1) {
    Serial.println("정지");
    stop();
  }
}


void right() {
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}

void left() {
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void forward() {
  digitalWrite(motor_A1, HIGH);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, HIGH);
  digitalWrite(motor_B2, LOW);
}

void stop() {
  digitalWrite(motor_A1, LOW);
  digitalWrite(motor_A2, LOW);
  digitalWrite(motor_B1, LOW);
  digitalWrite(motor_B2, LOW);
}

