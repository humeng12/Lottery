//
//  defineParam.h
//  merchant
//
//  Created by HRT on 16/3/24.
//  Copyright © 2016年 Hrtpayment. All rights reserved.
//

#ifndef defineParam_h
#define defineParam_h



#define CONNECTIME                 60
#define AICONNECTTIME              30
#define AILANCONNECTTIME           30

#define CMTI_SIZE				4
#define PAN_SIZE				19
#define EXP_DATE_SIZE			4
#define T1_SIZE				7
#define T2_SIZE				39
#define T3_SIZE				150
#define CVV2_SIZE				6
#define USR_INV_NUM_SIZE           12
#define TID_SIZE				8
#define MID_SIZE				15
#define CTPDU_SIZE				10
#define NII_SIZE				3
#define DATE_SIZE				6
#define TIME_SIZE				6
#define RRN_SIZE				12
#define APPR_CODE_SIZE			6
#define RESP_CODE_SIZE			2
#define SERVICE_CODE_SIZE		3
#define CARD_NAME_SIZE			18
#define CARDNAMECH_SIZE			20
#define POS_EM_SIZE				3
#define FLD_55_SIZE				256
#define PIN_BLOCK_SIZE			8
#define MAC_BLOCK_SIZE			8
#define LEN_AMOUNT				12
#define	NO_CARD_TXN_ERR_SIZE	32
#define VER_NUM                    4
#define PRO_CODE                   6
#define CURRENCY_SIZE              3
#define PASS_SIZE                  16
#define OPER_SIZE                  3
#define STAN_SIZE                  6
#define BATCH_NUM_SIZE             6
#define MAC_SIZE                   12
#define APPR_CODE_SOZE             6
#define CARDNAME_SIZE              20


#define HEADER                34
#define BITMAP                64
#define KAHAO                 22
#define PROC_CODE_SIZE        6
#define MAX_ISO_MSG_SIZE      1500
#define POS_CON_SIZE          2
#define INV_NUM_SIZE          6
#define POS_EM_SIZE           3
#define NII_SIZE              3
#define POS_CON_SIZE          2
#define FLD61_SIZE            15


#define FLD44_SIZE            16
#define FLD53_SIZE            16
#define FLD64_SIZE            (8*2)
#define DES_KEY_SIZE          8
#define FLD49_SIZE            27
#define FLD_43_SIZE           40
#define FLD_61_SIZE           999
#define FLD_64_SIZE           8
#define FLD_60_SIZE           18


#define SETTLE                21
#define TC_UPLOAD             13





#define MAX_ISO_MSG_SIZE      1500
#define PACK_BCD              2
#define PACK_HEX              3
#define MAX_ISO_FIELDS        128
#define MAX_TEMP_BUFFER_SZ    1024
#define MAX_ISO_MESG_SZ       4096
#define I_ISO_8583            1
#define I_ISO_B24             2

#define E_MISSING_DATA        80008
#define E_EMPTY_MESSAGE       80002
#define E_LEN_TOO_SHORT       80003
#define E_INSUF_DATA          80007


#define DEFAULT_BITMAP_SZ     8
#define MAX_FIELD_LEN         4


#define TYPE_A				0
#define TYPE_AN			1
#define TYPE_ANS			2
#define TYPE_N				3
#define TYPE_B				4
#define TYPE_Z				5
#define TYPE_XN			6
#define TYPE_UNKNOWN		-1


#define ISO_DUMMY_SZ		250
#define ISO_TPDU_SZ			10
#define ISO_MTI_SZ			4
#define ISO_BITMAP_SZ		32
#define ISO_CARDPAN_SZ		19	// 2
#define ISO_PRODCODE_SZ		6	// 3
#define ISO_AMT_SZ			12	// 4
#define ISO_DATE_TIME_SZ      10	// 7
#define ISO_STAN_SZ			6	// 11
#define ISO_TXNTIME_SZ		6	// 12
#define ISO_TXNDATE_SZ		4	// 13
#define ISO_EXPDATE_SZ		4	// 14
#define ISO_SETTLEDATE_SZ	4	// 15
#define ISO_POSENTRYMODE_SZ	3	// 22
#define ISO_APP_PAN_NO_SZ	3	// 23
#define ISO_NII_SZ			3	// 24
#define ISO_POSCONDCODE_SZ	2	// 25
#define ISO_ACQINSTID_SZ      11	// 32
#define ISO_FWDINSTID_SZ      11	// 33
#define ISO_TRACK2_SZ		39	// 35
#define ISO_TRACK3_SZ		104	// 36
#define ISO_RRN_SZ			12	// 37
#define ISO_AUTHCODE_SZ		6	// 38
#define ISO_RESPCODE_SZ		2	// 39
#define ISO_TID_SZ			8	// 41
#define ISO_MID_SZ			15	// 42
#define ISO_TRACK1_SZ		76	// 45
#define ISO_FIELD47_SZ		200 // 47
#define ISO_ADDTDATA_SZ		100	// 48
#define ISO_TXNCURCODE_SZ	27	// 49
#define ISO_PINBLOCK_SZ		16	// 52
#define ISO_FIELD54_SZ		120	// 54
#define ISO_EMVDATA_SZ		300	// 55
#define ISO_FIELD60_SZ		200	// 60
#define ISO_FIELD61_SZ		200	// 61
#define ISO_FIELD62_SZ		200	// 62
#define ISO_FIELD63_SZ		200	// 63
#define ISO_MAC_SZ			16	// 64


#endif /* defineParam_h */
