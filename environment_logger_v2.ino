/* 
 * Temperature and humidity logger for the bat project
 * can be used as a generic stand alone temperature / humidity logger as well
 *
 * Records environment data with timestamp to a SD-card (note: needs datalogging shield!)
 * Output file ENVLOG.TXT (comma separated, data format compatible format with the BatPi scripts)
 *
 * the main loop writes data only once per 10 minutes, so you
 * will have to run the program long enough to record data
 *
 * a LED for basic information on error status is used on pin 9
 *
 * error blink codes:
 * 1 x red = Clock module RTC not found 
 * 2 x red = SD card not found
 * 3 x red = no filesystem found on SD Card
 * 4 x red = file write error
 * 5 x red = error reading sensor
 *
 * Version 1: Octobre 2016
 * Version 2: Octobre 2017 
 *   - added blinking error led, for easy handling in the field
 *   - replaced DHT11 with the more accurate DHT22
 *   - DHT22 also supports negative temperatures
 */

#include <SD.h>
#include <Wire.h>
#include <RTClib.h>
#include <string.h>

// Temperature and Humidity sensor uses Adafruit DHT Library
// See https://learn.adafruit.com/dht for more information and download

#include "DHT.h"
#define DHTPIN 3        // what digital pin the temperature sensor is connected to
#define DHTTYPE DHT22   // DHT 22

//////////////////////////
// Hardware definitions //
//////////////////////////

// SD Card - Datalogger pin
const int chipSelect = 10; 

////////////////
// Variables //
///////////////

RTC_DS1307 RTC;
Sd2Card card;
SdVolume volume;
DHT dht(DHTPIN, DHTTYPE);

File myFile;
File tempFile;

String line;
DateTime now;
boolean logmode;

char cbuffer[61]; // used as logline
int lastminute;
int currentminute;
int currenthour;
int currentday;
int currentmonth;
int currentyear;
int theLED = 9; // led connected to pin 9 - used as error led

// setting RTC
char datestr[20];
char timestr[20];
char *ptr;
int  idx;
char c;


////////////////////
// Setup function //
////////////////////

void setup() {
  
  // uncomment following for sending debug messages
  // Serial.begin(9600); 

  pinMode (theLED, OUTPUT); 

  // initialize sensor
  dht.begin();      // init temp sensor
  checkSensor();    // if error reading sensens, this will exit the programm and blink the error led

  // initialoze real time clock
  Wire.begin();
  RTC.begin();  

  // uncomment following line to set the RTC to the date & time this sketch was compiled
  //RTC.adjust(DateTime(__DATE__, __TIME__));

  if (! RTC.isrunning()) {
    // RTC not running or not set
    blink_err (1);    
  } 

  // get actual date
  now= RTC.now();  

  // initialize SD-card...  
  pinMode(chipSelect, OUTPUT);
  if (!SD.begin(10)) {
    // SD-slot initialization failed
    blink_err (2);
  }

  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    // SD-hardware initialization failed
    blink_err (2);
  } 

  // open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    // Could not find FAT16/FAT32 partition
    blink_err (3);
  }
  
  // open logfile and add a line with date and time
  myFile = SD.open("logger.txt", FILE_WRITE);
  line=getDateTimeString(now);
      
  // now write to file
  if (myFile) {
    myFile.println(line + " power up");
    myFile.close();
  } 
  else {
    // failed to write file
    blink_err (4);
  } 

  logmode= false; // logging has not started, yet
  currentminute= now.minute();
  lastminute = currentminute;
  currenthour= now.hour();
  currentday = now.day();
  currentmonth= now.month();
  currentyear = now.year();  
  
}


//////////////////
// Main program //
//////////////////

void loop() {
  

  now = RTC.now(); // read date/time for this loop
  //digitalWrite (theLED, HIGH);
 
  if (logmode) {
   
    //digitalWrite (theLED, LOW);
          
    // is a new minute beginning ?  
    currentminute= now.minute();
    
    if (currentminute != lastminute) {
      lastminute= currentminute;        
                  
      // log temperature and humidity to a file - every 10 minutes
      if (currentminute==1 || currentminute==11 || currentminute==21 || currentminute==31 || currentminute==41 || currentminute==51) {
        logHumTemp(currentday, currentmonth, currentyear, currenthour,currentminute);
      }      
    }
    
    // is a new hour beginning ?
    if (currenthour != now.hour()) {      
      currenthour= now.hour();
    }
    
    // new day beginning ?
    if (currentday != now.day()) {
      currentday= now.day();            
    }
    
    // new month beginning ?
    if (currentmonth != now.month()) {
      currentmonth= now.month();
    }
    
  } else {    
    
     // blink  LED to show that logging begins soon
    if (now.second() % 2 == 0) {
      digitalWrite (theLED, HIGH);
    } else {
      digitalWrite (theLED, LOW);
    }

    // can we start logging now ?    
    if (now.second() == 0) {  // start at the full minute
      blinkLedsAB();
      logmode= true;
    } else {
      Serial.println ("waiting for next full minute to start: " + String (now.second()));
      delay (1000);
    }
  }  
}


////////////////////////////
// User defined functions //
////////////////////////////


// insert a leading "0" , used by getDate()
String str2c (String in) {
  if (in.length()==2) {
    return (in);
  } else {
    return ('0' + in);
  }
}

// blink led quickly during 2 seconds 
void blinkLedsAB(){
  int i;
  for (i= 0; i<20; i++) {
    digitalWrite (theLED, HIGH);
    delay (100);
    digitalWrite (theLED, LOW);
    delay (100);
  }
}

// return a formatted date string
String getDate() {
  DateTime now = RTC.now();
  line= str2c (String(now.day())) + '.' + str2c (String (now.month()))+ '.' +  + now.year();
  return (line);
}

// return a formatted time string
String getDateTimeString(DateTime theTimeStamp) {
  //DateTime now = RTC.now();
  line= str2c (String(theTimeStamp.day())) + '.' + str2c (String (theTimeStamp.month()))+ '.' +  theTimeStamp.year() 
    + " " + str2c (String (theTimeStamp.hour())) + ":" + str2c (String (theTimeStamp.minute()));
  return (line);
}

// log a string with timestamp, humidity and temperature 
void logHumTemp (int theDay, int theMonth, int theYear, int hours, int minutes) {

  float h = dht.readHumidity();  
  float t = dht.readTemperature();
  
  minutes = minutes - 1;
  
   // open logfile and add a line with date and time
  tempFile = SD.open("envlog.txt", FILE_WRITE);

  // now write to file
  if (tempFile) {
    tempFile.print(theDay); 
    tempFile.print(".");
    tempFile.print(theMonth);   
    tempFile.print(".");
    tempFile.print(theYear);   
    tempFile.print(";");
    
    tempFile.print(hours); 
    tempFile.print(":");
    if (minutes == 0) 
      tempFile.print("00");
    else 
      tempFile.print(minutes);       
    tempFile.print(";");
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
       tempFile.print("Error reading temperature sensor;");
       blink_err (5);  
    }
    else {       
       tempFile.print(t);
       tempFile.print(";");
       tempFile.print(h);       
    }    
    tempFile.println();
  }
  tempFile.close();   
}

// check the sensor, exit the programm into an error loop if sensor does not return valid values
void checkSensor() {

  float h = dht.readHumidity();  
  float t = dht.readTemperature();
      
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
     blink_err (5);  
  }
}

// show error code - this routine never returns !
void blink_err (int n) {
  int i;

  while (1) {
    for (i= 0; i<n; i++) {
      digitalWrite (theLED, HIGH);
      delay (250);
      digitalWrite (theLED, LOW);
      delay (250);
    }
    delay (2000); 
  }
}
