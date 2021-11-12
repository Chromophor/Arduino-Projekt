# Arduino-Projekt
Enrichment-Kurs

Code für eine Ampelschaltung mit einem Arduino



const int button = 5;
const int buzzer = 7;
int state = 0;
const int rot1 = 1;
const int gelb1 = 2;
const int grun1 = 3;
const int rot2 = 6;
const int gelb2 = 4;
const int grun2 = 0;

void setup()
{
  pinMode(rot1, OUTPUT); 
  pinMode(gelb1, OUTPUT);
  pinMode(grun1, OUTPUT);
  pinMode(rot2, OUTPUT); 
  pinMode(gelb2, OUTPUT);
  pinMode(grun2, OUTPUT);
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() 
{
  state = digitalRead(button);
  
  digitalWrite(grun2, HIGH);
  
  if(state == HIGH) {
  
  clightr();
  delay(1000);
  plight();
  delay(1000);
  clightg();

  } else {
  digitalWrite(rot1, HIGH);
  }
}

void plight() {
  digitalWrite(rot1, HIGH);
  delay(1000);
  digitalWrite(gelb1, HIGH);
  delay(1000);
  digitalWrite(rot1, LOW);
  delay(100);
  digitalWrite(gelb1, LOW);
  delay(10);
  digitalWrite(grun1, HIGH);
  sound();
  digitalWrite(gelb1, HIGH);
  delay(10);
  digitalWrite(grun1, LOW);
  delay(1000);
  digitalWrite(gelb1, LOW);
  delay(10);
  digitalWrite(rot1, HIGH);
}

void clightr(){
  digitalWrite(grun2, LOW);
  digitalWrite(gelb2, HIGH);
  delay(500);
  digitalWrite(rot2, HIGH);
  delay(100);
  digitalWrite(gelb2, LOW);
}

void clightg(){
  digitalWrite(gelb2, HIGH);
  delay(500);
  digitalWrite(rot2, LOW);
  delay(500);
  digitalWrite(gelb2, LOW);
  digitalWrite(grun2, HIGH);
}

void sound(){
  tone(buzzer, 400);
  delay(1000);
  noTone(buzzer);
  delay(1000);
  tone(buzzer, 400);
  delay(1000);
  noTone(buzzer);
  delay(1000);
  tone(buzzer, 400);
  delay(1000);
  noTone(buzzer);
}

![Copy of Ampel](https://user-images.githubusercontent.com/88386049/141505817-fa38ad63-de32-456b-ba5c-0c8856f134b2.png)


