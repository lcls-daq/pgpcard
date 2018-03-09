//---------------------------------------------------------------------------------
// Title         : Kernel Module For PGP To PCI Bridge Card Status
// Project       : PGP To PCI-E Bridge Card
//---------------------------------------------------------------------------------
// File          : PgpCardG3Status.h
// Author        : jackp
// Created       : Wed Jan  6 09:49:47 PST 2016
//---------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------
// Copyright (c) 2016 by SLAC National Accelerator Laboratory. All rights reserved.
//---------------------------------------------------------------------------------
// Modification history:
//---------------------------------------------------------------------------------

#ifndef __PGP_CARD_G3_STATUS_H__
#define __PGP_CARD_G3_STATUS_H__
// Status Structure
typedef struct {

   // General Status
   __u32 Version;       // version
   __u32 SerialNumber[2];// [0] = serNumUpper, [1] = serNumLower
   __u32 ScratchPad;    // ScratchPad
   __u32 BuildStamp[64];// BuildStamp[0->63]
   __u32 CountReset;    // cardRstStat & 1
   __u32 CardReset;     // cardRstStat>>1 & 1

   // PCI Status & Control Registers
   __u32 PciCommand;    // pciStat[0]>>16 & 0xffff
   __u32 PciStatus;     // pciStat[0]     & 0xffff
   __u32 PciDCommand;   // pciStat[1]>>16 & 0xffff
   __u32 PciDStatus;    // pciStat[1]>>16 & 0xffff
   __u32 PciLCommand;   // pciStat[2]>>16 & 0xffff
   __u32 PciLStatus;    // pciStat[2]>>16 & 0xffff
   __u32 PciLinkState;  // pciStat[3]>>24 & 0x7
   __u32 PciFunction;   // pciStat[3]>>16 & 0x3
   __u32 PciDevice;     // pciStat[3]>>8  & 0xf
   __u32 PciBus;        // pciStat[3]     & 0xff
   __u32 PciBaseHdwr;   // skip
   __u32 PciBaseLen;    // skip

   // PGP Status
   __u32 PpgRate;       // pgpRate
   __u32 PgpLoopBack[8];// (pgpCardStat[0] >> lane) & 0x1
   __u32 PgpTxReset[8];// (pgpCardStat[0] >> (lane+16)) & 0x1
   __u32 PgpRxReset[8];// (pgpCardStat[0] >> (lane+8)) & 0x1
   __u32 PgpTxPllRst[2];// (pgpCardStat[0] >> ((0|1)+26)) & 0x1
   __u32 PgpRxPllRst[2];// (pgpCardStat[0] >> ((0|1)+24)) & 0x1
   __u32 PgpTxPllRdy[2];// (pgpCardStat[0] >> ((0|1)+30)) & 0x1
   __u32 PgpRxPllRdy[2];// (pgpCardStat[0] >> ((0|1)+28)) & 0x1
   __u32 PgpLocLinkReady[8];// (pgpCardStat[1] >> (lane + 8) & 1
   __u32 PgpRemLinkReady[8];// (pgpCardStat[1] >> (lane + 0) & 1
   __u32 PgpRxCount[8][4];// (pgpLaneStat[lane] >> ((4*vc)) & 0xf
   __u32 PgpCellErrCnt[8];// (pgpLaneStat[lane] >> (20) & 0xf
   __u32 PgpLinkDownCnt[8];// (pgpLaneStat[lane] >> (24) & 0xf
   __u32 PgpLinkErrCnt[8];// (pgpLaneStat[lane] >> (28) & 0xf
   __u32 PgpFifoErrCnt[8];// (pgpLaneStat[lane] >> (16) & 0xf

   // EVR Status & Control Registers
   __u32 EvrRunCode[8];// runCode[lane] & 0xff
   __u32 EvrAcceptCode[8];// acceptCode[lane] & 0xff
   __u32 EvrEnHdrCheck[8][4];// evrCardStat[2] >> ((4*lane)+vc)
   __u32 EvrEnable;     // evrCardStat[1] & 0x1
   __u32 EvrReady;      // (evrCardStat[0] >> 4) & 0x1
   __u32 EvrReset;      // (evrCardStat[1] >> 1) & 0x1
   __u32 EvrRunMask;    // (evrCardStat[0] >> 16) & 0xff
   __u32 EvrLaneStatus; // (evrCardStat[1] >> 24) & 0xff
   __u32 EvrLaneEnable; // (evrCardStat[1] >> 16) & 0xff
   __u32 EvrLaneMode;   // (evrCardStat[1] >> 8) & 0xff
   __u32 EvrPllRst;     // (evrCardStat[1] >> 2) & 0x1
   __u32 EvrErrCnt;     // evrLinkErrorCount
   __u32 EvrFiducial;   // evrFiducial
   __u32 EvrRunDelay[8];// runDelay[lane]
   __u32 EvrAcceptDelay[8];// acceptDelay[lane]
   __u32 EvrRunCodeCount[8];// runCodeCount[lane]
   __u32 EvrLutDropCount[8];// LutDropCount[lane]
   __u32 EvrAcceptCount[8];// AcceptCount[lane]
   __u32 EvrLaneFiducials[8];// fiducials[lane]

   // RX Descriptor Status
   __u32 RxFreeFull[8]; // (rxFreeStat[lane] >> 31) & 1
   __u32 RxFreeValid[8];// (rxFreeStat[lane] >> 30) & 1
   __u32 RxFreeFifoCount[8];// rxFreeStat[lane] & 0x3ff
   __u32 RxReadReady;   // (rxStatus >> 31) & 1
   __u32 RxRetFifoCount;// rxStatus & 0x3ff
   __u32 RxCount;       // rxCount
   __u32 RxWrite[8];    // skip
   __u32 RxRead[8];     // skip

   // TX Descriptor Status
   __u32 TxDmaAFull[8]; // (txStat[0] >> lane) & 1
   __u32 TxReadReady;   // (txStat[1] >> 31) & 1
   __u32 TxRetFifoCount;// (txStat[1] & 0x3ff
   __u32 TxCount;       // txCount
   __u32 TxRead;        // skip

} PgpCardG3Status;

#define NUMBER_OF_LANES 8
typedef struct {
  __u32 Version;       // Software_Addr = 0x000,        Firmware_Addr(13 downto 2) = 0x000
  __u32 SerialNumber[2];// Software_Addr = 0x004,        Firmware_Addr(13 downto 2) = 0x001
  __u32 ScratchPad;       // Software_Addr = 0x00C,        Firmware_Addr(13 downto 2) = 0x003
  __u32 cardRstStat;   // Software_Addr = 0x010,        Firmware_Addr(13 downto 2) = 0x004
  __u32 irq;           // Software_Addr = 0x014,        Firmware_Addr(13 downto 2) = 0x005
  __u32 pgpRate;       // Software_Addr = 0x018,        Firmware_Addr(13 downto 2) = 0x006
  __u32 sysSpare0[2];  // Software_Addr = 0x020:0x01C,  Firmware_Addr(13 downto 2) = 0x008:0x007
  __u32 txLocPause;    // Software_Addr = 0x024,        Firmware_Addr(13 downto 2) = 0x009
  __u32 txLocOvrFlow;  // Software_Addr = 0x028,        Firmware_Addr(13 downto 2) = 0x00A
  __u32 pciStat[4];    // Software_Addr = 0x038:0x02C,  Firmware_Addr(13 downto 2) = 0x00E:0x00B
  __u32 sysSpare1;     // Software_Addr = 0x03C,        Firmware_Addr(13 downto 2) = 0x00F

  __u32 evrCardStat[3];// Software_Addr = 0x048:0x040,  Firmware_Addr(13 downto 2) = 0x012:0x010
  __u32 evrLinkErrorCount; // Software_Addr = 0x04C,    Firmware_Addr ????
  __u32 evrFiducial;   // Software_addr = 0x050,
  __u32 evrSpare0[11]; // Software_Addr = 0x07C:0x054,  Firmware_Addr(13 downto 2) = 0x01F:0x013

 __u32 pgpCardStat[2];// Software_Addr = 0x084:0x080,  Firmware_Addr(13 downto 2) = 0x021:0x020
  __u32 pgpSpare0[54]; // Software_Addr = 0x15C:0x088,  Firmware_Addr(13 downto 2) = 0x057:0x022

  __u32 fiducials[NUMBER_OF_LANES]; // Software_Addr = 0x17C:0x160,  Firmware_Addr(13 downto 2) = 0x05F:0x058
  __u32 runCode[NUMBER_OF_LANES];   // Software_Addr = 0x19C:0x180,  Firmware_Addr(13 downto 2) = 0x067:0x060
  __u32 acceptCode[NUMBER_OF_LANES];// Software_Addr = 0x1BC:0x1A0,  Firmware_Addr(13 downto 2) = 0x06F:0x068

  __u32 runDelay[NUMBER_OF_LANES];   // Software_Addr = 0x1DC:0x1C0,  Firmware_Addr(13 downto 2) = 0x077:0x070
  __u32 acceptDelay[NUMBER_OF_LANES];// Software_Addr = 0x1FC:0x1E0,  Firmware_Addr(13 downto 2) = 0x07F:0x078

  __u32 pgpLaneStat[NUMBER_OF_LANES];// Software_Addr = 0x21C:0x200,  Firmware_Addr(13 downto 2) = 0x087:0x080
  __u32 evrRunCodeCount[NUMBER_OF_LANES]; // Software_Addr = 0x23C:0x220, Firmware_Addr ????
  __u32 LutDropCnt[NUMBER_OF_LANES]; // Software_addr = ox25C:0x240, Firmware_addr ????
  __u32 AcceptCnt[NUMBER_OF_LANES]; // Software addr = 0x27C:0x260, Firmware_addr ????
  __u32 pgpSpare1[32]; // Software_Addr = 0x2FC:0x280,  Firmware_Addr(13 downto 2) = 0x0BF:0x088
  __u32 BuildStamp[64];// Software_Addr = 0x3FC:0x300,  Firmware_Addr(13 downto 2) = 0x0FF:0x0C0

  //PciRxDesc.vhd
  __u32 rxFree[NUMBER_OF_LANES];     // Software_Addr = 0x41C:0x400,  Firmware_Addr(13 downto 2) = 0x107:0x100
  __u32 rxSpare0[24];  // Software_Addr = 0x47C:0x420,  Firmware_Addr(13 downto 2) = 0x11F:0x108
  __u32 rxFreeStat[NUMBER_OF_LANES]; // Software_Addr = 0x49C:0x480,  Firmware_Addr(13 downto 2) = 0x127:0x120
  __u32 rxSpare1[24];  // Software_Addr = 0x4FC:0x4A0,  Firmware_Addr(13 downto 2) = 0x13F:0x128
  __u32 rxMaxFrame;    // Software_Addr = 0x500,        Firmware_Addr(13 downto 2) = 0x140
  __u32 rxCount;       // Software_Addr = 0x504,        Firmware_Addr(13 downto 2) = 0x141
  __u32 rxStatus;      // Software_Addr = 0x508,        Firmware_Addr(13 downto 2) = 0x142
  __u32 rxRead[2];     // Software_Addr = 0x510:0x50C,  Firmware_Addr(13 downto 2) = 0x144:0x143
  __u32 rxSpare2[187]; // Software_Addr = 0x77C:0x514,  Firmware_Addr(13 downto 2) = 0x1FF:0x145

  //PciTxDesc.vhd
  __u32 txWrA[8];      // Software_Addr = 0x81C:0x800,  Firmware_Addr(13 downto 2) = 0x207:0x200
  __u32 txSpare0[24];  // Software_Addr = 0x87C:0x820,  Firmware_Addr(13 downto 2) = 0x21F:0x208
  __u32 txWrB[8];      // Software_Addr = 0x89C:0x880,  Firmware_Addr(13 downto 2) = 0x227:0x220
  __u32 txSpare1[24];  // Software_Addr = 0x8FC:0x8A0,  Firmware_Addr(13 downto 2) = 0x23F:0x228
  __u32 txStat[2];     // Software_Addr = 0x904:0x900,  Firmware_Addr(13 downto 2) = 0x241:0x240
  __u32 txCount;       // Software_Addr = 0x908,        Firmware_Addr(13 downto 2) = 0x242
  __u32 txRead;        // Software_Addr = 0x90C,        Firmware_Addr(13 downto 2) = 0x243
} PgpCardG3Regs;


#endif
