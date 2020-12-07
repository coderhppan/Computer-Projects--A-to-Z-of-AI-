#include "ESP32_MailClient.h"

const int pir = 26;
const int led = 2;
const char* ssid = "JioFiber @ Tribhuwan";
const char* password = "spartan7";
const int ldr = 34;
int x = 0;

#define emailsender "developercoder01@gmail.com"
#define emailreciver "harshpan21052007@gmail.com"
#define emailsubject "Security Alert"
#define emailsenderpassword "#definevar"
#define smtpserver "smtp.gmail.com"
#define smtpserverport 465

SMTPData smtpData;

void sendCallback(SendStatus info);
void setup() {
  Serial.begin(9600);
  Serial.println();
  pinMode(ldr,INPUT);
   pinMode(pir,INPUT);
  pinMode(led,OUTPUT);
  Serial.println("Warming up PIR");
  delay(50000);
  
  Serial.print("Connecting to internet");
  WiFi.begin(ssid,password);

  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
   Serial.println("Connected");
  Serial.println("Preparing to send Email");
}

stmpData.setLogin(stmpserver,smtpserverport,emailsender,emailsenderpassword);
stmpData.setSender("Security System Alert",emailsender);
stmpData.addRecipient(emailreciver);
stmpData.setSubject(emailsubject);
stmpData.setMessage("Some movement is detected in the house....");
stmpData.setPriority("High");

void loop() {
  bool pir_state = digitalRead(pir);
  int ldr_state = analogRead(ldr);
  if(ldr_state < 300)
  {
   digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
  }
  if(pir_state == true && x == 0)
  {
    x = x+1;
    Serial.println("Motion Detected!!");
    stmpData.setSendCallback(sendCallback);
    digitalWrite(led,HIGH);
    delay(10000);
    
    smtpdata.setSendCallback(sendCallback);
    if (!MailClient.sendMail(smtpdata))
    {
      Serial.println("Error send Email ERROR = "+MailClient.smtpErrorReason());
      smtpdata.empty();
    }
    sendCallBack();
  }
  else{
    digitalWrite(led,LOW);
  }
}
  

  void sendCallback(SendStatus msg)
  {
    Serial.println(msg.info());

    if(msg.success())
    {
      Serial.print("THE SENDING WAS SUCCESSFUL");
      x = 0;
    }
  
  }
