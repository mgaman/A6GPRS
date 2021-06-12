/*
*   Provides functions signified as 'weak' in the A6* header files.
*   A function defined as weak will not cause a linkage error is not provided but will cause
*   an execution exception if called and found to be lacking at run time
*/
#include <Arduino.h>
#include <A6Services.h>

#define TRANSISTOR_CONTROL 7 // connect to base of transistor
#define A6_RESET_TIME 50     // ms

extern A6GPRS gsm;
extern bool smsArrived;

void A6DEVICE::HWReset()
{
    /*
   * The A6 modem takes about 70mA throuh the reset pin which is too much for an Arduino GPIO pin
   * Instead connect an Arduino GPIO pin to the base of a transistor and toggle that.
   * Connect the emitter of the transistor to ground and the collector to the A6 reset pin
   * http://electronics.stackexchange.com/questions/82222/how-to-use-a-transistor-to-pull-a-pin-low
   */
    pinMode(TRANSISTOR_CONTROL, OUTPUT);
    digitalWrite(TRANSISTOR_CONTROL, LOW);
    digitalWrite(TRANSISTOR_CONTROL, HIGH);
    delay(A6_RESET_TIME);
    digitalWrite(TRANSISTOR_CONTROL, LOW);
}
void A6DEVICE::debugWrite(unsigned c)
{
    if (enableDebug)
        Serial.print(c);
}
void A6DEVICE::debugWrite(int c)
{
    if (enableDebug)
        Serial.print(c);
}
void A6DEVICE::debugWrite(char c)
{
    if (enableDebug)
        Serial.write(c);
}
void A6DEVICE::debugWrite(char const *s)
{
    if (enableDebug)
        Serial.print(s);
}
void A6DEVICE::debugWrite(const __FlashStringHelper *s)
{
    if (enableDebug)
        Serial.print(s);
}

void A6DEVICE::onException(eExceptions e, int i)
{
    Serial.print("Exception: ");
    Serial.print(e);
    Serial.print(", Value: ");
    Serial.println(i);
}

