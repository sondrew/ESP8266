/*
 * Code example for reading and storing the ID of a RFID/NFC tag with ESP8266.
 * Reads a RFID tag and output its UID values in hex and decimal.
 * Doesn't output UID of tag if it's the same tag as the last one read.
 * UID of tags are usually output in hex, but I've included output in dec, 
 * as is much simpler to store and compare.
 * 
 * You can store tags in runtime by giving the last read tag a name and 
 * sending it to Serial monitor. Every subsequent read of that tag will now 
 * display its name. You can fill in your own code do perform specific actions, 
 * depending on specific cards. If you want to have tags pre-stored at runtime, 
 * just hardcode the decimal UID of the tag in 'idStoredTags' and the String 
 * name in 'nameStoredTags'. For example:
 * 
 *    unsigned long idStoredTags[] = {0123456789, 1234567890, 2345678910};
 *    String nameStoredTags[] = {"Omar", "McNulty", "Bubbles"};
 * 
 * 
 * This example is for reading and storing RFID tags, if you just want to read
 * tags, check out my RFID_read read example
 * 
 * Install the library 'MFRC522' by 'GithubCommunity' in the Arduino IDE, 
 * or download here: https://github.com/miguelbalboa/rfid
 * 
 * 
 * -----------------------------------------------------
 *             RFID reader  NodeMCU       Arduino
 *             (MFRC522)    (ESP8266)     Uno/101
 * Signal      Pin          Pin           Pin    
 * -----------------------------------------------------
 * RST/Reset   RST          D3            9      
 * SPI SS      SDA (SS)     D8            10     
 * SPI MOSI    MOSI         D7            11     
 * SPI MISO    MISO         D6            12     
 * SPI SCK     SCK          D5            13     
 *
 * Pin connections for all Arduino boards: https://www.arduino.cc/en/Reference/SPI
 * 
 */

// Include libraries
#include <SPI.h>                              // Library included in the Arduino IDE
#include <MFRC522.h>                          // Install/download instructions above

// Define pinout
#define RST_PIN  D3
#define SS_PIN   D8

MFRC522 rfid(SS_PIN, RST_PIN);                // Create MFRC522 instance

const int MAX_STORED_TAGS = 5;                // Maximum number of stored tags
unsigned long idStoredTags[MAX_STORED_TAGS];  // Array containing decimal value UID of tags
String nameStoredTags[MAX_STORED_TAGS];       // Array containing user-defined names of tags
int numOfStoredTags = 0;                      // Integer to keep track of number of stored tags

unsigned long lastTagId;                      // Last tag read (decimal UID value)
const int DELAY_AFTER_READ = 1000;            // Delay time after tag is read to avoid multiple reads

void setup() {
  Serial.begin(115200);                       // Initialize serial communications
  SPI.begin();                                // Init SPI bus
  rfid.PCD_Init();                            // Init MFRC522
  delay(200);
  Serial.println();
  Serial.println("RFID reader ready");
}

void loop() { 

  // In case of user input in Serial monitor: Store last scanned RFID tag with input as name
  if (Serial.available()) {
    // Read input from Serial monitor
    String serialInput = Serial.readString();

    // Print all stored tags if Serial input is 'print', otherwise store with given name
    if (serialInput == "print") {
      printStoredTags();
    } else {
      storeTag(lastTagId, serialInput);
    }
  }
  
  // Look for new tags
  if ( ! rfid.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  // Select one of the tags
  if ( ! rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Read decimal UID value of tag
  unsigned long newTagId = getDecUid(rfid.uid.uidByte);

  // Check if tag is same as last one read
  if (lastTagId == newTagId) {
    Serial.println("Previous tag read again");
    delay(DELAY_AFTER_READ);
    return;
  } else {
    // Check if read tag is stored
    int tagIndex = getStoredTagIndex(newTagId);
    
    if (tagIndex > -1) { // Print name and UID if tag is stored
      Serial.println("Read stored tag '" + nameStoredTags[tagIndex] + "' (id: " + (String) newTagId + ")");
      lastTagId = newTagId;

      /*
       * If you want to do something with the identified stored tags, do it here
       */
      
      delay(DELAY_AFTER_READ);
      return; // Read complete, return to start of loop
    } else { // Tag is not stored, proceed to print UID
      Serial.println("Read new RFID tag");
    }
  }
  
  // Print UID of tag to Serial as hex values
  Serial.print("Tag hex UID: ");
  dump_byte_array(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  // Print UID of tag to Serial as decimal values
  Serial.print("Tag dec UID:  ");
  Serial.println(newTagId);

  // Declare new scanned tag as last scanned tag
  lastTagId = newTagId;

  /* Some users online halts the reader after every loop.
   * I've had no difference in functionality without it,
   * and as such I've chosen to comment it out.
   *  
   * // Halt PICC
   * rfid.PICC_HaltA();
  */
  
  // Avoid reading same tag multiple times within given time
  delay(DELAY_AFTER_READ);
}



/* 
 * Helper routine to dump a byte array as hex values to Serial 
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}


/*
 *  Return a long integer for the tag's UID which is easily stored and compared
 */
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


/*
 * Store tag with given name and dec UID
 */
void storeTag(unsigned long tagId, String tagName) {
  // Check if tag is already stored
  if (getStoredTagIndex(tagId) > -1) {
    Serial.println("Unable to store: Tag is already stored");
    return;
  }

  // Check if storage is full
  if (MAX_STORED_TAGS > numOfStoredTags) {
    idStoredTags[numOfStoredTags] = tagId;
    nameStoredTags[numOfStoredTags] = tagName;
    numOfStoredTags += 1;
    Serial.println("Stored tag with name '" + tagName + "' (id: " + (String) tagId + ")");
  } else {
    Serial.println("Unable to store: Maximum number of stored tags has been reached");
  }
  
}


/**
 * Return index of RFID tag in 'idStoredTags' array (-1 if not present)
 */
int getStoredTagIndex(unsigned long tagId) {
  for (int index = 0; index < numOfStoredTags; index ++) {
    if (idStoredTags[index] == tagId) {
      return index;
    }
  }
  return -1;
}


/*
 * Print all stored tags when received 'send' in Serial monitor
 */
void printStoredTags() {
  // Check if any tags are stored before printing
  if (numOfStoredTags == 0) {
    Serial.println("No stored tags");
    return;
  }
  
  Serial.println();
  Serial.println("STORED TAGS");
  Serial.println("Index      UID               UID");
  for (int i = 0; i < numOfStoredTags; i++) {
    Serial.println((String) i + "          " + (String) idStoredTags[i] + "        " + nameStoredTags[i]);
  }
  Serial.println();
}
