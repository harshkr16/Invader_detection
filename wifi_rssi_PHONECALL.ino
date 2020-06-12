  #include <WiFi.h> 

 
WiFiClient client;
WiFiServer server(80);
const char* myKey = "cyg_84yTHZnW7d34s6LAcW";//get key from IFTTT

char ssid[] = "Harshseth";       // your network SSID (name)
char password[] = "12344464";
int count=0;
void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  server.begin();
  
}
// Set web server port number to 80


void loop() {
  
  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println("harshseth");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
     Serial.println("\nConnected.");
  } 
     if (WiFi.status() == WL_CONNECTED) // Make sure we're still connected to our router
      {
        Serial.println("connecting...");
        if (client.connect("maker.ifttt.com", 80)) // Test the connection to the server
        {
          Serial.println("Connected to Maker");
           // Request SMS text to the number provided in IFTTT
  
        } 
    
    }
  long rssi[50];
  // Measure Signal Strength (RSSI) of Wi-Fi connection
  
  for(int i=0;i<6;i++)
  { 
    rssi[i] = WiFi.RSSI();
  }
  long mean=0,sum=0;
  for(int i=0;i<6;i++)
  {
    sum+=rssi[i];
  }
  mean=sum/5;
  
 Serial.println(mean);

  if(mean<-77)
  {
    
     Serial.println("!!!!SOMEONE IS PRESENT!!!!");
    sendSMS(1); 
    }
    
  
  else
  {
    Serial.println("!!!NO ONE IS PRESENT!!!");
  }
  // Write value to Field 1 of a ThingSpeak Channel
 // int httpCode = ThingSpeak.writeField(myChannelNumber, 1, rssi, myWriteAPIKey);


  //if (httpCode == 200) {
    //Serial.println("Channel write successful.");
 // }
  //else {
    //Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  //}

  // Wait 2 seconds to update the channel again
 delay(1000);
 } 

 void sendSMS(boolean a)  // Built HTTP packet to send to Maker
{

  client.print("POST /trigger/");
  client.print("Occupancy_detection"); //this will send notification to smart device
  // client.print("ESP");//this will send sms (if You have made IFTTT applet for that)
  client.print("/with/key/");
  client.print(myKey);
  client.println(" HTTP/1.1");

  client.println("Host: maker.ifttt.com");
  client.println("User-Agent: ESP");
  client.println("Connection: close");

  client.println();

}
