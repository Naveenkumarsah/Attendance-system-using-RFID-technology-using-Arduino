#include <SPI.h>
#include <MFRC522.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

#define SS_PIN 10 //RX slave select
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

byte card_ID[4]; //card UID size 4byte
byte Name1[4]={0x43,0x06,0x75,0x0C};//First UID card
byte Name2[4]={0x4B,0xBB,0xC9,0xA5};//second UID card
byte Name3[4]={0x9C,0x4A,0x51,0x18};//Third UID card

//if you want the arduino to detect the cards only once
int NumbCard[3];//this array content the number of cards. in my case i have just three cards.
int j=0;        

int const RedLed=6;
int const GreenLed=5;
int const Buzzer=8;

String Name;//user name
long Number;//user number
int n ;//The number of card you want to detect (optional)  

void setup() {
  Serial.begin(9600);// Initialize serial communications with the PC
  lcd.begin(16,2);
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  
  Serial.println("CLEARSHEET");                 // clears starting at row 1
  lcd.print("  Good morning  ");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print(" put your card !");
  
  Serial.println("LABEL,Date,Time,Name,Number");// make four columns (Date,Time,[Name:"user name"]line 48 & 52,[Number:"user number"]line 49 & 53)

  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(Buzzer,OUTPUT);

   }
    
void loop() {
  //look for new card
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }


 for (byte i = 0; i < mfrc522.uid.size; i++) {
     card_ID[i]=mfrc522.uid.uidByte[i];

       if(card_ID[i]==Name1[i]){
       Name="Naveen Kr Sah";//user name
       Number=88;//user number
       j=0;//first number in the NumbCard array : NumbCard[j]
       lcd.clear();
       lcd.print(" Naveen Kr Sah  ");
       lcd.setCursor(0,1);
       lcd.print("mark present(88)");
       delay(800);
       lcd.setCursor(0,1);
       lcd.print("  list updated  ");
       delay(500);
       lcd.setCursor(0,1);
       lcd.print("  your welcome  ");
       delay(500);
       lcd.clear();
       lcd.setCursor(0,1);
       lcd.print("> next please >>");
 
      }
      else if(card_ID[i]==Name2[i]){
       Name="Mayank Saini";//user name
       Number=77;//user number
       j=1;//Second number in the NumbCard array : NumbCard[j]
       
       lcd.clear();
       lcd.print(" mayank saini  ");
       lcd.setCursor(0,1);
       lcd.print("mark present(77)");
       delay(800);
       lcd.setCursor(0,1);
       lcd.print("  list updated  ");
       delay(500);
       lcd.setCursor(0,1);
       lcd.print("  your welcome  ");
       delay(500);
       lcd.clear();
       lcd.setCursor(0,1);
       lcd.print("> next please >>");
      }
      else if(card_ID[i]==Name3[i]){
       Name="Visitor";//user name
       Number=3;//user number
       j=2;//Third number in the NumbCard array : NumbCard[j]

       lcd.clear();
       lcd.print("   Visitor !!   ");
       lcd.setCursor(0,1);
       lcd.print("mark present(3)");
       delay(800);
       lcd.setCursor(0,1);
       lcd.print("  list updated  ");
       delay(500);
       lcd.setCursor(0,1);
       lcd.print("  your welcome  ");
       delay(500);
       lcd.clear();
       lcd.setCursor(0,1);
       lcd.print("> next please >>");

      }
      else{
          digitalWrite(GreenLed,LOW);
          digitalWrite(RedLed,HIGH);
          goto cont;//go directly to line 85
     }
}
      if(NumbCard[j] == 1){//to check if the card already detect
      //if you want to use LCD
      Serial.println("Already Exsits");
      lcd.setCursor(0,0);
      lcd.print(" Already Exsist ");
      digitalWrite(RedLed,HIGH);
      digitalWrite(Buzzer,HIGH);
      delay(30);
      digitalWrite(Buzzer,LOW);
      }
      else{
      NumbCard[j] = 1;//put 1 in the NumbCard array : NumbCard[j]={1,1} to let the arduino know if the card was detecting 
      n++;//(optional)
      Serial.print("DATA,DATE,TIME," + Name);//send the Name to excel
      Serial.print(",");
      Serial.println(Number); //send the Number to excel
      digitalWrite(GreenLed,HIGH);
      digitalWrite(RedLed,LOW);
      digitalWrite(Buzzer,HIGH);
      delay(30);
      digitalWrite(Buzzer,LOW);
      Serial.println("SAVEWORKBOOKAS,Names/WorkNames");
      }
      delay(1000);
cont:
delay(2000);
digitalWrite(GreenLed,LOW);
digitalWrite(RedLed,LOW);

//if you want to close the Excel when all card had detected and save Excel file in Names Folder. in my case i have just 3 card (optional)
//if(n==3){
    
  //Serial.println("FORCEEXCELQUIT");
  // }
}
    
