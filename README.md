# TelegramDoorEvents

With this project you will receive a notification on your phone as soon as your frontdoor is being locked or unlocked. The other way around you can type a command in your phone, after which you will receive an answer with the current status of your frontdoor (locked or unlocked).
The project also includes a red and green LED which show the current status of your frontdoor so you can see if it's locked or not just by looking at it. You can also choose to turn off the LEDs or notifications by phone.

The architecture in short: the project is built around an ESP8266, a magnet and reedcontact in your frontdoor and a Telegram bot on your phone. 

## Demonstration

[![TelegramDoorEvents](http://img.youtube.com/vi/YS4xPLxDfxo/0.jpg)](http://www.youtube.com/watch?v=YS4xPLxDfxo "TelegramDoorEvents")

Here is an example of the input/output in your Telegram Bot, where you see some notifications of events and some commands and answers:

![alt text](https://i.postimg.cc/Gmvcwf8n/telegram-frontdoor-bot.png)


## Parts
* ESP8266 (I used a clone NodeMCU)
* Magnet
* Reedcontact
* some electro components
* Phone

## Software
* Arduino IDE
* Additional Board Manager URL in your Arduino preferences: http://arduino.esp8266.com/stable/package_esp8266com_index.json. (I used ESP8266 Boards 2.7.1)
* ArduinoJson 5.13.5 from Benoît Blanchon
* UniversalTelegramBot 1.1.0 from Brian Lough
* This project software
* Telegram app on your phone

## Closeups

The NodeMCU ESP8266:

![alt text](https://i.postimg.cc/fbJk4CNc/esp8266-frontdoor.jpg)

The reedcontact in the closing bowl:

![alt text](https://i.postimg.cc/x1sqF7Wj/reedcontact-frontdoor.jpg)

The magnet glued onto the deadbolt: 

![alt text](https://i.postimg.cc/pTCSDfmS/magnet-frontdoor.png)
