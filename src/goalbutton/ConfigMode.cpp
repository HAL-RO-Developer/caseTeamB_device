#include "System.h"
#include "ArduinoLibrary.h"
#include "prototype.h"
#include "config.h"

ESP8266WebServer server( 80 );
IPAddress ip( 192, 168, 4, 1 );
IPAddress subnet( 255, 255, 255, 0 );

/* prototype宣言(private) */
void handleRootGet( void );
void handleWiFiGet( void );
void handleWiFiPost( void );
void handleRegistGet( void );
void handleRegistPost( void );

void goConfigMode( void )
{
    WiFi.mode( WIFI_AP );
    WiFi.softAPConfig( ip, ip, subnet );
    WiFi.softAP( ap_ssid, ap_pass );

    server.on( "/", HTTP_GET, handleRootGet );
    server.on( "/wifi", HTTP_GET, handleWiFiGet );
    server.on( "/wifi", HTTP_POST, handleWiFiPost );
    server.on( "/regist", HTTP_GET, handleRegistGet );
    server.on( "/regist", HTTP_POST, handleRegistPost );
    
    server.begin();
    while(1){
        server.handleClient();
        delay(1);
    }
}

void handleRootGet( void )
{
    String html = "";
    html += "<h1>CONFIG MODE</h1>";
    html += "<a href=\"/wifi\">WiFi Settings</a></br>";
    html += "<a href=\"/regist\">Device Regitration</a>";
    html += "</form>";
    
    server.send( 200, "text/html", html );
}

void handleWiFiGet( void )
{
    String html = "";
    html += "<h1>WiFi Settings</h1>";
    html += "<form method='post'>";
    html += "  SSID : <input type='text' name='ssid' placeholder='SSID'><br>";
    html += "  PASS : <input type='password' name='pass' placeholder='PASS'><br>";
    html += "  <input type='submit'><br>";
    html += "</form>";
    
    server.send( 200, "text/html", html );
}

void handleWiFiPost()
{
    String  ssid = server.arg("ssid");
    String  pass = server.arg("pass");

    /* JSON作成 */
    String json = "{";
    json += "\"ssid\":\"" + ssid + "\",";
    json += "\"pass\":\"" + pass + "\"";
    json += "}";

    File    fd = SPIFFS.open( config_json, "w" );
    fd.println( json );
    fd.close();
    
    String html = "";
    html += "<h1>WiFi Settings</h1>";
    html += "<p>Settings changed</p>";
    html += "<table>";
    html += "  <tr><td>SSID</td><td>" + ssid + "</td></tr>";
    html += "  <tr><td>PASS</td><td>[Not display]</td></tr>";
    html += "</table>";
	
    server.send( 200, "text/html", html );
}

void handleRegistGet( void )
{
    String html = "";
    html += "<h1>Device Registration</h1>";
    html += "<form method='post'>";
    html += "  PIN : <input type='text' name='pin' placeholder='PIN'><br>";
    html += "  <input type='submit'><br>";
    html += "</form>";
    
    server.send( 200, "text/html", html );
}

void handleRegistPost()
{
    String  pin = server.arg("pin");

    /* JSON作成 */
    String json = "{";
    json += "\"pin\":\"" + pin + "\"";
    json += "}";

    File    fd = SPIFFS.open( device_json, "w" );
    fd.println( json );
    fd.close();
    
    String html = "";
    html += "<h1>Device Registration</h1>";
    html += "<p>Regist Complete</p>";
    html += "<table>";
    html += "  <tr><td>PIN</td><td>" + pin + "</td></tr>";
    html += "</table>";
    
    server.send( 200, "text/html", html );
}
