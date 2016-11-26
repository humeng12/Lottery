//
//  dealTrans.c
//  POSsys
//
//  Created by MAC on 14-10-11.
//  Copyright (c) 2014年 MAC. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "dealTrans.h"
#include "Trans.h"
#include <stdlib.h>
#include "PublicMethod.h"
#include "printLog.h"
#include "connect.h"

//签到
int d6134ca9a8a36d99e3fd09dd057f88c2 (T_TRANS_OBJECT *psrTxnObject,unsigned char *psz_ISOMsg, int *pi_ISOMsgSize)
{
     unsigned long iRetVal = 0;
     char acErrMsg[50];

     ulResetAllFields();

     char szMTI[4+1];
     char szProcCode[6+1];
     char szNII[3+1];
     char szField61[FLD_61_SIZE +1];
     char szField11[6+1];
     memset(szMTI,0,sizeof(szMTI));
     memset(szProcCode,0,sizeof(szProcCode));
     memset(szNII,0,sizeof(szNII));
     memset(szField61,0,sizeof(szField61));
     memset(szField11,0,sizeof(szField11));

     strcpy(szMTI,"0800");
     //3
     strcpy(szProcCode,"990000");

     //24
     strcpy(szNII,"009");


     //11
     TransToString(psrTxnObject->lSTAN,szField11,6);

     iRetVal = ulSetTPDU ((char *)psrTxnObject->szTPDU, CTPDU_SIZE);
     if (0 != iRetVal) goto errHandler;

     iRetVal = ulSetMTI (szMTI, CMTI_SIZE);
     if (0 != iRetVal) goto errHandler;


     //----------------------
     // Set field 3
     //----------------------
     iRetVal = ulSetField (3, szProcCode, PROC_CODE_SIZE);
     if (0 != iRetVal) goto errHandler;

     //-----------------------
     // Set field 11
     //-----------------------
     iRetVal = ulSetField (11,szField11, STAN_SIZE);
     if (0 != iRetVal) goto errHandler;

     //------------------------
     // Set field 24
     //------------------------
     iRetVal = ulSetField (24, szNII, NII_SIZE);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 41
     //------------------------------
     iRetVal = ulSetField (41,(char *)psrTxnObject->szTID, (int)strlen((const char *)psrTxnObject->szTID));
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 42
     //------------------------------
     iRetVal = ulSetField (42,(char *)psrTxnObject->szMID, (int)strlen((const char *)psrTxnObject->szMID));
     if (0 != iRetVal) goto errHandler;

     //--------------------------------
     // Set field 61
     //--------------------------------
     FIELD61(psrTxnObject->lBatchNum,"001",szField61);
     iRetVal = ulSetField (61, szField61, (int)strlen(szField61));
     if (0 != iRetVal) goto errHandler;

     iRetVal = ulForm (psz_ISOMsg, pi_ISOMsgSize, acErrMsg);
     if (0 != iRetVal) goto errHandler;

     iRetVal = 0;

errHandler:

     if (0 != iRetVal)
     {
          iRetVal = -1;
     }

     return ((int)iRetVal);;
}


//组消费报文
int a9a2689f68769581dccfb7484ea1a9e6 (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize)
{
     unsigned long  iRetVal = 0;
     char szMTI[CMTI_SIZE + 1];
     char szProcCode[PROC_CODE_SIZE + 1];
     char szPOSCon[POS_CON_SIZE + 1];
     char szFld61Buf[FLD61_SIZE + 1];
     char acErrMsg[50];
     char szTxnAmt[12+1];
     char szField11[6+1];
     unsigned char Field52[8+1];
     unsigned char Field55[256+1];

     char szNII[NII_SIZE + 1];

     initStruct();

     //--------Must Reset-------
     ulResetAllFields();

     //memset and do the default padding char
     memset (szMTI, 0,sizeof(szMTI));
     memset (szProcCode, 0,sizeof(szProcCode));

     memset (szPOSCon, 0,sizeof(szPOSCon));
     memset (szFld61Buf, 0, sizeof(szFld61Buf));
     memset(szTxnAmt,0,sizeof(szTxnAmt));
     memset(szField11,0,sizeof(szField11));
     memset(Field52,0,sizeof(Field52));
     memset(Field55,0,sizeof(Field55));

     iRetVal = ulSetTPDU ((char *)psrTxnObject->szTPDU, CTPDU_SIZE);
     if (0 != iRetVal) goto errHandler;

     //MTI 消息类型标识
     strcpy (szMTI,"0200");
     iRetVal = ulSetMTI (szMTI, CMTI_SIZE);
     if (0 != iRetVal) goto errHandler;

     //--------------------
     // Set field 2 卡号
     //--------------------
     iRetVal = ulSetField (2,(char *)psrTxnObject->szPAN,(int)strlen((const char *)psrTxnObject->szPAN));
     if (0 != iRetVal) goto errHandler;    Print("szPAN=%s\n", psrTxnObject->szPAN);

     //----------------------
     // Set field 3 交易处理码
     //----------------------
     strcpy(szProcCode,"000000");
     iRetVal=ulSetField(3,szProcCode,6);
     if (0 != iRetVal) goto errHandler; Print("szProcCode=%s\n", szProcCode);


     //----------------------
     // Set field 4 消费金额
     //----------------------
     STRINGNBULING(psrTxnObject->lTxnAmt,szTxnAmt,12);
     iRetVal = ulSetField (4,szTxnAmt,12);
     if (0 != iRetVal) goto errHandler;Print("szTxnAmt=%s\n", szTxnAmt);

     //-----------------------
     // Set field 11 流水号
     //-----------------------
     STRINGNBULING(psrTxnObject->lSTAN,szField11,6);
     iRetVal = ulSetField (11,szField11, STAN_SIZE);
     if (0 != iRetVal) goto errHandler;Print("szField11=%s\n", szField11);

     //-----------------------
     // Set field 14 卡有效期
     //-----------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          iRetVal = ulSetField (14,(char *)psrTxnObject->carddate,4);
          if (0 != iRetVal) goto errHandler;Print("carddate=%s\n", psrTxnObject->carddate);
     }

     //------------------------
     // Set field 22 获取卡号和密码的方式
     //------------------------
     iRetVal = ulSetField (22,(char *)psrTxnObject->szPOSEntryMode, POS_EM_SIZE);
     if (0 != iRetVal) goto errHandler;Print("szPOSEntryMode=%s\n", psrTxnObject->szPOSEntryMode);


     //------------------------
     // Set field 23 IC卡序列号
     //------------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          if(strcmp((const char *)psrTxnObject->cardnum,"010")<0)
          {
               iRetVal=ulSetField(23,(char *)psrTxnObject->cardnum,3);Print("cardnum=%s\n", psrTxnObject->cardnum);
               if (0 != iRetVal) goto errHandler;
          }
     }

     //------------------------
     // Set field 24 国际网络标识
     //------------------------
     strcpy (szNII, "008");
     iRetVal = ulSetField (24, szNII, NII_SIZE);Print("szNII=%s\n", szNII);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 25 通过POS交易
     //------------------------------
     strcpy (szPOSCon, "14");
     iRetVal = ulSetField (25, szPOSCon, POS_CON_SIZE);Print("szPOSCon=%s\n", szPOSCon);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 35    二磁道数据
     //------------------------------
     iRetVal = ulSetField (35,(char *)psrTxnObject->szTrack2, (int)strlen((const char *)psrTxnObject->szTrack2));
     if (0 != iRetVal) goto errHandler;Print("szTrack2=%s\n", psrTxnObject->szTrack2);

     //------------------------------
     // Set field 41   POS终端编号
     //------------------------------
     iRetVal = ulSetField (41, (char *)psrTxnObject->szTID,8);Print("szTID=%s\n", psrTxnObject->szTID);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 42   商户编号
     //------------------------------
     iRetVal = ulSetField (42, (char *)psrTxnObject->szMID,15);Print("szMID=%s\n", psrTxnObject->szMID);
     if (0 != iRetVal) goto errHandler;


     //-----------------------------
     // Set field 49   货币编号
     //-----------------------------
     iRetVal = ulSetField (49,(char *)psrTxnObject->currency,3);Print("currency=%s\n", psrTxnObject->currency);
     if (0 != iRetVal) goto errHandler;



     //-----------------------------
     // Set field 46    持卡人姓名
     //-----------------------------
     if(strlen(psrTxnObject->cardHolderName)>1)
     {
          iRetVal=ulSetField(46,(char *)psrTxnObject->cardHolderName,(int)strlen(psrTxnObject->cardHolderName));Print("cardHolderName=%s\n", psrTxnObject->cardHolderName);
          if(0 != iRetVal) goto errHandler;
     }


     //-----------------------------
     // Set field 52   卡密码
     //-----------------------------
     if(strlen((const char *)psrTxnObject->password)>1)
     {
          int length=0;
          iHexToByte1((char *)psrTxnObject->password,Field52,&length);
          iRetVal=ulSetField(52,(char *)Field52,length);Print("password=%s\n", Field52);
          if (0 != iRetVal) goto errHandler;
     }


     //--------------------------------
     // Set field 55 IC卡55域数据
     //--------------------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          int length=0;
          unsigned char sendField55[256+1];
          memset(sendField55,0,sizeof(sendField55));
          iHexToByte1((char *)psrTxnObject->ICinfo,sendField55,&length);
          iRetVal = ulSetField (55,(char *)sendField55,length);Print("sendField55=%s\n", sendField55);
          if (0 != iRetVal) goto errHandler;
     }

     //-----------------------------
     // Set field 61 自定义域：批次号、操作员号、查询号
     //-----------------------------
     memset(szFld61Buf, 0, sizeof(szFld61Buf));
     TransToString61(psrTxnObject->lBatchNum,"001",psrTxnObject->lChayNum,szFld61Buf);
     iRetVal = ulSetField (61, szFld61Buf, (int)strlen(szFld61Buf));Print("szFld61Buf=%s\n", szFld61Buf);
     if (0 != iRetVal) goto errHandler;


    //-----------------------------
    // Set field 64 MAC
    //-----------------------------
     unsigned char szMacBuf[9];
     memset(szMacBuf,0,sizeof(szMacBuf));
     int len;
     iHexToByte1((char *)psrTxnObject->szMACBlock,szMacBuf,&len);
     iRetVal = ulSetField (64,"88888888",8);
     if (0 != iRetVal) goto errHandler;


     iRetVal = ulForm (psz_ISOMsg, pi_ISOMsgSize, acErrMsg);
     if (0 != iRetVal) goto errHandler;
    

     initStruct();
     
     iRetVal = 0;
     
errHandler:
     initStruct();
     if (0 != iRetVal)
     {
          iRetVal = -1;
          Print("Msg form err!\n");
     }
     return ((int)iRetVal);
}

//解析消费报文
int iParseSALEISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int pi_ISOMsgSize)
{
     unsigned char	pTPDU[CTPDU_SIZE+1];
     unsigned char	pMTI[CMTI_SIZE+1];
     T_TRANS_OBJECT	srTxn;
     char			szSTAN[STAN_SIZE + 1];
     char			szTID[TID_SIZE + 1];
     char			szMID[MID_SIZE + 1];
     char			szError[100];
     int			iFieldLen = 0;
     long			lRetVal = 0;
     char			szAmt[ LEN_AMOUNT+1 ];
     char			szAmt2[ LEN_AMOUNT+1 ];
     char			szField32[11 + 1];
     char			szField44[FLD44_SIZE + 1];
     char			szField53[FLD53_SIZE + 1];
     char            szField10[LEN_AMOUNT +1];
     char			szField64[FLD64_SIZE + 1];
     char			szField63[250 + 1];
     char			szField61[200 + 1];
     int			iField61Len = 0;
     char			szField9[LEN_AMOUNT + 1];
     char			szPAN[PAN_SIZE+1];
     char           szField3[6+1];
     char           szField4[12+1];
     char           szField49[4+1];

     ulResetAllFields(); //Must reset


     memset (pTPDU, 0, sizeof(pTPDU));
     memset (pMTI, 0, sizeof(pMTI));
     memset (&srTxn, 0, sizeof(T_TRANS_OBJECT));
     memset (szSTAN, 0, sizeof(szSTAN));
     memset (szTID, 0, sizeof(szTID));
     memset (szMID, 0, sizeof(szMID));
     memset (szError, 0, sizeof(szError));
     memset (szAmt, 0, sizeof(szAmt));
     memset (szAmt2, 0, sizeof(szAmt2));
     memset (szField32, 0, sizeof(szField32));
     memset (szField44, 0, sizeof(szField44));
     memset (szField53, 0, sizeof(szField53));
     memset (szField61, 0, sizeof(szField61));
     memset (szField10, 0, sizeof(szField10));
     memset (szField64, 0, sizeof(szField64));
     memset (szField63, 0, sizeof(szField63));
     memset (szField9, 0, sizeof(szField9));
     memset (szField49, 0, sizeof(szField49));

     lRetVal = ulParse (psz_ISOMsg,pi_ISOMsgSize, szError);
     if (lRetVal != 0) goto ErrHandler;

     lRetVal = ulGetTPDU ((char *)pTPDU, &iFieldLen);
     if (lRetVal != 0) goto ErrHandler;

     lRetVal = ulGetMTI ((char *)pMTI, &iFieldLen);
     if (lRetVal != 0) goto ErrHandler;

     memcpy (&srTxn, psrTxnObject, sizeof(T_TRANS_OBJECT));


     memset(szPAN, 0, sizeof(szPAN));
     lRetVal = ulGetField (2, szPAN, &iFieldLen);

     memset(szField3, 0, sizeof(szField3));
     lRetVal = ulGetField (3,(char *)szField3, &iFieldLen);
     strncpy(srTxn.szFiled3,szField3,6);

     memset(szField4, 0, sizeof(szField4));
     lRetVal = ulGetField (4,szField4, &iFieldLen);


     lRetVal = ulGetField (37, (char *)srTxn.szRRN, &iFieldLen);

     lRetVal = ulGetField (38, (char *)srTxn.szApprovalCode, &iFieldLen);

     lRetVal = ulGetField (39, (char *)srTxn.szRespCode, &iFieldLen);
     if (lRetVal != 0) goto ErrHandler;

     lRetVal = ulGetField (41, szTID, &iFieldLen);

     lRetVal = ulGetField (42, szMID, &iFieldLen);

     memset(szField49, 0, sizeof(szField49));
     lRetVal = ulGetField (49,(char *)srTxn.currency, &iFieldLen);


     lRetVal = ulGetField (53, szField53, &iFieldLen);

     memset(srTxn.szCardName, 0, sizeof(srTxn.szCardName));
     lRetVal = ulGetField (61, szField61, &iField61Len);

     if (iField61Len > 15)
     {
          memcpy(srTxn.szCardName, szField61 + 17, iField61Len - 17);
          srTxn.cardNameLength=iField61Len-17;
     }


     lRetVal = ulGetField (64,(char *)srTxn.szMACBlock64, &iFieldLen);

     lRetVal = ulGetField (11, szSTAN, &iFieldLen);
     strncpy(srTxn.szFiled11,szSTAN,iFieldLen);
     lRetVal = ulGetField (12, (char *)srTxn.szTxnTime, &iFieldLen);
     lRetVal = ulGetField (13, (char *)srTxn.szTxnDate, &iFieldLen);


     Print("==========消费接收报文各域值===========\n");
     Print("szPAN=%s\n",szPAN);
     Print("szSTAN=%s\n",szSTAN);
     Print("szField3=%s\n",szField3);
     Print("szField4=%s\n",srTxn.lTxnAmt);
     Print("szTxnTime=%s\n",srTxn.szTxnTime);
     Print("szTxnDate=%s\n",srTxn.szTxnDate);
     Print("szRRN=%s\n",srTxn.szRRN);
     Print("szApprovalCode=%s\n",srTxn.szApprovalCode);
     Print("szRespCode=%s\n",srTxn.szRespCode);
     Print("szField49=%s\n",srTxn.currency);
     Print("szTID=%s\n",szTID);
     Print("szMID=%s\n",szMID);
     Print("szField44=%s\n",szField44);
     Print("szField53=%s\n",szField53);
     Print("szField61=%s\n",szField61);
     Print("szField64=%s\n",srTxn.szMACBlock64);
     Print("srTxn.szCardName==%s\n",srTxn.szCardName);
     Print("==========消费接收报文各域值===========\n");
     memcpy (psrTxnObject, &srTxn, sizeof(T_TRANS_OBJECT));
     lRetVal = 0;
     
ErrHandler:
     
     memset (&srTxn, 0, sizeof(T_TRANS_OBJECT));
     return ((int)lRetVal);
     
}


//验证报文
int iValidateISOMsg( T_TRANS_OBJECT *psrTxnObject, unsigned char *sz_RcvMsg, int i_iRcvMsgSize, unsigned char *sz_SendMsg, int i_iSendMsgSize )
{
     int				iRet = 0;
     char			szSendSTAN[STAN_SIZE + 1];
     char			szSendMTI[CMTI_SIZE + 1];
     char			szSendTID[TID_SIZE + 1];
     char			szSendMID[MID_SIZE + 1];
     char			szSendMsg2[400];
     char			szRecvSTAN[STAN_SIZE + 1];
     char			szRecvMTI[CMTI_SIZE + 1];
     char			szRecvTID[TID_SIZE + 1];
     char			szRecvMID[MID_SIZE + 1];
     char			szField61MSG[200 + 1];
     char			szField62MSG[200 + 1];
     char			szError [100];
     long			lRetVal = 0 ;
     int				iFieldLen = 0;
     unsigned char	szErrMsg[NO_CARD_TXN_ERR_SIZE + 1];


     memset(szSendSTAN, 0, sizeof(szSendSTAN));
     memset(szSendMTI, 0, sizeof(szSendMTI));
     memset(szSendTID , 0, sizeof(szSendTID));
     memset(szSendMID, 0, sizeof(szSendMID));
     memset(szSendMsg2, 0, sizeof(szSendMsg2));
     memset(szRecvSTAN, 0, sizeof(szRecvSTAN));
     memset(szRecvMTI, 0, sizeof(szRecvMTI));
     memset(szRecvTID , 0, sizeof(szRecvTID));
     memset(szRecvMID, 0, sizeof(szRecvMID));
     memset(szField61MSG, 0, sizeof(szField61MSG));
     memset(szField62MSG, 0, sizeof(szField62MSG));
     memset(szError, 0, sizeof(szError));
     memset(szErrMsg, 0, sizeof(szErrMsg));


     ulResetAllFields();

     lRetVal = ulParse (sz_SendMsg, i_iSendMsgSize, szError);

     if (lRetVal != 0)
     {
          Print("MSG_VALIDATE_ISO_ERR111!\n");
          memset(psrTxnObject->szRespCode, 0, sizeof(psrTxnObject->szRespCode));
          iRet = -1;
          goto ErrHandler;
     }

     lRetVal = ulGetMTI(szSendMTI, &iFieldLen);
     lRetVal = ulGetField (11, szSendSTAN, &iFieldLen);
     lRetVal = ulGetField (41, szSendTID, &iFieldLen);
     lRetVal = ulGetField (42, szSendMID, &iFieldLen);



     ulResetAllFields();
     //Get the STAN and TID from rcv message
     lRetVal = ulParse (sz_RcvMsg, i_iRcvMsgSize, szError);
     if (lRetVal != 0)
     {
          Print("MSG_VALIDATE_ISO_ERR!\n");
          memset(psrTxnObject->szRespCode, 0, sizeof(psrTxnObject->szRespCode));
          iRet = 80007;
          goto ErrHandler;
     }

     lRetVal = ulGetMTI(szRecvMTI, &iFieldLen);
     lRetVal = ulGetField (11, szRecvSTAN, &iFieldLen);
     lRetVal = ulGetField (41, szRecvTID, &iFieldLen);
     lRetVal = ulGetField (42, szRecvMID, &iFieldLen);


     if (atoi(szSendMTI) != (atoi(szRecvMTI) - 10))
     {
          memset(psrTxnObject->szRespCode, 0, sizeof(psrTxnObject->szRespCode));
          iRet = -1;
          goto ErrHandler;
     }

     //Compare TID from send and receive message
     if (0 != memcmp(szRecvTID, szSendTID, TID_SIZE) )
     {
          Print("MSG_VALIDATE_TID_ERR!\n");
          memset(psrTxnObject->szRespCode, 0, sizeof(psrTxnObject->szRespCode));
          iRet = -1;
          goto ErrHandler;
     }



     //Check the field 39 ( Resp code )
     if( 0 != memcmp( "00", psrTxnObject->szRespCode, 2) )
     {
          iRet=-1;
          if (95 ==lStr2Long((char *)psrTxnObject->szRespCode))
          {
               iRet = 0;
               goto ErrHandler;
          }
          else if (25 ==lStr2Long((char *)psrTxnObject->szRespCode))
          {
               iRet = 0;
               goto ErrHandler;
          }
          else if (0 == memcmp(szSendMTI, "0400", 4) &&
                   (25 ==lStr2Long((char *)psrTxnObject->szRespCode) || 12 ==lStr2Long((char *)psrTxnObject->szRespCode)))
          {
               iRet = 0;
               goto ErrHandler;
          }

     }

ErrHandler:
     iFieldLen = 0;
     lRetVal = ulGetField (62, szField62MSG, &iFieldLen);
     if (0 != iFieldLen && (iRet != 0 || iRet == -1))
     {

     }

     if ( (0 == iRet) && ( 0 == memcmp( "00", psrTxnObject->szRespCode, 2) ) )
     {

     }

     return iRet;
}

//组撤销报文
int iFormVOIDSALEISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize)
{
     long iRetVal = 0;
     char szMTI[CMTI_SIZE + 1];
     char szProcCode[PROC_CODE_SIZE + 1];
     char szTxnAmt[12 + 1];
     char szSTAN[STAN_SIZE + 1];
     char szTxnDate[DATE_SIZE + 1];
     char szPOSEM[POS_EM_SIZE + 1];
     char szPOSCon[POS_CON_SIZE + 1];
     char szCVV2[CVV2_SIZE + 1];
     char szInvNum[INV_NUM_SIZE + 1];
     T_TRANS_OBJECT srTxn;
     char acErrMsg[50];
     char szFld44Buf[FLD44_SIZE + 1];
     char szFld49Buf[FLD49_SIZE + 1];
     char szFld53Buf[FLD53_SIZE + 1];
     char szFld61Buf[FLD61_SIZE + 1];
     char szFld62Buf[24 + 1];
     char szFld64Buf[FLD64_SIZE + 1];
     char szNII[NII_SIZE + 1];

     initStruct();
     ulResetAllFields();

     memset (szMTI, 0,sizeof(szMTI));
     memset (szProcCode, 0,sizeof(szProcCode));
     memset (szTxnAmt, 0,sizeof(szTxnAmt));
     memset (szSTAN, 0, sizeof(szSTAN));
     memset (szTxnDate, 0,sizeof(szTxnDate));
     memset (szPOSEM, 0,sizeof(szPOSEM));
     memset (szPOSCon, 0, sizeof(szPOSCon));
     memset (szInvNum, 0,sizeof(szInvNum));
     memset (szNII, 0,sizeof(szNII));
     memset (szCVV2, 0, sizeof(szCVV2));
     memset (szFld44Buf, 0, sizeof(szFld44Buf));
     memset (szFld49Buf, 0, sizeof(szFld49Buf));
     memset (szFld53Buf, 0, sizeof(szFld53Buf));
     memset (szFld61Buf, 0, sizeof(szFld61Buf));
     memset (szFld62Buf, 0, sizeof(szFld62Buf));
     memset (szFld64Buf, 0, sizeof(szFld64Buf));
     memcpy (&srTxn, psrTxnObject, sizeof(T_TRANS_OBJECT));


     //MTI
     strcpy(szMTI,"0200");

     //3
     strcpy(szProcCode,"200000");

     //4
     STRINGNBULING(srTxn.lOrgTxnAmt,szTxnAmt,12);

     //11
     STRINGNBULING(srTxn.lSTAN,szSTAN,6);


     //22
     strcpy(szPOSEM,(const char *)srTxn.szPOSEntryMode);

     //24
     strcpy((char *)szNII,"008");

     //25
     strcpy((char *)szPOSCon,"14");

     iRetVal = ulSetTPDU ((char *)srTxn.szTPDU, CTPDU_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     iRetVal = ulSetMTI (szMTI, CMTI_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //------------------
     // Set field 2 卡号
     //------------------
     iRetVal = ulSetField (2, (char *)srTxn.szPAN, (int)strlen((const char *)srTxn.szPAN));
     if (0 != iRetVal) goto ErrHandler;

     //------------------
     // Set field 3 交易处理码
     //------------------
     iRetVal = ulSetField (3, szProcCode, PROC_CODE_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //------------------
     // Set field 4 消费金额
     //------------------
     iRetVal = ulSetField (4, szTxnAmt,12);
     if (0 != iRetVal) goto ErrHandler;

     //-------------------
     // Set field 11 流水号
     //-------------------
     iRetVal = ulSetField (11, szSTAN, STAN_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //-----------------------
     // Set field 14 卡有效期
     //-----------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          iRetVal = ulSetField (14,(char *)psrTxnObject->carddate,4);
          if (0 != iRetVal) goto ErrHandler;
     }

     //---------------------
     // Set field 22 获取卡号和密码的方式
     //---------------------
     iRetVal = ulSetField (22, szPOSEM, POS_EM_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //------------------------
     // Set field 23c IC卡序列号
     //------------------------
     if(1==srTxn.TypeOfTxn)
     {
          if(strcmp((const char *)srTxn.cardnum,"010")<0)
          {
               iRetVal=ulSetField(23,(char *)srTxn.cardnum,3);
               if (0 != iRetVal) goto ErrHandler;
          }
     }


     //------------------------
     // Set field 24 国际网络标识码
     //------------------------
     iRetVal = ulSetField (24, szNII, NII_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //---------------------
     // Set field 25 POS交易
     //---------------------
     iRetVal = ulSetField (25, szPOSCon, POS_CON_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //---------------------
     // Set field 35 二磁道数据
     //---------------------
     iRetVal = ulSetField (35, (char *)srTxn.szTrack2, (int)strlen((const char *)srTxn.szTrack2));
     if (0 != iRetVal) goto ErrHandler;
     
     //---------------------
     // Set field 38 授权码
     //---------------------
     if (strlen((const char *)srTxn.szOrgApprovalCode)!=0)
     {
          iRetVal = ulSetField (38,(char *)srTxn.szOrgApprovalCode, APPR_CODE_SIZE);
          if (0 != iRetVal) goto ErrHandler;
     }

     //---------------------
     // Set field 41 POS终端编号
     //---------------------
     iRetVal = ulSetField (41, (char *)srTxn.szTID,8);
     if (0 != iRetVal) goto ErrHandler;

     //---------------------
     // Set field 42 商户编号
     //---------------------
     iRetVal = ulSetField (42, (char *)srTxn.szMID,15);
     if (0 != iRetVal) goto ErrHandler;


     //---------------------
     // Set field 46
     //---------------------
//     if(strlen(srTxn.cardHolderName)>1)
//     {
//          iRetVal = ulSetField (46, (char *)srTxn.cardHolderName,(int)strlen(srTxn.cardHolderName));
//          if (0 != iRetVal) goto ErrHandler;
//     }

     //-----------------------------
     // Set field 49 货币编号
     //-----------------------------
     iRetVal = ulSetField (49,(char *)srTxn.currency,3);
     if (0 != iRetVal) goto ErrHandler;


     //-----------------------------
     // Set field 52 卡密码
     //-----------------------------

     if(strlen((const char *)srTxn.password)>1)
     {
          int length=0;
          unsigned char Field52[8+1];
          memset(Field52,0,sizeof(Field52));
          iHexToByte1((char *)srTxn.password,Field52,&length);
          iRetVal=ulSetField(52,(char *)Field52,length);
          if (0 != iRetVal) goto ErrHandler;
     }


     //-----------------------------
     // Set field 61 自定义域：批次号、操作员号、查询号
     //-----------------------------
     memset(szFld61Buf, 0, sizeof(szFld61Buf));
     TransToString61(srTxn.lBatchNum,"001",srTxn.lChayNum,szFld61Buf);
     iRetVal = ulSetField (61, szFld61Buf, (int)strlen(szFld61Buf));
     if (0 != iRetVal) goto ErrHandler;


     //--------------------------------
     // Set field 62 交易日期和时间
     //--------------------------------
     memcpy(szTxnDate, srTxn.szOrgTxnDate, 4);
     TransToStringVoid(szMTI,srTxn.lOrgSTAN,szTxnDate,(char *)srTxn.szOrgTxnTime,szFld62Buf);
     iRetVal = ulSetField (62, szFld62Buf, 20);
     if (0 != iRetVal) goto ErrHandler;

    //--------------------------------
    // Set field 64 MAC：信息校验码
    //--------------------------------
     unsigned char szMacBuf[9];
     memset(szMacBuf,0,sizeof(szMacBuf));
     int len;
     iHexToByte1((char *)srTxn.szMACBlock,szMacBuf,&len);
     iRetVal = ulSetField (64,"88888888",8);
     if (0 != iRetVal) goto ErrHandler;

     Print("===============撤销报文各域值===============\n");
     Print("szPAN=%s\n",srTxn.szPAN);
     Print("szProcCode=%s\n",szProcCode);
     Print("szTxnAmt=%s\n",szTxnAmt);
     Print("szSTAN=%s\n",szSTAN);
     Print("szPOSEM=%s\n",szPOSEM);
     Print("szNII=%s\n",szNII);
     Print("szPOSCon=%s\n",szPOSCon);
     Print("srTxn.szTrack2=%s\n",srTxn.szTrack2);
     Print("srTxn.szOrgRRN=%s\n",srTxn.szOrgRRN);
     Print("srTxn.szApprovalCode=%s\n",srTxn.szApprovalCode);
     Print("srTxn.password=%s\n",srTxn.password);
     Print("szFld61Buf=%s\n",szFld61Buf);
     Print("szFld62Buf=%s\n",szFld62Buf);
     Print("===============撤销报文各域值===============\n");

     iRetVal = ulForm (psz_ISOMsg, pi_ISOMsgSize, acErrMsg);
     if (0 != iRetVal)
     {
          goto ErrHandler;
     }

     iRetVal = 0;

     memcpy (psrTxnObject, &srTxn, sizeof(T_TRANS_OBJECT));

ErrHandler:

     if (0 != iRetVal)
     {
          iRetVal = -1;
     }

     return ((int)iRetVal);
}

//解析撤销报文
int iParseVOIDSALEISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int i_ISOMsgSize)
{
     unsigned char	pTPDU[CTPDU_SIZE+1];
     unsigned char	pMTI[CMTI_SIZE+1];
     T_TRANS_OBJECT	srTxn;
     char			szSTAN[STAN_SIZE + 1];
     char			szTID[TID_SIZE + 1];
     char			szMID[MID_SIZE + 1];
     char			szError[100];
     int				iFieldLen = 0;
     long			lRetVal = 0;
     char			szField32[11 + 1];
     char			szField44[FLD44_SIZE + 1];
     char			szField53[FLD53_SIZE + 1];
     char            szField10[LEN_AMOUNT +1];
     char			szField61[200 + 1];
     char			szField63[250 + 1];
     char			szField64[FLD64_SIZE + 1];
     int				iField61Len = 0;
     char			szAmt[LEN_AMOUNT + 1];
     char			szField9[LEN_AMOUNT + 1];
     char			szField49[FLD49_SIZE + 1];
     char			szPAN[PAN_SIZE+1];
     char           szField3[6+1];

     //Must reset
     ulResetAllFields();

     memset (pTPDU, 0, sizeof(pTPDU));
     memset (pMTI, 0, sizeof(pMTI));
     memset (&srTxn, 0, sizeof(T_TRANS_OBJECT));
     memset (szSTAN, 0, sizeof(szSTAN));
     memset (szTID, 0, sizeof(szTID));
     memset (szMID, 0, sizeof(szMID));
     memset (szError, 0, sizeof(szError));
     memset(szField32, 0, sizeof(szField32));
     memset (szField44, 0, sizeof(szField44));
     memset(szField53, 0, sizeof(szField53));
     memset(szField61, 0, sizeof(szField61));
     memset(szField10, 0, sizeof(szField10));
     memset(szField63, 0, sizeof(szField63));
     memset(szField64, 0, sizeof(szField64));
     memset(szAmt, 0, sizeof(szAmt));
     memset(szField9, 0, sizeof(szField9));
     memset(szField49, 0, sizeof(szField49));
     memset(szField3,0,sizeof(szField3));


     lRetVal = ulParse (psz_ISOMsg, i_ISOMsgSize, szError);
     if (lRetVal != 0)
     {
          goto ErrHandler;
     }

     lRetVal = ulGetTPDU ((char *)pTPDU, &iFieldLen);
     if (lRetVal != 0)
     {
          goto ErrHandler;
     }

     lRetVal = ulGetMTI ((char *)pMTI, &iFieldLen);
     if (lRetVal != 0)
     {
          goto ErrHandler;
     }

     memcpy (&srTxn, psrTxnObject, sizeof(T_TRANS_OBJECT));

     memset(szPAN, 0, sizeof(szPAN));
     lRetVal = ulGetField (2, szPAN, &iFieldLen);

     lRetVal = ulGetField (3,szField3, &iFieldLen);
     strncat(srTxn.szFiled3,szField3,6);

     lRetVal = ulGetField (37, (char *)srTxn.szOrgRRN, &iFieldLen);

     lRetVal = ulGetField (38, (char *)srTxn.szApprovalCode, &iFieldLen);

     lRetVal = ulGetField (39, (char *)srTxn.szRespCode, &iFieldLen);
     if (lRetVal != 0) goto ErrHandler;

     lRetVal = ulGetField (41, szTID, &iFieldLen);

     lRetVal = ulGetField (42, szMID, &iFieldLen);

     lRetVal = ulGetField (11, szSTAN, &iFieldLen);
     strncpy(srTxn.szFiled11,szSTAN,iFieldLen);
     lRetVal = ulGetField (12, (char *)srTxn.szOrgTxnTime, &iFieldLen);
     lRetVal = ulGetField (13, (char *)srTxn.szOrgTxnDate, &iFieldLen);



     lRetVal = ulGetField (53, szField53, &iFieldLen);
     memset(srTxn.szCardName, 0, sizeof(srTxn.szCardName));
     lRetVal = ulGetField (61, szField61, &iField61Len);

     if (iField61Len > 15)
     {
          memcpy(srTxn.szCardName, szField61 + 17, iField61Len - 17);
          srTxn.cardNameLength=iField61Len-17;
     }


     lRetVal = ulGetField (64,(char *)srTxn.szMACBlock64, &iFieldLen);

     Print("==========消费接111收报文各域值===========\n");
     Print("szPAN=%s\n",szPAN);
     Print("szSTAN=%s\n",szSTAN);
     Print("szTxnTime=%s\n",srTxn.szOrgTxnTime);
     Print("szTxnDate=%s\n",srTxn.szOrgTxnDate);
     Print("szRRN=%s\n",srTxn.szRRN);
     Print("szApprovalCode=%s\n",srTxn.szApprovalCode);
     Print("szRespCode=%s\n",srTxn.szRespCode);
     Print("szTID=%s\n",szTID);
     Print("szMID=%s\n",szMID);
     Print("szField44=%s\n",szField44);
     Print("szField53=%s\n",szField53);
     Print("szField61=%s\n",szField61);
     Print("szField64=%s\n",srTxn.szMACBlock64);
     Print("srTxn.szCardName==%s\n",srTxn.szCardName);
     Print("==========消费接收报文各域值===========\n");

     memcpy (psrTxnObject, &srTxn, sizeof(T_TRANS_OBJECT));
     lRetVal = 0;

ErrHandler:

     memset (&srTxn, 0, sizeof(T_TRANS_OBJECT));
     
     if( 0 < lRetVal )
     {
          lRetVal = -1;
     }
     return ((int)lRetVal);
}

int iFormVOIDRVSISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize)
{
     long iRetVal = 0;
     char szMTI[CMTI_SIZE + 1];
     char szProcCode[PROC_CODE_SIZE + 1];
     char szTxnAmt[12 + 1];
     char szSTAN[STAN_SIZE + 1];
     char szTxnDate[DATE_SIZE + 1];
     char szPOSEM[POS_EM_SIZE + 1];
     char szPOSCon[POS_CON_SIZE + 1];
     char szCVV2[CVV2_SIZE + 1];
     char szInvNum[INV_NUM_SIZE + 1];
     T_TRANS_OBJECT srTxn;
     char acErrMsg[50];
     char szFld44Buf[FLD44_SIZE + 1];
     char szFld49Buf[FLD49_SIZE + 1];
     char szFld53Buf[FLD53_SIZE + 1];
     char szFld61Buf[FLD61_SIZE + 1];
     char szFld62Buf[24 + 1];
     char szFld64Buf[FLD64_SIZE + 1];
     char szNII[NII_SIZE + 1];


     ulResetAllFields();//Must reset

     memset (szMTI, 0, sizeof(szMTI));
     memset (szProcCode, 0,sizeof(szProcCode));
     memset (szTxnAmt, 0,sizeof(szTxnAmt));
     memset (szSTAN, 0, sizeof(szSTAN));
     memset (szTxnDate, 0, sizeof(szTxnDate));
     memset (szPOSEM, 0, sizeof(szPOSEM));
     memset (szPOSCon, 0, sizeof(szPOSCon));
     memset (szInvNum, 0,sizeof(szInvNum));
     memset (szNII, 0, sizeof(szNII));
     memset (szCVV2, 0, sizeof(szCVV2));
     memset (szFld44Buf, 0, sizeof(szFld44Buf));
     memset (szFld49Buf, 0, sizeof(szFld49Buf));
     memset (szFld53Buf, 0, sizeof(szFld53Buf));
     memset (szFld61Buf, 0, sizeof(szFld61Buf));
     memset (szFld62Buf, 0, sizeof(szFld62Buf));
     memset (szFld64Buf, 0, sizeof(szFld64Buf));
     memcpy (&srTxn, psrTxnObject, sizeof(T_TRANS_OBJECT));


     //MTI
     strcpy(szMTI, "0400");

     //3
     strcpy(szProcCode,"200000");

     //4
     STRINGNBULING(srTxn.lOrgTxnAmt,szTxnAmt,12);


     //11
     STRINGNBULING(srTxn.lRevSTAN,szSTAN,6);

     //22
     strcpy(szPOSEM,(char *)srTxn.szPOSEntryMode);

     //24
     strcpy((char *)szNII,"008");

     //25
     strcpy((char *)szPOSCon,"14");


     //------------------
     // Set field 2
     //------------------
     iRetVal = ulSetField (2, (char *)srTxn.szPAN, (int)strlen((const char *)srTxn.szPAN));
     if (0 != iRetVal) goto ErrHandler;

     //------------------
     // Set field 3
     //------------------
     iRetVal = ulSetField (3, szProcCode, PROC_CODE_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //------------------
     // Set field 4
     //------------------
     iRetVal = ulSetField (4, szTxnAmt,12);
     if (0 != iRetVal) goto ErrHandler;

     //-------------------
     // Set field 11
     //-------------------
     iRetVal = ulSetField (11, szSTAN, STAN_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //-----------------------
     // Set field 14 IC
     //-----------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          iRetVal = ulSetField (14,(char *)psrTxnObject->carddate,4);
          if (0 != iRetVal) goto ErrHandler;
     }

     //---------------------
     // Set field 22
     //---------------------
     iRetVal = ulSetField (22, szPOSEM, POS_EM_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //------------------------
     // Set field 23c IC
     //------------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          if(strcmp((char *)psrTxnObject->cardnum,"010")<0)
          {
               iRetVal=ulSetField(23,(char *)psrTxnObject->cardnum,3);
               if (0 != iRetVal) goto ErrHandler;
          }
     }


     //------------------------
     // Set field 24
     //------------------------
     iRetVal = ulSetField (24, szNII, NII_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //---------------------
     // Set field 25
     //---------------------
     iRetVal = ulSetField (25, szPOSCon, POS_CON_SIZE);
     if (0 != iRetVal) goto ErrHandler;

     //---------------------
     // Set field 35
     //---------------------
     iRetVal = ulSetField (35, (char *)srTxn.szTrack2, (int)strlen((char *)srTxn.szTrack2));
     if (0 != iRetVal) goto ErrHandler;

     //---------------------
     // Set field 38
     //---------------------
     if (strlen((char *)srTxn.szOrgApprovalCode)!=0)
     {
          iRetVal = ulSetField (38,(char *)srTxn.szOrgApprovalCode, APPR_CODE_SIZE);
          if (0 != iRetVal) goto ErrHandler;
     }

     //---------------------
     // Set field 41
     //---------------------
     iRetVal = ulSetField (41, (char *)srTxn.szTID,8);
     if (0 != iRetVal) goto ErrHandler;

     //---------------------
     // Set field 42
     //---------------------
     iRetVal = ulSetField (42, (char *)srTxn.szMID,15);
     if (0 != iRetVal) goto ErrHandler;

     //-----------------------------
     // Set field 49
     //-----------------------------
     iRetVal = ulSetField (49,(char *)srTxn.currency,3);
     if (0 != iRetVal) goto ErrHandler;


     //-----------------------------
     // Set field 52
     //-----------------------------

     if(strlen((char *)srTxn.password)>1)
     {
          int length=0;
          unsigned char Field52[8+1];
          memset(Field52,0,sizeof(Field52));
          iHexToByte1((char *)srTxn.password,Field52,&length);
          iRetVal=ulSetField(52,(char *)Field52,length);
          if (0 != iRetVal) goto ErrHandler;
     }


     //-----------------------------
     // Set field 61
     //-----------------------------
     memset(szFld61Buf, 0, sizeof(szFld61Buf));
     //sprintf((char*)szFld61Buf, "%06s%03s%06s",srTxn.lBatchNum,"001",srTxn.lChayNum);
     TransToString61(srTxn.lBatchNum,"001",srTxn.lChayNum,szFld61Buf);
     iRetVal = ulSetField (61, szFld61Buf, (int)strlen(szFld61Buf));
     if (0 != iRetVal) goto ErrHandler;


     //--------------------------------
     // Set field 62
     //--------------------------------
     memcpy(szTxnDate, srTxn.szOrgTxnDate, 4);
     //sprintf((char*)szFld62Buf, "%s%06s%s%s","0400",srTxn.lOrgSTAN, szTxnDate, srTxn.szOrgTxnTime);
     TransToStringVoid("0400",srTxn.lOrgSTAN,szTxnDate,(char *)srTxn.szOrgTxnTime,szFld62Buf);
     iRetVal = ulSetField (62, szFld62Buf, 20);


     unsigned char szMacBuf[9];
     memset(szMacBuf,0,sizeof(szMacBuf));
     int len;
     iHexToByte1((char *)srTxn.szMACBlock1,szMacBuf,&len);
     iRetVal = ulSetField (64,"88888888",8);
     if (0 != iRetVal) goto ErrHandler;


     Print("============撤销冲正报文各域值==================\n");
     Print("szPAN=%s\n",srTxn.szPAN);
     Print("szProcCode=%s\n",szProcCode);
     Print("szTxnAmt=%s\n",szTxnAmt);
     Print("szSTAN=%s\n",szSTAN);
     Print("szPOSEM=%s\n",szPOSEM);
     Print("szNII=%s\n",szNII);
     Print("szPOSCon=%s\n",szPOSCon);
     Print("srTxn.szTrack2=%s\n",srTxn.szTrack2);
     Print("srTxn.szOrgRRN=%s\n",srTxn.szOrgRRN);
     Print("srTxn.szApprovalCode=%s\n",srTxn.szApprovalCode);
     Print("srTxn.password=%s\n",srTxn.password);
     Print("szFld61Buf=%s\n",szFld61Buf);
     Print("szFld62Buf=%s\n",szFld62Buf);
     Print("============撤销冲正报文各域值==================\n");

     iRetVal = ulForm (psz_ISOMsg, pi_ISOMsgSize, acErrMsg);
     if (0 != iRetVal)
     {
          goto ErrHandler;
     }

     iRetVal = 0;

     memcpy (psrTxnObject, &srTxn, sizeof(T_TRANS_OBJECT));
     
ErrHandler:
     
     if (0 != iRetVal)
     {
          iRetVal = -1;
     }
     
     return ((int)iRetVal);
     
}


int iFormBalanceISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize)
{
     unsigned long  iRetVal = 0;
     char szMTI[CMTI_SIZE + 1];
     char szProcCode[PROC_CODE_SIZE + 1];
     char szTxnAmt[12 + 1];
     char szSTAN[STAN_SIZE + 1];
     char szPOSEM[POS_EM_SIZE + 1];
     char szPOSCon[POS_CON_SIZE + 1];
     char szCVV2[CVV2_SIZE + 1];
     char szInvNum[INV_NUM_SIZE + 1];
     char szFld44Buf[FLD44_SIZE + 1];
     char szFld49Buf[FLD49_SIZE + 1];
     char szFld53Buf[FLD53_SIZE + 1];
     char szFld61Buf[FLD61_SIZE + 1];
     char szFld64Buf[FLD64_SIZE + 1];
     char szFld55Buf[FLD_55_SIZE + 1];
     T_TRANS_OBJECT srTxn;
     char acErrMsg[50];
     char szNII[NII_SIZE + 1];

     initStruct();
     //--------Must Reset-------
     ulResetAllFields();

     //memset and do the default padding char
     memset (szMTI, 0, sizeof(szMTI));
     memset (szProcCode, 0, sizeof(szProcCode));
     memset (szTxnAmt, 0, sizeof(szTxnAmt));
     memset (szSTAN, 0, sizeof(szSTAN));
     memset (szPOSEM, 0, sizeof(szPOSEM));
     memset (szPOSCon, 0, sizeof(szPOSCon));
     memset (szInvNum, 0, sizeof(szInvNum));
     memset (szNII, 0, sizeof(szNII));
     memset (szCVV2, 0, sizeof(szCVV2));
     memset (szFld44Buf, 0, sizeof(szFld44Buf));
     memset (szFld49Buf, 0, sizeof(szFld49Buf));
     memset (szFld53Buf, 0, sizeof(szFld53Buf));
     memset (szFld61Buf, 0, sizeof(szFld61Buf));
     memset (szFld64Buf, 0, sizeof(szFld64Buf));
     memset (szFld55Buf, 0, sizeof(szFld55Buf));
     memset(&srTxn, 0, sizeof(T_TRANS_OBJECT));
     memcpy (&srTxn, psrTxnObject, sizeof(T_TRANS_OBJECT));


     //MTI
     strcpy(szMTI,"0200");

     //3 proc code
     strcpy(szProcCode,"310000");

     //11
     STRINGNBULING(srTxn.lSTAN,szSTAN,6);

     //22
     strcpy(szPOSEM,(char *)srTxn.szPOSEntryMode);

     //24
     strcpy(szNII,"008");

     //25
     strcpy(szPOSCon,"14");


     iRetVal = ulSetTPDU ((char *)srTxn.szTPDU, CTPDU_SIZE);
     if (0 != iRetVal) goto errHandler;

     iRetVal = ulSetMTI (szMTI, CMTI_SIZE);
     if (0 != iRetVal) goto errHandler;

     //--------------------
     // Set field 2 卡号
     //--------------------
     iRetVal = ulSetField (2, (char *)srTxn.szPAN, (int)strlen((char *)srTxn.szPAN));

     //----------------------
     // Set field 3 交易处理码
     //----------------------
     iRetVal = ulSetField (3, szProcCode, PROC_CODE_SIZE);
     if (0 != iRetVal) goto errHandler;

     //-----------------------
     // Set field 11 流水号
     //-----------------------
     iRetVal = ulSetField (11, szSTAN, STAN_SIZE);
     if (0 != iRetVal) goto errHandler;

     //-----------------------
     // Set field 14 卡有效期
     //-----------------------
     if(1==srTxn.TypeOfTxn)
     {
          iRetVal = ulSetField (14,(char *)srTxn.carddate,4);
          if (0 != iRetVal) goto errHandler;
     }


     //------------------------
     // Set field 22 获取卡号和密码的方式
     //------------------------
     iRetVal = ulSetField (22, szPOSEM, POS_EM_SIZE);
     if (0 != iRetVal) goto errHandler;

     //------------------------
     // Set field 23c IC序列号
     //------------------------
     if(1==srTxn.TypeOfTxn)
     {
          if(strcmp((char *)srTxn.cardnum,"010")<0)
          {
               iRetVal=ulSetField(23,(char *)srTxn.cardnum,3);
               if (0 != iRetVal) goto errHandler;
          }
     }


     //------------------------
     // Set field 24 国际网络标识符
     //------------------------
     iRetVal = ulSetField (24, szNII, NII_SIZE);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 25 POS交易
     //------------------------------
     iRetVal = ulSetField (25, szPOSCon, POS_CON_SIZE);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 35 二磁道数据
     //------------------------------
     iRetVal = ulSetField (35,(char *)srTxn.szTrack2, (int)strlen((char *)srTxn.szTrack2));
     if (0 != iRetVal) goto errHandler;

     // Set field 41 POS终端编号
     //------------------------------
     iRetVal = ulSetField (41, (char *)srTxn.szTID,8);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 42 商户编号
     //------------------------------
     iRetVal = ulSetField (42, (char *)srTxn.szMID,15);
     if (0 != iRetVal) goto errHandler;


     //-----------------------------
     // Set field 49 货币编号
     //-----------------------------
     iRetVal = ulSetField (49,(char *)srTxn.currency,3);
     if (0 != iRetVal) goto errHandler;

     //-----------------------------
     // Set field 52 卡密码
     //-----------------------------

     if(strlen((char *)srTxn.password)>1)
     {
          int length=0;
          unsigned char Field52[8+1];
          memset(Field52,0,sizeof(Field52));
          iHexToByte1((char *)srTxn.password,Field52,&length);
          iRetVal=ulSetField(52,(char *)Field52,length);
          if (0 != iRetVal) goto errHandler;
     }


     //--------------------------------
     // Set field 55 IC55域数据
     //--------------------------------
     if(1==srTxn.TypeOfTxn)
     {
          int length=0;
          unsigned char sendField55[256+1];
          memset(sendField55,0,sizeof(sendField55));
          iHexToByte1((char *)srTxn.ICinfo,sendField55,&length);
          iRetVal = ulSetField (55,(char *)sendField55,length);
          if (0 != iRetVal) goto errHandler;
     }


     //-----------------------------
     // Set field 61 自定义域：批次号、操作员号、查询号
     //-----------------------------
     memset(szFld61Buf, 0, sizeof(szFld61Buf));
     TransToString61(srTxn.lBatchNum,"001",srTxn.lChayNum,szFld61Buf);
     iRetVal = ulSetField (61, szFld61Buf, (int)strlen(szFld61Buf));
     if (0 != iRetVal) goto errHandler;

    //-----------------------------
    // Set field 64 MAC：信息校验码
    //-----------------------------
     unsigned char szMacBuf[9];
     memset(szMacBuf,0,sizeof(szMacBuf));
     int len;
     iHexToByte1((char *)srTxn.szMACBlock,szMacBuf,&len);
     iRetVal = ulSetField (64,"88888888",8);
     if (0 != iRetVal) goto errHandler;

     Print("==========组报文========================\n");
     Print("srTxn.szPAN=%s\n",srTxn.szPAN);
     Print("srTxn.szProcCode=%s\n",szProcCode);
     Print("szSTAN=%s\n",szSTAN);
     Print("srTxn.carddate=%s\n",srTxn.carddate);
     Print("szPOSEM=%s\n",szPOSEM);
     Print("srTxn.cardnum=%s\n",srTxn.cardnum);
     Print("szNII=%s\n",szNII);
     Print("szPOSCon=%s\n",szPOSCon);
     Print("srTxn.szTrack2=%s\n",srTxn.szTrack2);
     Print("srTxn.szTID=%s\n",srTxn.szTID);
     Print("srTxn.szMID=%s\n",srTxn.szMID);
     Print("srTxn.currency=%s\n",srTxn.currency);
     Print("srTxn.password=%s\n",srTxn.password);
     Print("szFld61Buf=%s\n",szFld61Buf);
     Print("==========组报文========================\n");


     iRetVal = ulForm (psz_ISOMsg, pi_ISOMsgSize, acErrMsg);
     if (0 != iRetVal) goto errHandler;
     
     iRetVal = 0;
     
     
errHandler:
     
     if (0 != iRetVal)
     {
          iRetVal = -1;
          Print("faile zhu!\n");
     }
     
     return ((int)iRetVal);
}


int iParseBalanceISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int i_ISOMsgSize)
{
     unsigned char	pTPDU[CTPDU_SIZE+1];
     unsigned char	pMTI[CMTI_SIZE+1];
     T_TRANS_OBJECT	srTxn;
     char			szSTAN[STAN_SIZE + 1];
     char			szTID[TID_SIZE + 1];
     char			szMID[MID_SIZE + 1];
     char			szError[100];
     int			iFieldLen = 0;
     long			lRetVal = 0;
     char			szAmtInF4[LEN_AMOUNT+1];
     char			szField32[11 + 1];
     char			szField44[FLD44_SIZE + 1];
     char			szField53[FLD53_SIZE + 1];
     char			szField54[20 * 3 + 1];
     char			szField61[FLD61_SIZE + 1];
     char			szField64[FLD64_SIZE + 1];
     char			szField4[LEN_AMOUNT+1 ];
     char			szField63[250+1];
     char           szField3[6+1];
     //int			iField61Len = 0;




     ulResetAllFields();

     memset (pTPDU, 0, sizeof(pTPDU));
     memset (pMTI, 0, sizeof(pMTI));
     memset (&srTxn, 0, sizeof(T_TRANS_OBJECT));
     memset (szSTAN, 0, sizeof(szSTAN));
     memset (szTID, 0, sizeof(szTID));
     memset (szMID, 0, sizeof(szMID));
     memset (szError, 0, sizeof(szError));
     memset (szAmtInF4, 0, sizeof(szAmtInF4));
     memset (szField32, 0, sizeof(szField32));
     memset (szField44, 0, sizeof(szField44));
     memset (szField53, 0, sizeof(szField53));
     memset (szField54, 0, sizeof(szField54));
     memset (szField61, 0, sizeof(szField61));
     memset (szField64, 0, sizeof(szField64));
     memset (szField4, 0, sizeof(szField4));
     memset (szField63, 0, sizeof(szField63));
     memset(szField3,0,sizeof(szField3));


     lRetVal = ulParse (psz_ISOMsg, i_ISOMsgSize, szError);
     if (lRetVal != 0)
     {
          goto ErrHandler;
     }

     lRetVal = ulGetTPDU ((char *)pTPDU, &iFieldLen);
     if (lRetVal != 0)
     {
          goto ErrHandler;
     }

     lRetVal = ulGetMTI ((char *)pMTI, &iFieldLen);
     if (lRetVal != 0)
     {
          goto ErrHandler;
     }

     memcpy (&srTxn, psrTxnObject, sizeof(T_TRANS_OBJECT));


     lRetVal = ulGetField (2, (char *)srTxn.szPAN, &iFieldLen);

     lRetVal = ulGetField (3,szField3, &iFieldLen);
     strncpy(srTxn.szFiled3,szField3,6);

     lRetVal = ulGetField (37, (char *)srTxn.szRRN, &iFieldLen);

     lRetVal = ulGetField (38, (char *)srTxn.szApprovalCode, &iFieldLen);

     lRetVal = ulGetField (39, (char *)srTxn.szRespCode, &iFieldLen);

     lRetVal = ulGetField (41, szTID, &iFieldLen);

     lRetVal = ulGetField (42, szMID, &iFieldLen);

     lRetVal = ulGetField (53, szField53, &iFieldLen);

     // Get The Amt
     lRetVal = ulGetField (54, szField54, &iFieldLen);

     strcpy((char *)srTxn.totalmoney,szField54);

     //printf("余额===%s\n",szField54);

     // May Be F4 Have the Amt
     memset(szField4, 0, sizeof(szField4));
     lRetVal = ulGetField (4, szField4, &iFieldLen);


     lRetVal = ulGetField (64, szField64, &iFieldLen);
     strncpy((char *)srTxn.szMACBlock64,szField64,iFieldLen);

     lRetVal = ulGetField (11, szSTAN, &iFieldLen);
     strncpy(srTxn.szFiled11,szSTAN,iFieldLen);
     lRetVal = ulGetField (12, (char *)srTxn.szTxnTime, &iFieldLen);
     lRetVal = ulGetField (13, (char *)srTxn.szTxnDate, &iFieldLen);


     Print("==========解报文========================\n");
     Print("szPAN=%s\n",srTxn.szPAN);
     Print("szSTAN=%s\n",szSTAN);
     Print("szTxnTime=%s\n",srTxn.szTxnTime);
     Print("szTxnDate=%s\n",srTxn.szTxnDate);
     Print("szRRN=%s\n",srTxn.szRRN);
     Print("szApprovalCode=%s\n",srTxn.szApprovalCode);
     Print("szRespCode=%s\n",srTxn.szRespCode);
     Print("szTID=%s\n",szTID);
     Print("szMID=%s\n",szMID);
     Print("szField44=%s\n",szField44);
     Print("szField53=%s\n",szField53);
     Print("szField61=%s\n",szField61);
     Print("szField64=%s\n",szField64);
     Print("==========解报文========================\n");

     memcpy (psrTxnObject, &srTxn, sizeof(T_TRANS_OBJECT));
     lRetVal = 0;

ErrHandler:
     memset (&srTxn, 0, sizeof(T_TRANS_OBJECT));
     
     if( 0 < lRetVal )
     {
          lRetVal = -1;
     }
     
     return ((int)lRetVal);
}


int iFormSALERVSISOMsg (T_TRANS_OBJECT *psrTxnObject, unsigned char *psz_ISOMsg, int *pi_ISOMsgSize)
{
     long  iRetVal =0;
     char szMTI[CMTI_SIZE + 1];
     char szProcCode[PROC_CODE_SIZE + 1];
     char szTxnAmt[12 + 1];
     char szSTAN[STAN_SIZE + 1];
     char szPOSEM[POS_EM_SIZE + 1];
     char szPOSCon[POS_CON_SIZE + 1];
     char szCVV2[CVV2_SIZE + 1];
     char szInvNum[INV_NUM_SIZE + 1];
     char szFld44Buf[FLD44_SIZE + 1];
     char szFld49Buf[FLD49_SIZE + 1];
     char szTxnDate[DATE_SIZE + 1];
     char Field52[12 + 1];
     char szFld53Buf[FLD53_SIZE + 1];
     char szFld61Buf[FLD61_SIZE + 1];
     char szFld62Buf[20 + 1];
     char szFld64Buf[FLD64_SIZE + 1];
     char szFld55Buf[FLD_55_SIZE + 1];
     T_TRANS_OBJECT srTxn;
     char acErrMsg[50];
     char szNII[NII_SIZE + 1];

     initStruct();

     //--------Must Reset-------
     ulResetAllFields();

     memset (szMTI, 0, sizeof(szMTI));
     memset (szProcCode, 0, sizeof(szProcCode));
     memset (szTxnAmt, 0, 12 + 1);
     memset (szSTAN, 0, sizeof(szSTAN));
     memset (szPOSEM, 0, sizeof(szPOSEM));
     memset (szPOSCon, 0, sizeof(szPOSCon));
     memset (szInvNum, 0, sizeof(szInvNum));
     memset (szNII, 0,sizeof(szNII));
     memset (szCVV2, 0, sizeof(szCVV2));
     memset (szFld44Buf, 0, sizeof(szFld44Buf));
     memset (szFld49Buf, 0, sizeof(szFld49Buf));
     memset (Field52, 0, sizeof(Field52));
     memset (szFld53Buf, 0, sizeof(szFld53Buf));
     memset (szFld61Buf, 0, sizeof(szFld61Buf));
     memset (szFld62Buf, 0, sizeof(szFld62Buf));
     memset (szFld64Buf, 0, sizeof(szFld64Buf));
     memset (szFld55Buf, 0, sizeof(szFld55Buf));
     memset(szTxnDate,0,sizeof(szTxnDate));
     memset(&srTxn, 0, sizeof(T_TRANS_OBJECT));
     memcpy (&srTxn, psrTxnObject, sizeof(T_TRANS_OBJECT));


     //MTI
     strcpy(szMTI,"0400");

     //3 proc code
     strcpy(szProcCode,"000000");

     //4 Amt
     STRINGNBULING(srTxn.lTxnAmt,szTxnAmt,12);

     //11
     STRINGNBULING(srTxn.lRevSTAN,szSTAN,6);

     //22
     //sprintf(szPOSEM,srTxn.szPOSEntryMode);
     strcpy(szPOSEM,(char *)srTxn.szPOSEntryMode);

     //24
     strcpy(szNII,"008");

     //25
     strcpy(szPOSCon,"14");


     iRetVal = ulSetTPDU ((char *)srTxn.szTPDU, CTPDU_SIZE);
     if (0 != iRetVal) goto errHandler;

     iRetVal = ulSetMTI (szMTI, CMTI_SIZE);
     if (0 != iRetVal) goto errHandler;


     //--------------------
     // Set field 2
     //--------------------
     iRetVal = ulSetField (2, (char *)srTxn.szPAN, (int)strlen((char *)srTxn.szPAN));

     //----------------------
     // Set field 3
     //----------------------
     iRetVal = ulSetField (3, szProcCode, PROC_CODE_SIZE);
     if (0 != iRetVal) goto errHandler;

     //----------------------
     // Set field 4
     //----------------------
     iRetVal = ulSetField (4, szTxnAmt,12);
     if (0 != iRetVal) goto errHandler;

     //-----------------------
     // Set field 11
     //-----------------------
     iRetVal = ulSetField (11, szSTAN, STAN_SIZE);
     if (0 != iRetVal) goto errHandler;


     //-----------------------
     // Set field 14 IC
     //-----------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          iRetVal = ulSetField (14,(char *)psrTxnObject->carddate,4);
          if (0 != iRetVal) goto errHandler;
     }

     //-----------------------
     // Set field 22
     //-----------------------
     iRetVal = ulSetField (22, szPOSEM, POS_EM_SIZE);
     if (0 != iRetVal) goto errHandler;


     //------------------------
     // Set field 23c IC
     //------------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          if(strcmp((char *)psrTxnObject->cardnum,"010")<0)
          {
               //printf("cardnum=%s\n",psrTxnObject->cardnum);
               iRetVal=ulSetField(23,(char *)psrTxnObject->cardnum,3);
               if (0 != iRetVal) goto errHandler;
          }
     }


     //------------------------
     // Set field 24
     //------------------------
     iRetVal = ulSetField (24, szNII, NII_SIZE);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 25
     //------------------------------
     iRetVal = ulSetField (25, szPOSCon, POS_CON_SIZE);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 35
     //------------------------------
     iRetVal = ulSetField (35,(char *)srTxn.szTrack2, (int)strlen((char *)srTxn.szTrack2));
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 41
     //------------------------------
     iRetVal = ulSetField (41,(char *)srTxn.szTID,8);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 42
     //------------------------------
     iRetVal = ulSetField (42, (char *)srTxn.szMID,15);
     if (0 != iRetVal) goto errHandler;


     //-----------------------------
     // Set field 49
     //-----------------------------
     iRetVal = ulSetField (49,(char *)srTxn.currency,3);
     if (0 != iRetVal) goto errHandler;


     //-----------------------------
     // Set field 52
     //-----------------------------

     if(strlen((char *)srTxn.password)>1)
     {
          int length=0;
          iHexToByte1((char *)srTxn.password,(unsigned char *)Field52,&length);
          iRetVal=ulSetField(52,Field52,length);
          if (0 != iRetVal) goto errHandler;
     }


     //--------------------------------
     // Set field 55 IC
     //--------------------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          int length=0;
          unsigned char sendField55[256+1];
          memset(sendField55,0,sizeof(sendField55));
          iHexToByte1((char *)psrTxnObject->ICinfo,sendField55,&length);
          iRetVal = ulSetField (55,(char *)sendField55,length);
          if (0 != iRetVal) goto errHandler;
     }


     //-----------------------------
     // Set field 61
     //-----------------------------
     memset(szFld61Buf, 0, sizeof(szFld61Buf));
     //sprintf((char*)szFld61Buf, "%06s%03s%06s",srTxn.lBatchNum,"001",srTxn.lChayNum);
     TransToString61(srTxn.lBatchNum,"001",srTxn.lChayNum,szFld61Buf);
     iRetVal = ulSetField (61, szFld61Buf, (int)strlen(szFld61Buf));
     if (0 != iRetVal) goto errHandler;

     //--------------------------------
     // Set field 62
     //--------------------------------
     memcpy(szTxnDate, srTxn.szOrgTxnDate, 4);
     //sprintf((char*)szFld62Buf, "%s%06s%s","0400",srTxn.lRevSTAN,"0000000000");
     TransToString62("0400",srTxn.lRevSTAN,"0000000000",szFld62Buf);
     iRetVal = ulSetField (62, szFld62Buf, 20);

     unsigned char szMacBuf[9];
     memset(szMacBuf,0,sizeof(szMacBuf));
     int len;
     iHexToByte1((char *)srTxn.szMACBlock1,szMacBuf,&len);
     iRetVal = ulSetField (64,"88888888",8);
     if (0 != iRetVal) goto errHandler;

     iRetVal = ulForm (psz_ISOMsg, pi_ISOMsgSize, acErrMsg);
     if (0 != iRetVal) goto errHandler;
     initStruct();
     iRetVal = 0;
     
errHandler:
     
     if (0 != iRetVal)
     {
          iRetVal = -1;
     }
     
     return ((int)iRetVal);
     //return 0;
}


int d73cb60c11af1afd8036426d1673296d(char *szSendMess)//如果存在冲正就发送冲正报文
{
     int len=0,recvLen,recvResult;
     char szError[100];
     unsigned char szRespCode[2+1];
     int iFieldLen=0;
     unsigned char szFileBuf[1500+1];
     unsigned char szRecvBuf[1500+1];
     memset(szFileBuf,0,sizeof(szFileBuf));
     memset(szRecvBuf,0,sizeof(szRecvBuf));
     memset(szRespCode,0,sizeof(szRespCode));


     iHexToByte1((char *)szSendMess,szFileBuf,&len);//把字符串转成16进制
     recvResult=af2d87ec65d7e992873c381e78ee17d7(szFileBuf,&len,szRecvBuf,&recvLen);

     if(recvResult<=0)
     {
          recvResult=1;
     }
     else
     {
          ulResetAllFields();

          ulParse (szRecvBuf,recvLen,szError);

          ulGetField (39,(char *)szRespCode,&iFieldLen);

          if(strlen((char *)szRespCode)!=0)
          {
               recvResult=0;
          }
          else
          {
               recvResult=2;
          }
     }
     return recvResult;
}


int iFormRapidConsumpte(T_TRANS_OBJECT *psrTxnObject,unsigned char *psz_ISOMsg, int *pi_ISOMsgSize)
{
     T_TRANS_OBJECT srTxn;
     long  iRetVal =0;
     char szMTI[CMTI_SIZE + 1];
     char szProcCode[PROC_CODE_SIZE + 1];
     char szTxnAmt[12 + 1];
     char szPOSEM[POS_EM_SIZE + 1];
     char szPOSCon[POS_CON_SIZE + 1];
     char szNII[NII_SIZE + 1];
     char szSTAN[STAN_SIZE + 1];
     char acErrMsg[50];


     initStruct();
     //--------Must Reset-------
     ulResetAllFields();

     memset (szMTI, 0, sizeof(szMTI));
     memset (szProcCode, 0, sizeof(szProcCode));
     memset (szTxnAmt, 0, 12 + 1);
     memset (szPOSEM, 0, sizeof(szPOSEM));
     memset (szPOSCon, 0, sizeof(szPOSCon));
     memset (szNII, 0,sizeof(szNII));
     memset (szSTAN, 0, sizeof(szSTAN));
     memset(acErrMsg,0,sizeof(acErrMsg));
     memset(&srTxn, 0, sizeof(T_TRANS_OBJECT));
     memcpy (&srTxn, psrTxnObject, sizeof(T_TRANS_OBJECT));



     //MTI
     strcpy(szMTI,"0220");

     //3 proc code
     strcpy(szProcCode,"000000");

     //4 Amt
     STRINGNBULING(srTxn.lTxnAmt,szTxnAmt,12);

     //11
     STRINGNBULING(srTxn.lRevSTAN,szSTAN,6);


     //22
     strcpy(szPOSEM,(char *)srTxn.szPOSEntryMode);

     //24
     strcpy(szNII,"008");

     //25
     strcpy(szPOSCon,"14");

     iRetVal = ulSetTPDU ((char *)srTxn.szTPDU, CTPDU_SIZE);
     if (0 != iRetVal) goto errHandler;

     iRetVal = ulSetMTI (szMTI, CMTI_SIZE);
     if (0 != iRetVal) goto errHandler;

     //--------------------
     // Set field 2
     //--------------------
     iRetVal = ulSetField (2, (char *)srTxn.szPAN, (int)strlen((char *)srTxn.szPAN));

     //----------------------
     // Set field 3
     //----------------------
     iRetVal = ulSetField (3, szProcCode, PROC_CODE_SIZE);
     if (0 != iRetVal) goto errHandler;

     //----------------------
     // Set field 4
     //----------------------
     iRetVal = ulSetField (4, szTxnAmt,12);
     if (0 != iRetVal) goto errHandler;

     //-----------------------
     // Set field 11
     //-----------------------
     iRetVal = ulSetField (11, szSTAN, STAN_SIZE);
     if (0 != iRetVal) goto errHandler;

     //-----------------------
     // Set field 12 IC
     //-----------------------
     iRetVal = ulSetField(12,(char *)srTxn.szTxnTime,(int)strlen((char *)srTxn.szTxnTime));
     if (0 != iRetVal) goto errHandler;

     //-----------------------
     // Set field 13 IC
     //-----------------------
     iRetVal = ulSetField(13,(char *)srTxn.szTxnDate,(int)strlen((char *)srTxn.szTxnDate));
     if (0 != iRetVal) goto errHandler;

     //-----------------------
     // Set field 14 IC
     //-----------------------
     if(1==psrTxnObject->TypeOfTxn)
     {
          iRetVal = ulSetField (14,(char *)psrTxnObject->carddate,4);
          if (0 != iRetVal) goto errHandler;
     }


     //-----------------------
     // Set field 22
     //-----------------------
     iRetVal = ulSetField (22, szPOSEM, POS_EM_SIZE);
     if (0 != iRetVal) goto errHandler;


     //------------------------
     // Set field 23c IC
     //------------------------
     if(1 == psrTxnObject->TypeOfTxn)
     {
          if(strcmp((char *)psrTxnObject->cardnum,"010")<0)
          {
               iRetVal=ulSetField(23,(char *)psrTxnObject->cardnum,3);
               if (0 != iRetVal) goto errHandler;
          }
     }


     //------------------------
     // Set field 24
     //------------------------
     iRetVal = ulSetField (24, szNII, NII_SIZE);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 25
     //------------------------------
     iRetVal = ulSetField (25, szPOSCon, POS_CON_SIZE);
     if (0 != iRetVal) goto errHandler;


     //------------------------
     // Set field 39
     //------------------------
     iRetVal = ulSetField (39,"Y1",2);
     if (0 != iRetVal) goto errHandler;


     //------------------------------
     // Set field 41
     //------------------------------
     iRetVal = ulSetField (41,(char *)srTxn.szTID,8);
     if (0 != iRetVal) goto errHandler;

     //------------------------------
     // Set field 42
     //------------------------------
     iRetVal = ulSetField (42, (char *)srTxn.szMID,15);
     if (0 != iRetVal) goto errHandler;


     //-----------------------------
     // Set field 48
     //-----------------------------

     //-----------------------------
     // Set field 49
     //-----------------------------
     iRetVal = ulSetField (49,(char *)srTxn.currency,3);
     if (0 != iRetVal) goto errHandler;



     //--------------------------------
     // Set field 55 IC
     //--------------------------------
     if(psrTxnObject->TypeOfTxn == 1)
     {
          int length=0;
          unsigned char sendField55[256+1];
          memset(sendField55,0,sizeof(sendField55));
          iHexToByte1((char *)psrTxnObject->ICinfo,sendField55,&length);
          iRetVal = ulSetField (55,(char *)sendField55,length);
          if (0 != iRetVal) goto errHandler;

     }

     unsigned char szMacBuf[9];
     memset(szMacBuf,0,sizeof(szMacBuf));
     int len;
     iHexToByte1((char *)srTxn.szMACBlock1,szMacBuf,&len);
     iRetVal = ulSetField (64,"88888888",8);
     if (0 != iRetVal) goto errHandler;



     iRetVal = ulForm (psz_ISOMsg, pi_ISOMsgSize, acErrMsg);
     if (0 != iRetVal) goto errHandler;
     initStruct();
     return 0;


errHandler:

     if (0 != iRetVal)
     {
          iRetVal = -1;
     }

     return ((int)iRetVal);
}



int iFormBalanceMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg)
{
     int length;
     length = (int)strlen((char *)psrTxnObject->szPAN);

     if(length % 2 == 1)
     {
          strncat(psz_ISOMsg,"0",1);
     }
     strncat(psz_ISOMsg,(const char *)psrTxnObject->szPAN,length);
     strncat(psz_ISOMsg,"310000",6);

     char szSTAN[7];
     memset(szSTAN,0,sizeof(szSTAN));
     STRINGNBULING(psrTxnObject->lSTAN,szSTAN,6);
     strncat(psz_ISOMsg,szSTAN,6);

     strncat(psz_ISOMsg,"0156",4);

     char filed41[17];
     memset(filed41,0,sizeof(filed41));
     vdHex2Str((char *)psrTxnObject->szTID,8,filed41);

     strncat(psz_ISOMsg,filed41,16);
     return 0;
}

int iFormBalanceBackMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg)
{
     int length;
     length = (int)strlen((char *)psrTxnObject->szPAN);

     if(length % 2 == 1)
     {
          strncat(psz_ISOMsg,"0",1);
     }
     strncat(psz_ISOMsg,(const char *)psrTxnObject->szPAN,length);

     strncat(psz_ISOMsg,psrTxnObject->szFiled3,6);

     char szSTAN[7];
     memset(szSTAN,0,sizeof(szSTAN));
     STRINGNBULING(psrTxnObject->lSTAN,szSTAN,6);
     strncat(psz_ISOMsg,szSTAN,6);

     strncat(psz_ISOMsg,(const char *)psrTxnObject->szTxnTime,6);

     strncat(psz_ISOMsg,(char *)psrTxnObject->szTxnDate,4);

     strncat(psz_ISOMsg,"0156",4);

     char szFiled38[13];
     memset(szFiled38,0,sizeof(szFiled38));

     if(strlen((char *)psrTxnObject->szApprovalCode) > 0)
     {
          vdHex2Str((char *)psrTxnObject->szApprovalCode,6,szFiled38);
          strncat(psz_ISOMsg,szFiled38,12);
     }

     char filed39[5];
     memset(filed39,0,sizeof(filed39));
     vdHex2Str((char *)psrTxnObject->szRespCode,2,filed39);
     strncat(psz_ISOMsg,filed39,4);

     char filed41[5];
     memset(filed41,0,sizeof(filed41));
     vdHex2Str((char *)psrTxnObject->szTID,8,filed41);
     strncat(psz_ISOMsg,filed41,16);

     return 0;
}


int iFormSALEMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg)
{
     int length;
     length = (int)strlen((char *)psrTxnObject->szPAN);

     if(length % 2 == 1)
     {
          strncat(psz_ISOMsg,"0",1);
     }
     strncat(psz_ISOMsg,(const char *)psrTxnObject->szPAN,length);

     strncat(psz_ISOMsg,"000000",6);

     char szFiled4[13];
     memset(szFiled4,0,sizeof(szFiled4));
     STRINGNBULING(psrTxnObject->lTxnAmt,szFiled4,12);
     strncat(psz_ISOMsg,szFiled4,12);

     char szSTAN[7];
     memset(szSTAN,0,sizeof(szSTAN));
     STRINGNBULING(psrTxnObject->lSTAN,szSTAN,6);
     strncat(psz_ISOMsg,szSTAN,6);

     strncat(psz_ISOMsg,"0156",4);

     char filed41[5];
     memset(filed41,0,sizeof(filed41));
     vdHex2Str((char *)psrTxnObject->szTID,8,filed41);
     strncat(psz_ISOMsg,filed41,16);

     return 0;
}

int iFormSALEBackMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg)
{
     int length;
     length = (int)strlen((char *)psrTxnObject->szPAN);

     if(length % 2 == 1)
     {
          strncat(psz_ISOMsg,"0",1);
     }
     strncat(psz_ISOMsg,(const char *)psrTxnObject->szPAN,length);

     strncat(psz_ISOMsg,psrTxnObject->szFiled3,6);

     char szFiled4[13];
     memset(szFiled4,0,sizeof(szFiled4));
     STRINGNBULING(psrTxnObject->lTxnAmt,szFiled4,12);
     strncat(psz_ISOMsg,szFiled4,12);

     char szSTAN[7];
     memset(szSTAN,0,sizeof(szSTAN));
     STRINGNBULING(psrTxnObject->lSTAN,szSTAN,6);
     strncat(psz_ISOMsg,szSTAN,6);


     strncat(psz_ISOMsg,(char *)psrTxnObject->szTxnTime,6);

     strncat(psz_ISOMsg,(char *)psrTxnObject->szTxnDate,4);

     strncat(psz_ISOMsg,"0156",4);

     char szFiled38[13];
     memset(szFiled38,0,sizeof(szFiled38));
     if(strlen((char *)psrTxnObject->szApprovalCode) > 0)
     {
          vdHex2Str((char *)psrTxnObject->szApprovalCode,6,szFiled38);
          strncat(psz_ISOMsg,szFiled38,12);
     }

     char filed39[5];
     memset(filed39,0,sizeof(filed39));
     vdHex2Str((char *)psrTxnObject->szRespCode,2,filed39);
     strncat(psz_ISOMsg,filed39,4);

     char filed41[5];
     memset(filed41,0,sizeof(filed41));
     vdHex2Str((char *)psrTxnObject->szTID,8,filed41);
     strncat(psz_ISOMsg,filed41,16);
     
     return 0;
}

int iFormVOIDSALEMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg)
{
     int length;
     length = (int)strlen((char *)psrTxnObject->szPAN);

     if(length % 2 == 1)
     {
          strncat(psz_ISOMsg,"0",1);
     }
     strncat(psz_ISOMsg,(const char *)psrTxnObject->szPAN,length);

     strncat(psz_ISOMsg,"200000",6);

     char szFiled4[13];
     memset(szFiled4,0,sizeof(szFiled4));
     STRINGNBULING(psrTxnObject->lOrgTxnAmt,szFiled4,12);
     strncat(psz_ISOMsg,szFiled4,12);

     char szFiled11[7];
     memset(szFiled11,0,sizeof(szFiled11));
     STRINGNBULING(psrTxnObject->lOrgSTAN,szFiled11,6);
     strncat(psz_ISOMsg,szFiled11,6);


     strncat(psz_ISOMsg,(char *)psrTxnObject->szOrgTxnTime,6);

     strncat(psz_ISOMsg,(char *)psrTxnObject->szOrgTxnDate,4);

     strncat(psz_ISOMsg,"0156",4);

     char szFiled38[13];
     memset(szFiled38,0,sizeof(szFiled38));
     if(strlen((char *)psrTxnObject->szOrgApprovalCode) > 0)
     {
          vdHex2Str((char *)psrTxnObject->szOrgApprovalCode,6,szFiled38);
          strncat(psz_ISOMsg,szFiled38,12);
     }

     char filed41[5];
     memset(filed41,0,sizeof(filed41));
     vdHex2Str((char *)psrTxnObject->szTID,8,filed41);
     strncat(psz_ISOMsg,filed41,16);
     
     return 0;
}

int iFormVOIDSALEBackMACMsg (T_TRANS_OBJECT *psrTxnObject,char *psz_ISOMsg)
{
     int length;
     length = (int)strlen((char *)psrTxnObject->szPAN);

     if(length % 2 == 1)
     {
          strncat(psz_ISOMsg,"0",1);
     }
     strncat(psz_ISOMsg,(const char *)psrTxnObject->szPAN,length);

     strncat(psz_ISOMsg,psrTxnObject->szFiled3,6);

     char szFiled4[13];
     memset(szFiled4,0,sizeof(szFiled4));
     STRINGNBULING(psrTxnObject->lOrgTxnAmt,szFiled4,12);
     strncat(psz_ISOMsg,szFiled4,12);

     char szFiled11[7];
     memset(szFiled11,0,sizeof(szFiled11));
     STRINGNBULING(psrTxnObject->szFiled11,szFiled11,6);
     strncat(psz_ISOMsg,szFiled11,6);

     strncat(psz_ISOMsg,(char *)psrTxnObject->szTxnTime,6);
     strncat(psz_ISOMsg,(char *)psrTxnObject->szTxnDate,4);

     strncat(psz_ISOMsg,"0156",4);

     char szFiled38[13];
     memset(szFiled38,0,sizeof(szFiled38));
     if(strlen((char *)psrTxnObject->szApprovalCode) > 0)
     {
          vdHex2Str((char *)psrTxnObject->szApprovalCode,6,szFiled38);
          strncat(psz_ISOMsg,szFiled38,12);
     }

     char filed39[5];
     memset(filed39,0,sizeof(filed39));
     vdHex2Str((char *)psrTxnObject->szRespCode,2,filed39);
     strncat(psz_ISOMsg,filed39,4);

     char filed41[5];
     memset(filed41,0,sizeof(filed41));
     vdHex2Str((char *)psrTxnObject->szTID,8,filed41);
     strncat(psz_ISOMsg,filed41,16);

     return 0;
}
