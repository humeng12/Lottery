//
//  bufInfo.c
//  merchant
//
//  Created by HRT on 16/3/24.
//  Copyright © 2016年 Hrtpayment. All rights reserved.
//

#include "bufInfo.h"



unsigned char szSendMsg[1500 +1];//暂时保存发送的报文
unsigned char szRecvMsg[1500 +1];//暂时保存接收的报文
unsigned char szSendMsg2[1500 +1];//暂时保存冲正报文
int iSendSize=0,iRecvSize=0,iSendSize2=0;//保存报文的长度