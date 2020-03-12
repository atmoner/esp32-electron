#include <WiFi.h>
#include <WebSocketClient.h>
 

const char* ssid     = "";
const char* password = "";
char path[] = "/";
char host[] = "localhost";

WebSocketClient webSocketClient;

// Use WiFiClient class to create TCP connections
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println("Wifi-local");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(5000);
  

  // Connect to the websocket server
  if (client.connect("192.168.1.15", 8050)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
    while(1) {
      // Hang on failure
    }
  }

  // Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
    }  
  }

}


void loop() {
  String data;
      	
  if (client.connected()) {
    
		webSocketClient.sendData( String(  ESP.getFreeHeap()  ).c_str() ); 		
 	  Serial.println(ESP.getFreeHeap());

 
  } else {
  	Serial.println("Client disconnected.");
    while (1) {
      // Hang on disconnect.
 
    }
  }
 
  delay(500);
  
}
