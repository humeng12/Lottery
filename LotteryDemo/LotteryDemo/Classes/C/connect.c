//
//  connect.c
//  MyPOSHRT3
//
//  Created by Y on 14-9-26.
//  Copyright (c) 2014年 Y. All rights reserved.
//
#include "connect.h"
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <stdbool.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/dirent.h>
#include <sys/ioctl.h>
#include <sys/filio.h>
#include <netdb.h>
#include "Trans.h"
#include "defineParam.h"

/******************************************/
int iSocket;
/******************************************/

/**************************socked编程***********************************************/
int b19177539def0aacd028c1431978290b(const char *szHostName, unsigned int nPort, unsigned int uiTimeOut)
{
     int res,flags,error;
     socklen_t len;
     fd_set rset,wset;
     struct timeval tval;
     tval.tv_sec=uiTimeOut;
     tval.tv_usec=0;
     struct sockaddr_in serv_addr;


     if((iSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
     {
          return -2;
     }

     serv_addr.sin_family=AF_INET;
     serv_addr.sin_port=htons(nPort);
     serv_addr.sin_addr.s_addr=inet_addr(szHostName);
     bzero(&(serv_addr.sin_zero),8);
     flags=fcntl(iSocket,F_GETFL,0);
     fcntl(iSocket,F_SETFL,flags|O_NONBLOCK);


     if( (res = connect(iSocket, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) )< 0)
     {
          if(errno != EINPROGRESS)
          {
               return -2;
               close(iSocket);
          }
     }
     if(0 == res)
          goto done;

     FD_ZERO(&rset);
     FD_SET(iSocket,&rset);
     wset=rset;
     if( ( res = select(iSocket+1, NULL, &wset, NULL,&tval) ) <= 0)
     {
          close(iSocket);
          return -2;
     }
     else
     {
          len=sizeof(error);
          getsockopt(iSocket, SOL_SOCKET, SO_ERROR, &error, &len);
          if(error)
          {
               fprintf(stderr, "Error in connection() %d - %s\n", error, strerror(error));
               return -2;
          }
     }

done:
     return 0;
}

int f472719992051827f84c213642172140(unsigned char *i_pszData, int i_iLength)
{
     if( send (iSocket, i_pszData, i_iLength,0) != i_iLength)
     {
          close(iSocket);
          return -5;
     }

     return i_iLength;
}

int iReceiveTCPIPData(unsigned char *o_pszData, int *o_iLength, int i_iTimeOut)
{
     fd_set fdMask;
     int iSelected;
     struct timeval srTimeOut;
     int j;
     srTimeOut.tv_sec = i_iTimeOut;
     srTimeOut.tv_usec = 0;

     FD_ZERO (&fdMask);
     FD_SET (iSocket, &fdMask);

     iSelected = select(iSocket+1,&fdMask,NULL, NULL,&srTimeOut);

     if( iSelected<= 0 )
     {
          j = 0;
     }
     else
     {
          j = (int)recv (iSocket, o_pszData,MAX_ISO_MSG_SIZE, 0);

          *o_iLength = j;
     }
     close(iSocket);
     return j;
}

int af2d87ec65d7e992873c381e78ee17d7(unsigned char *i_uszSendPacket,int *i_ulSendSize,
                 unsigned char *o_puszRecvPacket,int *i_pulRecvSize)
{
     int iRetVal;
     iPackLenInRequestPacket(PACK_HEX,i_uszSendPacket,i_ulSendSize);
     iRetVal=f472719992051827f84c213642172140(i_uszSendPacket,*i_ulSendSize);
     if(iRetVal==-5)
     {
          return 1;
     }
     else
     {
          iRetVal=iReceiveTCPIPData(o_puszRecvPacket,i_pulRecvSize,CONNECTIME);
     }

     return iRetVal;
}
/**************************socked编程 end***********************************************/