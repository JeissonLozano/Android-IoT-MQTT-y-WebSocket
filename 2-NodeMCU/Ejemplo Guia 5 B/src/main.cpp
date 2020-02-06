//Ejemplo MQTT-WebSocket & ESP8266 y la tarjeta de entrenamiento 

//--------------Librerias---------------------------------------- 

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
//-------------------VARIABLES GLOBALES--------------------------
int contconexion = 0;

const char* ssid = "Vecinos2019";
const char* password = "Vecinos20191";
const char* mqtt_server = "100.25.254.82";
const int mqttPort = 1883;
 
WiFiClient espClient;
PubSubClient client(espClient);

//Para el sensor de temperatura
unsigned long previousMillis = 0;
String strtemp = "";

char Datos;
String Cadena="";


char POT1[50];
char POT2[50];
char valueStr[15];

//---------------------------  CALLBACK ------------------------------------------------

void callback(char* topic, byte* payload, unsigned int length) {
 char PAYLOAD[5] = "    ";
  
 if(String(topic) == "IoT/Led1"){
   if(payload[1] == 'N'){ // Cuando llega un ON
     digitalWrite(5,HIGH);
   }
   if(payload[1] == 'F'){ // Cuando llega un OFF
     digitalWrite(5,LOW);
   }
 }

 if(String(topic) == "IoT/Led2"){
   if(payload[1] == 'N'){ // Cuando llega un ON
     digitalWrite(4,HIGH);
   }
   if(payload[1] == 'F'){ // Cuando llega un OFF
     digitalWrite(4,LOW);
   }
 }

 if( String(topic) == "IoT/Text"){ 
  Serial.print("{}"); //Para limpiar pantalla
  Serial.print("{");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.print("}");
  Serial.println();
}

}

//------------------------------------------------------------------------------

void reconnect() {
  // Loop hasta que nos reconectemos
    while (!client.connected()) 
    {              
        if (client.connect("IoT-ESP8266-A")) 
        {
          Serial.println("Conectado");
          client.subscribe("inTopic");
          client.subscribe("IoT/Led1");
          client.subscribe("IoT/Led2");
          client.subscribe("IoT/Text");
        }        
   
    }
}

//--------------------------------------------------------------------------------------

void setup() {

  pinMode(5,OUTPUT); //Pin D1 Como salida.
  digitalWrite(5,LOW);
  pinMode(4,OUTPUT); //Pin D2 Como salida.
  digitalWrite(4,LOW);

  Serial.begin(115200); //Start Serial
  
  // Conexión WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) 
  { //Cuenta hasta 50 si no se puede conectar lo cancela
    ++contconexion;
    delay(500);
  }
  
  
    
  client.setServer(mqtt_server, mqttPort);
  client.setCallback(callback);
  
  String Pot1 = "IoT/Pot1"; 
  Pot1.toCharArray(POT1, 50);

  String Pot2 = "IoT/Pot2"; 
  Pot2.toCharArray(POT2, 50);


}
 
void loop() {

  if (!client.connected()) 
    {
      reconnect();
    }
  
  client.loop();

  // ----------------------------------------
     if (Serial.available() > 0) 
     {
        Datos = Serial.read();
        Cadena += Datos;
            
        if (Datos == '}')
        {
            byte desde = Cadena.indexOf('A') + 2;
            byte hasta = Cadena.indexOf(';');
            String Poten1 = Cadena.substring(desde, hasta);
            desde = hasta;
            desde = Cadena.indexOf('B') + 2;
            hasta = Cadena.indexOf(';', desde);
            String Poten2 = Cadena.substring(desde, hasta); 
            Poten1.toCharArray(valueStr, 15);
            client.publish(POT1, valueStr);        
            Poten2.toCharArray(valueStr, 15);
            client.publish(POT2, valueStr);
            Cadena = "";
        }
    
    }


  // ----------------------------------------
  // Aqui la parte de la temperatura
  
   unsigned long currentMillis = millis();
    
  if (currentMillis - previousMillis >= 4000) { //envia la temperatura cada 4 segundos
    previousMillis = currentMillis;
    int analog = analogRead(17);
    float temp = analog*0.322265625;
    strtemp = String(temp, 1); //1 decimal
    char tempstring[3];
    dtostrf(temp,3,1,tempstring);
    char buffer[80]=" "; 
    char* formato="%s°C";
    sprintf(buffer, formato, tempstring);    
    client.publish("IoT/Temp", buffer);
  }
   // ----------------------------------------

}