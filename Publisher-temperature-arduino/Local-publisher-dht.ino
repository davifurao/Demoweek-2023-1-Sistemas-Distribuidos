#include <ESP8266WiFi.h>//biblioteca do esp
#include <PubSubClient.h>//biblioteca do mqtt
#include <DHT.h>

const char* ssid = "12345678";//nome da rede
const char* password = "12345678";//senha da rede
const char* mqttServer = "test.mosquitto.org";//broker
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
const char* topic_u = "dddfurao_u";//tópico
const char* topic_t = "dddfurao_t";//tópico

float temperatura;
float umidade;

WiFiClient espClient;
PubSubClient client(espClient);


#define DHTPIN 4 //Pino digital D2 (GPIO5) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
   dht.begin(); //Inicializa o sensor DHT11
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setServer(mqttServer, mqttPort);
  while (!client.connect("NodeMCU", mqttUser, mqttPassword)) {
    Serial.println("Connecting to MQTT...");
    delay(500);
  }
  Serial.println("Connected to MQTT");
}

void loop() {
  int value = analogRead(A0);//Lê o pino A0, caso queira fazer alguma alteração no projeto, é só mudar o pino(pino de leitura dos dados)
  char message[1000];

  char u[1000];
  char t[1000];
 int temperatura = dht.readTemperature();  //Realiza a leitura da temperatura
  //int umidade = dht.readHumidity();
  int umidade = dht.readHumidity(); //Realiza a leitura da umidade
  
  sprintf(u, "%d", temperatura);
  sprintf(t, "%d", umidade);
  
 
  client.publish(topic_u, t);//publica a mensagem
  client.publish(topic_t, u);
  
  delay(1000);//intervalo entre as mensagens
}

