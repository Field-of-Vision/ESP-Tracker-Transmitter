#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "time.h"
#include "BluetoothSerial.h" 


#define AWS_IOT_PUBLISH_TOPIC   "esp32/globalTest"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"


WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
BluetoothSerial ESP_BT; 


const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600*3;
const int   daylightOffset_sec = 0;


String topicBT;
char incoming;
String result = "";
int ind1;
int ind2;
int ind3;
int incomingByte = 0;
const byte numChars = 150;
char receivedChars[numChars];

boolean newData = false;

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}


void connectAWS(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to " +String(WIFI_SSID));
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);
  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);
  // Create a message handler
  //client.setCallback(messageHandler);#########################################
  Serial.print("Connecting to AWS IOT");
  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }
  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS IoT Connected!");
}


void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["Instance"] = (receivedChars);
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
 // client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
  //Serial.println(receivedChars);

//  StaticJsonDocument<512> doc;
 // doc["Instance"] = "{\"timestamp\": 8.5,\"x\": 83,\"y\": 0,\"possession\": \"N\",\"pass\": 0,\"receive\": 0,\"home goal\": 0,\"away goal\": 0,\"out\": 0}";
  //char jsonBuffer[512];
  //serializeJson(doc, jsonBuffer); // print to client
  //client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}


//"timetamp": 0,
//"x": 345,
//"y":  123,
//"posession": 0,
//"pass": 0,
//"receive": 1,
//"home Goal": 0,
//"away Goal": 0,
//"out": 0


//void messageHandler(char* topic, byte* payload, unsigned int length) {
//  Serial.print("incoming: ");
//  Serial.println(topic);
//  StaticJsonDocument<200> doc;
//  deserializeJson(doc, payload);
//  const char* number = doc["timestamp"];
//  const char* xReceived = doc["x"];
//  const char* yReceived = doc["x"];
//  const char* teamPosession = doc["possession"];
//  const char* homeTouch = doc["pass"];
//  const char* awayTouch = doc["receive"];
//  const char* homeGoal = doc["home Goal"];
//  const char* awayGoal = doc["away Goal"] ;
//  const char* outBounds = doc["out"] ;
//  Serial.println(number);
//  Serial.println(xReceived);
//  Serial.println(yReceived);
//  Serial.println(homeTouch);
//  Serial.println(awayTouch);
//  Serial.println(homeGoal);
//  Serial.println(awayGoal);
//}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
     //   Serial.println(receivedChars);
        Serial.println(String(receivedChars) + ">");
          client.publish(AWS_IOT_PUBLISH_TOPIC, receivedChars);
        newData = false;
    }
}



void setup() {
  Serial.begin(115200);
  //ESP_BT.begin("FIELD OF VISION");
  //bluetoothGetWIFI();
  //stringToChar();
  connectAWS();
//  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
 // printLocalTime();
}


void loop() {
    recvWithStartEndMarkers();
    showNewData();
  publishMessage();
 // printLocalTime();
  client.loop();
  delay(140);
}
