// Version 3 dated 13/02/2016
// corrected number of pulses of pipistrellus calls - because of wrong frequency measurement

// Version 2 dated 30/01/2016
// added automatic programms for bat logger testing

int batcallNumber=29; //number of calls in one sequence
int pauseMin=5000;    //minimum time between sequences (msec)
int pauseMax=10000;   //maximum time between sequences (msec)

int led = 13;
int transducer = 12;
int button = 2;
int inPin1 = 10;
int inPin2 = 9;
int inPin3 = 8;
int inPin4 = 7;
int inPin5 = 6;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  pinMode(transducer, OUTPUT);     
  pinMode(inPin1, INPUT_PULLUP);
  pinMode(inPin2, INPUT_PULLUP);
  pinMode(inPin3, INPUT_PULLUP);
  pinMode(inPin4, INPUT_PULLUP);
  pinMode(inPin5, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(57600);

}

void loop() {

  // Pipistrellus pipistrellus A
  // Peak 41.66 KHz / Length 3 ms / TBC 75 ms 
  // DIP 1 0 0 0 0  
  if(!digitalRead(inPin1) && digitalRead(inPin2) && digitalRead(inPin3) && digitalRead(inPin4) && digitalRead(inPin5)) // if 
  {
    Serial.println("zwerg a");
    if(!digitalRead(button)){
      bat_call(7, 74, 125);
    }
    else{
      bat_call_series(7, 74, 125, batcallNumber);  
    }
  }
  
  // Pipistrellus pipistrellus B
  // Peak 55.55 KHz / Length 10 ms / TBC 130 ms 
  // DIP 1 0 0 0 1  
  if(!digitalRead(inPin1) && digitalRead(inPin2) && digitalRead(inPin3) && digitalRead(inPin4) && !digitalRead(inPin5)) // if 
  {
    Serial.println("zwerg b");
    if(!digitalRead(button)){
      bat_call(4, 138, 500);
    }
    else{
      bat_call_series(4, 138, 500, batcallNumber);  
    }    
  }
  
  // Barbastella A
  // Peak 29.41 KHz / Length 2 ms / TBC 50 ms 
  // DIP 0 1 0 0 0  
  if(digitalRead(inPin1) && !digitalRead(inPin2) && digitalRead(inPin3) && digitalRead(inPin4) && digitalRead(inPin5)) // if 
  {
    Serial.println("mops a");
    if(!digitalRead(button)){
      bat_call(12, 52, 59);
    }
    else{
      bat_call_series(12, 52, 59, batcallNumber);  
    }
  }
 
  // Barbastella B
  // Peak 45.45 KHz / Length 6 ms / TBC 75 ms 
  // DIP 0 1 0 0 1  
  if(digitalRead(inPin1) && !digitalRead(inPin2) && digitalRead(inPin3) && digitalRead(inPin4) && !digitalRead(inPin5)) // if 
  {
    Serial.println("mops b");
    if(!digitalRead(button)){
      bat_call(6, 74, 270);
    }
    else{
      bat_call_series(6, 74, 270, batcallNumber);  
    }
  }
  
  // Myotis bechsteinii A
  // Peak 38.4 KHz / Length 2 ms / TBC 90 ms 
  // DIP 0 0 1 0 0  
  if(digitalRead(inPin1) && digitalRead(inPin2) && !digitalRead(inPin3) && digitalRead(inPin4) && digitalRead(inPin5)) // if 
  {
    Serial.println("bechstein a");
    if(!digitalRead(button)){
      bat_call(8, 85, 77);
    }
    else{
      bat_call_series(8, 85, 77, batcallNumber);  
    }
  }
 
  // Myotis bechsteinii B
  // Peak 50 KHz / Length 6 ms / TBC 110 ms 
  // DIP 0 0 1 0 1  
  if(digitalRead(inPin1) && digitalRead(inPin2) && !digitalRead(inPin3) && digitalRead(inPin4) && !digitalRead(inPin5)) // if 
  {
    Serial.println("bechstein b");
    if(!digitalRead(button)){
      bat_call(5, 102, 300);
    }
    else{
      bat_call_series(5, 102, 300, batcallNumber);  
    }
  }
  
  // Myotis myotis A
  // Peak 27.4 KHz / Length 5 ms / TBC 90 ms 
  // DIP 0 0 0 1 0  
  if(digitalRead(inPin1) && digitalRead(inPin2) && digitalRead(inPin3) && !digitalRead(inPin4) && digitalRead(inPin5)) // if 
  {
    Serial.println("mausohr a");
    if(!digitalRead(button)){
      bat_call(13, 83, 120);
    }
    else{
      bat_call_series(13, 83, 120, batcallNumber);  
    }
  }
 
  // Myotis myotis B
  // Peak 38.4 KHz / Length 10 ms / TBC 160 ms 
  // DIP 0 0 0 1 1  
  if(digitalRead(inPin1) && digitalRead(inPin2) && digitalRead(inPin3) && !digitalRead(inPin4) && !digitalRead(inPin5)) // if 
  {
    Serial.println("mausohr b");
    if(!digitalRead(button)){
      bat_call(8, 160, 360);
    }
    else{
      bat_call_series(8, 160, 360, batcallNumber);  
    }
  }
  
  
  // Nyctalus noctula A
  // Peak 17.2 KHz / Length 5 ms / TBC 150 ms 
  // DIP 1 1 0 0 0  
  if(!digitalRead(inPin1) && !digitalRead(inPin2) && digitalRead(inPin3) && digitalRead(inPin4) && digitalRead(inPin5)) // if 
  {
    Serial.println("abendsegler a");
    if(!digitalRead(button)){
      bat_call(23, 140, 70);
    }
    else{
      bat_call_series(23, 140, 70, batcallNumber);  
    }
  }

  // Nyctalus noctula B
  // Peak 29.41 KHz / Length 28 ms / TBC 300 ms 
  // DIP 1 1 0 0 1  
  if(!digitalRead(inPin1) && !digitalRead(inPin2) && digitalRead(inPin3) && digitalRead(inPin4) && !digitalRead(inPin5)) // if 
  {
    Serial.println("abendesgler b");
    if(!digitalRead(button)){
      bat_call(12, 266, 700);
    }
    else{
      bat_call_series(12, 266, 700, batcallNumber);  
    }
  }

  // pipistrellus pygmaeus A
  // Peak 50 KHz / Length 3 ms / TBC 65 ms 
  // DIP 1 0 1 0 0  
  if(!digitalRead(inPin1) && digitalRead(inPin2) && !digitalRead(inPin3) && digitalRead(inPin4) && digitalRead(inPin5)) // if 
  {
    Serial.println("mücken a");
    if(!digitalRead(button)){
      bat_call(5, 62, 115);
    }
    else{
      bat_call_series(5, 62, 115, batcallNumber);  
    }
  }
 
  // pipistrellus pygmaeus B
  // Peak 62.5 KHz / Length 10 ms / TBC 95 ms 
  // DIP 1 0 1 0 1  
  if(!digitalRead(inPin1) && digitalRead(inPin2) && !digitalRead(inPin3) && digitalRead(inPin4) && !digitalRead(inPin5)) // if 
  {
    Serial.println("mücken b");
    if(!digitalRead(button)){
      bat_call(3, 80, 600);
    }
    else{
      bat_call_series(3, 80, 600, batcallNumber);  
    }
  }
  
  // myotis daubentonii A
  // Peak 38.4 KHz / Length 3 ms / TBC 65 ms 
  // DIP 1 0 0 1 0  
  if(!digitalRead(inPin1) && digitalRead(inPin2) && digitalRead(inPin3) && !digitalRead(inPin4) && digitalRead(inPin5)) // if 
  {
    Serial.println("wasser a");
    if(!digitalRead(button)){
      bat_call(8, 57, 115);
    }
    else{
      bat_call_series(8, 57, 115, batcallNumber);  
    }
  }
 
  // myotis daubentonii B
  // Peak 55.55 KHz / Length 7 ms / TBC 95 ms 
  // DIP 1 0 0 1 1  
  if(!digitalRead(inPin1) && digitalRead(inPin2) && digitalRead(inPin3) && !digitalRead(inPin4) && !digitalRead(inPin5)) // if 
  {
    Serial.println("wasser b");   
    if(!digitalRead(button)){
      bat_call(4, 80, 360);
    }
    else{
      bat_call_series(4, 80, 360, batcallNumber);  
    }
  }
  
  // automatic night programm a
  // simulates all species one after another - continuously
  // useful for testing hand detectors and microphones
  // DIP 1 1 1 1 0  
  if(!digitalRead(inPin1) && !digitalRead(inPin2) && !digitalRead(inPin3) && !digitalRead(inPin4) && digitalRead(inPin5)) // if 
  {
   
      Serial.println("automatik programm a");
      all_bat_calls(1);  // alle arten nach einander - kontinuierlich    
      

  }

  // automatic night programm b
  // simulates all species one after another - every 15 minutes a species
  // usefur for testing automatic bat logger 
  // DIP 1 1 1 1 1  
  if(!digitalRead(inPin1) && !digitalRead(inPin2) && !digitalRead(inPin3) && !digitalRead(inPin4) && !digitalRead(inPin5)) // if 
  {
   
      Serial.println("automatik programm b");
      all_bat_calls(900000);  
      
  }
}

// this simulates a single bat call
void bat_call(int pulse_micro, int delay_milli, int number_pulses) {
  
  digitalWrite(led, HIGH);   		// turn the LED on (HIGH is the voltage level)  
  digitalWrite(transducer, HIGH);   	// start pulse for transducer (HIGH is the voltage level)  
  
  //start pulse train 
  for (int i=0; i <= number_pulses; i++){
     delayMicroseconds(pulse_micro);  	// wait a few microseconds
     digitalWrite(transducer, LOW);   	// stop transducer pulse
     delayMicroseconds(pulse_micro);  	// wait a few microseconds
     digitalWrite(transducer, HIGH);	// start a transducer pulse
   }     
  digitalWrite(transducer, LOW);   	// stop transducer pulse
  digitalWrite(led, LOW);    		// turn the LED off by making the voltage LOW
  if(delay_milli>0){
    delay(delay_milli);  		// wait a few milliseconds
  }
}

// this simulates a series of bat calls
void bat_call_series(int pulse_micro, int delay_milli, int number_pulses, int number_calls) {
  
  for (int i=0; i <= number_calls; i++){
    bat_call(pulse_micro, delay_milli, number_pulses);
  }
  int pause = random(pauseMin, pauseMax); //random pause between min and max seconds
  delay(pause);   
}


// simulates common european bat call sequences
void all_bat_calls(long delay_between_bats) {
       
      delay(15000);
      
      // pipistrellus pipistrellus type a
      bat_call_series(7, 70, 125, batcallNumber);  
      delay(delay_between_bats);
     
      // barbastella type a
      bat_call_series(12, 47, 59, batcallNumber);
      delay(delay_between_bats);
      
      // myotis bechsteinii type a
      bat_call_series(8, 85, 77, batcallNumber);	
      delay(delay_between_bats);
      
      //myotis myotis type a
      bat_call_series(13, 83, 120, batcallNumber);   
      delay(delay_between_bats);
      
      //nyctalus noctula type a
      bat_call_series(23, 140, 70, batcallNumber); 
      delay(delay_between_bats);
      
      //pipistrellus pygmaeus type a
      bat_call_series(5, 62, 115, batcallNumber);  
      delay(delay_between_bats);      
      
      // myotis daubentonii type a
      bat_call_series(8, 57, 115, batcallNumber); 
      delay(delay_between_bats);
      
      // pipistrellus pipistrellus type b
      bat_call_series(4, 130, 500, batcallNumber);
      delay(delay_between_bats);      
      
      // barbastella type b
      bat_call_series(6, 70, 270, batcallNumber); //mops b
      delay(delay_between_bats);      
      
      // myotis bechsteinii type b
      bat_call_series(5, 102, 300, batcallNumber);  
      delay(delay_between_bats);      
      
      //myotis myotis type b
      bat_call_series(8, 160, 360, batcallNumber);  
      delay(delay_between_bats);      
      
      //nyctalus noctula type b
      bat_call_series(12, 266, 700, batcallNumber); 
      delay(delay_between_bats);      
      
      //pipistrellus pygmaeus type b
      bat_call_series(3, 80, 600, batcallNumber); 
      delay(delay_between_bats);      
      
      // myotis daubentonii type b
      bat_call_series(4, 80, 360, batcallNumber);  
      delay(delay_between_bats);            
  
}
