/*  Author: Suchdeep Juneja       Instagram:@suchdeep
 *  The video demonstration of this project can be seen through the following link:
 *  https://youtu.be/n7jioWfKq1I
 *  
 *  COMPONENT LIST
 *  1x   Arduino Uno
 *  2x   HC-SR04 Ultrasonic sensor
 *  8x   Jumper Wires (Male to Male)
 *  1x   Breadboard
 */

int trigPin1=3;     // Trigger Pin for sensor 1 connected to Digital Pin number 3 of arduino uno
int echoPin1=2;     // Echo Pin for sensor 1 connected to Digital Pin number 2 of arduino uno

int trigPin2=5;
int echoPin2=4;

void setup() {
  Serial.begin (9600);   // Serial Initialisation with Baud rate 9600
  
  pinMode(trigPin1, OUTPUT);    // Ultrasonic Sensor 1 pin Initialisation
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);    // Ultrasonic Sensor 2 pin Initialisation
  pinMode(echoPin2, INPUT);
}

void loop() {

  delay(100);
   /***************************************** SENSOR 1  ********************************************/
  long duration1, distance1;
  delay(60);
  digitalWrite(trigPin1, LOW);  
  delayMicroseconds(5);  
  digitalWrite(trigPin1, HIGH);   // Sending a High pulse on trigger pin
  delayMicroseconds(10); 
  digitalWrite(trigPin1, LOW);  
  delayMicroseconds(5);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;   // Calculating distance travelled by pulse
  //Serial.println("distance1");      // While Sending MIDI Data to Hairless MIDI make sure these print lines are commented out as it will otherwise send garbage value to the MIDI Receiver
  //Serial.println(distance1);        // Use Print statements only for debugging purpose on Serial monitor
  delay(100);
  if(distance1<5)
  {
    distance1 *= 2;                   // If the Hand is too close to sensor then sending MIDI value twice of the distance reading
    MIDImessage(176, 1,distance1);    //  176 = Control Channel command, 1 = Note Number, distance2 = value to send to MIDI
    delay(80);
  }
  else if(distance1>=10 && distance1<=126)
  {
   MIDImessage(176, 1, distance1);
   delay(80);
  }
  else if(distance1>126) 
  {
   MIDImessage(176, 1, 126);   // If The sensor reading is greater than the max limit of MIDI(126) then sending 126 value to MIDI
   delay(80);
  }
   else
    MIDImessage(176, 1, distance1);
  delay(100);
  
   /***************************************** SENSOR 2  ********************************************/
  long duration2, distance2;
  delay(60);
  digitalWrite(trigPin2, LOW);  
  delayMicroseconds(5);  
  digitalWrite(trigPin2, HIGH);   // Sending a High pulse on trigger pin
  delayMicroseconds(10); 
  digitalWrite(trigPin2, LOW);  
  delayMicroseconds(5);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;   // Calculating distance travelled by pulse
  //Serial.println("distance2");      // While Sending MIDI Data to Hairless MIDI make sure these print lines are commented out as it will otherwise send garbage value to the MIDI Receiver
  //Serial.println(distance2);        // Use Print statements only for debugging purpose on Serial monitor

  delay(100);
  if(distance2<5)
  {
    distance2 *= 2;                     // If the Hand is too close to sensor then sending MIDI value twice of the distance reading
    MIDImessage(176, 2,distance2);      //  176 = Control Channel command, 2 = Note Number, distance2 = value to send to MIDI
    delay(80);
  }
  else if(distance2>=10 && distance2<=126)
  {
   MIDImessage(176, 2, distance2);
   delay(80);
  }
  else if(distance2>126) 
  {
   MIDImessage(176, 2, 126);   // If The sensor reading is greater than the max limit of MIDI(126) then sending 126 value to MIDI
   delay(80);
  }
   else
    MIDImessage(176, 2, distance2);
  delay(100);  //small delay to control fluctuations
}
  
/*
  The MIDImessage has three bytes, first is the Control Channel, 
  the other two bytes denotes the note number and velocity/pressure value respectively.

  Refer below link for additional info on status bytes:

  https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes
*/

void MIDImessage(byte command, byte data1, byte data2)  
{
   Serial.write(command);
   Serial.write(data1);
   Serial.write(data2);
}
