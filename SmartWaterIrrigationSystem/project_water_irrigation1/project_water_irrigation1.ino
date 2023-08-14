#include<HCSR04.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);       //SDA = A4, SCL = A5
#include<Servo.h>
Servo s1;

int water;
int relay=3;
long trig=7;
long echo=6;
long timeInMicro;
long distanceInCm;
long level;
#define sensor A2
#define wet 210
#define dry 510

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  s1.attach(9);
  // s1.write(0);
  pinMode(3, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop(){
  water=analogRead(sensor);
  int pre = map(water, wet, dry, 0, 100);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(100);
  digitalWrite(trig, LOW);
  timeInMicro=pulseIn(echo, HIGH);
  distanceInCm=timeInMicro/29/2;
  Serial.println(distanceInCm);
  delay(1000);
  long level = map(28-distanceInCm, 0, 28, 0, 100 );
  if(level>=80){
    s1.write(120);
    lcd.setCursor(10, 1);
    lcd.print("CLOSED");
  }
  else if(level<80){
    s1.write(0);
    lcd.setCursor(10, 1);
    lcd.print("OPEN");
    
  }
  if(pre>50 && level>15){
    digitalWrite(3, LOW);
    lcd.setCursor(5, 1);
    lcd.print("ON ");
  }
  else {
    digitalWrite(3, HIGH);
    lcd.setCursor(5, 1);
    lcd.print("OFF");
  }
  delay(200);
  
  
  if(pre>50){
    lcd.setCursor(5, 0);
    lcd.print("DRY");
  }
  else if(pre<=50){
    lcd.setCursor(5, 0);
    lcd.print("WET");
  }
  lcd.setCursor(0, 0);
  lcd.print("SOIL:");
  lcd.setCursor(0, 1);
  lcd.print("PUMP:");
  
  lcd.setCursor(9, 0);
  lcd.print("TANK");
  lcd.setCursor(13, 0);
  lcd.print(level);
  lcd.print("%");
  



}