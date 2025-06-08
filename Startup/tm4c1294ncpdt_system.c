//*****************************************************************************
//
// Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>

#include "hw_nvic.h"
#include "hw_types.h"

void SystemInit() {
  //
  // Enable the floating-point unit.  This must be done here to handle the
  // case where main() uses floating-point and the function prologue saves
  // floating-point registers (which will fault if floating-point is not
  // enabled).  Any configuration of the floating-point unit using DriverLib
  // APIs must be done here prior to the floating-point unit being enabled.
  //
  // Note that this does not use DriverLib since it might not be included in
  // this project.
  //
  HWREG(NVIC_CPAC) =
      ((HWREG(NVIC_CPAC) & ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) |
       NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
void NmiSR(void) {
  //
  // Enter an infinite loop.
  //
  while (1) {
  }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
void FaultISR(void) {
  //
  // Enter an infinite loop.
  //
  while (1) {
  }
}