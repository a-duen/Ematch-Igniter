/*
 * Igniter Header
 *
 * @file    igniter.h
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

#ifndef IGNITER_H
#define IGNITER_H

/*Includes------------------------------------------------------------*/
#include <Arduino.h>

/*Constants------------------------------------------------------------*/

/*Functions------------------------------------------------------------*/
void initIgniter(void);
void deployDrogue(void);
void deployMain(void);
bool MainContinuityCheck(void);
bool DrogueContinuityCheck(void);

#endif  // IGNITER_H
