int greenPin=2;
   int yellowPin=3;
   int redPin=4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setup_adc();
  pinMode(greenPin,OUTPUT);
  pinMode(yellowPin,OUTPUT);
  pinMode(redPin,OUTPUT);
}
void loop()
{
  delay(1000);
    ADCSRA |= (1<<ADSC);//comand citirea valorii potentiometrului
}
void setup_adc()
{
  ADMUX |= (1<<REFS0);//activez tensiunea interna de 5 volti ca prag superior pentru procesarea semnalului analogic
  ADMUX |= (1<<MUX1) ;// ADMUX |=(1<<1) ;  voi citi semnalul analogic de pe pinul A2
  ADCSRA |= (1<<3); //activez intreruperea de la finalul conversiei ADC
  ADCSRA |= 0b00000111;//setez valoarea prescalerului la 128
  ADCSRA |= (1<<7);//activez convertorul ADC
}
ISR(ADC_vect)
{
  Serial.println("--------------------------------------------------------------");
  Serial.println(ADC);
  if(ADC < 470)
    {
      Serial.println("LOW GAS LEVEL IN AIR");
   digitalWrite(greenPin,HIGH);
   digitalWrite(yellowPin,LOW);
   digitalWrite(redPin,LOW);    }
  else if(ADC>=470 &&ADC<=480)
  {
    Serial.println("MEDIUM GAS LEVEL IN AIR");
   digitalWrite(greenPin,LOW);
   digitalWrite(yellowPin,HIGH);
   digitalWrite(redPin,LOW);  }
    else if(ADC>480)
    {
    Serial.println("HIGH GAS LEVEL IN AIR");
   digitalWrite(greenPin,LOW);
   digitalWrite(yellowPin,LOW);
   digitalWrite(redPin,HIGH);    }
Serial.println("--------------------------------------------------------------");
}
