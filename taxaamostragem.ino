const int potPin = 34;
// variable for storing the potentiometer value
int potValue = 0;
uint16_t val1, val2, val3, val4, val5, val6, val7, val8, val9, val10;
uint16_t t1, t2, t3, t4, t5, t6, t7, t8, t9, t10; 

void setup() {
  Serial.begin(115200);
  delay(1000);
  // Reading potentiometer value
  t1=micros();
  val1 = analogRead(potPin);
  t2=micros();
  val2 = analogRead(potPin);
  t3=micros();
  val3 = analogRead(potPin);
  t4=micros();
  val4 = analogRead(potPin);
  t5=micros();
  val5 = analogRead(potPin);
  t6=micros();
  val6 = analogRead(potPin);
  t7=micros();
  val7 = analogRead(potPin);
  t8=micros();
  val8 = analogRead(potPin);
  t9=micros();
  val9 = analogRead(potPin);
  t10=micros();
  val10 = analogRead(potPin);

  
  Serial.print("1- microsegundo="); Serial.print(t1); Serial.print(" - Valor="); Serial.println(val1);
  Serial.print("2- microsegundo="); Serial.print(t2); Serial.print(" - Valor="); Serial.println(val2);
  Serial.print("3- microsegundo="); Serial.print(t3); Serial.print(" - Valor="); Serial.println(val3);
  Serial.print("4- microsegundo="); Serial.print(t4); Serial.print(" - Valor="); Serial.println(val4);
  Serial.print("5- microsegundo="); Serial.print(t5); Serial.print(" - Valor="); Serial.println(val5);
  Serial.print("6- microsegundo="); Serial.print(t6); Serial.print(" - Valor="); Serial.println(val6);
  Serial.print("7- microsegundo="); Serial.print(t7); Serial.print(" - Valor="); Serial.println(val7);
  Serial.print("8- microsegundo="); Serial.print(t8); Serial.print(" - Valor="); Serial.println(val8);
  Serial.print("9- microsegundo="); Serial.print(t9); Serial.print(" - Valor="); Serial.println(val9);
  Serial.print("10- microsegundo="); Serial.print(t10); Serial.print(" - Valor="); Serial.println(val10);
}

void loop() {

}
