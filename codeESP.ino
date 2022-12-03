#define WET A0 // this pin will read with Moisture Meter testing sensor
#define BABYWAKE 13 // this pin read the command from arduino nano (controlling the sensors) to know if the baby wake up or not
#define EN1 14 //D5 
#define EN2 12//D6
// D5 and D6 pin used to communicate with aruino nano which controlling the servo
#include<ESP8266WiFi.h>
const char WiFiPassword[] = "";  // no password
const char AP_NameChar[] = "AKA" ; // name of ESP wifi
int b;
// Static IP.
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0); 

WiFiServer server(80);


String request = "";

bool veSinh;
bool baby_wake=0;






void setup() {
  pinMode(BABYWAKE,INPUT);
  pinMode(WET,INPUT);
  pinMode(EN1,OUTPUT);
  pinMode(EN2,OUTPUT);
  Serial.begin(115200);
  WiFi.disconnect();
  Serial.println(AP_NameChar); 
  boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
//  WiFi.softAPConfig(local_IP, gateway, subnet);
  server.begin();
}

void check_sensor(){
     baby_wake= digitalRead(BABYWAKE);
   Serial.print("baby wake: ");
   Serial.println(baby_wake);
   b= analogRead(WET);
   if (b<930){
    veSinh=1;
   }
   else {veSinh=0;}
   Serial.print("ve sinh: ");
   Serial.println(veSinh);
}


void sendMessage(char kt){
  if (kt =='A'){
    digitalWrite(EN1,0);
    digitalWrite(EN2,0);
  }
    if (kt =='B'){
    digitalWrite(EN1,0);
    digitalWrite(EN2,1);
  }
    if (kt =='C'){
    digitalWrite(EN1,1);
    digitalWrite(EN2,0);
  }
    if (kt =='d'){
    digitalWrite(EN1,1);
    digitalWrite(EN2,1);
  }
  
}

void loop() {
  // check sensor 

   // Check if a client has connected
  WiFiClient client = server.available();

  if (!client)  {

    return;
  }
  check_sensor(); // per 1 seconds
  Serial.println("");
  Serial.println("WiFi connected"); 
  // Read the first line of the request from App
  request = client.readStringUntil('\r');
  if       ( request.indexOf("MODEA") > 0 )  {
   

    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    sendMessage('A');
    Serial.println("A");
  }
  else if  ( request.indexOf("MODEB") > 0 ) {
    

    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    sendMessage('B');
    Serial.println("B");
  }
    else if  ( request.indexOf("MODEC") > 0 ) {
    

    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    sendMessage('C');
    Serial.println("C");
  }
    else if  ( request.indexOf("MODED") > 0 ) {
    

    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    sendMessage('d');
    Serial.println("D");
  }
    else if ( request.indexOf("UP") > 0 )  {
   

    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.write("W");
  }
  else if  ( request.indexOf("DOWN") > 0 ) {
    

    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.write("S");
  }
    else if  ( request.indexOf("LEFT") > 0 ) {
    

    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.write("A");;
  }
    else if  ( request.indexOf("RIGHT") > 0 ) {
    

    client.println("HTTP/1.1 200 OK\r\n");
    client.flush();
    Serial.write("D");
  }
      else if  ( request.indexOf("STOP") > 0 ) {
    
    client.println("HTTP/1.1 200 OK\r\n");
    
    client.flush();
    Serial.write("F");
  }
    else if  ( request.indexOf("AUTO") > 0 ) {
   
    client.println("HTTP/1.1 200 OK\r\n");
    
    client.flush();
    Serial.write("Q");
  }
     else if  ( request.indexOf("CONTROL") > 0 ) {
    
    client.println("HTTP/1.1 200 OK\r\n");
    
    client.flush();
   Serial.write("E");
  }
  else if  ( request.indexOf("CHECK") > 0 ) {
    if ((veSinh==1)||(baby_wake==1))
  {
    client.println("HTTP/1.1 200 OK\r\n");
    client.println( "SOUNDON");
    client.flush();
    Serial.println("send warning");
  }
  else{
    client.println("HTTP/1.1 200 OK\r\n");
    
    client.flush();
  }
  }
}
