/*
 * Igniter Source
 *
 * @file    igniter.cpp
 * @author  Anthony Duen for UBC Rocket Avionics 2018/2019
 * @description  Initializes pins that enable control of
 *  drogue and main parachute releases.
 *
 * There is a function that implements continuity testing
 *  of the ematch - required as per IREC regulations.
 *
 * @section LICENSE
 * This program is free software; you can redistribute it and/or
 * modify it without restriction under the terms of the MIT License.
 *
 * Distributed as-is; no warranty is given.
 */

/*Includes------------------------------------------------------------*/
#include <Arduino.h>
#include "igniter.h"

/*Constants------------------------------------------------------------*/
#define SerialUSB   Serial

//Double, triple check pin assignments !
#define MAIN_IGNITER_PIN 16
#define DROGUE_IGNITER_PIN 35

#define MAIN_CONTINUITY_CHECK_PIN 4
#define MAIN_CONTINUITY_CHECK_ADC 14

#define DROGUE_CONTINUITY_CHECK_PIN 17
#define DROGUE_CONTINUITY_CHECK_ADC 34

#define IGNITER_DELAY 25    // in milliseconds
#define CONTINUITY_CHECK_DELAY 50 // in microseconds!

//tested at 11.1V with a 2.2k/470 divider (606) or 1.3k/330 (642)
//  or 1.33k/330 (629)
// threshold for a discontinuous ematch -> read voltage / 3.3 * 1023
#define DISCONTINUOUS_THRESHOLD 650

/*Variables------------------------------------------------------------*/

/*Functions------------------------------------------------------------*/
/**
  * @brief  Initializes pins for e-match firing and continuity checking.
  * @param  None
  * @return None
  */
void initIgniter(void)
{
    pinMode(MAIN_IGNITER_PIN, OUTPUT);
    digitalWrite(MAIN_IGNITER_PIN, LOW);

    SerialUSB.println("main igniter pin initialized low");

    /*init ematch continuity check pins */
    pinMode(MAIN_CONTINUITY_CHECK_PIN, OUTPUT);
    digitalWrite(MAIN_CONTINUITY_CHECK_PIN, LOW);
    // the ADC read pin does not need to be initialized !!

    SerialUSB.println("main release continuity pins initialized");

    /*init drogue igniter*/
    pinMode(DROGUE_IGNITER_PIN, OUTPUT);
    digitalWrite(DROGUE_IGNITER_PIN, LOW);

    SerialUSB.println("drogue igniter pin initialized low");


    /*init drogue ematch continuity check pins */
    pinMode(DROGUE_CONTINUITY_CHECK_PIN, OUTPUT);
    digitalWrite(DROGUE_CONTINUITY_CHECK_PIN, LOW);

    SerialUSB.println("drogue continuity pins initialized");
}

/**
  * @brief  Fires e-match to deploy drogue and payload
  * @param  None
  * @return None
  */
void deployDrogue(void)
{
    digitalWrite(DROGUE_IGNITER_PIN, HIGH);

    delay(IGNITER_DELAY);
    digitalWrite(DROGUE_IGNITER_PIN, LOW);

    SerialUSB.println("DROGUE IGNITER FIRED");
}

/**
  * @brief  Fires e-match for main release
  * @param  None
  * @return None
  */
void deployMain(void)
{
    digitalWrite(MAIN_IGNITER_PIN, HIGH);
    delay(IGNITER_DELAY);
    digitalWrite(MAIN_IGNITER_PIN, LOW);

    SerialUSB.println("MAIN IGNITER FIRED");
}

/** bool continuityCheck(void)
  * @brief  Checks the ematches for continuity
  * @param  None
  * @return bool flag that is true if there is continuity,
  *             false if the ematch is disconnected or broken.
  */
 bool MainContinuityCheck(void){
    // Main continuity check
    digitalWrite(MAIN_CONTINUITY_CHECK_PIN, HIGH);
    delayMicroseconds(CONTINUITY_CHECK_DELAY);

    int main_continuity = analogRead(MAIN_CONTINUITY_CHECK_ADC);
    digitalWrite(MAIN_CONTINUITY_CHECK_PIN, LOW);

    SerialUSB.print("Main contiunity check ADC read: ");
    SerialUSB.println(main_continuity);

    if (main_continuity <= DISCONTINUOUS_THRESHOLD)
        return false;

    return true;
 }

/** bool DrogueContinuityCheck(void)
  * @brief  Checks the drogue e-match for continuity
  * @param  None
  * @return bool flag that is true if there is continuity,
  *             false if the ematch is disconnected or broken.
  */
bool DrogueContinuityCheck(void){
    // Drogue continuity check
    digitalWrite(DROGUE_CONTINUITY_CHECK_PIN, HIGH);
    delayMicroseconds(CONTINUITY_CHECK_DELAY);

    int drogue_continuity = analogRead(DROGUE_CONTINUITY_CHECK_ADC);
    digitalWrite(DROGUE_CONTINUITY_CHECK_PIN, LOW);

    SerialUSB.print("Drogue contiunity check ADC read: ");
    SerialUSB.println(drogue_continuity);

    if (drogue_continuity <= DISCONTINUOUS_THRESHOLD)
        return false;

    return true;
 }
