/*
 * Debugger Source
 *
 * @file    debugger.cpp
 * @author  Anthony Duen for UBC Rocket Avionics 2018/2019
 * @description   Implementing serial commands to control the igniters.
 *
 * @section LICENSE
 * This program is free software; you can redistribute it and/or
 * modify it without restriction under the terms of the MIT License.
 *
 * Distributed as-is; no warranty is given.
 */

/* Includes-------------------------------------------------------------*/
#include "debugger.h"
#include "igniter.h"

/* Constants -----------------------------------------------------------*/
#define SerialUSB   Serial

/* Functions------------------------------------------------------------*/
void serviceDebug()
{
    static bool mainCheck, drogueCheck = true;
    char command = SerialUSB.read();

    switch(command){
    // Configuration Commands
    case 'd':
        deployDrogue();
        break;
    case 'm':
        deployMain();
        break;
    case 'c':
        mainCheck = MainContinuityCheck();
        drogueCheck = DrogueContinuityCheck();
        break;
    default:
        SerialUSB.println("Invalid command please try again");
        break;
    }
}
