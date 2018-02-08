#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

char firstName[16]; // First name array
char lastName[16]; // Last name array
String lastNameStr;
String lastNameArray[8];
int currentUser;

//*****************************************************************************************//
void setup() {
  pinMode(5, OUTPUT);
  pinMode(4, INPUT);
  digitalWrite(5, HIGH);
  digitalWrite(4, HIGH);
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
  lastNameArray[0] = "Faisal";
  lastNameArray[1] = "Shehri";
  lastNameArray[2] = "???";
  lastNameArray[3] = "Bahamel";
  lastNameArray[4] = "Thabet";
  lastNameArray[5] = "Seden";
  lastNameArray[6] = "Saci";
  lastNameArray[7] = "arkawi";
  lastNameArray[8] = "Global";

}

//*****************************************************************************************//
void loop() {

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  Serial.print(F("Name: "));

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }
  Serial.print(" ");

  //---------------------------------------- GET LAST NAME

  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );
    lastName[i] = buffer2[i];
    
  }
  lastNameStr = lastName;

  for(int i = 0; i < 9; i++){
      if(lastNameStr == lastNameArray[i]){
            currentUser = i;
            i = 9;
        }
      }


  currentUser = 7;
Serial.println(currentUser);
 switch(currentUser){
      
      case 0: //"Faisal":
      break;

      case 1: //"Shehri":
      break;
      
      case 2: //"???":
      break;

      case 3: //"Bahamel":
      break;

      case 4: //"Thabet":
      break;

      case 5: //"Seden":
      break;

      case 6: //"Saci":
      break;
      
      case 7: //"Arkawi":
      while(digitalRead(4) == LOW)
      {
        Serial.println("hello");
        digitalWrite(5, LOW);
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
      }
      digitalWrite(5, HIGH);
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
      break;
      
      case 8: //Global:
      break;
      
    }


  //----------------------------------------

  Serial.println(F("\n**End Reading**\n"));

  delay(1000); //change value if you want to read cards faster

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
//*****************************************************************************************//


