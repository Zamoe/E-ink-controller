#ifndef _mqtt_h
#define _mqtt_h

/******************************************************************************
MQTT_Switch_Example.ino
Example for controlling a light using an MQTT switch
by: Alex Wende, SparkFun Electronics

This sketch connects the ESP32 to a MQTT broker and subcribes to the topic
room/light. When the button is pressed, the client will toggle between
publishing "on" and "off".
******************************************************************************/

#include <WiFi.h>
#include <PubSubClient.h>
#include "settings.h"


// MQTT Network
IPAddress broker(10,0,0,32); // IP address of your MQTT broker eg. 192.168.1.50
WiFiClient wclient;

const char *ID = "DeskController";  // Name of our device, must be unique
const char *TOPIC = "rotarybutton";  // Topic to subcribe to
int SWITCH_PIN = 27;

//State received from HA topics:
const char *BedroomSpeakerVolume = "test/media_player/bedroom_speaker/volume_level";
//const char *subTopic = "test/light/#";

String response;
float volume=0;



PubSubClient client(wclient); // Setup MQTT client
bool state=0;
String prevSpotify = "";
String prevSpotifyArtist = "";
// Handle incomming messages from the broker
void callback(char* topic, byte* payload, unsigned int length) {
  String tempTopic = String(topic);

  for (int i = 0; i < length; i++) {
    response += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(response);
  volume = response.toInt();
  if (ContMode == "default"){
  if (tempTopic == "test/media_player/bedroom_speaker/volume_level"){
      Serial.println("Loop run");
      volume = response.toFloat();
      volume = volume*10;
      ledLoop(volume);
    }
  else if(tempTopic == "test/light/roof_lights/state"){
    if (response == "on"){
      ceilingState = 1;
      }
    else if (response == "off"){
      ceilingState = 0;
      //icons(0,lampx,lampy,backlight);
      }
    else{
      ceilingState = 3;
      }
    icons(ceilingState,ceilingx,ceilingy,ceiling,response);
    }
  else if(tempTopic == "test/light/lamp/state"){
    if (response == "on"){
      lampState = 1;
      //icons(1,lampx,lampy,backlight);
      }
    else if (response == "off"){
      lampState = 0;
      //icons(0,lampx,lampy,backlight,response);
      }
    else{
      lampState = 3;
      }
    icons(lampState,lampx,lampy,lamp,response);
    }
  else if(tempTopic == "test/light/bed/state"){
    if (response == "on"){
      bedState = 1;
      //icons(1,lampx,lampy,backlight,response);
      }
    else if (response == "off"){
      bedState = 0;
      //icons(0,lampx,lampy,backlight);
      }
    else{
      bedState = 3;
      }
    icons(bedState,bedx,bedy,bed,response);
    }
  else if(tempTopic == "test/media_player/samsung_tv_remote/state"){
    if (response == "on"){
      tvState = 1;
      //icons(1,lampx,lampy,backlight,response);
      }
    else if (response == "off"){
      tvState = 0;
      //icons(0,lampx,lampy,backlight);
      }
    else{
      tvState = 3;
      }
    icons(tvState,tvx,tvy,tv,response);
    }
  else if(tempTopic == "test/media_player/samsung_tv_remote/source"){
    if (tvState == 1){
      Serial.println(response);
      response.remove(0,1);
      int len = response.length();
      response.remove(len-1,1);
      tvSource = response;
      Serial.println(tvSource);
      icons(4,tvx,tvy,tv,response);
      }
    }
  else if(tempTopic == "test/light/tv_backlight/state"){
    if (response == "on"){
      backlightState = 1;
      //icons(1,lampx,lampy,backlight);
      }
    else if (response == "off"){
      backlightState = 0;
      //icons(0,lampx,lampy,backlight);
      }
    else{
      backlightState =3;
      }
    icons(backlightState,backlightx,backlighty,backlight,response);
    }
  else if(tempTopic == "test/media_player/spotify_zameer_mahomed/media_title"){
    //if (tvState == 1){
      //Serial.println(response);
      response.remove(0,1);
      int len = response.length();
      response.remove(len-1,1);
      Serial.println(tvSource);
      if(prevSpotify != response){
        //only update display if song changes
        displaySpotify(1,response);
        prevSpotify = response;
        Serial.println("Song Updated");
      }
      //}
    }
  else if(tempTopic == "test/media_player/spotify_zameer_mahomed/media_artist"){
    //if (tvState == 1){
      //Serial.println(response);
      response.remove(0,1);
      int len = response.length();
      response.remove(len-1,1);
      if(prevSpotifyArtist != response){
        displaySpotify(2,response);
        prevSpotifyArtist = response;
        Serial.println("Artist Updated");
      }
    
      //}
    }
  }
  allStatesNew = ceilingState + lampState + backlightState + tvState + bedState;
  response = "";
  
  //updateStates();
}


void mqttRegisterButtons(){
  //registers buttons as sensors in homeassistant
  client.publish("homeassistant/sensor/mode/config","{\"name\":\"Desk Controller Mode\",\"object_id\":\"mode\",\"state_topic\": \"homeassistant/sensor/mode/state\"}",true);
  client.publish("homeassistant/sensor/mode/state", "default");
  client.publish("homeassistant/sensor/left1/config","{\"name\":\"Left 1\",\"object_id\":\"left1\",\"state_topic\": \"homeassistant/sensor/left1/state\"}",true);
  client.publish("homeassistant/sensor/left2/config","{\"name\":\"Left 2\",\"object_id\":\"left2\",\"state_topic\": \"homeassistant/sensor/left2/state\"}",true);
  client.publish("homeassistant/sensor/left3/config","{\"name\":\"Left 3\",\"object_id\":\"left3\",\"state_topic\": \"homeassistant/sensor/left3/state\"}",true);
  client.publish("homeassistant/sensor/left4/config","{\"name\":\"Left 4\",\"object_id\":\"left4\",\"state_topic\": \"homeassistant/sensor/left4/state\"}",true);

  client.publish("homeassistant/sensor/right1/config","{\"name\":\"Right 1\",\"object_id\":\"right1\",\"state_topic\": \"homeassistant/sensor/right1/state\"}",true);
  client.publish("homeassistant/sensor/right2/config","{\"name\":\"Right 2\",\"object_id\":\"right2\",\"state_topic\": \"homeassistant/sensor/right2/state\"}",true);
  client.publish("homeassistant/sensor/right3/config","{\"name\":\"Right 3\",\"object_id\":\"right3\",\"state_topic\": \"homeassistant/sensor/right3/state\"}",true);
  client.publish("homeassistant/sensor/right4/config","{\"name\":\"Right 4\",\"object_id\":\"right4\",\"state_topic\": \"homeassistant/sensor/right4/state\"}",true);

  client.publish("homeassistant/sensor/rotary/config","{\"name\":\"Rotary Encoder\",\"object_id\":\"rotary\",\"state_topic\": \"homeassistant/sensor/rotary/state\"}",true);
  client.publish("homeassistant/sensor/rtbtn/config","{\"name\":\"Rotary Button\",\"object_id\":\"rtbtn\",\"state_topic\": \"homeassistant/sensor/rtbtn/state\"}",true);
  }
void mqttSubscribe(){
  client.subscribe(BedroomSpeakerVolume);
  //client.subscribe(subTopic);
  //client.subscribe("test/light/#");
  client.subscribe("test/light/roof_lights/state");
  client.subscribe("test/light/lamp/state");
  client.subscribe("test/light/bed/state");
  client.subscribe("test/media_player/samsung_tv_remote/state"); 
  client.subscribe("test/light/tv_backlight/state");
  client.subscribe("test/media_player/samsung_tv_remote/source"); 
  client.subscribe("test/media_player/spotify_zameer_mahomed/media_title");
  client.subscribe("test/media_player/spotify_zameer_mahomed/media_artist");
  }
// Connect to WiFi network
void setup_wifi() {
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // Connect to network

  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Reconnect to client
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(ID,HA_USER,HA_PASS)) {
      Serial.println("connected");
      Serial.print("Publishing to: ");
      Serial.println(TOPIC);
      Serial.println('\n');
      mqttRegisterButtons();
      mqttSubscribe();
      /*client.subscribe(BedroomSpeakerVolume);
      //client.subscribe(subTopic);
      //client.subscribe("test/light/#");
      client.subscribe("test/light/roof_lights/state");
      client.subscribe("test/light/lamp/state");
      client.subscribe("test/light/tv_backlight/state");
      client.subscribe("test/light/bed/state");
      client.subscribe("test/media_player/samsung_tv_remote/state"); 
      client.subscribe("test/media_player/samsung_tv_remote/source"); 
      client.subscribe("test/media_player/spotify_zameer_mahomed/media_title");
      client.subscribe("test/media_player/spotify_zameer_mahomed/media_artist");*/
        Serial.print("Subcribed to: ");
        Serial.println(BedroomSpeakerVolume);
        Serial.println('\n');
      //subscribe to topics
      /*for (int i = 0; i<subtopicsSize; i++){
        char Temp;
        String tempString = subtopics[i];
        tempString.toCharArray(Temp);
        client.subscribe(Temp);
        Serial.print("Subcribed to: ");
        Serial.println(Temp);
        Serial.println('\n');
        }*/
      
      

    } else {
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setupMQTT() {
  //Serial.begin(115200); // Start serial communication at 115200 baud
  pinMode(SWITCH_PIN,INPUT);  // Configure SWITCH_Pin as an input
  digitalWrite(SWITCH_PIN,HIGH);  // enable pull-up resistor (active low)
  delay(100);
  setup_wifi(); // Connect to network
  client.setServer(broker, 1883);
  client.setCallback(callback);// Initialize the callback routine
  mqttRegisterButtons();
}
void delayoff(unsigned long prevMilli, const char *mqttButtonPress){
//  char mqttButtonPress[40] = input;
  unsigned long currentMilli = millis();
  Serial.println("delay start");
  if (currentMilli-prevMilli >= 1000){
    Serial.println("delay run");
    client.publish(mqttButtonPress, "off");
    }
  }
void mqttButtons(int btn, int pressed){
  unsigned long prevMilli = millis();
  char mqttButtonState[10];
  char mqttButtonPress[40] = "homeassistant/sensor/\0";
  switch (pressed) {
    case 1:
      strcpy(mqttButtonState,"short\0");
      break;
    case 2:
      strcpy(mqttButtonState,"double\0");
      break;
    case 3:
      strcpy(mqttButtonState,"long\0");
      break;
  }
  if (btn == 0){
    strcat(mqttButtonPress,"left1\0");
    }
  else if(btn == 1){
    strcat(mqttButtonPress,"left2\0");
    }
  else if(btn == 2){
    strcat(mqttButtonPress,"left3\0");
    }
  else if(btn == 3){
    strcat(mqttButtonPress,"left4\0");
    }
  else if(btn == 4){
    strcat(mqttButtonPress,"right1\0");
    }
  else if(btn == 5){
    strcat(mqttButtonPress,"right2\0");
    }
  else if(btn == 6){
    strcat(mqttButtonPress,"right3\0");
    }
  else if(btn == 7){
    strcat(mqttButtonPress,"right4\0");
    }
  
  else if(btn == 27){
    strcat(mqttButtonPress,"rtbtn\0");
    } 
  strcat(mqttButtonPress,"/state"); 
  Serial.print("mqttButtonState: ");
  Serial.println(mqttButtonState);
  Serial.print("mqttButtonPress: ");
  Serial.println(mqttButtonPress);
  //String temp = "homeassistant/sensor/"+mqttButtonPress+"/state";
  client.publish(mqttButtonPress, mqttButtonState);
  Serial.print("mqttButtonSend");
  //Serial.println(mqttButtonSend);
  
  //delayoff(prevMilli, mqttButtonPress);
  delay(10);
  client.publish(mqttButtonPress, "off");
  }
int prevCount = 0;

void mqttRotary(int tempCount){
  //Serial.print("Count: ");
  //Serial.println(tempCount);
  //Serial.print("PrevCount: ");
  //Serial.println(prevCount);
  if (tempCount > prevCount){
    prevCount = tempCount;
    Serial.println("CW");
    client.publish("homeassistant/sensor/rotary/state", "CW");
    }
  else if (tempCount < prevCount){
    prevCount = tempCount;
    Serial.println("CCW");
    client.publish("homeassistant/sensor/rotary/state", "CCW");
    }
  else {
    return;
    }
   delay(10);
   client.publish("homeassistant/sensor/rotary/state", "off");
  }
#endif
