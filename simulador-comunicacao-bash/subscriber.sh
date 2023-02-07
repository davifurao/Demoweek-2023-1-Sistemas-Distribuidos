#!/bin/bash
#somente irá variar o tópico nesse código

saida_instrucao = "Caso você queira terminar a operação, aperte Ctrl+c"
function atualizacao(){
sudo apt-get update
sudo apt-get upgrade
sudo apt install mosquitto
sudo apt install mosquitto-clients

}


echo "primeiro iremos verificar se está tudo atualizado"
atualizacao


printf "lembre-se que você está no cliente"
printf""

printf  "Digite o tópico a ser subscrito:  "
read topico

function mosquitto-sub(){
sudo service mosquitto start
echo $saida_instrucao\n
echo $host
echo $topico
sudo mosquitto_sub -h test.mosquitto.org  -t topico #O broker sempre será esse

}
mosquitto-sub
