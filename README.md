# Anti House Thief

Protect your house with this Arduino and Raspberry PI setup!

## Installation on Raspberry pi
Get ip of Raspberry pi
```
ifconfig
```

Install mosquitto
```
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




## Credits

[Casper](https://github.com/CaspervdHoek) +
[Doron](https://github.com/DoronHartog) +
[Juryt](https://github.com/Juryt) +
[Kelvin](https://github.com/Kelvin-Meyer) 
