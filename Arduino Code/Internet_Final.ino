/*

Internet Shield Example

This example shows an application on 1Sheeld's internet shield.

By using this example, you can get response of certain GET request and 
print it all out on the terminal shield 64 bytes by 64 bytes.
 
OPTIONAL:
To reduce the library compiled size and limit its memory usage, you
can specify which shields you want to include in your sketch by
defining CUSTOM_SETTINGS and the shields respective INCLUDE_ define. 

*/

#define CUSTOM_SETTINGS
#define INCLUDE_INTERNET_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_PUSH_BUTTON_SHIELD
#define INCLUDE_TEXT_TO_SPEECH_SHIELD

/* Include 1Sheeld library. */
#include <OneSheeld.h>

/* Create an Http request with 1Sheeld website's url. */
/* It's important to be created here as a global object. */
HttpRequest GetControl("WebsitePath/api/GetControl");
HttpRequest SetSensors("WebsitePath/api/SetSensors/Temperature/");  
/* Set an LED on pin 13.*/
int LightsPin = 11;
int DoorLockPin = 12;
int WindowsPin = 13;
int DistanceSensorPin = A0;
int PIRSensorPin = 7;
bool Flag = true;
bool Flag2 = false;
bool Flag3=true;
struct ControlParameters
{
  char Lights;
  char DoorLock;
  char Windows;
};

ControlParameters CP;

void setup() 
{
  /* Start communication. */
  OneSheeld.begin();
  //oneSheeldRequest.addHeader("User-Agent","angular");
  /* LED pin mode is output. */
  pinMode(LightsPin,OUTPUT);
  pinMode(DoorLockPin,OUTPUT);
  pinMode(WindowsPin,OUTPUT);
  pinMode(DistanceSensorPin,INPUT);
  pinMode(PIRSensorPin,INPUT); 
  /* Subscribe to success callback for the request. */
  GetControl.setOnSuccess(&onSuccess);
  SetSensors.setOnSuccess(&onSuccess2);
  /* Subscribe to failure callback for the request. */
  GetControl.setOnFailure(&onFailure);
  /* Subscribe to start callback for the request. */
  GetControl.setOnStart(&onStart);
  /* Subscribe to finish callback for the request. */
  GetControl.setOnFinish(&onFinish);
  /* Sunbscribe to setOnNextResponseBytesUpdate to be notified once the bytes is updated in the response object. */
  GetControl.getResponse().setOnNextResponseBytesUpdate(&onBytesUpdate);
  /* Subscribe to response errors. */
  GetControl.getResponse().setOnError(&onError);
  GetControl.getResponse().setOnJsonResponse(&GetControlResponse);
  /* Perform a GET request using the Internet shield. */  
}

void loop()
{
  if(Flag==true)
  {
    Flag=false;
    Internet.performGet(GetControl);
  }
  else if(Flag2==true)
  {
    Flag2=false;
    String URL="WebsitePath/api/SetSensors/Temperature/"+ReadDistanceSensor();
    SetSensors.setUrl(URL.c_str());
    Internet.performGet(SetSensors);
  }
  else if(Flag3==true)
  {
    Flag3=false;
    String URL="WebsitePath/api/SetSensors/PIR/"+ReadPIRSensor();
    SetSensors.setUrl(URL.c_str());
    Internet.performGet(SetSensors);
  }
}

void onSuccess(HttpResponse &response)
{
  char *Temp=response.getBytes();
  Terminal.println(Temp);
  CP.Lights=Temp[0];
  CP.DoorLock=Temp[1];
  CP.Windows=Temp[2];
  Control(CP.Lights-'0',CP.DoorLock-'0',CP.Windows-'0');
  Terminal.println("-----------");
  Flag2=true;
}

void onSuccess2(HttpResponse &response)
{
  static int FlagNumber=2;
  if(FlagNumber==2)
  {
    FlagNumber=3;
    Flag3=true;
  }
  else
  {
    FlagNumber=2;
    Flag=true;
  }
}

void GetControlResponse(JsonKeyChain& chain,char value [])
{ 
}

void onFailure(HttpResponse &response)
{
  /* Print out the status code of failure.*/
  Terminal.println(response.getStatusCode());
  /* Print out the data failure.*/
  Terminal.println(response.getBytes());
}

void onStart()
{
  /* Turn on the LED when the request is started. */
  //digitalWrite(13,HIGH);
}

void onFinish()
{
  /* Turn off the LED when the request has finished. */
  //digitalWrite(13,LOW);
}

void onBytesUpdate(HttpResponse &response)
{
  
  /* Print out the data on the terminal. */
  //Terminal.println(response.getBytes());
  /* Check if the reponse is sent till the last byte. */
  //if(!response.isSentFully())
  //  {       
  //    /* Ask for the next 64 bytes. */
  //    response.getNextBytes();
  //  }
}

void onError(int errorNumber)
{
  /* Print out error Number.*/
  Terminal.print("Error:");
  switch(errorNumber)
  {
    case INDEX_OUT_OF_BOUNDS: Terminal.println("INDEX_OUT_OF_BOUNDS");break;
    case RESPONSE_CAN_NOT_BE_FOUND: Terminal.println("RESPONSE_CAN_NOT_BE_FOUND");break;
    case HEADER_CAN_NOT_BE_FOUND: Terminal.println("HEADER_CAN_NOT_BE_FOUND");break;
    case NO_ENOUGH_BYTES: Terminal.println("NO_ENOUGH_BYTES");break;
    case REQUEST_HAS_NO_RESPONSE: Terminal.println("REQUEST_HAS_NO_RESPONSE");break;
    case SIZE_OF_REQUEST_CAN_NOT_BE_ZERO: Terminal.println("SIZE_OF_REQUEST_CAN_NOT_BE_ZERO");break;
    case UNSUPPORTED_HTTP_ENTITY: Terminal.println("UNSUPPORTED_HTTP_ENTITY");break;
    case JSON_KEYCHAIN_IS_WRONG: Terminal.println("JSON_KEYCHAIN_IS_WRONG");break;
  }
}

void Control(int Lights, int DoorLock, int Windows)
{
  int Parameters[3]={Lights,DoorLock,Windows};
  for(int i=11;i<=13;i++)
  {
    if(Parameters[i-11])
    {
      digitalWrite(i,HIGH);
    }
    else
    {
      digitalWrite(i,LOW);
    }
  }
}

String ReadDistanceSensor()
{
  String StrS(6787 / (analogRead(DistanceSensorPin) - 3) - 4);  
  return StrS;
}

String ReadPIRSensor()
{
  if(digitalRead(PIRSensorPin)==HIGH)
  {
    return "1";
  }
  else
  {
    return "0";
  }
}
