int ledpin = 7;
int ldrpin = 5;
int valor = 0;
int percentual = 0;

void setup(){
	pinMode(7,OUTPUT);
  	Serial.begin(9600);
}

void loop(){
	valor = analogRead(ldrpin);
  	percentual = map(valor,0,1023,0,100);
  if (percentual<40){
  	digitalWrite(ledpin,1);

  }else{
    digitalWrite(ledpin,0);}
    Serial.print("Porcentagem de Luz na sala: ");
    Serial.print(percentual);
    Serial.println("%");
    delay(500);
}
