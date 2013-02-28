// http://alanesq.com/arduino/ethernet_test.txt


#include <EtherCard.h>

#define STATIC 1 // set to 1 to disable DHCP (adjust myip/gwip values below)

#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,0,2 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };
#endif

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

char page[] PROGMEM =
"HTTP/1.0 200 OK\r\n"
"Content-Type: text/html\r\n"
"\r\n"
"<html>"
"<head>"
"<title>Hypn's Arduino HTTP Server</title>"
"<body>"
"	<center>"
"		<img src=\"http://myriadrf.org/wp-content/uploads/2013/01/LogoArduino.png\">"
"		<br />"
"		<br />"
"		<div>"
"			<button>Lights On</button>"
"			<button>Lights Off</button>"
"		</div>"
"		<br />"
"		<div>Made by Hypn :D</div>"
"	</center>"
"</body>"
"</html>"
;

void setup(){
  Serial.begin(57600);
  
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println( "Failed to access Ethernet controller");
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip); 
}

void loop(){
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  
  // check if valid tcp data is received
  if (pos) {
    char* data = (char *) Ethernet::buffer + pos;
    
    if (strncmp( "GET /?led1=on" , data , 12 ) == 0) {
      Serial.println("LED1 = ON");
    }  
    if (strncmp( "GET /?led1=off" , data , 13 ) == 0) {
      Serial.println("LED1 = OFF");
    }
    
    if (strncmp( "GET /?led2=on" , data , 12 ) == 0) {
      Serial.println("LED2 = ON");
    }  
    if (strncmp( "GET /?led2=off" , data , 13 ) == 0) {
      Serial.println("LED2 = OFF");
    }
    
    if (strncmp( "GET /?led3=on" , data , 12 ) == 0) {
      Serial.println("LED3 = ON");
    }  
    if (strncmp( "GET /?led3=off" , data , 13 ) == 0) {
      Serial.println("LED3 = OFF");
    }
    
    if (strncmp( "GET /?led4=on" , data , 12 ) == 0) {
      Serial.println("LED4 = ON");
    }  
    if (strncmp( "GET /?led4=off" , data , 13 ) == 0) {
      Serial.println("LED4 = OFF");
    }
    
    if (strncmp( "GET /?led5=on" , data , 12 ) == 0) {
      Serial.println("LED5 = ON");
    }  
    if (strncmp( "GET /?led5=off" , data , 13 ) == 0) {
      Serial.println("LED1 = OFF");
    }
    
    if (strncmp( "GET /?led6=on" , data , 12 ) == 0) {
      Serial.println("LED6 = ON");
    }  
    if (strncmp( "GET /?led6=off" , data , 13 ) == 0) {
      Serial.println("LED6 = OFF");
    }
    
    if (strncmp( "GET /?led7=on" , data , 12 ) == 0) {
      Serial.println("LED7 = ON");
    }  
    if (strncmp( "GET /?led7=off" , data , 13 ) == 0) {
      Serial.println("LED7 = OFF");
    }
    
    if (strncmp( "GET /?led8=on" , data , 12 ) == 0) {
      Serial.println("LED8 = ON");
    }  
    if (strncmp( "GET /?led8=off" , data , 13 ) == 0) {
      Serial.println("LED8 = OFF");
    }

    memcpy_P(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
  }
  
//  // wait for an incoming TCP packet, but ignore its contents
//  if (ether.packetLoop(ether.packetReceive())) {
//    memcpy_P(ether.tcpOffset(), page, sizeof page);
//    ether.httpServerReply(sizeof page - 1);
//  }
}
