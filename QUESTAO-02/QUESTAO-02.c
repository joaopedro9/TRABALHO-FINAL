const int pingPin = 6;
long cemtimetros = 0;

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  
  lcd.setCursor(4,0);
  lcd.print("Projeto");
  
  lcd.setCursor(2,1);   
  lcd.print("Trena Digital");
  
  Serial.begin(9600);
}

void loop() {
  long duration, cm;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = microsecondsToCentimeters(duration);

  if (cm != cemtimetros) {
   
    cemtimetros = cm;

    Serial.println(cm);

    lcd.setCursor(2,0);
    lcd.print("Medida em Cm");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(6,1);
    lcd.print(cm);
    lcd.print("cm");
  }

  delay(80);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
