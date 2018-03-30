/*
 * Simple code example for reading the ID of a RFID/NFC tag with ESP8266.
 * Reads a RFID tag and output its UID values in hex and decimal.
 * Doesn't output UID of tag if it's the same tag as the last one read.
 * UID of tags are usually output in hex, but I've included output in dec, 
 * as is much simpler to store and compare.
 * 
 * This example is an easy RFID UID read, if you want to store tags and 
 * recognize stored tags, check out my other example
 * 
 * Install the library 'MFRC522' by 'GithubCommunity' in the Arduino IDE, 
 * or download here: https://github.com/miguelbalboa/rfid
 * 
 * 
 * -----------------------------------------------------
 *             RFID reader  Arduino       NodeMCU
 *             (MFRC522)    Uno/101       (ESP8266)
 * Signal      Pin          Pin           Pin      
 * -----------------------------------------------------
 * RST/Reset   RST          9             D3        
 * SPI SS      SDA (SS)     10            D8       
 * SPI MOSI    MOSI         11            D7       
 * SPI MISO    MISO         12            D6       
 * SPI SCK     SCK          13            D5       
 *
 * Pin connections for all Arduino boards: https://www.arduino.cc/en/Reference/SPI
 * 
 */

// Include libraries
#include <SPI.h>                    // Library included in Arduino IDE
#include <MFRC522.h>                // Install/download instructions above

// Define pinout
#define RST_PIN  D3
#define SS_PIN   D8

MFRC522 rfid(SS_PIN, RST_PIN);      // Create MFRC522 instance

unsigned long lastTagId;            // Last tag to be scanned (decimal UID value)
const int DELAY_AFTER_READ = 1000;  // Waiting time after card is read to avoid multiple reads

void setup() {
  Serial.begin(115200);             // Initialize serial communications
  SPI.begin();                      // Init SPI bus
  rfid.PCD_Init();                  // Init MFRC522
  delay(200);
  Serial.println();
  Serial.println("RFID reader ready");
}

void loop() { 

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }

  // Select one of the cards
  if ( ! rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  
  // Read and store decimal UID value of RFID tag
  unsigned long newTagId = getDecUid(rfid.uid.uidByte);

  // Don't print UID if tag is same as last read
  if (lastTagId == newTagId) {
    Serial.println("Previous tag read again");
    delay(DELAY_AFTER_READ);
    return;
  } else {
    Serial.println("Read new RFID tag");
  }
  
  // Print UID of tag to Serial as hex values
  Serial.print("Card hex UID: ");
  dump_byte_array(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  // Print UID of tag to Serial as decimal values
  Serial.print("Card dec UID:  ");
  Serial.println(newTagId);

  // Declare new scanned tag as last scanned tag
  lastTagId = newTagId;

  /* Some users online halts the reader after every loop.
   * I've had no problems in functionality without it,
   * and as such I've chosen to comment it out.
   *  
   * // Halt PICC
   * rfid.PICC_HaltA();
  */
  
  // Don't read same card multiple times within given time
  delay(DELAY_AFTER_READ);
}


// Helper routine to dump a byte array as hex values to Serial
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

// Returns a long integer for the tag's UID which is easily stored and compared
unsigned long getDecUid(byte* byteArray) {
  unsigned long hex_num;
  unsigned long first = byteArray[0];
  unsigned long second = byteArray[1];
  unsigned long third = byteArray[2];
  unsigned long fourth = byteArray[3];
  hex_num =  first << 24;
  hex_num += second << 16;
  hex_num += third <<  8;
  hex_num += fourth;
  return hex_num;
}
