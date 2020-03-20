#include <OSCMessage.h>

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    
#include <OSCMessage.h>

EthernetUDP Udp;

IPAddress ip(192,168,0,120); //must be unique! First three numbers must be the same as the destination machine (subnet)
//destination IP
IPAddress outIp(192,168,0,21); //check the destination machine //164,11,214,124
const unsigned int outPort = 7500; //destination port
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // you can find this written on the board of some Arduino Ethernets or shields


const int slide1 = A0;
const int slide2 = A1;
const int slide3 = A2;
const int slide4 = A3;

const int btn1 = 7;
const int btn2 = 5;

int btn1_val = 0;
int btn2_val = 0;

void setup() {
  // put your setup code here, to run once:
  Ethernet.begin(mac,ip);
    Udp.begin(8888);
    
  pinMode(slide1, INPUT);
  pinMode(slide2, INPUT);
  pinMode(slide3, INPUT);
  pinMode(slide4, INPUT);

  pinMode(btn1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int32_t slide1_val = analogRead(slide1);
  int32_t slide2_val = analogRead(slide2);
  int32_t slide3_val = analogRead(slide3);
  int32_t slide4_val = analogRead(slide4);

  btn1_val = digitalRead(btn1);
  btn2_val = digitalRead(btn2);
/*  if (btn1_val == HIGH) {
    Serial.println("1 Pressed");
  } else Serial.println("No Signal");

  if (btn2_val == HIGH) {
    Serial.println("2 Pressed");
  } else Serial.println("NO"); */
  //Serial.println(slide1_val);
  OSCMessage msg("/analogue");
    msg.add(slide1_val); // add reading from analogue pin 0
    msg.add(slide2_val); // add reading from analogue pin 0
    msg.add(slide3_val); // add reading from analogue pin 0
    msg.add(slide4_val); // add reading from analogue pin 0
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp); // send the bytes to the SLIP stream
    Udp.endPacket(); // mark the end of the OSC Packet
    msg.empty(); // free space occupied by message

    delay(20);
//  Serial.println(btn1);
//  Serial.println("slider 2: " + slide1_val);
//  Serial.println("slider 3: " + slide1_val);
//  Serial.println("slider 4: " + slide1_val);
}
