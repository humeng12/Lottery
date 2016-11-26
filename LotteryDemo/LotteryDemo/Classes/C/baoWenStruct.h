//
//  baoWenStruct.h
//  merchant
//
//  Created by HRT on 16/3/24.
//  Copyright © 2016年 Hrtpayment. All rights reserved.
//

#ifndef baoWenStruct_h
#define baoWenStruct_h

#include "defineParam.h"


//此结构体存储组报文的一些信息
typedef struct
{
     int                       TypeOfTxn;//标识   由此来判断是否组 14  23 55
     unsigned char            iTxnType[10+1];//保存交易类型（消费 撤销 快速消费   查余额）
     unsigned char            version[VER_NUM+1];
     unsigned char            procode[PRO_CODE +1];
     unsigned char            servicecode[SERVICE_CODE_SIZE +1];
     unsigned char            currency[CURRENCY_SIZE+1];
     unsigned char            password[PASS_SIZE +1];
     unsigned char            operatorNO[OPER_SIZE +1];
     char                      lSTAN[STAN_SIZE +1];//流水号
     char                      szFiled3[7];//解析返回的报文 的 消息类型
     char                      szFiled11[7];//解析返回报文的 流水号
     char                      lBatchNum[BATCH_NUM_SIZE +1];//批次号
     char                      lChayNum[6+1];//查询号
     char                      lTxnAmt[LEN_AMOUNT+1];//消费金额
     unsigned char            Mac[MAC_SIZE +1];
     unsigned char            szPAN[PAN_SIZE + 1];//卡号
     unsigned char            szTrack2[T2_SIZE + 1];//二磁道
     unsigned char            szTID[TID_SIZE + 1];
     unsigned char            szMID[MID_SIZE + 1];
     unsigned char            szTPDU[CTPDU_SIZE + 1];
     unsigned char            szNII[NII_SIZE + 1];
     unsigned char            szPOSEntryMode[POS_EM_SIZE + 1];//密码类型
     unsigned char            szRRN[RRN_SIZE +1];//参考号
     unsigned char            szApprovalCode[APPR_CODE_SOZE +1];// 授权码
     unsigned char            szRespCode[RESP_CODE_SIZE +1];//响应吗
     unsigned char            szCardName[CARDNAME_SIZE +1];
     int                       cardNameLength;
     unsigned char            szTxnTime[TIME_SIZE +1];//解析返回的报文  的时间
     unsigned char            szTxnDate[DATE_SIZE +1];//解析返回的报文  的日期
     unsigned char            carddate[4+1];//卡有效期
     unsigned char            cardnum[3+1];//卡片序列号
     unsigned char            ICinfo[300+1];//IC卡数据
     unsigned char            totalmoney[30+1];//可用余额不可用余额
     unsigned char            szMACBlock[16+1];//64域 加密 后 的结果
     unsigned char            szMACBlock1[16+1];
     unsigned char            szMACBlock64[MAC_BLOCK_SIZE+1];


     char                      cardHolderName[40];//持卡人姓名


     char                      lOrgSTAN[STAN_SIZE +1];//撤销时的流水号
     unsigned char            szOrgTxnTime[TIME_SIZE +1];//撤销时的交易时间
     unsigned char            szOrgTxnDate[DATE_SIZE +1];//撤销时的交易日期
     char                      lOrgTxnAmt[LEN_AMOUNT+1];//撤销时的交易金额
     unsigned char            szOrgRRN[RRN_SIZE +1];
     unsigned char            szInvNum[6+1];
     unsigned char            szOrgApprovalCode[APPR_CODE_SOZE +1];// 授权码
     unsigned char            lOrgChayNum[6+1];//查询号

     char                      lRevSTAN[STAN_SIZE +1];//冲正时用流水号

     char                      szCardName1[CARDNAME_SIZE +1];

}T_TRANS_OBJECT;

T_TRANS_OBJECT transobj;

extern T_TRANS_OBJECT transobj;


#endif /* baoWenStruct_h */
