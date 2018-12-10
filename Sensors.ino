#define ENABLE 5
#define DIRA 3
#define DIRB 4


int sensorPin  =  A2;     // select the input  pin for  the potentiometer
int RedPin  =  11;   // select the pin for  the LED
int GreenPin = 12;
int sensorValue =  0;  // variable to  store  the value  coming  from  the sensor
int SmPin = 7;
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
//int LEDpin = 11;          // connect Red LED to pin 11 (PWM pin)
int LEDbrightness;        //
int log2 = 0;

int mq2_analogPin = A1;


void setup()
{
 
  pinMode(RedPin,OUTPUT);
  pinMode(GreenPin,OUTPUT);

  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);

  pinMode(SmPin,OUTPUT);


  Serial.begin(9600);
}
void loop()
{
sensorValue =  analogRead(sensorPin);

//Serial.println(sensorValue,  DEC);


if (sensorValue > 200)
{
    digitalWrite(RedPin, HIGH);
    digitalWrite(GreenPin, LOW);
    delay(1000);
}
else
{
  digitalWrite(RedPin, LOW);
  digitalWrite(GreenPin, HIGH);
}

 photocellReading = analogRead(photocellPin);  
 
  //Serial.print("Analog reading = ");
  //Serial.println(photocellReading);     // the raw analog reading
 
  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  photocellReading = 1023 - photocellReading;
  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  LEDbrightness = map(photocellReading, 0, 1023, 0, 255);
  // analogWrite(LEDpin, LEDbrightness);

if (photocellReading > 400)
{
  //Serial.println("Mphka molis sthn if");
  digitalWrite(ENABLE,HIGH); // enable on  
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  log2 = 1;
  delay(10);
}
else if(log2 == 1)
{
  //Serial.println("Mphka sthn deyeterh if");
  digitalWrite(ENABLE,LOW); // disable
   log2 = 0;
  delay(3000);
}
 

int mq2_value = analogRead(mq2_analogPin);
if (mq2_value < 600)
{
  Serial.println("nomizw piasame fwtia");
  delay(1000);
  int mq2_value = analogRead(mq2_analogPin);
  if (mq2_value < 600)
  {
   Serial.println("piasame ontos fwtia");
   
   digitalWrite(SmPin, HIGH);
   delay(500);
   digitalWrite(SmPin, LOW);
   delay(500);
  }
}

delay(100);

}
