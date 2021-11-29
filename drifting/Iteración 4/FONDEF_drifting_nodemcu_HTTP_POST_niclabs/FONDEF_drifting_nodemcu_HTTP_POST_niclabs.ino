/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  
  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//-----------------------------------------------------------
//------------------- CONFIGURAR WIFI -----------------------
const char* ssid = "VTR-2968799 2.4G";
const char* password = "cs6bhYnspgdp";
//-----------------------------------------------------------
//-----------------------------------------------------------

const char* serverName = "http://agua.niclabs.cl/data/http";
const char* queryApiKey = "919c5e5e086a492398141c1ebd95b711";

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  //Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  Serial.print("Waiting for payload.. ");
}

void loop() {
  if (Serial.available() > 0) {
    //Check WiFi connection status
    Serial.print("Serial stream received.. ");
    if(WiFi.status()== WL_CONNECTED) {
      Serial.print("Wifi connected.. ");
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("query-api-key", queryApiKey);
      //String httpRequestData =  String("{") +
      //                            "\"app_id\": \"app123\"," +
      //                            "\"dev_id\": \"rasp01\"," +
      //                            "\"payload_raw\": \"[" +
      //                                "{'i': 201, 'v':202.0, 't': " + String(unixTime) + "000000000}," +
      //                                "{'i': 202, 'v':74.0, 't': " + String(unixTime) + "000000000}," +
      //                                "{'i': 203, 'v':-1.0,  't': " + String(unixTime) + "000000000}" +
      //                              "]\"" +
      //                          String("}");

      String httpRequestData = Serial.readStringUntil('\n');
      //http.addHeader("content-length", String(httpRequestData.length()));
      //http.addHeader("host", "agua.niclabs.cl");
      Serial.println(httpRequestData);
      Serial.println("");
      int httpResponseCode = http.POST(httpRequestData);
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    
    Serial.print("Waiting for payload.. ");
  }
}

// 19:18:27.333 -> 
// {"app_id": "app123","dev_id": "rasp01","payload_raw": "[{'i': 201, 'v':3.00, 't': 1636744629000000000},{'i': 202, 'v':2.00, 't': 1636744629000000000},{'i': 203, 'v':2.00, 't': 1636744629000000000}]"}
// {"app_id": "app123","dev_id": "rasp01","payload_raw": "[{'i': 201, 'v':3.00, 't': 1636744629000000000}]"}
