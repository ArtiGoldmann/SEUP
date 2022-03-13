//###########################################################################
//
// FILE:    DSP2803x_CpuTimers.h
//
// TITLE:   DSP2803x CPU 32-bit Timers Register Definitions.
//
//###########################################################################
// $TI Release: F2803x Support Library v2.01.00.00 $
// $Release Date: Sat Sep 16 15:27:09 CDT 2017 $
// $Copyright:
// Copyright (C) 2009-2017 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef DSP2803x_CPU_TIMERS_H
#define DSP2803x_CPU_TIMERS_H

#ifdef __cplusplus
extern "C" {
#endif

//
// CPU Timer Register Bit Definitions:
//

//
// TCR - Control register bit definitions
//
struct  TCR_BITS {          // bits  description
   Uint16    rsvd1:4;       // 3:0   reserved
   Uint16    TSS:1;         // 4     Timer Start/Stop
   Uint16    TRB:1;         // 5     Timer reload
   Uint16    rsvd2:4;       // 9:6   reserved
   Uint16    SOFT:1;        // 10    Emulation modes
   Uint16    FREE:1;        // 11
   Uint16    rsvd3:2;       // 12:13 reserved
   Uint16    TIE:1;         // 14    Output enable
   Uint16    TIF:1;         // 15    Interrupt flag
};

union TCR_REG {
   Uint16           all;
   struct TCR_BITS  bit;
};

//
// TPR - Pre-scale low bit definitions
//
struct  TPR_BITS {        // bits  description
   Uint16     TDDR:8;     // 7:0   Divide-down low
   Uint16     PSC:8;      // 15:8  Prescale counter low
};

union TPR_REG {
   Uint16           all;
   struct TPR_BITS  bit;
};

//
// TPRH - Pre-scale high bit definitions
//
struct  TPRH_BITS {       // bits  description
   Uint16     TDDRH:8;      // 7:0   Divide-down high
   Uint16     PSCH:8;       // 15:8  Prescale counter high
};

union TPRH_REG {
   Uint16           all;
   struct TPRH_BITS bit;
};

//
// TIM, TIMH - Timer register definitions
//
struct TIM_REG {
   Uint16  LSW;
   Uint16  MSW;
};

union TIM_GROUP {
   Uint32          all;
   struct TIM_REG  half;
};

//
// PRD, PRDH - Period register definitions
//
struct PRD_REG {
   Uint16  LSW;
   Uint16  MSW;
};

union PRD_GROUP {
   Uint32          all;
   struct PRD_REG  half;
};

//
// CPU Timer Register File
//
struct CPUTIMER_REGS {
   union TIM_GROUP TIM;     // Timer counter register
   union PRD_GROUP PRD;     // Period register
   union TCR_REG   TCR;     // Timer control register
   Uint16          rsvd1;   // reserved
   union TPR_REG   TPR;     // Timer pre-scale low
   union TPRH_REG  TPRH;    // Timer pre-scale high
};

//
// CPU Timer Support Variables:
//
struct CPUTIMER_VARS {
   volatile struct  CPUTIMER_REGS  *RegsAddr;
   Uint32    InterruptCount;
   float   CPUFreqInMHz;
   float   PeriodInUSec;
};

//
// Function prototypes and external definitions
//
void InitCpuTimers(void);
void ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period);

extern volatile struct CPUTIMER_REGS CpuTimer0Regs;
extern struct CPUTIMER_VARS CpuTimer0;

extern volatile struct CPUTIMER_REGS CpuTimer1Regs;
extern volatile struct CPUTIMER_REGS CpuTimer2Regs;

extern struct CPUTIMER_VARS CpuTimer1;
extern struct CPUTIMER_VARS CpuTimer2;

//
// Useful Timer Operations
//

//
// Start Timer
//
#define StartCpuTimer0()   CpuTimer0Regs.TCR.bit.TSS = 0

//
// Stop Timer
//
#define StopCpuTimer0()   CpuTimer0Regs.TCR.bit.TSS = 1

//
// Reload Timer With period Value
//
#define ReloadCpuTimer0() CpuTimer0Regs.TCR.bit.TRB = 1

//
// Read 32-Bit Timer Value
//
#define ReadCpuTimer0Counter() CpuTimer0Regs.TIM.all

//
// Read 32-Bit Period Value
//
#define ReadCpuTimer0Period() CpuTimer0Regs.PRD.all

//
// Start Timer
//
#define StartCpuTimer1()   CpuTimer1Regs.TCR.bit.TSS = 0
#define StartCpuTimer2()   CpuTimer2Regs.TCR.bit.TSS = 0

//
// Stop Timer
//
#define StopCpuTimer1()   CpuTimer1Regs.TCR.bit.TSS = 1
#define StopCpuTimer2()   CpuTimer2Regs.TCR.bit.TSS = 1

//
// Reload Timer With period Value
//
#define ReloadCpuTimer1() CpuTimer1Regs.TCR.bit.TRB = 1
#define ReloadCpuTimer2() CpuTimer2Regs.TCR.bit.TRB = 1

//
// Read 32-Bit Timer Value
//
#define ReadCpuTimer1Counter() CpuTimer1Regs.TIM.all
#define ReadCpuTimer2Counter() CpuTimer2Regs.TIM.all

//
// Read 32-Bit Period Value
//
#define ReadCpuTimer1Period() CpuTimer1Regs.PRD.all
#define ReadCpuTimer2Period() CpuTimer2Regs.PRD.all

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_CPU_TIMERS_H definition

//
// End of file
//

