/**
 * HTTP Webserver for ESP8266 
 * ESP8266 WiFi adapted Arduino
 *
 * This code is only for ESP controller!
 * See documentation for more information
 * and examples.
 *
 * Used Stefan Thesen's example (04/2015)
 * Tested with v2.1.0 of ESP library.
 */

#include <ESP8266WiFi.h>

const char* ssid = "HUAWEI_P20";
const char* password = "BULGARIA";

unsigned long ulReqcount;
unsigned long ulReconncount;


// Create an instance of the server on Port 80
WiFiServer server(80);

void setup() 
{
  // setup globals
  ulReqcount=0; 
  ulReconncount=0;
  
  // start serial
  Serial.begin(9600);
  delay(1);
  
  // inital connect
  WiFi.mode(WIFI_STA);
  WiFiStart();
}

void WiFiStart()
{
  ulReconncount++;
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() 
{
  // check if WLAN is connected
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFiStart();
  }
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  unsigned long ultimeout = millis()+250;
  while(!client.available() && (millis()<ultimeout) )
  {
    delay(1);
  }
  if(millis()>ultimeout) 
  { 
    Serial.println("client connection time-out!");
    return; 
  }
  
  // Read the first line of the request
  String sRequest = client.readStringUntil('\r');
  //Serial.println(sRequest);
  client.flush();
  
  // stop client, if request is empty
  if(sRequest=="")
  {
    Serial.println("empty request! - stopping client");
    client.stop();
    return;
  }
  
  String sPath="",sParam="", sCmd="";
  String sGetstart="GET ";
  int iStart,iEndSpace,iEndQuest;
  iStart = sRequest.indexOf(sGetstart);
  if (iStart>=0)
  {
    iStart+=+sGetstart.length();
    iEndSpace = sRequest.indexOf(" ",iStart);
    iEndQuest = sRequest.indexOf("?",iStart);
    
    // are there parameters?
    if(iEndSpace>0)
    {
      if(iEndQuest>0)
      {
        // there are parameters
        sPath  = sRequest.substring(iStart,iEndQuest);
        sParam = sRequest.substring(iEndQuest,iEndSpace);
      }
      else
      {
        // NO parameters
        sPath  = sRequest.substring(iStart,iEndSpace);
      }
    }
  }
  
  // output parameters to serial, you may connect e.g. an Arduino and react on it
  if(sParam.length()>0)
  {
    int iEqu=sParam.indexOf("=");
    if(iEqu>=0)
    {
      sCmd = sParam.substring(iEqu+1,sParam.length());
      Serial.println(sCmd);
    }
  }
  
  // format the html response
  String sResponse,sHeader;
  
  // 404 for non-matching path
  if(sPath!="/")
  {
    sResponse="<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";
    
    sHeader  = "HTTP/1.1 404 Not found\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }
  // format the html page
  else
  {
    ulReqcount++;
 sResponse  = "<html><head><title>RSAI-Project</title><meta charset=\"utf-8\"></head><body>";
    sResponse += "<font color=\"#ffffff\"><body>";
    sResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">";
    sResponse += "<center><a href=\"#\"><img src=\"http://www.clker.com/cliparts/F/F/3/p/w/R/small-car-park-md.png\" alt=\"TU-Sofia\"></a><h1>WiFi control:</h1>";
    sResponse += "FUNCTION1- <BR>";
    sResponse += "FUNCTION2- <BR>";
    sResponse += "<FONT SIZE=+1>";
    sResponse += "<p>FUNCTION 1 <a href=\"?pin=FUNCTION1ON\"><button>on</button></a>&nbsp;<a href=\"?pin=FUNCTION1OFF\"><button>off</button></a></p>";
    sResponse += "<p>FUNCTION 2 <a href=\"?pin=FUNCTION2ON\"><button>on</button></a>&nbsp;<a href=\"?pin=FUNCTION2OFF\"><button>off</button></a></p>";
    
    // react on parameters
    if (sCmd.length()>0)
    {
      // write received command to html page
      sResponse += "Cmd:" + sCmd + "<BR>";
      
      // switch GPIO
      if(sCmd.indexOf("FUNCTION1ON")>=0)
      {
        Serial.write("lights_on");
      }
      else if(sCmd.indexOf("FUNCTION1OFF")>=0)
      {
        Serial.write("lights_off");
      }
    }
    
    sResponse += "<FONT SIZE=-2>";
    sResponse += "<BR>Count="; 
    sResponse += ulReqcount;
    sResponse += "</body></html>";
    
    sHeader  = "HTTP/1.1 200 OK\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }
  
  // Send the response to the client
  client.print(sHeader);
  client.print(sResponse);
  
  // and stop the client
  client.stop();
  Serial.println("Client disonnected");
}