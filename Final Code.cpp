#include <SPI.h>
#include <MFRC522.h>

/*-
SCK  52   BLACK \ YELLOW
MOSI 51   VITKARI \ RED
MISO 50   JAMBALII \ ORANGE
GND       GREEN \ WHITE \ ORANGE
VOLT      BLUE \ GRAY\ 
SDA       WHITE \ ORANGE \RED \YELLOW
RST       BLACK \ JAMBALA
*/

#define SS_PIN_1 53       // WHITE \ BLUE 53
#define SS_PIN_2 47       // WHITE \ WHITE \ YELLOW 47
#define SS_PIN_3 43       // ORANGE \ RED 43
#define SS_PIN_4 39       // WHITE 39

#define RST_PIN_1 49      //  BLACK \ VITKARI 49
#define RST_PIN_2 45      //  BLACK \ GRAY \ JAMBHALA 45
#define RST_PIN_3 41      //  BLACK \ JAMBHALI 41
#define RST_PIN_4 37      //  BLACK 37

MFRC522 mfrc522_4(SS_PIN_4, RST_PIN_4);   // Create Instance For Lane 4 RED
MFRC522 mfrc522_3(SS_PIN_3, RST_PIN_3);   // Create Instance For Lane 3 RED
MFRC522 mfrc522_2(SS_PIN_2, RST_PIN_2);   // Create Instance For Lane 2 RED
MFRC522 mfrc522_1(SS_PIN_1, RST_PIN_1);   // Create Instance For Lane 1 RED
int Lane1[] = {2,3,4};      // Lane 1 Red, Yellow, and Green
int Lane2[] = {5,6,7};      // Lane 3 Red, Yellow, and Green
int Lane3[] = {8,9,10};     // Lane 4 Red, Yellow and Green
int Lane4[] = {11,12,13};   // Lane 2 Red, Yellow, and Green

void setup() 
{
  Serial.begin(9600);     // Initiate a serial communication
  SPI.begin();            // Initiate  SPI bus
  mfrc522_4.PCD_Init();   // Initiate  RFID Reader IN Lane 4 RED
  mfrc522_3.PCD_Init();   // Initiate  RFID Reader IN Lane 3 RED
  mfrc522_2.PCD_Init();   // Initiate  RFID Reader IN Lane 2 RED
  mfrc522_1.PCD_Init();   // Initiate  RFID Reader IN Lane 1 RED
  Serial.println("TRAFFIC LIGHT WORK PROPERLY!!!");
  Serial.println();

 for (int i = 0; i < 3; i++)
  {
    pinMode(Lane1[i], OUTPUT); 
    pinMode(Lane2[i], OUTPUT);
    pinMode(Lane3[i], OUTPUT);
    pinMode(Lane4[i], OUTPUT);
  }
}

void loop() 
{ 
  while( ! mfrc522_4.PICC_IsNewCardPresent() || ! mfrc522_4.PICC_ReadCardSerial() || ! mfrc522_3.PICC_IsNewCardPresent() || ! mfrc522_3.PICC_ReadCardSerial() || ! mfrc522_2.PICC_IsNewCardPresent() || ! mfrc522_2.PICC_ReadCardSerial() || ! mfrc522_1.PICC_IsNewCardPresent() || ! mfrc522_1.PICC_ReadCardSerial()){
    
    Lane1G();
    Lane1Y_2Y();
    Lane2G();
    Lane2Y_3Y();
    Lane3G();
    Lane3Y_4Y();
    Lane4G();
    Lane4Y_1Y();
    Lane1Y_4R();
  } 
}

//  START TRAFFIC LIGHT

void Lane1G(){
  digitalWrite(Lane1[2], HIGH);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[0], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 GREEN");
    DetectLane3R_1G();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 GREEN
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 GREEN");
    DetectLane4R_1G();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 GREEN
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

void Lane1Y_2Y(){
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  delay(2000);  //  MAKE LANE 1 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 AND LANE 2 YELLOW");
    DetectLane1R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
   if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 2 YELLOW");
    DetectLane3R_1Y_2Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 2 Yellow");
    DetectLane4R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

void Lane2G(){
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane2[2], HIGH);
  delay(4000);  // MAKE LANE 2 GREEN

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 GREEN");
    DetectLane1R_2G();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 GREEN
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 GREEN");
    DetectLane4R_2G();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 GREEN
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

void Lane2Y_3Y(){
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 AND LANE 3 YELLOW");
    DetectLane1R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 3 YELLOW");
    DetectLane2R_2Y_3Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 3 Yellow");
    DetectLane4R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

void Lane3G(){
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane3[2], HIGH);
  digitalWrite(Lane2[0], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 GREEN");
    DetectLane1R_3G();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 GREEN
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 GREEN");
    DetectLane2R_3G(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 GREEN
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

void Lane3Y_4Y(){
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 3 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 AND LANE 4 YELLOW");
    DetectLane1R_3Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
    if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 4 YELLOW");
    DetectLane3R_3Y_4Y(); //  AMBULNACE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("AMBULNACE DETECT IN LANE 2 RED WHEN LANE 1 AND LANE 4 YELLOW");
    DetectLane2R_3Y_4Y(); //  AMBULNACE DETECT IN LANE 2 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

void Lane4G(){
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  //  MAKE LANE 4 GREEN

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 GREEN");
    DetectLane3R_4G();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 GREEN
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 GREEN");
    DetectLane2R_4G(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 GREEN
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

void Lane4Y_1Y(){
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane4[0], LOW);
  delay(2000);  //  MAKE LANE 4 AND 1 YELLOW

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 AND LANE 1 YELLOW");
    DetectLane3R_4Y_1Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 AND LANE 1 YELLOW");
    DetectLane2R_4Y_1Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN Lane 4 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 1 Yellow");
    DetectLane4R_4Y_1Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

void Lane1Y_4R(){
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane4[1], LOW);
}

//  START AMBULANCE DETECTION 

/********************************************************************************************************************************************************************/

//  START LANE 1 RED AMBULANCE DETECTION

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 GREEN
void DetectLane1R_2G(){
  Serial.println("Ambulance Detect in Lane1R");
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 2 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 AND LANE 2 YELLOW");
    DetectLane1R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 AND LANE 2 YELLOW");
    DetectLane2R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 AND LANE 2 YELLOW");
    DetectLane3R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 AND LANE 2 YELLOW");
    DetectLane4R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 GREEN
void DetectLane1R_3G(){
  Serial.println("Ambulance Detect in Lane1R");
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 3 YELLOW
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane1R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane2R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane3R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane4R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  1 AND LANE 2 YELLOW
void DetectLane1R_1Y_2Y(){
  Serial.println("Ambulance Stuck in Lane 1R");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  // MAKE LANE 1 GREEN
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  // MAKE LANE 1 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 AND LANE 2 YELLOW");
    DetectLane1R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 AND LANE 2 YELLOW");
    DetectLane2R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 AND LANE 2 YELLOW");
    DetectLane3R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 AND LANE 2 YELLOW");
    DetectLane4R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  2 AND LANE 3 YELLOW
void DetectLane1R_2Y_3Y(){
  Serial.println("Ambulance Detect in Lane1R");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 2 YELLOW
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane1R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane2R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane3R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane4R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  3 AND LANE 4 YELLOW
void DetectLane1R_3Y_4Y(){
  Serial.println("Ambulance Detect in Lane1R");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 4 YELLOW
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 AND LANE 4 YELLOW");
    DetectLane1R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 AND LANE 4 YELLOW");
    DetectLane2R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 AND LANE 4 YELLOW");
    DetectLane3R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 AND LANE 4 YELLOW");
    DetectLane4R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  1 AND LANE 3 YELLOW
void DetectLane1R_1Y_3Y(){
  Serial.println("Ambulance Detect in Lane1R");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane1R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane2R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane3R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 AND LANE 3 YELLOW");
    DetectLane4R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  1 AND LANE 4 YELLOW
void DetectLane1R_1Y_4Y(){
  Serial.println("Ambulance Detect in Lane1R");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 AND LANE 4 YELLOW");
    DetectLane1R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 AND LANE 4 YELLOW");
    DetectLane2R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 AND LANE 4 YELLOW");
    DetectLane3R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 AND LANE 4 YELLOW");
    DetectLane4R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  STOP LANNE 1 RED AMBULANCE DETECTION 

/**************************************************************************************************************************************************************************/

//  START LANE 2 RED AMBULANCE DETECTION

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 GREEN
void DetectLane2R_3G(){
  Serial.println("Ambulance Detect in Lane2R");
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 AND LANE 3 YELLOW");
    DetectLane1R_2Y_3Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN Lane 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 AND LANE 3 YELLOW");
    DetectLane2R_2Y_3Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN Lane 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 AND LANE 3 YELLOW");
    DetectLane3R_2Y_3Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN Lane 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 AND LANE 3 YELLOW");
    DetectLane4R_2Y_3Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN Lane 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 GREEN
void DetectLane2R_4G(){
  Serial.println("Ambulance Detect in Lane2R");
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane1R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 AND LANE 2 YELLOW");
    DetectLane2R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane3R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane4R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 AND LANE 3 YELLOW
void DetectLane2R_2Y_3Y(){
  Serial.println("Ambulance Detect in Lane2R");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 AND LANE 3 YELLOW");
    DetectLane1R_2Y_3Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN Lane 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 AND LANE 3 YELLOW");
    DetectLane2R_2Y_3Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN Lane 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 AND LANE 3 YELLOW");
    DetectLane3R_2Y_3Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN Lane 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 AND LANE 3 YELLOW");
    DetectLane4R_2Y_3Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN Lane 2 AND LANE 3 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 AND LANE 4 YELLOW
void DetectLane2R_3Y_4Y(){
  Serial.println("Ambulance Detect in Lane2R");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane1R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane2R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane3R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane4R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 AND LANE 1 YELLOW
void DetectLane2R_4Y_1Y(){
  Serial.println("Ambulance Detect in Lane2R");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 AND LANE 1 YELLOW");
    DetectLane1R_2Y_1Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN Lane 2 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 AND LANE 1 YELLOW");
    DetectLane2R_2Y_1Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN Lane 2 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 AND LANE 1 YELLOW");
    DetectLane3R_2Y_1Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN Lane 2 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 AND LANE 1 YELLOW");
    DetectLane4R_2Y_1Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN Lane 2 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 AND LANE 4 YELLOW
void DetectLane2R_2Y_4Y(){
  Serial.println("Ambulance Detect in Lane2R");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane1R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane2R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane3R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 AND LANE 4 YELLOW");
    DetectLane4R_2Y_4Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN Lane 2 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 AND LANE 4 YELLOW
void DetectLane2R_2Y_1Y(){
  Serial.println("Ambulance Detect in Lane2R");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 AND LANE 1 YELLOW");
    DetectLane1R_2Y_1Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN Lane 2 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 AND LANE 1 YELLOW");
    DetectLane2R_2Y_1Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN Lane 2 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 AND LANE 1 YELLOW");
    DetectLane3R_2Y_1Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN Lane 2 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 AND LANE 1 YELLOW");
    DetectLane4R_2Y_1Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN Lane 2 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}

//  STOP LANNE 2 RED AMBULANCE DETECTION 

/*******************************************************************************************************************************************************************************/

//  START LANE 3 RED AMBULANCE DETECTION

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 GREEN
void DetectLane3R_1G(){
  Serial.println("Ambulance Stuck in Lane 3RED");
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  // MAKE LANE 1 AND LANE 3 YELLOW
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane3[2], HIGH);
  delay(4000);  // MAKE LANE 3 GREEN
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  delay(2000);  //  MAKE LANE 3 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 AND LANE 1 YELLOW");
    DetectLane1R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 AND LANE 1 YELLOW 
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 AND LANE 1 YELLOW");
    DetectLane2R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 AND LANE 1 YELLOW 
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 AND LANE 1 YELLOW");
    DetectLane3R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 AND LANE 1 YELLOW 
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  
//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 AND LANE 1 YELLOW");
    DetectLane4R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 AND LANE 1 YELLOW 
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane3[1], LOW);
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 GREEN
void DetectLane3R_4G(){
  Serial.println("Ambulance Stuck in Lane 3");
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  // MAKE LANE 1 AND LANE 3 YELLOW
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane3[2], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 3 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 AND LANE 4 YELLOW");
    DetectLane1R_3Y_4Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 43 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 AND LANE 4 YELLOW");
    DetectLane2R_3Y_4Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 43 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 AND LANE 4 YELLOW");
    DetectLane3R_3Y_4Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 43 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 AND LANE 4 YELLOW");
    DetectLane4R_3Y_4Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 43 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane3[1], LOW);
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 AND LANE 2 YELLOW
void DetectLane3R_1Y_2Y(){
  Serial.println("Ambulance Stuck in Lane 3");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 3 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane3[2], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane2[0], LOW);
  delay(2000);  //  MAKE LANE 3 AND 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 AND LANE 2 YELLOW");
    DetectLane1R_3Y_2Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 AND LANE 2 YELLOW");
    DetectLane2R_3Y_2Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 AND LANE 2 YELLOW");
    DetectLane3R_3Y_2Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 AND LANE 2 YELLOW");
    DetectLane4R_3Y_2Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 AND LANE 4 YELLOW
void DetectLane3R_3Y_4Y(){
  Serial.println("Ambulance Stuck in Lane 3");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[2], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 3 AND LANE 4 YELLOW

//  RFID LANE 1
   if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 AND LANE 4 YELLOW");
    DetectLane1R_3Y_4Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
   if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 AND LANE 4 YELLOW");
    DetectLane2R_3Y_4Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
   if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 AND LANE 4 YELLOW");
    DetectLane3R_3Y_4Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
   if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 AND LANE 4 YELLOW");
    DetectLane4R_3Y_4Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 AND LANE 4 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 AND LANE 1 YELLOW
void DetectLane3R_4Y_1Y(){
  Serial.println("Ambulance Stuck in Lane 3");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 3 AND LANE 4 YELLOW
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane3[2], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  delay(2000);  //  MAKE LANE 3 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 AND LANE 1 YELLOW");
    DetectLane1R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 AND LANE 1 YELLOW");
    DetectLane2R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 AND LANE 1 YELLOW");
    DetectLane3R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 AND LANE 1 YELLOW");
    DetectLane4R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 AND LANE 2 YELLOW
void DetectLane3R_3Y_2Y(){
  Serial.println("Ambulance Detect in Lane3R");
  digitalWrite(Lane3[2], HIGH);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane2[1], LOW);
  delay(4000);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  delay(2000);  // MAKE LANE 3 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 AND LANE 2 YELLOW");
    DetectLane1R_3Y_2Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 AND LANE 2 YELLOW");
    DetectLane2R_3Y_2Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 AND LANE 2 YELLOW");
    DetectLane3R_3Y_2Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 AND LANE 2 YELLOW");
    DetectLane4R_3Y_2Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 AND LANE 2 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 AND LANE 1 YELLOW
void DetectLane3R_3Y_1Y(){
  Serial.println("Ambulance Detect in Lane3R");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[2], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 3 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 And Lane 1 YELLOW");
    DetectLane1R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 And Lane 1 YELLOW");
    DetectLane2R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 And Lane 1 YELLOW");
    DetectLane3R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 And Lane 1 YELLOW");
    DetectLane4R_3Y_1Y(); //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 AND LANE 1 YELLOW
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}
//  STOP LANNE 3 RED AMBULANCE DETECTION 

/***************************************************************************************************************************************************************************/

//  START LANE 4 RED AMBULANCE DETECTION

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 GREEN
void DetectLane4R_1G(){
  Serial.println("Ambulance Stuck in Lane 4RED");
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 1 YELLOW
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  // MAKE LANE 4 GREEN
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  delay(2000);  //  MAKE LANE 4 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 1 Yellow");
    DetectLane1R_4Y_1Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 1 Yellow");
    DetectLane2R_4Y_1Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 1 Yellow");
    DetectLane3R_4Y_1Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 1 Yellow");
    DetectLane4R_4Y_1Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane4[1], LOW);
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 GREEN
void DetectLane4R_2G(){
  Serial.println("Ambulance Stuck in Lane 4RED");
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 2 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  // MAKE LANE 4 GREEN
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  delay(2000);  //  MAKE LANE 4 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 2 Yellow");
    DetectLane1R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 2 Yellow");
    DetectLane2R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 2 Yellow");
    DetectLane3R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 2 Yellow");
    DetectLane4R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane4[1], LOW);
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 AND LANE 2 YELLOW
void DetectLane4R_1Y_2Y(){
  Serial.println("Ambulance Stuck in Lane 4RED");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 2 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  // MAKE LANE 4 GREEN
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 2 Yellow");
    DetectLane1R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 2 Yellow");
    DetectLane2R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 2 Yellow");
    DetectLane3R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 2 Yellow");
    DetectLane4R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  2 AND LANE 3 YELLOW
void DetectLane4R_2Y_3Y(){
  Serial.println("Ambulance Stuck in Lane 4RED");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 2 YELLOW
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  // MAKE LANE 4 GREEN
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 2 Yellow");
    DetectLane1R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 2 Yellow");
    DetectLane2R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 2 Yellow");
    DetectLane3R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 2 Yellow");
    DetectLane4R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  4 AND LANE 1 YELLOW
void DetectLane4R_4Y_1Y(){
  Serial.println("Ambulance Stuck in Lane 4RED");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  // MAKE LANE 4 GREEN
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 1 Yellow");
    DetectLane1R_4Y_1Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 1 Yellow");
    DetectLane2R_4Y_1Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 1 Yellow");
    DetectLane3R_4Y_1Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 1 Yellow");
    DetectLane4R_4Y_1Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  4 AND LANE 2 YELLOW
void DetectLane4R_4Y_2Y(){
  Serial.println("Ambulance Stuck in Lane 4RED");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  // MAKE LANE 4 GREEN
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 2 Yellow");
    DetectLane1R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 2 Yellow");
    DetectLane2R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 2 Yellow");
    DetectLane3R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  
//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 2 Yellow");
    DetectLane4R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  4 AND LANE 3 YELLOW
void DetectLane4R_4Y_3Y(){
  Serial.println("Ambulance Stuck in Lane 4RED");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  // MAKE LANE 4 GREEN
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 3 Yellow");
    DetectLane1R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 3 Yellow");
    DetectLane2R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 3 Yellow");
    DetectLane3R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 3 Yellow");
    DetectLane4R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  STOP LANE 4 RED AMBULANCE DETECTION 

/*****************************************************************************************************************************************************************************/

//  NEW LANE 1 START AMBULANCE DETECTION

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE  1 AND LANE 2 YELLOW
void DetectLane2R_1Y_2Y(){
  Serial.println("Ambulance Detect in Lane 2 RED");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 And Lane 2 Yellow");
    DetectLane1R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 2 Yellow");
    DetectLane2R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 2 Yellow");
    DetectLane3R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 2 Yellow");
    DetectLane4R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE  1 AND LANE 3 YELLOW
void DetectLane2R_1Y_3Y(){
  Serial.println("Ambulance Detect in Lane 2 RED");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 And Lane 2 Yellow");
    DetectLane1R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 And Lane 2 Yellow");
    DetectLane2R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 And Lane 2 Yellow");
    DetectLane3R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 And Lane 2 Yellow");
    DetectLane4R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE  1 AND LANE 3 YELLOW
void DetectLane3R_1Y_3Y(){
  Serial.println("Ambulance Detect in Lane 3 RED");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[2], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 And Lane 1 Yellow");
    DetectLane1R_3Y_1Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 And Lane 1 Yellow");
    DetectLane2R_3Y_1Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 And Lane 1 Yellow");
    DetectLane3R_3Y_1Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 And Lane 1 Yellow");
    DetectLane4R_3Y_1Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  1 AND LANE 3 YELLOW
void DetectLane4R_1Y_3Y(){
  Serial.println("Ambulance Detect in Lane 4 RED");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 4 AND LANE 3 YELLOW
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  //  MAKE LANE 4 GREEN
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 4 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 And Lane 4 Yellow");
    DetectLane1R_3Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 And Lane 4 Yellow");
    DetectLane2R_3Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 And Lane 4 Yellow");
    DetectLane3R_3Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 And Lane 4 Yellow");
    DetectLane4R_3Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE  1 AND LANE 4 YELLOW
void DetectLane2R_1Y_4Y(){
  Serial.println("Ambulance Detect in Lane 2 RED");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 4 AND LANE 2 YELLOW
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 4 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 And Lane 4 Yellow");
    DetectLane1R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 4 Yellow");
    DetectLane2R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 And Lane 4 Yellow");
    DetectLane3R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 4 Yellow");
    DetectLane4R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE  1 AND LANE 4 YELLOW
void DetectLane3R_1Y_4Y(){
  Serial.println("Ambulance Detect in Lane 3 RED");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 4 AND LANE 3 YELLOW
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[2], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 4 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 And Lane 4 Yellow");
    DetectLane1R_3Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 And Lane 4 Yellow");
    DetectLane2R_3Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 And Lane 4 Yellow");
    DetectLane3R_3Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 And Lane 4 Yellow");
    DetectLane4R_3Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  1 AND LANE 4 YELLOW
void DetectLane4R_1Y_4Y(){
  Serial.println("Ambulance Detect in Lane 4 RED");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[2], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  delay(4000);  //  MAKE LANE 4 GREEN
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 1 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 And Lane 4 Yellow");
    DetectLane1R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 4 Yellow");
    DetectLane2R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 4 Yellow");
    DetectLane3R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 4 Yellow");
    DetectLane4R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}
//  NEW LANE 1 STOP AMBULANCE DETECTION

/***************************************************************************************************************************************************************************/

//  START NEW LANE 2  AMBULANCE DETECTION

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE  2 AND LANE 3 YELLOW
void DetectLane3R_2Y_3Y(){
  Serial.println("Ambulance Detect in Lane 3 RED");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[2], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 And Lane 3 Yellow");
    DetectLane1R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 3 Yellow");
    DetectLane2R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 And Lane 3 Yellow");
    DetectLane3R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 3 Yellow");
    DetectLane4R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  2 AND LANE 4 YELLOW
void DetectLane4R_2Y_4Y(){
  Serial.println("Ambulance Detect in Lane 4 RED");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  //  MAKE LANE 4 GREEN
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 And Lane 4 Yellow");
    DetectLane1R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 4 Yellow");
    DetectLane2R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 And Lane 4 Yellow");
    DetectLane3R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 4 Yellow");
    DetectLane4R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE  2 AND LANE 4 YELLOW
void DetectLane3R_2Y_4Y(){
  Serial.println("Ambulance Detect in Lane 3 RED");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[2], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 And Lane 3 Yellow");
    DetectLane1R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 3 Yellow");
    DetectLane2R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 And Lane 3 Yellow");
    DetectLane3R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 3 Yellow");
    DetectLane4R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  2 AND LANE 4 YELLOW
void DetectLane1R_2Y_4Y(){
  Serial.println("Ambulance Detect in Lane 1 RED");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 And Lane 1 Yellow");
    DetectLane1R_2Y_1Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 1 Yellow");
    DetectLane2R_2Y_1Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 And Lane 1 Yellow");
    DetectLane3R_2Y_1Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 2 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 1 Yellow");
    DetectLane4R_2Y_1Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  2 AND LANE 1 YELLOW
void DetectLane1R_2Y_1Y(){
  Serial.println("Ambulance Detect in Lane 1 RED");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 And Lane 1 Yellow");
    DetectLane1R_2Y_1Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 1 Yellow");
    DetectLane2R_2Y_1Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 And Lane 1 Yellow");
    DetectLane3R_2Y_1Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 2 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 1 Yellow");
    DetectLane4R_2Y_1Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 1 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE  2 AND LANE 1 YELLOW
void DetectLane3R_2Y_1Y(){
  Serial.println("Ambulance Detect in Lane 3 RED");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[2], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 And Lane 3 Yellow");
    DetectLane1R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 3 Yellow");
    DetectLane2R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 And Lane 3 Yellow");
    DetectLane3R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 3 Yellow");
    DetectLane4R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  2 AND LANE 1 YELLOW
void DetectLane4R_2Y_1Y(){
  Serial.println("Ambulance Detect in Lane 4 RED");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[2], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  delay(4000);  //  MAKE LANE 3 GREEN
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 And Lane 4 Yellow");
    DetectLane1R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 4 Yellow");
    DetectLane2R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 And Lane 4 Yellow");
    DetectLane3R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 4 Yellow");
    DetectLane4R_2Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
}
//  NEW LANE 2 STOP AMBULANCE DETECTION

/**********************************************************************************************************************************************************************************/

//  NEW LANE 3 START AMBULANCE DETECTION

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  3 AND LANE 1 YELLOW
void DetectLane4R_3Y_1Y(){
  Serial.println("Ambulance Detect in Lane 4 RED");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 4 AND LANE 1 YELLOW
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[2], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  delay(4000);  //  MAKE LANE 4 GREEN
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 4 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 And Lane 4 Yellow");
    DetectLane1R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 4 Yellow");
    DetectLane2R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 4 Yellow");
    DetectLane3R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 4 Yellow");
    DetectLane4R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
}


//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE  3 AND LANE 1 YELLOW
void DetectLane2R_3Y_1Y(){
  Serial.println("Ambulance Detect in Lane 2 RED");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 And Lane 2 Yellow");
    DetectLane1R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 2 Yellow");
    DetectLane2R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 2 Yellow");
    DetectLane3R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 2 Yellow");
    DetectLane4R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}


//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  3 AND LANE 1 YELLOW
void DetectLane1R_3Y_1Y(){
  Serial.println("Ambulance Detect in Lane 1 RED");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 3 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 And Lane 3 Yellow");
    DetectLane1R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 3 Yellow");
    DetectLane2R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 3 Yellow");
    DetectLane3R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 3 Yellow");
    DetectLane4R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}


//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  3 AND LANE 4 YELLOW
void  DetectLane4R_3Y_4Y(){
  Serial.println("Ambulance Detect in Lane 4 RED");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[2], HIGH);
  delay(4000);  //  MAKE LANE 4 GREEN
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 3 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 3 Yellow");
    DetectLane1R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 3 Yellow");
    DetectLane2R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 3 Yellow");
    DetectLane2R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 3 Yellow");
    DetectLane3R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 3 Yellow");
    DetectLane4R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 4 RED WHEN LANE  3 AND LANE 2 YELLOW
void DetectLane4R_3Y_2Y(){
  Serial.println("Ambulance Detect in Lane 4 RED");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[2], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  delay(4000);  //  MAKE LANE 4 GREEN
  digitalWrite(Lane4[2], LOW);
  digitalWrite(Lane4[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 4 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 2 Yellow");
    DetectLane1R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 2 Yellow");
    DetectLane2R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 2 Yellow");
    DetectLane3R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 2 Yellow");
    DetectLane4R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE  3 AND LANE 2 YELLOW
void DetectLane2R_3Y_2Y(){
  Serial.println("Ambulance Detect in Lane 2 RED");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  delay(4000);  //  MAKE LANE 2 GREEN
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 And Lane 2 Yellow");
    DetectLane1R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 And Lane 2 Yellow");
    DetectLane2R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 And Lane 2 Yellow");
    DetectLane3R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 And Lane 2 Yellow");
    DetectLane4R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  3 AND LANE 2 YELLOW
void DetectLane1R_3Y_2Y(){
  Serial.println("Ambulance Detect in Lane 1 RED");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  delay(4000);  //  MAKE LANE 1 GREEN
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  //  MAKE LANE 2 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 And Lane 2 Yellow");
    DetectLane1R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 2 Yellow");
    DetectLane2R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 2 Yellow");
    DetectLane3R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 2 Yellow");
    DetectLane4R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
}
//  STOP NEW LANE 3 AMBULANCE DETECTION

/***************************************************************************************************************************************************************************/

//  NEW LANE 4 YELLOW AMBULANCE DETECTION 

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  4 AND LANE 1 YELLOW
void DetectLane1R_4Y_1Y(){
  Serial.println("Ambulance Stuck in Lane 1RED");
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  // MAKE LANE 1 GREEN
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 And Lane 4 Yellow");
    DetectLane1R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 4 Yellow");
    DetectLane2R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 4 Yellow");
    DetectLane3R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 4 Yellow");
    DetectLane4R_1Y_4Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 4 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}


//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE  4 AND LANE 2 YELLOW
void DetectLane3R_4Y_2Y(){
  Serial.println("Ambulance Stuck in Lane 3RED");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  // MAKE LANE 3 YELLOW AND LANE 2 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane3[2], HIGH);
  delay(4000);  // MAKE LANE 3 GREEN
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  // MAKE LANE 3 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 3 And Lane 2 Yellow");
    DetectLane1R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 3 And Lane 2 Yellow");
    DetectLane2R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 3 And Lane 2 Yellow");
    DetectLane3R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 3 And Lane 2 Yellow");
    DetectLane4R_3Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 3 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane3[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE  4 AND LANE 2 YELLOW
void DetectLane2R_4Y_2Y(){
  Serial.println("Ambulance Stuck in Lane 2RED");
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[2], HIGH);
  delay(4000);  // MAKE LANE 2 GREEN
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 2 Yellow");
    DetectLane1R_4Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 2 Yellow");
    DetectLane2R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 2 Yellow");
    DetectLane3R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 2 Yellow");
    DetectLane4R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  4 AND LANE 2 YELLOW
void DetectLane1R_4Y_2Y(){
  Serial.println("Ambulance Stuck in Lane 1RED");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  // MAKE LANE 1 YELLOW AND LANE 2 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane2[0], HIGH);
  digitalWrite(Lane1[2], HIGH);
  delay(4000);  // MAKE LANE 4 GREEN
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  // MAKE LANE 1 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 And Lane 2 Yellow");
    DetectLane1R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

  //  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 2 Yellow");
    DetectLane2R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 2 Yellow");
    DetectLane3R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 2 Yellow");
    DetectLane4R_1Y_2Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 2 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 3 RED WHEN LANE  4 AND LANE 3 YELLOW
void DetectLane3R_4Y_3Y(){
  Serial.println("Ambulance Stuck in Lane 3RED");
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane3[2], HIGH);
  delay(4000);  // MAKE LANE 3 GREEN
  digitalWrite(Lane4[0], LOW);
  digitalWrite(Lane3[2], LOW);
  digitalWrite(Lane3[1], HIGH);
  digitalWrite(Lane4[1], HIGH);
  delay(2000);  // MAKE LANE 4 AND LANE 3 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 4 And Lane 3 Yellow");
    DetectLane1R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 4 And Lane 3 Yellow");
    DetectLane2R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 4 And Lane 3 Yellow");
    DetectLane3R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 4 And Lane 3 Yellow");
    DetectLane4R_4Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 4 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
}

//  AMBULANCE DETECT IN LANE 2 RED WHEN LANE  4 AND LANE 3 YELLOW
void DetectLane2R_4Y_3Y(){
  Serial.println("Ambulance Stuck in Lane 2RED");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane2[0], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane2[1], HIGH);
  delay(2000);  // MAKE LANE 3 YELLOW AND LANE 2 YELLOW
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane2[2], HIGH);
  digitalWrite(Lane3[0], HIGH);
  delay(4000);  // MAKE LANE 2 GREEN
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane2[2], LOW);
  digitalWrite(Lane2[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  // MAKE LANE 3 AND LANE 2 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 2 And Lane 3 Yellow");
    DetectLane1R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 2 And Lane 3 Yellow");
    DetectLane2R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 2 And Lane 3 Yellow");
    DetectLane3R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 2 And Lane 3 Yellow");
    DetectLane4R_2Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 2 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane2[1], LOW);
  digitalWrite(Lane2[0], HIGH);
}

//  AMBULANCE DETECT IN LANE 1 RED WHEN LANE  4 AND LANE 3 YELLOW
void DetectLane1R_4Y_3Y(){
  Serial.println("Ambulance Stuck in Lane 1RED");
  digitalWrite(Lane4[1], LOW);
  digitalWrite(Lane1[0], LOW);
  digitalWrite(Lane4[0], HIGH);
  digitalWrite(Lane1[1], HIGH);
  delay(2000);  // MAKE LANE 3 YELLOW AND LANE 1 YELLOW
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane3[1], LOW);
  digitalWrite(Lane1[2], HIGH);
  digitalWrite(Lane3[0], HIGH);
  delay(4000);  // MAKE LANE 1 GREEN
  digitalWrite(Lane3[0], LOW);
  digitalWrite(Lane1[2], LOW);
  digitalWrite(Lane1[1], HIGH);
  digitalWrite(Lane3[1], HIGH);
  delay(2000);  // MAKE LANE 3 AND LANE 1 YELLOW

//  RFID LANE 1
  if( mfrc522_1.PICC_IsNewCardPresent() || mfrc522_1.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 1 RED When Lane 1 And Lane 3 Yellow");
    DetectLane1R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 1 RED WHEN LANE 1 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 2
  if( mfrc522_2.PICC_IsNewCardPresent() || mfrc522_2.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 2 RED When Lane 1 And Lane 3 Yellow");
    DetectLane2R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 2 RED WHEN LANE 1 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 3
  if( mfrc522_3.PICC_IsNewCardPresent() || mfrc522_3.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 3 RED When Lane 1 And Lane 3 Yellow");
    DetectLane3R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 3 RED WHEN LANE 1 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }

//  RFID LANE 4
  if( mfrc522_4.PICC_IsNewCardPresent() || mfrc522_4.PICC_ReadCardSerial())
  {
    Serial.println("Ambulance Detect in Lane 4 RED When Lane 1 And Lane 3 Yellow");
    DetectLane4R_1Y_3Y();  //  AMBULANCE DETECT IN LANE 4 RED WHEN LANE 1 And Lane 3 Yellow
    Serial.println("Ambulance Goes Sucessfully!!!");
  }
  digitalWrite(Lane1[1], LOW);
  digitalWrite(Lane1[0], HIGH);
}
//  STOP NEW LANE 4 AMBULANCE DETECTION

//  STOP AMBULANCE DETECTION

/*********************__________________&&&#######$$$$$@@@@@@@%%%%%!!!!!!!THANK YOU!!!!!!!%%%%%@@@@@@@$$$$$#######&&&__________________*********************/
