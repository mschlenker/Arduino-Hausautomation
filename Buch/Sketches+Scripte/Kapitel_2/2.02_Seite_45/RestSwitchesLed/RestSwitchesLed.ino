// #define BRIDGE_BAUDRATE 19200

#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;
YunClient client;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  YunClient client = server.accept();
  if (client) {
    process(client);
    client.stop();
  }
  delay(50);
}

void process(YunClient client) {
  String command = client.readString();
  command.trim();
  Serial.println(command);
  if (command == "high") {
    digitalWrite(13, HIGH);
    Bridge.put("ledhigh", "0");
  }
  if (command == "low") {
    digitalWrite(13, LOW);
    Bridge.put("ledhigh", "1");
  }
  client.print(command);
}
