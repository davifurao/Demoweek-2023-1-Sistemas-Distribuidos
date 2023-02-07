#include <ESP8266WiFi.h>               /* Inclusão da Biblioteca WiFi do ESP8266 */
#include "Adafruit_MQTT.h"            /* Inclusão da Biblioteca MQTT da Adafruit.IO */
#include "Adafruit_MQTT_Client.h"     /* Inclusão da Biblioteca do cliente MQTT da Adafruit.IO */
#include "DHT.h"                      /* Inclusão da Biblioteca do sensor de umidade */


#define WLAN_SSID       "OriginaL DevelopmenT"           /* Nome da rede WiFi */
#define WLAN_PASS       "kwy7514c"          /* Senha da rede Wifi */


#define DHTPIN 4 //Pino digital D2 (GPIO5) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11

#define AIO_USERNAME  "Davifurao"
#define AIO_KEY       "aio_ptjk04eUul7wMmdT5Wj0egP0PXB8"

#define AIO_SERVER      "io.adafruit.com"   /* Servidor MQTT */
#define AIO_SERVERPORT  1883                /* Porta do Servidor */

DHT dht(DHTPIN, DHTTYPE, 15);

WiFiClient client;  
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);  
/****************************************Feeds**********************************************************************/
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperatura"); /*Caso Queira alterar o feed é só mexer*/
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/umidade"); /*Caso queira alterar o feed é só mexer*/


/**************************************Conexão MQTT**********************************************************/

void MQTT_connect();
/******************************************Configuração******************************************************/
void setup() 
{ dht.begin();

Serial.begin(115200);  
  delay(10);            

  WiFi.begin(WLAN_SSID, WLAN_PASS);  
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);                    
                                        }
}

uint32_t x=0;

/***************************************Repetição*********************************************************/

void loop() {
 MQTT_connect(); 
 int tempe = (int)dht.readTemperature();
 int umid = (int)dht.readHumidity(); 


 if (! temperature.publish(tempe))        
    Serial.println(F("Falha na publicação da temperatura")); 
  else                                        
   Serial.println(F("Temperatura publicada!")); 
  if (! humidity.publish(umid))  
    Serial.println(F("Falha na publicação da umidade")); 
  else                                                   
    Serial.println(F("Umidade publicada!"));

    if(! mqtt.ping()) {      
    mqtt.disconnect();    
                    }

}

/****************************************Conexão com o broker********************************************************/

void MQTT_connect() {        
  
  int8_t ret;             


  if (mqtt.connected()) {   
    return;                 
  }

  Serial.print("Conectando... ");   

  uint8_t retries = 3;      
  while ((ret = mqtt.connect()) != 0) { 
       Serial.println(mqtt.connectErrorString(ret)); 
       Serial.println("Reconectando em 5s..."); 
       mqtt.disconnect();   
       delay(5000);  
       retries--;     
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println("Conectado!");   
}

                                    