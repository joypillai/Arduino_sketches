const byte numChars = 32;
const byte numCh = 32;
const byte numCheck = 32;
static char receivedChars[numChars]; // an array to store the received data
static char storedCh[numCh];
char check[numCheck];
boolean newData = false;
boolean allowConv = false;
int i;
int len=0;
int temp = 0;
int tempo=0;
int val1 =0;
String nav;
void setup() {
 Serial.begin(9600);
 Serial.println("<Arduino is ready>");
}

void loop() {
 recvWithEndMarker();
 showNewData();
 action();
}

void recvWithEndMarker() {
 val1=0;
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 temp=0;
  if (Serial.available() > 0) {
           while (Serial.available() > 0 && newData == false && allowConv == false) {
 rc = Serial.read();

 if (rc != endMarker) 
 {
 receivedChars[ndx] = rc;
 //storedCh[ndx] = rc;
 if (ndx<5)
 {
 check[ndx] = rc;
 }
 len++;
 ndx++;
 if (ndx >= numChars) {
  ndx = numChars - 1;
 }
 }
 else 
 {
 receivedChars[ndx] = '\0'; // terminate the string
 //storedCh[ndx] = '\0';
 check[5]='\0';
 ndx = 0;
 nav=receivedChars;
 
 newData = true;
 if (nav[0]=='r' && nav[1]=='e' && nav[2]=='a' && nav[3]=='d')
  temp=1;
 else if (nav[0]=='w' && nav[1]=='r' && nav[2]=='i' && nav[3]=='t' && nav[4]=='e')
  temp=2;
 else 
  temp =0;
 }
 }
}
}
void showNewData() {
 if (newData == true) {
 Serial.print("The Input received is \"");
 Serial.print(receivedChars);
 Serial.println("\"");
 if(nav[0]=='r')
 {
  for(i=5;i<nav.length();i++)
  {
    val1=val1*10;
    tempo=nav[i]-'0';
    val1=val1+tempo;
    
  }
 }
 newData = false;
 allowConv = true;
 len=0;
 }
}

void action()
{
  if (allowConv = true )
  {
    if (temp==1)
    {
      Serial.println("Reading...");
      Serial.println(val1); 
      allowConv = false;
      
    }
    else if (temp==2)
    {
      Serial.println("Writing...");
      allowConv = false;
    }
    else
    {
      allowConv = false;
    }
 
  }
}
