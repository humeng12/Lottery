//
//  printLog.h
//  merchant
//
//  Created by HRT on 15/6/23.
//  Copyright (c) 2015年 Hrtpayment. All rights reserved.
//

#ifndef merchant_printLog_h
#define merchant_printLog_h

//#define PRINTLOG

#ifdef PRINTLOG
#define Print(fmt, args...) Myprint(fmt, ##args)
#else
#define Print(fmt, args...)
#endif

void Myprint(char* fmt, ...);


/**
 *  @brief  以十六进制的形式打印缓冲区中的指定个数位
 *
 *  @param tip   提示信息，ASCII串 以0x00结束
 *  @param buff  要打印内容的缓冲区指针
 *  @param bytes 要打印的缓冲区的字节数
 */
void print_hex(char * tip,unsigned char* buff,int bytes);

#endif
