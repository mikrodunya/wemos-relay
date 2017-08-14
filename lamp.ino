
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>



const char* ssid     = "wifissid";// modeminizin wifi ismi
const char* password = "password";// modeminizin şifresi

ESP8266WebServer server(80);

IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

const int relayPin = 5;
void On() {
  String message = "<html>\n";
   message += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  message += "<head>\n";
  message += "<style>\n";
  message += ".onoffswitch {position: relative; width: 95px;-webkit-user-select:none; -moz-user-select:none; -ms-user-select: none;}\n ";
  message += ".onoffswitch-checkbox {display: none;}\n ";
  message += ".onoffswitch-label {display: block; overflow: hidden; cursor: pointer;border: 2px solid #999999; border-radius: 26px;}\n ";
  message += ".onoffswitch-inner {display: block; width: 200%; margin-left: -100%;transition: margin 0.3s ease-in 0s;}\n ";
  message += ".onoffswitch-inner:before, .onoffswitch-inner:after {display: block; float: left; width: 50%; height: 39px; padding: 0; line-height: 39px;font-size: 16px; color: white; font-family: Trebuchet, Arial, sans-serif; font-weight: bold;box-sizing: border-box;}\n ";
  message += ".onoffswitch-inner:before {content: \"ON\";padding-left: 18px;background-color: #34A7C1; color: #FFFFFF;}\n ";
  message += ".onoffswitch-inner:after {content: \"OFF\";padding-right: 18px;background-color: #EEEEEE; color: #999999;text-align: right;}\n ";
  message += ".onoffswitch-switch {display: block; width: 18px; margin: 10.5px;background: #FFFFFF;position: absolute; top: 0; bottom: 0;right: 52px;border: 2px solid #999999; border-radius: 26px;transition: all 0.3s ease-in 0s; }\n ";
  message += ".onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-inner {margin-left: 0;}\n ";
  message += ".onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-switch {right: 0px; }\n ";
  message += "</style>\n ";
  message += "</head>\n ";
  message += "<body>\n ";
 // message += "<h2>Lamp</h2>\n ";
  message += "<div class=\"onoffswitch\">\n ";
  message += "<input type=\"checkbox\" name=\"onoffswitch\" onclick=\"location.href='\\off'\" class=\"onoffswitch-checkbox\" id=\"myonoffswitch\" checked >\n";
  message += "<label class=\"onoffswitch-label\" for=\"myonoffswitch\">\n";
  message += "<span class=\"onoffswitch-inner\"></span>\n";
  message += "<span class=\"onoffswitch-switch\"></span>\n";
  message += "</label>\n";
  message += "</div>\n";
  message += "</body>\n";
  message += "</html>\n";
  digitalWrite(relayPin, HIGH);
  server.send(200, "text/html", message);
}

void off() {
  String message = "<html>\n";
   message += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  message += "<head>\n";
  message += "<style>\n";
  message += ".onoffswitch {position: relative; width: 95px;-webkit-user-select:none; -moz-user-select:none; -ms-user-select: none;}\n ";
  message += ".onoffswitch-checkbox {display: none;}\n ";
  message += ".onoffswitch-label {display: block; overflow: hidden; cursor: pointer;border: 2px solid #999999; border-radius: 26px;}\n ";
  message += ".onoffswitch-inner {display: block; width: 200%; margin-left: -100%;transition: margin 0.3s ease-in 0s;}\n ";
  message += ".onoffswitch-inner:before, .onoffswitch-inner:after {display: block; float: left; width: 50%; height: 39px; padding: 0; line-height: 39px;font-size: 16px; color: white; font-family: Trebuchet, Arial, sans-serif; font-weight: bold;box-sizing: border-box;}\n ";
  message += ".onoffswitch-inner:before {content: \"ON\";padding-left: 18px;background-color: #34A7C1; color: #FFFFFF;}\n ";
  message += ".onoffswitch-inner:after {content: \"OFF\";padding-right: 18px;background-color: #EEEEEE; color: #999999;text-align: right;}\n ";
  message += ".onoffswitch-switch {display: block; width: 18px; margin: 10.5px;background: #FFFFFF;position: absolute; top: 0; bottom: 0;right: 52px;border: 2px solid #999999; border-radius: 26px;transition: all 0.3s ease-in 0s; }\n ";
  message += ".onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-inner {margin-left: 0;}\n ";
  message += ".onoffswitch-checkbox:checked + .onoffswitch-label .onoffswitch-switch {right: 0px; }\n ";
  message += "</style>\n ";
  message += "</head>\n ";
  message += "<body>\n ";
 // message += "<h2>Lamp</h2>\n ";
  message += "<div class=\"onoffswitch\">\n ";
  message += "<input type=\"checkbox\" name=\"onoffswitch\" onclick=\"location.href='\\on'\" class=\"onoffswitch-checkbox\" id=\"myonoffswitch\" >\n";
  message += "<label class=\"onoffswitch-label\" for=\"myonoffswitch\">\n";
  message += "<span class=\"onoffswitch-inner\"></span>\n";
  message += "<span class=\"onoffswitch-switch\"></span>\n";
  message += "</label>\n";
  message += "</div>\n";
  message += "</body>\n";
  message += "</html>\n";
  digitalWrite(relayPin, LOW); 
  server.send(200, "text/html", message);
}

void setup() {
 pinMode(relayPin, OUTPUT);
  delay(1000);
  Serial.begin(115200);
  Serial.println();
   /*
  Serial.print("Configuring access point...");
 
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  */
 //WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

server.on("/", On);

  server.on("/on", On);
  server.on("/off", off);
  server.begin();
  Serial.println("HTTP server started");




}

void loop() {
  server.handleClient();
}
