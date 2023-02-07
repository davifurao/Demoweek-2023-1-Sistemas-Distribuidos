#!/bin/bash

#atualização do serviço toda vez que o inicia, por segurança
function atualizacao(){
sudo apt-get update
sudo apt-get upgrade
sudo apt install mosquitto
}


atualizacao

printf "Digite o tópico: "
printf ""
read topico

# for i in $(seq 1 10); do mosquitto_pub -h localhost -t test1 -m 'ola $i'; done 
#inicia o serviço
sudo service mosquitto start

function mosquitto_pub(){

#laço que vai computar 400 vezes o código
    for i in $(seq 1 400);
        do
                sudo mosquitto_pub -h test.mosquitto.org -t topico -m "mensagem-topico1-teste $i"; #a mensagem vai ser a mesma
                sleep 1; #espera 1 segundo
        done
}
#chamada da função
mosquitto_pub

