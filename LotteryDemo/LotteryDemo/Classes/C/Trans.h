//
//  Trans.h
//  POSsys
//
//  Created by MAC on 14-10-11.
//  Copyright (c) 2014年 MAC. All rights reserved.
//

#ifndef POSsys_Trans_h
#define POSsys_Trans_h

typedef struct ISOField
{
    int iSize;		// Max Field Size
    int iLen;		// Field Header Len in Byte
    char cType;	// Field Type (A, AN, ANS, N, B, Z, etc)
    char cFixed;	// Field Fixed Length? ('Y' or 'N')
    char cPadPos;	// Padding Position ('L' or 'R')
    char cPadChar;	// Padding Character
} ISOField;

typedef struct ISOFieldRec
{
    char cFlag;		// 1 - On, 0 - Off
    char *pcVal;
    int iLen;
} ISOFieldRec;

int iPackLenInRequestPacket (int i_iMode, unsigned char *io_puszReqBuf,int *io_puiReqLen);

/**
 *  @brief 把各域的标识 cFlag 置 0
 */
unsigned long	ulResetAllFields (void);
/**
 *  @brief 把TPDU  保存 到 临时 的 g_acTPDU  g_acMTI
 */
unsigned long	ulSetTPDU (char *p_pcInput, int p_iLen);
/**
 *  @brief 把消息类型  保存 到 临时 的 g_acMTI
 */
unsigned long	ulSetMTI (char *p_pcInput, int p_iLen);
/**
 *  @brief 把个域的值  保存 到 临时 的 Buf
 */
unsigned long  ulSetField (int p_iIdx, char *p_pcInput, int p_iLen);
/**
 *  @brief 计算位图
 */
unsigned long	ulGenBitmap (unsigned char *p_pucBitmap, int *p_piLen);

/**
 *  @brief 组报文
 */
unsigned long	ulForm (unsigned char *p_pucOutput, int *p_piLen, char *p_pcErrMsg);
/**
 *  @brief 根据各域的限制条件得到对应各域要求的数据
 */
unsigned long	ulFormField (int p_iFieldIdx, char *p_pcVal, int p_iLen, unsigned char *p_pucBuf, int *p_piIdx, char *p_pcErrMsg);
unsigned long	ulExtractField (int p_iID, unsigned char *p_pucInput, int p_iLen, int *p_piIdx, char *p_pcOutput, char *p_pcErrMsg, int *o_iLen);

unsigned long	ulGetTPDU (char *p_pcOutput, int *p_piLen);

unsigned long	ulGetMTI (char *p_pcOutput, int *p_piLen);

unsigned long	ulGetField (int p_iIdx, char *p_pcOutput, int *p_piLen);
/**
 *  @brief 解析报文
 */
unsigned long	ulParse (unsigned char *p_pucInput, int p_iLen, char *p_pcErrMsg);

long lStr2Long( char *i_pszStr );

/**
 *  @brief 把保存报文各域信息清空
 */
void initStruct();
/*********************************/
#endif
