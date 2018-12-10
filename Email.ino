/********************************
 * Libraries included            *
 *******************************/
#include <Ethernet.h>
#include <SPI.h>
#include <UbidotsEthernet.h>

/********************************
 * Constants and objects
 *******************************/
/* Assigns the Ubidots parameters */
char const * TOKEN = "A1E-YbA9TgGvzKO5qhuJmXmQuMAogTtKry"; // Assign your Ubidots TOKEN
char const * VARIABLE_LABEL_1 = "5c0cdbafc03f97329ca104a5"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_2 = "5c0cdb1cc03f973233a1e459"; // Assign the unique variable label to send the data
char const * VARIABLE_LABEL_3 = "5c0cdac1c03f97315066af57"; // Assign the unique variable label to send the data

/* Enter a MAC address for your controller below */
/* Newer Ethernet shields have a MAC address printed on a sticker on the shield */
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

/* initialize the instance */
Ubidots client(TOKEN);

int al=8;
int dr=7;
int sm=4;

int value_1;
int value_2;
int value_3;

int value_1_log = 0;
int value_2_log = 0;
int value_3_log = 0;

/********************************
 * Main Functions
 *******************************/
void setup()
{
  Serial.begin(9600);

  /*Inputs*/
  pinMode(al,INPUT);
  pinMode(dr,INPUT);
  pinMode(sm,INPUT);
      
  //client.setDebug(true);// uncomment this line to visualize the debug message
  /* start the Ethernet connection */
  Serial.print(F("Starting ethernet..."));
  if (!Ethernet.begin(mac)) {
    Serial.println(F("failed"));
  } else {
    Serial.println(Ethernet.localIP());
  }
  /* Give the Ethernet shield a second to initialize */
  delay(2000);
  Serial.println(F("Ready"));
}

void loop()
{

  Ethernet.maintain();
  Serial.println("ksekinaw");
  for(int i=0; i <= 2000; i++)
  {
      /* Sensors readings */
      value_1 = digitalRead(al);
      value_2 = digitalRead(dr);
      value_3 = digitalRead(sm);
      
      if (value_1 == 1)
      {
        value_1_log = 1;
      }
      
      if (value_2 == 1)
      {
        value_2_log = 1;
      }
      
      if (value_3 == 1)
      {
        value_3_log = 1;
      }
      Serial.println(i);
  } 
  
  Serial.println(value_1_log);
  Serial.println(value_2_log);
  Serial.println(value_3_log);

  Serial.println("teleiwsa");

  /* Sending values to Ubidots */
  
  client.add(VARIABLE_LABEL_1, value_1_log);
  client.add(VARIABLE_LABEL_2, value_2_log);
  client.add(VARIABLE_LABEL_3, value_3_log);
  client.sendAll();

  /*reset the values*/
  value_1_log = 0;
  value_2_log = 0;
  value_3_log = 0;
  
  //delay(5000); it does not make a diference because the for replace it
}
