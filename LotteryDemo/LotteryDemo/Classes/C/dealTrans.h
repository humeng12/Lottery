//
//  dealTrans.h
//  POSsys
//
//  Created by MAC on 14-10-11.
//  Copyright (c) 2014年 MAC. All rights reserved.
//

#ifndef POSsys_dealTrans_h
#define POSsys_dealTrans_h

#include "baoWenStruct.h"

/*
报文 ：  报文长度 + TPDU + 版本号 + 消息类型 + 位图 + 根据位图组的数据 
 */

int d73cb60c11af1afd8036426d1673296d(char *szSendMess);//73dcb60c11af1afd8036426d1673296d  iPerformReversal

int d6134ca9a8a36d99e3fd09dd057f88c2 (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize);//6134dca9a8a36d99e3fd09dd057f88c2   iFormLogonISOMsgGenerateMAC

//消费
int a9a2689f68769581dccfb7484ea1a9e6 (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize);//9aa2689f68769581dccfb7484ea1a9e6  iFormSALEISOMsg
int iParseSALEISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int pi_ISOMsgSize);
int iValidateISOMsg( T_TRANS_OBJECT *psrTxnObject, unsigned char *sz_RcvMsg, int i_iRcvMsgSize, unsigned char *sz_SendMsg, int i_iSendMsgSize );
int iFormSALERVSISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize);


//撤销
int iFormVOIDSALEISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize);
int iParseVOIDSALEISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int i_ISOMsgSize);

int iFormVOIDRVSISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize);


//查余额
int iFormBalanceISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize);
int iParseBalanceISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int i_ISOMsgSize);


//非接
int iFormRapidConsumpte (T_TRANS_OBJECT *psrTxnObject,unsigned char *psz_ISOMsg, int *pi_ISOMsgSize);

//组MAC数据
int iFormBalanceMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg);
int iFormBalanceBackMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg);

int iFormSALEMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg);
int iFormSALEBackMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg);


int iFormVOIDSALEMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg);
int iFormVOIDSALEBackMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg);

#endif
