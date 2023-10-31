# Video-Call-Warner-MQTT
 
This project make it possible to tell your coworkers if they can enter your office and make noise or if you are in a video call or phone and you must be left alone.

![webpage](images/webpage.jpg)

You can select on a webpage if the office is free or not and it lights up the corresponding light next to your door.

Technologies used :
- MQTT
- HTML/CSS/JS
- Mosquitto Broker
- ESP32

## Getting started

### Prerequisite

For this project I used :
- Mosquitto MQTT Broker running on a Raspberry Pi


### Install the broker

Install Mosquitto on the Raspberry Pi
```
sudo apt-get update
sudo apt-get install mosquitto
```

Configure the broker, add these lines in the configuration file. This will enable user, port 1883 and websockets port 8081
```
sudo nano /etc/mosquitto/mosquitto.conf


password_file /etc/mosquitto/passwd
listener 1883
listener 8081
protocol websockets
```

Add at least one user to your broker. Choose a username in the command, it will then ask you for a password for this user
```
mosquitto_passwd -c passwd USERNAME
```
Restart the service
```
sudo systemctl restart mosquitto
```