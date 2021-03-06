
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <linux/types.h>

#include "../include/PgpCardMod.h"
#include "../include/PgpCardG3Status.h"

using namespace std;

int main (int argc, char **argv) {
  PgpCardG3Status status;
  PgpCardTx pgpCardTx;
  unsigned size = sizeof(PgpCardTx);
  int           fd;
  int           x;
  int           y;

  if ( argc != 2 ) {
    printf("Usage: %s <device>\n", argv[0]);
    return(0);
  }

  if ( (fd = open(argv[1], O_RDWR)) <= 0 ) {
    cout << "Error opening " << argv[1] << endl;
    return(1);
  }

  memset(&status,0,sizeof(PgpCardG3Status));
  PgpCardTx* p = &pgpCardTx;

  p->model = sizeof(p);
  p->cmd   = IOCTL_Read_Status;
  p->data  = (__u32*)&status;
  write(fd, p, size);

  cout << endl;
  cout << " PGP Card Status:" << hex << uppercase << endl << endl;

  __u64 SerialNumber = status.SerialNumber[0];
  SerialNumber = SerialNumber << 32;
  SerialNumber |= status.SerialNumber[1];

  cout << "           Version: 0x" << setw(8) << setfill('0') << status.Version << endl;
  cout << "      SerialNumber: 0x" << setw(16)<< setfill('0') << SerialNumber << endl;
  cout << "        BuildStamp: "   << string((char *)status.BuildStamp)  << endl;
  cout << "        CountReset: 0x" << setw(1) << setfill('0') << status.CountReset << endl;
  cout << "         CardReset: 0x" << setw(1) << setfill('0') << status.CardReset << endl;
  cout << "        ScratchPad: 0x" << setw(8) << setfill('0') << status.ScratchPad << endl;
  cout << endl;

  cout << "          PciCommand: 0x" << setw(4) << setfill('0') << status.PciCommand << endl;
  cout << "           PciStatus: 0x" << setw(4) << setfill('0') << status.PciStatus << endl;
  cout << "         PciDCommand: 0x" << setw(4) << setfill('0') << status.PciDCommand << endl;
  cout << "          PciDStatus: 0x" << setw(4) << setfill('0') << status.PciDStatus << endl;
  cout << "         PciLCommand: 0x" << setw(4) << setfill('0') << status.PciLCommand << endl;
  cout << "          PciLStatus: 0x" << setw(4) << setfill('0') << status.PciLStatus << endl;
  cout << "Negotiated Link Width:  " << dec << ((status.PciLStatus >> 4) & 0x3f) << endl;
  cout << "        PciLinkState: 0x" << setw(1) << setfill('0') << status.PciLinkState << endl;
  cout << "         PciFunction: 0x" << setw(1) << setfill('0') << status.PciFunction << endl;
  cout << "           PciDevice: 0x" << setw(1) << setfill('0') << status.PciDevice << endl;
  cout << "              PciBus: 0x" << setw(2) << setfill('0') << status.PciBus << endl;
  cout << "         PciBaseAddr: 0x" << setw(8) << setfill('0') << status.PciBaseHdwr << endl;
  cout << "       PciBaseLength: 0x" << setw(8) << setfill('0') << status.PciBaseLen << endl;
  cout << endl;

  cout << "            PgpRate(Gbps): " << setprecision(3) << fixed  << ((double)status.PpgRate)*1.0E-3 << endl;
  cout << "         PgpLoopBack[0:7]: ";
  for(x=0;x<8;x++){
    cout <<  setw(1) << setfill('0') << status.PgpLoopBack[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "          PgpTxReset[0:7]: ";
  for(x=0;x<8;x++){
    cout <<  setw(1) << setfill('0') << status.PgpTxReset[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "          PgpRxReset[0:7]: ";
  for(x=0;x<8;x++){
    cout <<  setw(1) << setfill('0') << status.PgpRxReset[x];
    if(x!=7) cout << ", "; else cout << endl;
  }


  cout << " PgpTxCommonPllReset[3:0],[7:4]: 0x" <<  setw(1) << setfill('0') << status.PgpTxPllRst[0] << ", 0x";
  cout << status.PgpTxPllRst[1] << endl;


  cout << " PgpRxCommonPllReset[3:0],[7:4]: 0x" <<  setw(1) << setfill('0') << status.PgpRxPllRst[0] << ", 0x";
  cout << status.PgpRxPllRst[1] << endl;


  cout << "PgpTxCommonPllLocked[3:0],[7:4]: 0x" <<  setw(1) << setfill('0') << status.PgpTxPllRdy[0] << ", 0x";
  cout << status.PgpTxPllRdy[1] << endl;


  cout << "PgpRxCommonPllLocked[3:0],[7:4]: 0x" <<  setw(1) << setfill('0') << status.PgpRxPllRdy[0] << ", 0x";
  cout << status.PgpRxPllRdy[1] << endl;

  cout << "     PgpLocLinkReady[0:7]: ";
  for(x=0;x<8;x++){
    cout <<  setw(1) << setfill('0') << status.PgpLocLinkReady[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "     PgpRemLinkReady[0:7]: ";
  for(x=0;x<8;x++){
    cout <<  setw(1) << setfill('0') << status.PgpRemLinkReady[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  for(x=0;x<8;x++){
    cout << "       PgpRxCount["<<  setw(1) << setfill('0') << x <<"][0:3]: ";
    for(y=0;y<4;y++){
      cout << "0x" <<  setw(1) << setfill('0') << status.PgpRxCount[x][y];
      if(y!=3) cout << ", "; else cout << endl;
    }
  }

  cout << "       PgpCellErrCnt[0:7]: ";
  for(x=0;x<8;x++){
    cout << "0x" <<  setw(1) << setfill('0') << status.PgpCellErrCnt[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "      PgpLinkDownCnt[0:7]: ";
  for(x=0;x<8;x++){
    cout << "0x" <<  setw(1) << setfill('0') << status.PgpLinkDownCnt[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "       PgpLinkErrCnt[0:7]: ";
  for(x=0;x<8;x++){
    cout << "0x" <<  setw(1) << setfill('0') << status.PgpLinkErrCnt[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "       PgpFifoErrCnt[0:7]: ";
  for(x=0;x<8;x++){
    cout << "0x" <<  setw(1) << setfill('0') << status.PgpFifoErrCnt[x];
    if(x!=7) cout << ", "; else cout << endl;
  }
  cout << endl;
  cout << "        EvrRunCode[0:7]: ";
  for(x=0;x<8;x++){
    cout << dec << setw(1) << setfill('0') << status.EvrRunCode[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "     EvrAcceptCode[0:7]: ";
  for(x=0;x<8;x++){
    cout <<  setw(1) << setfill('0') << status.EvrAcceptCode[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "       EvrRunDelay[0:7]: ";
  for(x=0;x<8;x++){
    cout << status.EvrRunDelay[x];
    if (x==7) cout << endl; else cout << ", ";
  }

  cout << "    EvrAcceptDelay[0:7]: ";
  for(x=0;x<8;x++){
    cout << status.EvrAcceptDelay[x];
    if (x==7) cout << endl; else cout << ", ";
  }

  cout << "   EvrRunCodeCount[0:7]: ";
  for(x=0;x<8;x++){
    cout << status.EvrRunCodeCount[x];
    if (x==7) cout << endl; else cout << ", ";
  }

  for(x=0;x<8;x++){
    cout << "EvrLutDropCount["<<  setw(1) << setfill('0') << x <<"][0:3]: ";
    for(y=0;y<4;y++){
      cout << dec <<  setw(1) << setfill('0') << ((status.EvrLutDropCount[x]>>(y*8))&0xff);
      if(y!=3) cout << ", "; else cout << endl;
    }
  }

  cout << "    EvrAcceptCount[0:7]: ";
  for(x=0;x<8;x++){
    cout << status.EvrAcceptCount[x];
    if (x==7) cout << endl; else cout << ", ";
  }


  cout << "       EvrRunMask[0:7]:  ";
  for(x=0;x<8;x++){
    cout << dec << setw(1) << setfill('0') << ((status.EvrRunMask>>x)&1);
    if (x==7) cout << endl; else cout << ", ";
  }

  cout << "       EvrLaneMode[0:7]: ";
  for(x=0;x<8;x++){
    cout << dec << setw(1) << setfill('0') << ((status.EvrLaneMode>>x)&1);
    if (x==7) cout << endl; else cout << ", ";
  }

  cout << "  EvrLaneFiducials[0:7]: ";
  cout << hex;
  for(x=0;x<8;x++){
    cout << "0x" << status.EvrLaneFiducials[x];
    if (x==7) cout << endl; else cout << ", ";
  }
  cout << dec;

  cout << "     EvrLaneEnable[0:7]: ";
  for(x=0;x<8;x++){
    cout << dec << setw(1) << setfill('0') << ((status.EvrLaneEnable>>x)&1);
    if (x==7) cout << endl; else cout << ", ";
  }

  cout << "     EvrLaneStatus[0:7]: ";
  for(x=0;x<8;x++){
    cout << dec << setw(1) << setfill('0') << ((status.EvrLaneStatus>>x)&1);
    if (x==7) cout << endl; else cout << ", ";
  }

  cout << "              EvrEnable: " << setw(1) << setfill('0') << status.EvrEnable << endl;
  cout << "               EvrReady: " << setw(1) << setfill('0') << status.EvrReady << endl;
  cout << "               EvrReset: " << setw(1) << setfill('0') << status.EvrReset << endl;
  cout << "              EvrPllRst: " << setw(1) << setfill('0') << status.EvrPllRst << endl;
  cout << "              EvrErrCnt: " << setw(1) << setfill('0') << status.EvrErrCnt << endl;
  cout << hex;
  cout << "              EvrFiducial: 0x" << setw(1) << setfill('0') << status.EvrFiducial << endl;
  cout << dec;
  for(x=0;x<8;x++){
    cout << "  EvrEnHdrCheck["<<  setw(1) << setfill('0') << x <<"][0:3]: ";
    for(y=0;y<4;y++){
      cout <<  setw(1) << setfill('0') << status.EvrEnHdrCheck[x][y];
      if(y!=3) cout << ", "; else cout << endl;
    }
  }
  cout << endl;

  cout << "        TxAFull[0:7]: ";
  for(x=0;x<8;x++){
    cout << setw(1) << setfill('0') << status.TxDmaAFull[x];
    if(x!=7) cout << ", "; else cout << endl;
  }
  cout << hex << "         TxReadReady: 0x" << setw(1) << setfill('0') << status.TxReadReady << endl;
  cout << "      TxRetFifoCount: 0x" << setw(3) << setfill('0') << status.TxRetFifoCount << endl;
  cout << "             TxCount: 0x" << setw(8) << setfill('0') << status.TxCount << endl;
  cout << "              TxRead: 0x" << setw(2) << setfill('0') << status.TxRead  << endl;
  cout << endl;

  cout << "     RxFreeFull[0:7]: ";
  for(x=0;x<8;x++){
    cout << setw(1) << setfill('0') << status.RxFreeFull[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "    RxFreeValid[0:7]: ";
  for(x=0;x<8;x++){
    cout << setw(1) << setfill('0') << status.RxFreeValid[x];
    if(x!=7) cout << ", "; else cout << endl;
  }

  cout << "RxFreeFifoCount[0:7]: ";
  for(x=0;x<8;x++){
    cout << "0x" << setw(1) << setfill('0') << status.RxFreeFifoCount[x];
    if(x!=7) cout << ", "; else cout << endl;
  }
  cout << "         RxReadReady: 0x" << setw(1) << setfill('0') << status.RxReadReady << endl;
  cout << "      RxRetFifoCount: 0x" << setw(3) << setfill('0') << status.RxRetFifoCount << endl;
  cout << "             RxCount: 0x" <<  setw(8) << setfill('0') << status.RxCount << endl;
  cout << "        RxWrite[0:7]: ";
  for(x=0;x<8;x++){
    cout << "0x" << setw(3) << setfill('0') << status.RxWrite[x];
    if(x!=7) cout << ", "; else cout << endl;
  }
  cout << "         RxRead[0:7]: ";
  for(x=0;x<8;x++){
    cout << "0x" << setw(3) << setfill('0') << status.RxRead[x];
    if(x!=7) cout << ", "; else cout << endl;
  }
  cout << endl;

  p->cmd = IOCTL_Dump_Debug;
  if (write(fd, p, size) < 0) {
    perror("IOCTL_Dump_Debug");
  }

  p->cmd   = IOCTL_Show_Version;
  write(fd, p, sizeof(PgpCardTx));

  close(fd);
}
