# TelegramDoorEvents

With this project you will receive a notification on your phone as soon as your frontdoor is being locked or unlocked. The other way around you can type a message in your phone, after which you will receive an answer back with the current status of your frontdoor (locked or unlocked).
The project also includes a red and green LED which show the current status of your frontdoor so you can see if it's locked or not just by looking at it. You can also choose to turn off the LEDs or notifications by phone.


The architecture in short: the project is built around an ESP8266, a magnet and reedcontact in your frontdoor and a Telegram bot on your phone. 

Hardware you need:
* ESP8266
* Magnet
* Reedcontact
* some electro components
* Phone

Software you need:
* Arduino IDE
* Additional Board Manager URL in your Arduino preferences: http://arduino.esp8266.com/stable/package_esp8266com_index.json. (I used ESP8266 Boards 2.7.1)
* ArduinoJson 5.13.5 from Benoît Blanchon
* UniversalTelegramBot 1.1.0 from Brian Lough
* This project software
* Telegram app on your phone
