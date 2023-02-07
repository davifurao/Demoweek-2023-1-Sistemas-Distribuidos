#!/bin/bash
function atualizacao(){
sudo apt-get update
sudo apt-get upgrade
sudo apt install mosquitto
sudo apt install mosquitto-clients
sudo apt-get install python3
sudo apt-get install python3-pip
pip install paho-mqtt
sudo apt-get update
sudo apt-get upgrade
sudo service mosquitto start

}

atualizacao