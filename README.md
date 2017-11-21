# Arduino devices for a bat survey project

Here you find some Arduino sketches and other resources that were created for building small low cost devices supporting our bat surveys as part of a fauna, flora and habitat (FFH) monitoring project by an organisation in Germany: <a href="http://bi-wollenberg.org" target="_blank"> BI&nbsp;„Rettet&nbsp;den&nbsp;Wollenberg“&nbsp;e.V.</a>. Visit the [project's homepage (German only)](http://ffh-monitor.org) for more information.<br>
<br>
Code and information is provided in the hope that it is helpful to other bat friends and nature enthousiasts. We are open for questions or feedback. Please feel free to contact me through GitHub or drop a message in <a href=mailto:ffhmonitor@gmail.com>my mailbox</a>.<br>
<br>
FVG, November 2017
<hr>

## bat_simulator_v2.ino

A small low cost ultrasonic transmitter can be driven by the Arduino producing short ultrasonic pulse trains. The device does actually not produce real world bat call sequences, but the ultrasonic output helps to quickly test microphones, bat loggers and detectors.<br>
<br>
Different pulse frequencies, time between calls and sequence lengths can be selected by means of a dip switch, simulating calls of different European bat species. As human ears will not hear the sound produced, a LED blinks wenn an ultrasonic pulse train is transmitted.<br>
<br>
The transmitter is a common part found on distance measuring sensor-boards for Raspberry Pi or Arduino based devices and shouldn't be too difficult to get. We use a UST-40T and it works very well.<br>
<br>
Transmitter and dip switch both are directly connected to digital I/O pins. The comments in the sketch are straight forward and should deliver enough information to help you to build the circuit.
<hr>

## environment_logger_v2.ino

A temperature and humidity logger based on the Arduino data logging shield. The board provides a battery driven real time clock and an SD-card interface. 

The sketch records environment data with timestamp to a SD-card every 10 minutes, so you. A blinking LED provides basic information on error status in the Field:
 
 - 1 x red = Clock module RTC not found 
 - 2 x red = SD card not found
 - 3 x red = no filesystem found on SD Card
 - 4 x red = file write error
 - 5 x red = error reading sensor
 
 The sketch is commented and should be self-explaining.



