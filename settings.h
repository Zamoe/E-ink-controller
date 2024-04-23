#ifndef _settings_h
#define _settings_h
//All the settings are to be put here

// WiFi Network Credentials
const char *ssid =  "Secret";   // name of your WiFi network
const char *password =  "Secret"; // password of the WiFi network

// Home Assistant Credentials
const char *HA_USER = "Secret";
const char *HA_PASS = "Secret";

//mode of the controler
String ContMode ="default";
//RotbuttonPin
const unsigned int rotBtnPin = 27;
//  //C

//Button Pins
//L: Left side ; R: Right
const unsigned int btnPinA = 35;
//const unsigned int L1p = 25;
//const unsigned int L2p = 33;
//const unsigned int L3p = 35;
//const unsigned int L4p = 34;
//const int R1p = 22;
//const int R2p = 21;
//const int R3p = 25;
//const int R4p = 33;


//MQTT Topics to subscribe to:
//set array size
//int subtopicsSize = 2;
//String subtopics[2]={"test/light/lamp/state","test/media_player/befroom_speaker/volume_level"};

//MQTT topics to listen to:

//State variables
int ceilingState = 0;
int lampState = 0;
int bedState = 0;
int tvState = 0;
int backlightState = 0;
int allStatesNew = 0;
int allStatesOld = -1;
String tvSource ="";
String spotifyTitle = "";
String spotifyArtist = "";

//int lampState = 0;

int ceilingx = 5;
int ceilingy = 0;

int lampx = 5;
int lampy = 70;

int bedx = 5;
int bedy = 130;

int prevx = -10;
int prevy = 190;

int tvx = 73;
int tvy = 0;

int backlightx = 73;
int backlighty = 70;

//int x = 73;
//int bedy = 130;

int nextx = 88;
int nexty = 190;

#endif
