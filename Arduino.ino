#include <WiFiEspClient.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <PubSubClient.h>
#include "SoftwareSerial.h"

//#define WIFI_AP "HubGenial Guest"
//#define WIFI_PASSWORD "Albert Einstein"

#define WIFI_AP "HubGenial_EXT"
#define WIFI_PASSWORD "Alan Turing"

#define TOKEN "ARDUINO_DEMO_TOKEN"

const char* outTopic = "sleepff1out";
const char* inTopic = "sleepff1in";

const char* MQTT_SERVER = "192.168.1.11"; //Broker do Mosquitto.o

String payload = "2";
// Initialize the Ethernet client object
WiFiEspClient espClient;

PubSubClient client(espClient);

SoftwareSerial soft(2, 3); // RX, TX

int status = WL_IDLE_STATUS;
unsigned long lastSend;

void setup() {
  // initialize serial for debugging
  Serial.begin(9600);
  //  dht.begin();
  InitWiFi();
  //client.setServer( thingsboardServer, 1883 );
  client.setServer( MQTT_SERVER, 1883 );
  lastSend = 0;
  //Pinos ligados aos pinos 1, 2, 3 e 4 do teclado - Linhas
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  //Pinos ligados aos pinos 5, 6, 7 e 8 do teclado - Colunas
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}

void loop() {
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(WIFI_AP);
      // Connect to WPA/WPA2 network
      status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      delay(500);
    }
    Serial.println("Connected to AP");
  }

  if ( !client.connected() ) {
    reconnect();
  }

  if ( millis() - lastSend > 100 ) { // Update and send only after 1 seconds
    for (int linha = 8; linha <= 11; linha++)
    {
      //Alterna o estado dos pinos das linhas
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(linha, HIGH);
      //Verifica se alguma tecla da coluna 1 foi pressionada
      if (digitalRead(7) == HIGH)
      {
        imprime_linha_coluna(linha, 1);
        while (digitalRead(7) == HIGH) {}
      }

      //Verifica se alguma tecla da coluna 2 foi pressionada
      if (digitalRead(6) == HIGH)
      {
        imprime_linha_coluna(linha, 2);
        while (digitalRead(6) == HIGH) {};
      }

      //Verifica se alguma tecla da coluna 3 foi pressionada
      if (digitalRead(5) == HIGH)
      {
        imprime_linha_coluna(linha, 3);
        while (digitalRead(5) == HIGH) {}
      }

      //Verifica se alguma tecla da coluna 4 foi pressionada
      if (digitalRead(4) == HIGH)
      {
        imprime_linha_coluna(linha, 4);
        while (digitalRead(4) == HIGH) {}
      }
    }
    lastSend = millis();
  }

  client.loop();
}


void InitWiFi()
{
  // initialize serial for ESP module
  soft.begin(19200);
  // initialize ESP module
  WiFi.init(&soft);
  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(WIFI_AP);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    delay(500);
  }
  Serial.println("Connected to AP");
}
//

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(outTopic, "sleepff1 booted");
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      for (int i = 0; i < 5000; i++) {
        //       extButton();
        delay(1);
      }
    }
  }
}



void imprime_linha_coluna(int x, int y)
{

  delay(10);
  //       Serial.println();
  //String payload="0";
  Serial.println("Pressionou o numero:");

  if (y == 1) {
    if (x == 11) {
      Serial.print(1);
      payload = "1";
      Serial.println();
    }
    else if (x == 10) {
      Serial.print(4);
      payload = "4";
      Serial.println();
    }
    else if (x == 9) {
      Serial.print(7);
      payload = "7";
      Serial.println();
    }
    else if (x == 8) {
      Serial.print("*");
      payload = "*";
      Serial.println();
    }
  }
  if (y == 2) {
    //   Serial.println("Pressionou o numero:");
    if (x == 11) {
      Serial.print(2);
      payload = "2";
      Serial.println();
    }
    else if (x == 10) {
      Serial.print(5);
      payload = "5";
      Serial.println();
    }
    else if (x == 9) {
      Serial.print(8);
      payload = "8";
      Serial.println();
    }
    else if (x == 8) {
      Serial.print(0);
      payload = "0";
      Serial.println();
    }
  }
  if (y == 3) {
    //   Serial.println("Pressionou o numero:");
    if (x == 11) {
      Serial.print(3);
      payload = "3";
      Serial.println();
    }
    else if (x == 10) {
      Serial.print(6);
      payload = "6";
      Serial.println();
    }
    else if (x == 9) {
      Serial.print(9);
      payload = "9";
      Serial.println();
    }
    else if (x == 8) {
      Serial.print("#");
      payload = "#";
      Serial.println();
    }
  }
  if (y == 4) {
    //   Serial.println("Pressionou o numero:");
    if (x == 11) {
      Serial.print("A");
      payload = "A";
      Serial.println();
    }
    else if (x == 10) {
      Serial.print("B");
      payload = "B";
      Serial.println();
    }
    else if (x == 9) {
      Serial.print("C");
      payload = "C";
      Serial.println();
    }
    else if (x == 8) {
      Serial.print("D");
      payload = "D";
      Serial.println();
    }
  }
  char attributes[100];
  payload.toCharArray( attributes, 100 );
  client.publish("newMyT", attributes);
}
