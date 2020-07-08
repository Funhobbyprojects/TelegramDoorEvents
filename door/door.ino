#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

char ssid[] = "***";         // The SSID (name) of the Wi-Fi network you want to connect to
char password[] = "***";     // The password of the Wi-Fi network
// ------- Telegram config --------
#define BOT_TOKEN "***"  // your Bot Token (Get from Botfather)
char chat_id[] = "***";

String device = "Door: "; // Choose a friendly name for your frontdoor. It will show up in the Telegram bot
String receivedtext;
String showtext;
int ledredPin = D7; // the red LED's IO pin number on your device
int ledgreenPin = D6; // the green LED's IO pin number on your device
int reedPin = D5; // the reed contact's IO pin number on your device
int reedvalue = 0;
int reedvalueprevious = 0;
int leds_on = 0; // the LEDs will be default on (1) or off (0). Here it's off
int notif_on = 1; // the notifications to the Telegram bot will be default on (1) or off (0). Here it's on

// Language specific texts. Change them into what you want.
String lang_state_closed = "is closed";
String lang_state_open = "is open";
String lang_event_closed = "is being closed!";
String lang_event_opened = "is being opened!";
String lang_event_ledson = "the LEDS are now on!";
String lang_event_ledsoff = "the LEDS are now off!";
String lang_event_notifon = "the notifications are now on!";
String lang_event_notifoff = "the notifications are now off!";
String lang_input_door = "Door";
String lang_input_ledson = "Ledson";
String lang_input_ledsoff = "Ledsoff";
String lang_input_notifon = "Notifon";
String lang_input_notifoff = "Notifoff";
String lang_input_help = "Help";

// SSL client needed for library
WiFiClientSecure client;

UniversalTelegramBot bot(BOT_TOKEN, client);

String ipAddress = "";
bool sendMessage(String chat_id, String text, String parse_mode = "");
int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime; //last time messages' scan has been done

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting with ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connected!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the serial monitor
  
  // With this it stays a HTTPS connection but without SSL
  client.setInsecure();

  pinMode(ledredPin, OUTPUT);
  pinMode(ledgreenPin, OUTPUT);
  pinMode(reedPin, INPUT);

  reedvalue = digitalRead(reedPin);
  reedvalueprevious = reedvalue;
}

void loop() {
  // Read the status of the reedcontact. 1=open (green), 2=closed (red)
  reedvalue = digitalRead(reedPin);

  // Turn off the LEDS when variable is 0
  if(leds_on==0){
    digitalWrite(ledredPin, LOW);
    digitalWrite(ledgreenPin, LOW);
  }
  else {
      //Turn on and off the green and red LED according to the status of the reedcontact
      if(reedvalue==1){
        digitalWrite(ledredPin, LOW);
        digitalWrite(ledgreenPin, HIGH);
      }
      else {
        digitalWrite(ledredPin, HIGH);
        digitalWrite(ledgreenPin, LOW);
      }
    }
  // Serial.print("Reedcontact: ");
  // Serial.println(reedvalue);

  // Only send notifications when they are switched on
  if(notif_on==1){
       //Has the de status of the reedcontact changed since the previous loop? Then send a notification to Telegram
      if(reedvalue!=reedvalueprevious && reedvalue==1){
        showtext = device + lang_event_opened;
        Serial.println(showtext);
        bot.sendMessage(chat_id, showtext, "");
      }
      else {
        if(reedvalue!=reedvalueprevious && reedvalue==0){
        showtext = device + lang_event_closed;
        Serial.println(showtext);
        bot.sendMessage(chat_id, showtext, "");
        }
      }
  }

  //Check to see if new messages have been posted in Telegram since the previous loop.
  if (millis() > Bot_lasttime + Bot_mtbs)  {
  int numNewMessages = bot.getUpdates(bot.last_message_received);
    while(numNewMessages) {
      for (int i=0; i<numNewMessages; i++) {
        receivedtext = bot.messages[i].text;
        Serial.println(receivedtext);

        if(receivedtext==lang_input_ledson){
          leds_on=1;
          showtext = device + lang_event_ledson;
          Serial.println(showtext);
          bot.sendMessage(bot.messages[i].chat_id, showtext, "");
        }
        
        if(receivedtext==lang_input_ledsoff){
          leds_on=0;
          showtext = device + lang_event_ledsoff;
          Serial.println(showtext);
          bot.sendMessage(bot.messages[i].chat_id, showtext, "");
        }

        if(receivedtext==lang_input_notifon){
          notif_on=1;
          showtext = device + lang_event_notifon;
          Serial.println(showtext);
          bot.sendMessage(bot.messages[i].chat_id, showtext, "");
        }
        
        if(receivedtext==lang_input_notifoff){
          notif_on=0;
          showtext = device + lang_event_notifoff;
          Serial.println(showtext);
          bot.sendMessage(bot.messages[i].chat_id, showtext, "");
        }

        if(receivedtext==lang_input_door){
           if(reedvalue==0){
              showtext = device + lang_state_closed;
              Serial.println(showtext);
              bot.sendMessage(bot.messages[i].chat_id, showtext, "");
           }
           else {
             showtext = device + lang_state_open;
             Serial.println(showtext);
             bot.sendMessage(bot.messages[i].chat_id, showtext, "");
             }
          }
       
       if(receivedtext==lang_input_help){
          notif_on=0;
          showtext = device + lang_input_door + "; " + lang_input_ledson + "; " + lang_input_ledsoff + "; " + lang_input_notifon + "; " + lang_input_notifoff + "; " + lang_input_help;
          Serial.println(showtext);
          bot.sendMessage(bot.messages[i].chat_id, showtext, "");
        }
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

  Bot_lasttime = millis();
  }

    delay(500);
    reedvalueprevious = reedvalue;

}
