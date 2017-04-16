# Anti House Thief

Protect your house with this Arduino and Raspberry PI setup!

## Installation on Raspberry PI

Install mosquitto
```
sudo wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
sudo apt-key add mosquitto-repo.gpg.key
cd /etc/apt/sources.list.d/
sudo wget http://repo.mosquitto.org/debian/mosquitto-jessie.list
sudo apt-get update
sudo apt-get install mosquitto
```

Start mosquitto
```
sudo /etc/init.d/mosquitto start
```

Install mosquitto_sub
```
sudo apt-get install mosquitto_sub
```

Listen to a topic called 
```
mosquitto_sub -d -t nieuws
```


Install touchscreen drivers
```
// download the driver
wget http://www.waveshare.com/w/upload/4/4b/LCD-show-161112.tar.gz

// extract the compressed directory
tar xvf LCD-show-*.tar.gz
cd LCD-show/

// change premissions
chmod +x LCD35-show

// enable the display and rotate it 180 degrees
./LCD35-show 180
```

## Installation & configuration on D1 Mini
Install [pubsubclient](http://pubsubclient.knolleary.net) libary
Install [esp drivers](https://github.com/esp8266/arduino)

## Installation on phones
Approved by us:
[iOS](https://itunes.apple.com/nl/app/mqttool/id1085976398)


## Sources
http://www.switchdoc.com/2016/02/tutorial-installing-and-testing-mosquitto-mqtt-on-raspberry-pi/
http://www.waveshare.com/wiki/3.5inch_RPi_LCD_(A)



## Credits

[Casper](https://github.com/CaspervdHoek) +
[Doron](https://github.com/DoronHartog) +
[Juryt](https://github.com/Juryt) +
[Kelvin](https://github.com/Kelvin-Meyer) 
