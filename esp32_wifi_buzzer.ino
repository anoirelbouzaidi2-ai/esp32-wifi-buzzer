
#include <WiFi.h>

const char* ssid = "NOM_DU_RESEAU_WIFI";
const char* password = "MOT_DE_PASSE_WIFI";

WiFiServer server(80);

String header;

String buzzzer1State = "off";
String buzzzer2State = "off";

const int buzzzer1 = 2;
const int buzzzer2 = 21;

unsigned long currentTime = millis();

unsigned long previousTime = 0;

const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  
  pinMode(buzzzer1, OUTPUT);
  pinMode(buzzzer2, OUTPUT);
  
  digitalWrite(buzzzer1, LOW);
  digitalWrite(buzzzer2, LOW);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop(){
  WiFiClient client = server.available();   
  if (client) {                             
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  
      currentTime = millis();
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            //activation / desactivation

            //buzzer 1
            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("buzzer 1 on");
              Serial.println("BEEP");
              buzzzer1State = "on";
              digitalWrite(buzzzer1, HIGH);
              
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("buzzer 1 off");
              buzzzer1State = "off";
              digitalWrite(buzzzer1, LOW);
            }
            //buzzer 2
             else if (header.indexOf("GET /21/on") >= 0) {
              Serial.println("buzzzer 2 on");
              buzzzer2State = "on";
                for(int i=0; i<=50;i++){
                  digitalWrite(buzzzer2, HIGH);
              delay(100);
              digitalWrite(buzzzer2, LOW);
              delay(100);
              Serial.println("beep");}
              buzzzer2State = "off";
            } else if (header.indexOf("GET /21/off") >= 0) {
              Serial.println("buzzzer 2 off");
              buzzzer2State = "off";
              digitalWrite(buzzzer2, LOW);
            }
           //html page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
          
           
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            client.println("<body><h1>Buzzer</h1>");
            
            client.println("<p>buzzzer1 - State " + buzzzer1State + "</p>");
            
            if (buzzzer1State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
             
            client.println("<p>buzzzer2 - State " + buzzzer2State + "</p>");
                 
            if (buzzzer2State=="off") {
              client.println("<p><a href=\"/21/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/21/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
           
            client.println();
            
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
   
    header = "";
    
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}