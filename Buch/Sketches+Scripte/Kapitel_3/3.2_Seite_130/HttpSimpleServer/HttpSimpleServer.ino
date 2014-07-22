/*
 * UIPEthernet EchoServer example.
 *
 * UIPEthernet is a TCP/IP stack that can be used with a enc28j60 based
 * Ethernet-shield.
 *
 * UIPEthernet uses the fine uIP stack by Adam Dunkels <adam@sics.se>
 *
 *      -----------------
 *
 * This Hello World example sets up a server at 192.168.1.6 on port 1000.
 * Telnet here to access the service.  The uIP stack will also respond to
 * pings to test if you have successfully established a TCP connection to
 * the Arduino.
 *
 * This example was based upon uIP hello-world by Adam Dunkels <adam@sics.se>
 * Ported to the Arduino IDE by Adam Nielsen <malvineous@shikadi.net>
 * Adaption to Enc28J60 by Norbert Truchsess <norbert.truchsess@t-online.de>
 * Simplified for Arduino Hausautomation by Mattias Schlenker */

#include <UIPEthernet.h>

const char page[] = "HTTP/1.0 200 OK\r\n" 
  "Content-Type: text/plain\r\n\r\nHallo Welt!\r\n";
const byte mac[6] = { 0x23, 0x23, 0xDE, 0xAD, 0xBE, 0xEF };
const IPAddress myIP(10,76,23,111);

EthernetServer server = EthernetServer(80);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac,myIP);
  server.begin();
  Serial.println("\nListening...");
}

void loop() {
  if (EthernetClient client = server.available()) {
    Serial.println("\nAnswering...");
    client.println(page);
    client.stop();
    Serial.println("\nDisconnect...");
  }
}

