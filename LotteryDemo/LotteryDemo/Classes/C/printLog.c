//
//  printLog.c
//  merchant
//
//  Created by HRT on 15/6/23.
//  Copyright (c) 2015年 Hrtpayment. All rights reserved.
//

#include "printLog.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>



void print_hex(char * tip,unsigned char* buff,int bytes)
{
#ifdef PRINTLOG
     int byte_index = 0;
     printf("\n");
     printf("=======%s========\n", tip);

     for(byte_index = 0; byte_index < bytes; byte_index++)
     {
          printf("%02X ", buff[byte_index]);
     }
     printf("\n");
     printf("=======%s========\n", tip);
     printf("\n");
#endif
}

void printch(char ch)
{
     putchar(ch);
}

void printdec(int dec)
{
     if(dec==0)
     {
          return;
     }
     printdec(dec/10);
     printch( (char)(dec%10 + '0'));
}

void printflt(double flt)
{
     int tmpint = 0;

     tmpint = (int)flt;
     printdec(tmpint);
     printch('.');
     flt = flt - tmpint;
     tmpint = (int)(flt * 1000000);
     printdec(tmpint);
}

void printstr(char* str)
{
     while(*str)
     {
          printch(*str++);
     }
}

void printbin(int bin)
{
     if(bin == 0)
     {
          printstr("0b");
          return;
     }
     printbin(bin/2);
     printch( (char)(bin%2 + '0'));
}

void printhex(int hex)
{
     if(hex==0)
     {
          printstr("0x");
          return;
     }
     printhex(hex/16);
     if(hex < 10)
     {
          printch((char)(hex%16 + '0'));
     }
     else
     {
          printch((char)(hex%16 - 10 + 'a' ));
     }
}


void Myprint(char* fmt, ...)
{
     double vargflt = 0;
     int  vargint = 0;
     char* vargpch = NULL;
     char vargch = 0;
     char* pfmt = NULL;
     va_list vp;

     va_start(vp, fmt);
     pfmt = fmt;

     while(*pfmt)
     {
          if(*pfmt == '%')
          {
               switch(*(++pfmt))
               {

                    case 'c':
                         vargch = va_arg(vp, int);
                         printch(vargch);
                         break;
                    case 'd':
                    case 'i':
                         vargint = va_arg(vp, int);
                         printdec(vargint);
                         break;
                    case 'f':
                         vargflt = va_arg(vp, double);
                         printflt(vargflt);
                         break;
                    case 's':
                         vargpch = va_arg(vp, char*);
                         printstr(vargpch);
                         break;
                    case 'b':
                    case 'B':
                         vargint = va_arg(vp, int);
                         printbin(vargint);
                         break;
                    case 'x':
                    case 'X':
                         vargint = va_arg(vp, int);
                         printhex(vargint);
                         break;
                    case '%':
                         printch('%');
                         break;
                    default:
                         break;
               }
               pfmt++;
          }
          else
          {
               printch(*pfmt++);
          }
     }
     va_end(vp);
}