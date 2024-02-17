#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#include <server_page.h>

Preferences preferences;
const char *preferencesNamespace = "ip_storage";
const char *preferencesKey = "saved_ip";

bool networkMode = false;

AsyncWebServer server(80);

bool isValidIPAddress(const String &ipAddress);
bool saveIPAddress(const String &ipAddress);
String scanner_name;

#include <slidepage2.h>

void serverpage(){

  // Serve the HTML page at the root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //request->send(200, "text/html", "<html><body><form method='post' action='/submit'>Enter Server IP Address: <input type='text' name='textbox'><br><input type='submit' value='Submit'></form></body></html>");
    request->send(200, "text/html", index_html);
  });

  // Handle form submission
  server.on("/submit", HTTP_POST, [](AsyncWebServerRequest *request){
    String textboxValue = request->arg("textbox");
    PRINTLINE("Received data: " + textboxValue);
    if (isValidIPAddress(textboxValue)) {
      // Save the valid IP address in preferences
      if (saveIPAddress(textboxValue)) {
        PRINTLINE("Valid IP address. Saved in preferences.");
        request->send(200, "text/html", "Valid Server IP address Saved in Scanner...");
        ESP.restart();
      } else {
        PRINTLINE("Error saving IP address.");
        request->send(500, "text/html", "Internal Server Error");
      }
    } else {
      PRINTLINE("Invalid IP address.");
      request->send(200, "text/html", "Invalid IP address.");
    }
    request->send(200, "text/html", "Received data: " + textboxValue);
  });

  // Start server
  server.begin();

}

void networksetup() {

  WiFiManager wifiManager;

  //exit after config instead of connecting
  wifiManager.setBreakAfterConfig(true);

  //reset settings - for testing
  //wifiManager.resetSettings();
  //displayLine("Network Setup attempt");
  PRINTLINE("Network setup attempt");
  //tries to connect to last known settings
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP" with password "password"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("Madueke_Sim", "password")) {
    PRINTLINE("failed to connect");
    //displayLine("Failed to connect\n to WiFi. \nPress # Key to ignore.");
    delay(250);
    ESP.restart();
    delay(250);
  }

  //if you get here you have connected to the WiFi
  PRINTLINE("connected...yeey :)");
  //displayText("Connected to Wifi!");
  //displayLine(("IP Addr: \n" + WiFi.localIP().toString()).c_str());
  delay(250);
  PRINTLINE("local ip");
  PRINTLINE(WiFi.localIP());

  uint8_t mac[6];
  WiFi.macAddress(mac);
  char * name;
  //sprintf(name, mac.c_str());
  scanner_name = "Net_Scanner-" + String(mac, HEX);
  Serial.println("Scanner Name: " + scanner_name);
  
  //serverpage();
  serverpage2();

}


bool startPreferences() {
  return preferences.begin(preferencesNamespace, false);
}
void endPreferences() {
  preferences.end();
}
bool saveIPAddress(const String &ipAddress) {
  if (startPreferences()) {
    // Save the valid IP address in preferences
    preferences.putString(preferencesKey, ipAddress);
    endPreferences();
    return true;
  }
  return false;
}
bool isValidIPAddress(const String &ipAddress) {
  IPAddress ip;
  return ip.fromString(ipAddress);
}
String getSavedIPAddress() {
  if (startPreferences()) {
    // Retrieve the saved IP address from preferences
    String savedIP = preferences.getString(preferencesKey, "No saved IP address");
    endPreferences();
    PRINTLINE("Acquired Server IP: " + savedIP);
    //displayLine("Server IP:");
    //displayLine(savedIP);
    return savedIP;
  }
  return "Error accessing preferences";
}