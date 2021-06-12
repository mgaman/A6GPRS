/*
*  An example for how to setup the A6GPRS environment.
*  The attached source file, A6helpers.cpp provides functions that may optionally be called from
*  the A6* classes.
*  A6DEVICE class provides the functionality to send serial data to and from the A6 modem. It is used directly
*  from  A6GPRS class and you should ignore its existence.
*  A6GPRS is the main class employing the services of the A6Device. It sends messages to the device and buffers and analyzes
*  data from the device. A6GPRS is used to perform configuration of the device e.g. setting the mode of text messages
*  
*/
#include <Arduino.h>
#include <HardwareSerial.h>  // needed for Serial1
#include <A6Services.h>

A6GPRS gsm(Serial1,1000,900);  // CIRCULAR BUFFER 1000 bytes, largest anticipated message 900 bytes
char const *apn = "######";    // PUT YOUR apn HERE
char tempbuf[50];

void setup() {
  bool rc = false;
  Serial.begin(115200);
  Serial1.begin(115200);
  gsm.enableDebug = true;
  if (gsm.reset())
  {
    Serial.println("Reset success");
    if (gsm.getIMEI(tempbuf)) {
      Serial.print("IMEI "); Serial.println(tempbuf);
      if (gsm.setSmsMode(SMS_TEXT)) {
        Serial.println("SMS mode set success");
        if (gsm.begin(apn)) {
          Serial.println("begin success");
          if (gsm.getLocalIP(tempbuf)) {
            Serial.print("IP "); Serial.println(tempbuf);
            rc = true;
          }
            else
              Serial.println("get IP failed");
        }
        else
          Serial.println("begin failed");
      }
      else
        Serial.println("Set SMS mode failed");
    }
    else
      Serial.println("get IMEI failed");
  }
  else
    Serial.println("Reset failed");
  if (rc)
    Serial.println("Setup success");
  else
    Serial.println("Setup failed");
}

void loop() {
  // put your main code here, to run repeatedly:
}