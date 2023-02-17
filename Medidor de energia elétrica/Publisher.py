import paho.mqtt.client as mqtt
import time
import random

BROKER="test.mosquitto.org"
PORT=1883
KEEPALIVE=60
TOPIC="sensor_energia"
inicio_random=0
fim_random=30
time_sleep_pub=1

#Publisher
client = mqtt.Client()
client.connect(BROKER, PORT, KEEPALIVE)
client.loop_start()
#time.sleep(2)  # import time
#client.loop_forever()
try:
    while True:
        msg=random.randint(inicio_random,fim_random) #para o random entrar no loop
        client.publish(TOPIC, msg)
        time.sleep(time_sleep_pub)
except KeyboardInterrupt:
    print("\nSaindo")
    client.disconnect()
    client.loop_stop()