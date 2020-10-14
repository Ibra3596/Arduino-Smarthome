
#include <LiquidCrystal.h>
#include<Servo.h>
const int rain_D = 15;//A1
const int buzzerPin = 12;
const int flamePin = 13;
int Flame = LOW;
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int LEDr = 14;//A0
const int LEDg = 16;//A2
//const int LEDf = 9;
int ledrState = LOW;
int ledgState = LOW;
//int ledfState = LOW;
int const trigPin = 11;
int const echoPin = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo servo;


 
void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
    servo.attach(A3);
  pinMode(rain_D, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(flamePin, INPUT);
  pinMode(LEDr, OUTPUT);
  pinMode(LEDg, OUTPUT);
 // pinMode(LEDf, OUTPUT);
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("   Smart Home   ");
  // Print a message to the LCD.
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  RainAlert();

  FlameAlarm();

  GarageDoor();
  
  //GLed();
}

  void myDelay(int del) {
    unsigned long myPrevMillis = millis();
    unsigned long myCurrentMillis = myPrevMillis;
    while (myCurrentMillis - myPrevMillis <= del) {
    myCurrentMillis = millis();
    }
  }

  void FlameAlarm(){
    //digitalWrite(LEDf,ledfState);
  Flame = digitalRead(flamePin);
  if (Flame== HIGH)
  {
  //Serial.println("Fire!!!"); 
  //ledfState = HIGH;
  lcd.setCursor(6, 1);
  lcd.print("Fire!");
  digitalWrite(buzzerPin, HIGH);
  myDelay(300);
  digitalWrite(buzzerPin, LOW);
  
  }
  else
  {
  //Serial.println("No worries");
  defaultLCD();
  //digitalWrite(buzzerPin, LOW);
  //ledfState = LOW;
  }
    }
  void RainAlert(){
    digitalWrite(LEDr, ledrState);
  if(digitalRead(rain_D) == LOW) 
  {
    //Serial.println("Digital value : wet");
    lcd.setCursor(0, 1);
    lcd.print("Rain"); 
    ledrState = HIGH;
    myDelay(300);
  }
else
  {
    //Serial.println("Digital value : dry");
    ledrState = LOW;
    myDelay(300);
    defaultLCD();
  }
  }
  void GarageDoor(){
      int duration, distance;
  digitalWrite(trigPin, HIGH); 
  digitalWrite(trigPin, LOW);
  digitalWrite(LEDg, ledgState);
  // Measure the pulse input in echo pin
  duration = pulseIn(echoPin, HIGH);
  // Distance is half the duration devided by 29.1 (from datasheet)
  distance = (duration/2) / 29.1;
  // if distance less than 0.16.5 meter and more than 0 (0 or less means over range) 
  if (distance <= 16.5 && distance >= 0)
    {
      ledgState = HIGH;
      servo.write(50);
      lcd.setCursor(0, 1);
      lcd.print(" Garage is open");
      
        myDelay(3000);
       
    }
  else
    {
    servo.write(160);
    
      defaultLCD();
       ledgState = LOW;
       // Waiting 60 ms won't hurt any one
      myDelay(60);
      }
  }
  
  void defaultLCD(){
    lcd.clear();
    lcd.print("   Smart Home   ");
  }
