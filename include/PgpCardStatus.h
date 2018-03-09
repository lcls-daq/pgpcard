//---------------------------------------------------------------------------------
// Title         : Kernel Module For PGP To PCI Bridge Card
// Project       : PGP To PCI-E Bridge Card
//---------------------------------------------------------------------------------
// File          : PgpCardMod.h
// Author        : jackp
// Created       : Wed Jan  6 09:50:42 PST 2016
//---------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------
// Copyright (c) 2016 by SLAC National Accelerator Laboratory. All rights reserved.
//---------------------------------------------------------------------------------
// Modification history:
//---------------------------------------------------------------------------------
#ifndef PGP_CARD_STATUS_H
#define PGP_CARD_STATUS_H

typedef struct {
    __u32 PgpLoopBack;
    __u32 PgpRxReset;
    __u32 PgpTxReset;
    __u32 PgpLocLinkReady;
    __u32 PgpRemLinkReady;
    __u32 PgpRxReady;
    __u32 PgpTxReady;
    __u32 PgpRxCount;
    __u32 PgpCellErrCnt;
    __u32 PgpLinkDownCnt;
    __u32 PgpLinkErrCnt;
    __u32 PgpFifoErr;
} PgpCardLinkStatus;

// Status Structure
typedef struct {

   // General Status
   __u32 Version;

   // Scratchpad
   __u32 ScratchPad;

   // PCI Status & Control Registers
   __u32 PciCommand;
   __u32 PciStatus;
   __u32 PciDCommand;
   __u32 PciDStatus;
   __u32 PciLCommand;
   __u32 PciLStatus;
   __u32 PciLinkState;
   __u32 PciFunction;
   __u32 PciDevice;
   __u32 PciBus;

   PgpCardLinkStatus PgpLink[4];

   // TX Descriptor Status
   __u32 TxDma3AFull;
   __u32 TxDma2AFull;
   __u32 TxDma1AFull;
   __u32 TxDma0AFull;
   __u32 TxReadReady;
   __u32 TxRetFifoCount;
   __u32 TxCount;
   __u32 TxBufferCount;
   __u32 TxRead;

   // RX Descriptor Status
   __u32 RxFreeEmpty;
   __u32 RxFreeFull;
   __u32 RxFreeValid;
   __u32 RxFreeFifoCount;
   __u32 RxReadReady;
   __u32 RxRetFifoCount;
   __u32 RxCount;
   __u32 RxBufferCount;
   __u32 RxWrite[8];
   __u32 RxRead[8];

} PgpCardStatus;

typedef struct {
   __u32 version;     // 0x000
   __u32 scratch;     // 0x004
   __u32 irq;         // 0x008
   __u32 control;     // 0x00C
   __u32 l0Data;      // 0x010
   __u32 l1Data;      // 0x014
   __u32 l2Data;      // 0x018
   __u32 l3Data;      // 0x01C

   __u32 spare0[8];   // 0x020 - 0x03C

   __u32 pgp0Stat;    // 0x040
   __u32 pgp1Stat;    // 0x044
   __u32 pgp2Stat;    // 0x048
   __u32 pgp3Stat;    // 0x04C

   __u32 spare1[12];  // 0x050 - 0x07C

   __u32 pciStat0;    // 0x080
   __u32 pciStat1;    // 0x084
   __u32 pciStat2;    // 0x088
   __u32 pciStat3;    // 0x08C

   __u32 spare2[220]; // 0x090 - 0x3FC

   __u32 rxFree;      // 0x400
   __u32 rxMaxFrame;  // 0x404
   __u32 rxStatus;    // 0x408
   __u32 rxCount;     // 0x40C

   __u32 spare3[4];   // 0x410 - 0x41C

   __u32 rxRead0;     // 0x420
   __u32 rxRead1;     // 0x424

   __u32 spare4[246]; // 0x428 - 0x7FC

   __u32 txL0Wr0;     // 0x800
   __u32 txL0Wr1;     // 0x804
   __u32 txL1Wr0;     // 0x808
   __u32 txL1Wr1;     // 0x80C
   __u32 txL2Wr0;     // 0x810
   __u32 txL2Wr1;     // 0x814
   __u32 txL3Wr0;     // 0x818
   __u32 txL3Wr1;     // 0x81C
   __u32 txStatus;    // 0x820
   __u32 txRead;      // 0x824
   __u32 txCount;     // 0x828

   __u32 spare5[245]; // 0x82C - 0xBFC

   __u32 promRegs[3]; // Prom registers
} PgpCardG2Regs;

#endif
