#define relay 12
#define buzzer 3
 char a;
 bool on=false;
 int count=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(relay,OUTPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(relay,HIGH);
  digitalWrite(buzzer,LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    a=Serial.read();
    Serial.print(a);
    if(a=='@')
    {
      digitalWrite(relay,LOW);
      digitalWrite(buzzer,HIGH);
       delay(250);
       digitalWrite(buzzer,LOW);
       delay(250);
       digitalWrite(buzzer,HIGH);
       delay(250);
       digitalWrite(buzzer,LOW);
       on=true;
    }
    else if(a=='%')
    {
      digitalWrite(relay,HIGH);
      on=false;
      count=0;
    }
    else if(a=='&')
    {
      digitalWrite(buzzer,HIGH);
      delay(500);
      digitalWrite(buzzer,LOW);
    }
  }
else if(on){
  count++;
  if(count>=10000)
  {
    digitalWrite(relay,HIGH);
      on=false;
      count=0;
  }
  delay(1);
}

}
