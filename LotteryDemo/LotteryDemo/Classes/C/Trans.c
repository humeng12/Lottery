//
//  Trans.c
//  POSsys
//
//  Created by MAC on 14-10-11.
//  Copyright (c) 2014年 MAC. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "Trans.h"
#include <stdlib.h>
#include "defineParam.h"
#include "PublicMethod.h"
#include "printLog.h"


int g_iStandard=I_ISO_8583;
int g_iHeader=5;
int g_iMTILen=2;

char	g_acField43[ISO_DUMMY_SZ + 1];
char	g_acDummy[25 + 1];                           //46
char	g_acTPDU[ISO_TPDU_SZ + 1];
char	g_acMTI[ISO_MTI_SZ + 1];
char	g_acVersionNum[ISO_MTI_SZ + 1];
char	g_acBitmap[ISO_BITMAP_SZ + 1];
char	g_acCardPAN[ISO_CARDPAN_SZ + 1];			// 2
char	g_acProcCode[ISO_PRODCODE_SZ + 1];			// 3
char	g_acAmt[ISO_AMT_SZ + 1];					// 4
char	g_acTransmDtTm [ISO_DATE_TIME_SZ + 1];		// 7
char	g_acRate[ISO_AMT_SZ + 1];				// 9
char	g_acSTAN[ISO_STAN_SZ + 1];				// 11
char	g_acTxnTime[ISO_TXNTIME_SZ + 1];			// 12
char	g_acTxnDate[ISO_TXNDATE_SZ + 1];			// 13
char	g_acExpDate[ISO_EXPDATE_SZ + 1];			// 14
char	g_acSettleDate[ISO_SETTLEDATE_SZ+1];		// 15
char	g_acPOSEntryMode[ISO_POSENTRYMODE_SZ + 1];	// 22
char	g_acAppPANNo[ISO_APP_PAN_NO_SZ + 1];		// 23
char	g_acNII[ISO_NII_SZ + 1];					// 24
char	g_acPOSCondCode[ISO_POSCONDCODE_SZ + 1];	// 25
char	g_acAcqInstID[ISO_ACQINSTID_SZ + 1];		// 32
char	g_acFwdInstID[ISO_FWDINSTID_SZ + 1];		// 33
char	g_acTrack2[ISO_TRACK2_SZ + 1];			// 35
char	g_acTrack3[ISO_TRACK3_SZ + 1];			// 36
char	g_acRRN[ISO_RRN_SZ + 1];					// 37
char	g_acAuthCode[ISO_AUTHCODE_SZ + 1];			// 38
char	g_acRespCode[ISO_RESPCODE_SZ + 1];			// 39
char	g_acTID[ISO_TID_SZ + 1];					// 41
char	g_acMID[ISO_MID_SZ + 1];					// 42
char	g_acTrack1[ISO_TRACK1_SZ + 1];			// 45
char g_acField47[ISO_FIELD47_SZ + 1];             // 47
char	g_acAddtData[ISO_ADDTDATA_SZ + 1];			// 48
char	g_acTxnCurCode[ISO_TXNCURCODE_SZ + 1];		// 49
char	g_acPINBlock[ISO_PINBLOCK_SZ + 1];			// 52
char g_acAddtAmt[60+1];                 // 54
char	g_acEMVData[ISO_EMVDATA_SZ + 1];			// 55
char	g_acField60[ISO_FIELD60_SZ + 1];			// 60
char	g_acField61[ISO_FIELD61_SZ + 1];			// 61
char	g_acField62[ISO_FIELD62_SZ + 1];			// 62
//ar	g_acField63[ISO_FIELD63_SZ + 1];			// 63
char	g_acField63[1000 + 1];                       // 63   cgc add for GRC
char	g_acMAC[ISO_MAC_SZ + 1];					// 64


ISOField	g_astCUPISOField[MAX_ISO_FIELDS] = {
    { 64, 0, TYPE_B, 'Y', 'L', '0'},	// 1 - Bit Map Extended
    { 19, 1, TYPE_N, 'N', 'L', '0'},	// 2 - Primary Account Number (PAN)
    {  6, 0, TYPE_N, 'Y', 'L', '0'},	// 3 - Processing Code
    { 12, 0, TYPE_N, 'Y', 'L', '0'},	// 4 - Amount, Transaction
    { 12, 0, TYPE_N, 'Y', 'L', '0'},	// 5 - Amount, Settlement
    { 12, 0, TYPE_N, 'Y', 'L', '0'},	// 6 - Amount, Cardholder Billing
    { 10, 0, TYPE_N, 'Y', 'L', '0'},	// 7 - Transmission Date & Time
    {  8, 0, TYPE_N, 'Y', 'L', '0'},	// 8 - Amount, Cardholder Billing Fee
    {  8, 0, TYPE_N, 'Y', 'L', '0'},	// 9 - Conversion Rate, Settlement
    {  8, 0, TYPE_N, 'Y', 'L', '0'},	// 10 - Conversion Rate, Cardholder Billing
    
    {  6, 0, TYPE_N, 'Y', 'L', '0'},	// 11 - Systems Trace Audit Number
    {  6, 0, TYPE_N, 'Y', 'L', '0'},	// 12 - Time, Local Transaction (hhmmss)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 13 - Date, Local Transaction (mmdd)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 14 - Date, Expiration (yymm)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 15 - Date, Settlement (mmdd)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 16 - Date, Conversion (mmdd)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 17 - Date, Capture (mmdd)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 18 - Merchant Type
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 19 - Acquiring Institution Country Code
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 20 - PAN Extended, Country Code
    
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 21 - Forwarding Institution, Country Code
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 22 - Point of Service Entry Mode
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 23 - Application PAN Number
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 24 - Network International Identifier
    {  2, 0, TYPE_N, 'Y', 'L', '0'},	// 25 - Point of Service Condition Code
    {  2, 0, TYPE_N, 'Y', 'L', '0'},	// 26 - Point of Service Capture Code
    {  1, 0, TYPE_N, 'Y', 'L', '0'},	// 27 - Authorising Identification Response Length
    
    //2011-04-26 start
    #if 1
    {  1, 0, TYPE_N, 'Y', 'L', '0'},	// 28 - Amount, Transaction Fee
    #else
    {  9, 0, TYPE_AN, 'Y', 'L', '0'},	// 28 - Amount, Transaction Fee
    #endif
    //2011-04-26 end
    
    {  9, 0, TYPE_AN, 'Y', 'L', '0'},	// 29 - Amount, Settlement Fee
    {  9, 0, TYPE_AN, 'Y', 'L', '0'},	// 30 - Amount, Transaction Processing Fee
    
    {  9, 0, TYPE_AN,  'Y', 'L', '0'},	// 31 - Amount, Settlement Processing Fee
    { 11, 1, TYPE_N,   'N', 'L', '0'},	// 32 - Acquiring Institution Identification Code
    { 11, 1, TYPE_N,   'N', 'L', '0'},	// 33 - Forwarding Institution Identification Code
    { 28, 1, TYPE_ANS, 'N', 'L', '0'},	// 34 - Primary Account Number, Extended
    { 37, 1, TYPE_Z,   'N', 'L', '0'},	// 35 - Track 2 Data
    //{104, 2, TYPE_N,	'N', 'L', '0'},	// 36 - Track 3 Data
    {105, 2, TYPE_N,	'N', 'L', '0'},	// 36 - Track 3 Data
    { 12, 0, TYPE_AN,  'Y', 'L', '0'},	// 37 - Retrieval Reference Number
    {  6, 0, TYPE_AN,  'Y', 'L', '0'},	// 38 - Authorization Identification Response
    {  2, 0, TYPE_AN,  'Y', 'L', '0'},	// 39 - Response Code
    {  3, 0, TYPE_AN,  'Y', 'L', '0'},	// 40 - Service Restriction Code
    {  8, 0, TYPE_ANS, 'Y', 'R', 0x20},	// 41 - Card Acceptor Terminal Identification
    { 15, 0, TYPE_ANS, 'Y', 'R', 0x20},	// 42 - Card Acceptor Identification Code
    { 40, 0, TYPE_ANS, 'Y', 'L', '0'},	// 43 - Card Acceptor Name/Location
    { 25, 1, TYPE_ANS, 'N', 'L', '0'},	// 44 - Additional Response Data
    { 76, 1, TYPE_ANS, 'N', 'L', '0'},	// 45 - Track 1 Data
    { 25, 1, TYPE_ANS, 'N', 'L', '0'},	// 46 - Additional Data - ISO
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 47 - Additional Data - National
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 48 - Additional Data - Private
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 49 - Currency Code, Transaction
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 50 - Currency Code, Settlement
    
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 51 - Currency Code, Cardholder Billing
    { 8, 0, TYPE_ANS,   'Y', 'L', '0'},	// 52 - Personal Identification Number Data
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 53 - Security Related Control Information
    {120, 1, TYPE_ANS,  'N', 'L', '0'},	// 54 - Additional Amounts
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 55 - Reserved ISO
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 56 - Reserved ISO
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 57 - Reserved National
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 58 - Reserved National
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 59 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 60 - Advice/Reason Code (Private Reserved) (Terminal Data)
    
    {27, 2, TYPE_ANS, 'N', 'L', '0'},	// 61 - Reserved Private (Card Issuer-Category-Response Code Data)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 62 - Reserved Private (Postal Code)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 63 - Reserved Private (Additional Data)
    { 8, 0, TYPE_ANS,   'Y', 'R', '0'},	// 64 - Message Authentication Code (MAC)
    { 64, 0, TYPE_B,   'Y', 'L', '0'},	// 65 - Bit Map, Tertiary
    {  1, 0, TYPE_N,   'Y', 'L', '0'},	// 66 - Settlement Code
    {  2, 0, TYPE_N,   'Y', 'L', '0'},	// 67 - Extended Payment Code
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 68 - Receiving Institution Country Code
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 69 - Settlement Institution Country Code
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 70 - Network Management Information Code
    
    {  4, 0, TYPE_N,   'Y', 'L', '0'},	// 71 - Message Number
    {  4, 0, TYPE_N,   'Y', 'L', '0'},	// 72 - Message Number, Last
    {  6, 0, TYPE_N,   'Y', 'L', '0'},	// 73 - Date, Action (yymmdd)
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 74 - Credits, Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 75 - Credits, Reversal Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 76 - Debits, Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 77 - Debits, Reversal Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 78 - Transfer, Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 79 - Transfer, Reversal Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 80 - Inquiries, Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 81 - Authorisations, Number
    { 12, 0, TYPE_N,   'Y', 'L', '0'},	// 82 - Credits, Processing Fee Amount
    { 12, 0, TYPE_N,   'Y', 'L', '0'},	// 83 - Credits, Transaction Fee Amount
    { 12, 0, TYPE_N,   'Y', 'L', '0'},	// 84 - Debits, Processing Fee Amount
    { 12, 0, TYPE_N,   'Y', 'L', '0'},	// 85 - Debits, Transaction Fee Amount
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 86 - Credits, Amount
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 87 - Credits, Reversal Amount
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 88 - Debits, Amount
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 89 - Debits, Reversal Amount
    { 42, 0, TYPE_N,   'Y', 'L', '0'},	// 90 - Original Data Elements
    
    {  1, 0, TYPE_AN,  'Y', 'L', '0'},	// 91 - File Update Code
    {  2, 0, TYPE_AN,  'Y', 'L', '0'},	// 92 - File Security Code
    {  5, 0, TYPE_AN,  'Y', 'L', '0'},	// 93 - Response Indicator
    {  7, 0, TYPE_AN,  'Y', 'L', '0'},	// 94 - Service Indicator
    { 42, 0, TYPE_N,   'Y', 'L', '0'},	// 95 - Replacement Amounts
    { 64, 0, TYPE_B,   'Y', 'L', '0'},	// 96 - Message Security Code
    { 17, 0, TYPE_AN,  'Y', 'L', '0'},	// 97 - Amount, Net Settlement
    { 25, 0, TYPE_ANS, 'Y', 'L', '0'},	// 98 - Payee
    { 11, 1, TYPE_N,   'N', 'L', '0'},	// 99 - Settlement Institution Identification Code
    { 11, 1, TYPE_N,   'N', 'L', '0'},	// 100 - Receiving Institution Identification Code
    
    { 17, 1, TYPE_ANS, 'N', 'L', '0'},	// 101 - File Name
    { 28, 1, TYPE_ANS, 'N', 'L', '0'},	// 102 - Account Identification 1
    { 28, 1, TYPE_ANS, 'N', 'L', '0'},	// 103 - Account Identification 2
    {100, 2, TYPE_ANS, 'N', 'L', '0'},	// 104 - Transaction Description
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 105 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 106 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 107 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 108 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 109 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 110 - Reserved for ISO Use
    
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 111 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 112 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 113 - Authorising Agent Institution ID Code
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 114 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 115 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 116 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 117 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 118 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 119 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 120 - Reserved Private (Key Management / Terminal Address-Branch)
    
    {999, 2, TYPE_N,   'N', 'L', '0'},	// 121 - Reserved Private (Auth Indicators-CRT Authorization Data)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 122 - Reserved Private (Card Issuer Identification Code)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 123 - Reserved Private (Cryptographic Service Message / Invoice Data)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 124 - Info Text / Batch and Shift Data
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 125 - Network Management Information / Settlement Data
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 126 - Issuer Trace ID / Pre-Auth and Chargeback Data
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 127 - Reserved for Private Use (User Data)
    { 64, 0, TYPE_B,   'Y', 'R', '0'}	// 128 - Message Authentication Code (MAC)
};



ISOFieldRec	g_astISOFieldRec[MAX_ISO_FIELDS] = {
    {0, g_acDummy, 0},		// 1
    {0, g_acCardPAN, 0},      // 2
    {0, g_acProcCode, 0},	// 3
    {0, g_acAmt, 0},		// 4
    {0, g_acDummy, 0},		// 5
    {0, g_acDummy, 0},		// 6
    {0, g_acTransmDtTm, 0},	// 7
    {0, g_acDummy, 0},		// 8
    {0, g_acRate, 0},		// 9
    {0, g_acDummy, 0},		// 10
    {0, g_acSTAN, 0},		// 11
    {0, g_acTxnTime, 0},      // 12
    {0, g_acTxnDate, 0},      // 13
    {0, g_acExpDate, 0},      // 14
    {0, g_acSettleDate, 0},	// 15
    {0, g_acDummy, 0},		// 16
    {0, g_acDummy, 0},		// 17
    {0, g_acDummy, 0},		// 18
    {0, g_acDummy, 0},		// 19
    {0, g_acDummy, 0},		// 20
    {0, g_acDummy, 0},		// 21
    {0, g_acPOSEntryMode, 0}, // 22
    {0, g_acAppPANNo, 0},	// 23
    {0, g_acNII, 0},		// 24
    {0, g_acPOSCondCode, 0},  // 25
    {0, g_acDummy, 0},		// 26
    {0, g_acDummy, 0},		// 27
    {0, g_acDummy, 0},		// 28
    {0, g_acDummy, 0},		// 29
    {0, g_acDummy, 0},		// 30
    {0, g_acDummy, 0},		// 31
    {0, g_acAcqInstID, 0},	// 32
    {0, g_acFwdInstID, 0},	// 33
    {0, g_acDummy, 0},		// 34
    {0, g_acTrack2, 0},		// 35
    {0, g_acTrack3, 0},		// 36
    {0, g_acRRN, 0},		// 37
    {0, g_acAuthCode, 0},	// 38
    {0, g_acRespCode, 0},	// 39
    {0, g_acDummy, 0},		// 40
    {0, g_acTID, 0},		// 41
    {0, g_acMID, 0},		// 42
    {0, g_acField43, 0},      // 43
    {0, g_acDummy, 0},		// 44
    {0, g_acTrack1, 0},		// 45
    {0, g_acDummy, 0},		// 46
    {0, g_acDummy, 0},		// 47
    {0, g_acAddtData, 0},	// 48
    {0, g_acTxnCurCode, 0},	// 49
    {0, g_acDummy, 0},		// 50
    {0, g_acDummy, 0},		// 51
    {0, g_acPINBlock, 0},	// 52
    {0, g_acDummy, 0},		// 53
    
    //hy 2010-11-23
    //{0, g_acDummy, 0},	// 54
    {0, g_acAddtAmt, 0},	// 54
    //hy 2010-11-23
    
    {0, g_acEMVData, 0},	// 55
    {0, g_acDummy, 0},		// 56
    {0, g_acDummy, 0},		// 57
    {0, g_acDummy, 0},		// 58
    {0, g_acDummy, 0},		// 59
    {0, g_acField60, 0},	// 60
    {0, g_acField61, 0},	// 61
    {0, g_acField62, 0},	// 62
    {0, g_acField63, 0},	// 63
    {0, g_acMAC, 0},		// 64
};


ISOField	g_astISOField[MAX_ISO_FIELDS] = {
    { 64, 0, TYPE_B, 'Y', 'L', '0'},	// 1 - Bit Map Extended
    { 19, 1, TYPE_N, 'N', 'R', '0'},	// 2 - Primary Account Number (PAN)
    {  6, 0, TYPE_N, 'Y', 'L', '0'},	// 3 - Processing Code
    { 12, 0, TYPE_N, 'Y', 'L', '0'},	// 4 - Amount, Transaction
    { 12, 0, TYPE_N, 'Y', 'L', '0'},	// 5 - Amount, Settlement
    { 12, 0, TYPE_N, 'Y', 'L', '0'},	// 6 - Amount, Cardholder Billing
    { 10, 0, TYPE_N, 'Y', 'L', '0'},	// 7 - Transmission Date & Time
    {  8, 0, TYPE_N, 'Y', 'L', '0'},	// 8 - Amount, Cardholder Billing Fee
    {  8, 0, TYPE_N, 'Y', 'L', '0'},	// 9 - Conversion Rate, Settlement
    {  8, 0, TYPE_N, 'Y', 'L', '0'},	// 10 - Conversion Rate, Cardholder Billing
    
    {  6, 0, TYPE_N, 'Y', 'L', '0'},	// 11 - Systems Trace Audit Number
    {  6, 0, TYPE_N, 'Y', 'L', '0'},	// 12 - Time, Local Transaction (hhmmss)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 13 - Date, Local Transaction (mmdd)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 14 - Date, Expiration (yymm)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 15 - Date, Settlement (mmdd)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 16 - Date, Conversion (mmdd)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 17 - Date, Capture (mmdd)
    {  4, 0, TYPE_N, 'Y', 'L', '0'},	// 18 - Merchant Type
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 19 - Acquiring Institution Country Code
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 20 - PAN Extended, Country Code
    
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 21 - Forwarding Institution, Country Code
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 22 - Point of Service Entry Mode
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 23 - Application PAN Number
    {  3, 0, TYPE_N, 'Y', 'L', '0'},	// 24 - Network International Identifier
    {  2, 0, TYPE_N, 'Y', 'L', '0'},	// 25 - Point of Service Condition Code
    {  2, 0, TYPE_N, 'Y', 'L', '0'},	// 26 - Point of Service Capture Code
    {  1, 0, TYPE_N, 'Y', 'L', '0'},	// 27 - Authorising Identification Response Length
    
    //2011-04-29 start
    #if 1
    {  1, 0, TYPE_N, 'Y', 'L', '0'},	// 28 - Amount, Transaction Fee
    #else
    {  9, 0, TYPE_AN, 'Y', 'L', '0'},	// 28 - Amount, Transaction Fee
    #endif
    //2011-04-29 end
    
    {  9, 0, TYPE_AN, 'Y', 'L', '0'},	// 29 - Amount, Settlement Fee
    {  9, 0, TYPE_AN, 'Y', 'L', '0'},	// 30 - Amount, Transaction Processing Fee
    
    {  9, 0, TYPE_AN,  'Y', 'L', '0'},	// 31 - Amount, Settlement Processing Fee
    { 11, 1, TYPE_N,   'N', 'L', '0'},	// 32 - Acquiring Institution Identification Code
    { 11, 1, TYPE_N,   'N', 'L', '0'},	// 33 - Forwarding Institution Identification Code
    { 28, 1, TYPE_ANS, 'N', 'L', '0'},	// 34 - Primary Account Number, Extended
    { 37, 1, TYPE_Z,   'N', 'R', '0'},	// 35 - Track 2 Data
    //	{ 37, 1, TYPE_ANS, 'N', 'R', '0'},	// 35 - Track 2 Data	//COK
    {104, 2, TYPE_N,	'N', 'R', '0'},	// 36 - Track 3 Data
    { 12, 0, TYPE_AN,  'Y', 'L', '0'},	// 37 - Retrieval Reference Number
    {  6, 0, TYPE_AN,  'Y', 'L', '0'},	// 38 - Authorization Identification Response
    {  2, 0, TYPE_AN,  'Y', 'L', '0'},	// 39 - Response Code
    {  3, 0, TYPE_AN,  'Y', 'L', '0'},	// 40 - Service Restriction Code
    
    {  8, 0, TYPE_ANS, 'Y', 'R', 0x20},	// 41 - Card Acceptor Terminal Identification
    { 15, 0, TYPE_ANS, 'Y', 'R', 0x20},	// 42 - Card Acceptor Identification Code
    { 40, 0, TYPE_ANS, 'Y', 'L', '0'},	// 43 - Card Acceptor Name/Location
    { 25, 1, TYPE_ANS, 'N', 'L', '0'},	// 44 - Additional Response Data
    { 76, 1, TYPE_ANS, 'N', 'L', '0'},	// 45 - Track 1 Data
    { 25, 2, TYPE_ANS, 'N', 'L', '0'},	// 46 - Additional Data - ISO
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 47 - Additional Data - National
    //	{999, 2, TYPE_B, 'N', 'L', '0'},	// 47 - Additional Data - National	//2006/09/11  //COK
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 48 - Additional Data - Private
    {  3, 0, TYPE_AN,   'Y', 'L', '0'},	// 49 - Currency Code, Transaction
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 50 - Currency Code, Settlement
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 51 - Currency Code, Cardholder Billing
    //	{ 64, 0, TYPE_B,   'Y', 'L', '0'},	// 52 - Personal Identification Number Data
    { 8, 0, TYPE_ANS,   'Y', 'L', '0'},	// 52 - Personal Identification Number Data
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 53 - Security Related Control Information
    //	{ 16, 0, TYPE_ANS,   'Y', 'L', '0'},	// 53 - Security Related Control Information
    //	{120, 1, TYPE_AN,  'N', 'L', '0'},	// 54 - Additional Amounts
    //	{120, 2, TYPE_ANS, 'N', 'L', '0'},	// 54 - Additional Amounts	//COK
    {120, 1, TYPE_ANS,  'N', 'L', '0'},	// 54 - Additional Amounts	//Bocom Tips Adjust & Amt Adjust
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 55 - Reserved ISO
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 56 - Reserved ISO
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 57 - Reserved National
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 58 - Reserved National
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 59 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 60 - Advice/Reason Code (Private Reserved) (Terminal Data)
    
    
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 61 - Reserved Private (Card Issuer-Category-Response Code Data)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 62 - Reserved Private (Postal Code)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 63 - Reserved Private (Additional Data)
    //	{ 64, 0, TYPE_B,   'Y', 'R', '0'},	// 64 - Message Authentication Code (MAC)
    { 8, 0, TYPE_ANS,   'Y', 'R', '0'},	// 64 - Message Authentication Code (MAC)
    { 64, 0, TYPE_B,   'Y', 'L', '0'},	// 65 - Bit Map, Tertiary
    {  1, 0, TYPE_N,   'Y', 'L', '0'},	// 66 - Settlement Code
    {  2, 0, TYPE_N,   'Y', 'L', '0'},	// 67 - Extended Payment Code
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 68 - Receiving Institution Country Code
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 69 - Settlement Institution Country Code
    {  3, 0, TYPE_N,   'Y', 'L', '0'},	// 70 - Network Management Information Code
    
    {  4, 0, TYPE_N,   'Y', 'L', '0'},	// 71 - Message Number
    {  4, 0, TYPE_N,   'Y', 'L', '0'},	// 72 - Message Number, Last
    {  6, 0, TYPE_N,   'Y', 'L', '0'},	// 73 - Date, Action (yymmdd)
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 74 - Credits, Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 75 - Credits, Reversal Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 76 - Debits, Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 77 - Debits, Reversal Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 78 - Transfer, Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 79 - Transfer, Reversal Number
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 80 - Inquiries, Number
    
    { 10, 0, TYPE_N,   'Y', 'L', '0'},	// 81 - Authorisations, Number
    { 12, 0, TYPE_N,   'Y', 'L', '0'},	// 82 - Credits, Processing Fee Amount
    { 12, 0, TYPE_N,   'Y', 'L', '0'},	// 83 - Credits, Transaction Fee Amount
    { 12, 0, TYPE_N,   'Y', 'L', '0'},	// 84 - Debits, Processing Fee Amount
    { 12, 0, TYPE_N,   'Y', 'L', '0'},	// 85 - Debits, Transaction Fee Amount
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 86 - Credits, Amount
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 87 - Credits, Reversal Amount
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 88 - Debits, Amount
    { 16, 0, TYPE_N,   'Y', 'L', '0'},	// 89 - Debits, Reversal Amount
    { 42, 0, TYPE_N,   'Y', 'L', '0'},	// 90 - Original Data Elements
    
    {  1, 0, TYPE_AN,  'Y', 'L', '0'},	// 91 - File Update Code
    {  2, 0, TYPE_AN,  'Y', 'L', '0'},	// 92 - File Security Code
    {  5, 0, TYPE_AN,  'Y', 'L', '0'},	// 93 - Response Indicator
    {  7, 0, TYPE_AN,  'Y', 'L', '0'},	// 94 - Service Indicator
    { 42, 0, TYPE_N,   'Y', 'L', '0'},	// 95 - Replacement Amounts
    { 64, 0, TYPE_B,   'Y', 'L', '0'},	// 96 - Message Security Code
    { 17, 0, TYPE_AN,  'Y', 'L', '0'},	// 97 - Amount, Net Settlement
    { 25, 0, TYPE_ANS, 'Y', 'L', '0'},	// 98 - Payee
    { 11, 1, TYPE_N,   'N', 'L', '0'},	// 99 - Settlement Institution Identification Code
    { 11, 1, TYPE_N,   'N', 'L', '0'},	// 100 - Receiving Institution Identification Code
    { 17, 1, TYPE_ANS, 'N', 'L', '0'},	// 101 - File Name
    { 28, 1, TYPE_ANS, 'N', 'L', '0'},	// 102 - Account Identification 1
    { 28, 1, TYPE_ANS, 'N', 'L', '0'},	// 103 - Account Identification 2
    {100, 2, TYPE_ANS, 'N', 'L', '0'},	// 104 - Transaction Description
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 105 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 106 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 107 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 108 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 109 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 110 - Reserved for ISO Use
    
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 111 - Reserved for ISO Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 112 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 113 - Authorising Agent Institution ID Code
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 114 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 115 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 116 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 117 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 118 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 119 - Reserved for National Use
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 120 - Reserved Private (Key Management / Terminal Address-Branch)
    
    {999, 2, TYPE_N,   'N', 'L', '0'},	// 121 - Reserved Private (Auth Indicators-CRT Authorization Data)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 122 - Reserved Private (Card Issuer Identification Code)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 123 - Reserved Private (Cryptographic Service Message / Invoice Data)
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 124 - Info Text / Batch and Shift Data
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 125 - Network Management Information / Settlement Data
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 126 - Issuer Trace ID / Pre-Auth and Chargeback Data
    {999, 2, TYPE_ANS, 'N', 'L', '0'},	// 127 - Reserved for Private Use (User Data)
    { 64, 0, TYPE_B,   'Y', 'R', '0'}	// 128 - Message Authentication Code (MAC)
};


void initStruct()
{
     memset(g_acDummy,0,sizeof(g_acDummy));
     memset(g_acCardPAN,0,sizeof(g_acCardPAN));
     memset(g_acProcCode,0,sizeof(g_acProcCode));
     memset(g_acAmt,0,sizeof(g_acAmt));
     memset(g_acTransmDtTm,0,sizeof(g_acTransmDtTm));
     memset(g_acRate,0,sizeof(g_acRate));
     memset(g_acSTAN,0,sizeof(g_acSTAN));
     memset(g_acTxnTime,0,sizeof(g_acTxnTime));
     memset(g_acTxnDate,0,sizeof(g_acTxnDate));
     memset(g_acExpDate,0,sizeof(g_acExpDate));
     memset(g_acSettleDate,0,sizeof(g_acSettleDate));
     memset(g_acPOSEntryMode,0,sizeof(g_acPOSEntryMode));
     memset(g_acAppPANNo,0,sizeof(g_acAppPANNo));
     memset(g_acNII,0,sizeof(g_acNII));
     memset(g_acPOSCondCode,0,sizeof(g_acPOSCondCode));
     memset(g_acAcqInstID,0,sizeof(g_acAcqInstID));
     memset(g_acFwdInstID,0,sizeof(g_acFwdInstID));
     memset(g_acTrack2,0,sizeof(g_acTrack2));
     memset(g_acTrack3,0,sizeof(g_acTrack3));
     memset(g_acRRN,0,sizeof(g_acRRN));
     memset(g_acAuthCode,0,sizeof(g_acAuthCode));
     memset(g_acRespCode,0,sizeof(g_acRespCode));
     memset(g_acTID,0,sizeof(g_acTID));
     memset(g_acMID,0,sizeof(g_acMID));
}

unsigned long	ulResetAllFields (void)
{
    unsigned long ulRet = 0;
    int	iLoop;
    
    for (iLoop = 1; iLoop < MAX_ISO_FIELDS; iLoop++)
    {
        g_astISOFieldRec[iLoop].cFlag = 0;
    }
    
    return ulRet;
}

unsigned long	ulSetTPDU (char *p_pcInput, int p_iLen)
{
    unsigned long ulRet = 0;
    memcpy (g_acTPDU, p_pcInput, p_iLen);
    g_acTPDU[p_iLen] = 0;
    
    return ulRet;
}


unsigned long	ulSetMTI (char *p_pcInput, int p_iLen)
{
    unsigned long ulRet = 0;
    
    memcpy (g_acMTI, p_pcInput, p_iLen);
    g_acMTI[p_iLen] = 0;
    
    return ulRet;
}


unsigned long	ulSetField (int p_iIdx, char *p_pcInput, int p_iLen)
{
    unsigned long ulRet = 0;
    
    if (p_iIdx > MAX_ISO_FIELDS || p_iIdx < 2)
    {
        ulRet = 1;
        goto CleanUp;
    }
    
    memcpy (g_astISOFieldRec[p_iIdx - 1].pcVal, p_pcInput, p_iLen);
    g_astISOFieldRec[p_iIdx - 1].pcVal[p_iLen] = 0;
    g_astISOFieldRec[p_iIdx - 1].iLen = p_iLen;
    g_astISOFieldRec[p_iIdx - 1].cFlag = 1;
    
CleanUp:
    
    return ulRet;
}




unsigned long	ulGetTPDU (char *p_pcOutput, int *p_piLen)
{
    unsigned long ulRet = 0;    
    strcpy (p_pcOutput, g_acTPDU);
    *p_piLen = (int)strlen (g_acTPDU);
    
    return ulRet;
}

unsigned long	ulGetMTI (char *p_pcOutput, int *p_piLen)
{
    unsigned long ulRet = 0;
    
    strcpy (p_pcOutput, g_acMTI);
    *p_piLen = (int)strlen (g_acMTI);
    
    return ulRet;
}


unsigned long	ulGetField (int p_iIdx, char *p_pcOutput, int *p_piLen)
{
    unsigned long ulRet = 0;
    
    *p_piLen = 0;	//hy 2010-12-14
    
    if (p_iIdx > MAX_ISO_FIELDS || p_iIdx < 2)
    {
        ulRet = 1;
        goto CleanUp;
    }
    
    if (0 == g_astISOFieldRec[p_iIdx - 1].cFlag)
    {
        ulRet = 2;
        goto CleanUp;
    }
    
    memcpy (p_pcOutput, g_astISOFieldRec[p_iIdx - 1].pcVal, g_astISOFieldRec[p_iIdx - 1].iLen);
    p_pcOutput[g_astISOFieldRec[p_iIdx - 1].iLen] = 0;
    (*p_piLen) = g_astISOFieldRec[p_iIdx - 1].iLen;
    
CleanUp:
    
    return ulRet;
}

unsigned long	ulGenBitmap (unsigned char *p_pucBitmap, int *p_piLen)
{
    unsigned long	ulRet = 0;
    unsigned long	ulGrp1 = 0;
    unsigned long	ulGrp2 = 0;
    unsigned long	ulGrp3 = 0;
    unsigned long	ulGrp4 = 0;
    unsigned long	ulOne = 1;
    int				iLoop;
    
    // Get all Field IDs in the Message Container and set the bitmap
    for (iLoop = 2; iLoop <= MAX_ISO_FIELDS; iLoop++)
    {
        if (0 == g_astISOFieldRec[iLoop - 1].cFlag) continue;
        
        if (iLoop > 96)
            ulGrp4 += (ulOne << (128 - iLoop));
        else if (iLoop > 64)
            ulGrp3 += (ulOne << (96 - iLoop));
        else if (iLoop > 32)
            ulGrp2 += (ulOne << (64 - iLoop));
        else
            ulGrp1 += (ulOne << (32 - iLoop));
    }
    
    if (ulGrp3 != 0 || ulGrp4 != 0)
    {
        *p_piLen = DEFAULT_BITMAP_SZ * 2;
        
        for (iLoop = 0; iLoop < 4 ; iLoop++)
            (p_pucBitmap)[iLoop + 8] = (int) (ulGrp3 >> ((4 - iLoop - 1) * DEFAULT_BITMAP_SZ));
        
        for (iLoop = 0; iLoop < 4 ; iLoop++)
            (p_pucBitmap)[iLoop + 12] = (int) (ulGrp4 >> ((4 - iLoop - 1) * DEFAULT_BITMAP_SZ));
    }
    else
    {
        *p_piLen = DEFAULT_BITMAP_SZ;
    }
    
    for (iLoop = 0; iLoop < 4 ; iLoop++)
        (p_pucBitmap)[iLoop] = (int) (ulGrp1 >> ((4 - iLoop - 1) * DEFAULT_BITMAP_SZ));
    
    for (iLoop = 0; iLoop < 4 ; iLoop++)
        (p_pucBitmap)[iLoop + 4] = (int) (ulGrp2 >> ((4 - iLoop - 1) * DEFAULT_BITMAP_SZ));
    
    if (ulGrp3 != 0 || ulGrp4 != 0)
        (p_pucBitmap)[0] |= 1 << (DEFAULT_BITMAP_SZ - 1);
    
    return ulRet;
}


unsigned long	ulFormField (int p_iFieldIdx, char *p_pcVal, int p_iLen, unsigned char *p_pucBuf, int *p_piIdx, char *p_pcErrMsg)
{
    unsigned long	ulRet = 0;
    int				iRet;
    int				iLoop;
    int				iLen = 0;
    int				iDataLen = 0;
    int				iSize;
    char			cType;
    char			cFixed;
    char			cPadPos;
    char			cPadChar;
    char			*pcTemp = p_pcVal;
    char			acHex[MAX_FIELD_LEN + 1];
    unsigned char	aucTemp[MAX_TEMP_BUFFER_SZ];

    iDataLen = p_iLen;

     iSize	= g_astCUPISOField[p_iFieldIdx - 1].iSize;
     iLen      = g_astCUPISOField[p_iFieldIdx - 1].iLen;
     cFixed	= g_astCUPISOField[p_iFieldIdx - 1].cFixed;
     cType	= g_astCUPISOField[p_iFieldIdx - 1].cType;
     cPadPos   = g_astCUPISOField[p_iFieldIdx - 1].cPadPos;
     cPadChar  = g_astCUPISOField[p_iFieldIdx - 1].cPadChar;

    // Padding ISO Field
    if ('N' == cFixed)
    {
        if (iDataLen > iSize) iDataLen = iSize;
        
        if (I_ISO_8583 == g_iStandard)
        {
            if (TYPE_B == cType)
            {
                iDataLen = iDataLen / 2;
            }
            sprintf (acHex, "%d", iDataLen);
            
            if (2 == iLen)
            {
                if (iDataLen < 10)
                {
                    acHex[3] = acHex[0];
                    acHex[2] = acHex[1] = acHex[0] = '0';
                }
                else if (iDataLen < 100)
                {
                    acHex[3] = acHex[1];
                    acHex[2] = acHex[0];
                    acHex[1] = acHex[0] = '0';
                }
                else if (iDataLen < 1000)
                {
                    acHex[3] = acHex[2];
                    acHex[2] = acHex[1];
                    acHex[1] = acHex[0];
                    acHex[0] = '0';
                }
                acHex[4] = 0;
            }
            else
            {
                if (iDataLen < 10)
                {
                    acHex[1] = acHex[0];
                    acHex[0] = '0';
                }
                acHex[2] = 0;
            }

            iRet = iHexToByte (acHex, aucTemp, &iLen);

            memcpy (p_pucBuf + *p_piIdx, aucTemp, iLen);
        }
        else
        {
            sprintf (acHex, "%d", iDataLen);
            
            if (3 == iLen)
            {
                if (iDataLen < 10)
                {
                    acHex[2] = acHex[0];
                    acHex[1] = acHex[0] = '0';
                }
                else if (iDataLen < 100)
                {
                    acHex[2] = acHex[1];
                    acHex[1] = acHex[0];
                    acHex[0] = '0';
                }
                acHex[3] = 0;
            }
            else if (2 == iLen)
            {
                if (iDataLen < 10)
                {
                    acHex[1] = acHex[0];
                    acHex[0] = '0';
                }
                acHex[2] = 0;
            }

            memcpy (p_pucBuf + *p_piIdx, acHex, iLen);
        }
        (*p_piIdx) += iLen;
    }
    // Based on the type of the field, form the data in appropriate field type
    if (TYPE_A == cType || TYPE_AN == cType || TYPE_ANS == cType)
    {
        if ('Y' == cFixed)
        {
            memset (p_pucBuf + *p_piIdx, cPadChar, iSize);
            
            if (iDataLen > iSize) iDataLen = iSize;
            
            if ('L' == cPadPos)
            {

                memcpy (p_pucBuf + *p_piIdx + iSize - iDataLen, pcTemp, iDataLen);
            }
            else if ('R' == cPadPos)
            {

                memcpy (p_pucBuf + *p_piIdx, pcTemp, iDataLen);
            }
            
            if (iDataLen < iSize) iDataLen = iSize;
        }
        else
        {

            memcpy (p_pucBuf + *p_piIdx, pcTemp, iDataLen);
        }
        
        (*p_piIdx) += iDataLen;
        
    }
    else if (TYPE_N == cType)
    {
        if ('Y' == cFixed)
        {
            if (0 != iSize % 2) iSize++;
        }
        else
        {
            iSize = (0 != iDataLen % 2) ? iDataLen + 1 : iDataLen;
        }
        if (iDataLen >= iSize)
        {
            memcpy (aucTemp, pcTemp, iSize);
        }
        else
        {
            memset (aucTemp, cPadChar, iSize);
            
            if ('L' == cPadPos)
                memcpy (aucTemp + iSize - iDataLen, pcTemp, iDataLen);
            else if ('R' == cPadPos)
                memcpy (aucTemp, pcTemp, iDataLen);
        }
        aucTemp[iSize] = 0;

        iRet = iHexToByte ((char *) aucTemp, p_pucBuf + *p_piIdx, &iLen);
        
        (*p_piIdx) += iLen;
    }
    else if (TYPE_B == cType)
    {
        if ('Y' == cFixed)
        {
            if (iDataLen > iSize / 4) iDataLen = iSize / 4;
        }
        else
        {
            iDataLen *= 2;
        }
        
        if ('N' == cFixed || iDataLen >= iSize / 4)
        {
            strncpy ((char *) aucTemp, pcTemp, iDataLen);
            aucTemp[iDataLen] = 0;
        }
        else
        {
            memset (aucTemp, cPadChar, iSize / 4);
            
            if ('L' == cPadPos)
            {

                memcpy (aucTemp + (iSize / 4) - iDataLen, pcTemp, iDataLen);
            }
            else if ('R' == cPadPos)
            {

                memcpy (aucTemp, pcTemp, iDataLen);
            }
            
            aucTemp[iSize / 4] = 0;
        }

        iRet = iHexToByte ((char *) aucTemp, aucTemp, &iLen);

        
        memcpy (p_pucBuf + *p_piIdx, aucTemp, iLen);
        (*p_piIdx) += iLen;
    }
    else if (TYPE_Z == cType) 
    {
        if ('Y' == cFixed)
        {
            if (0 != iSize % 2) iSize++;
        }
        else
        {
            iSize = (0 != iDataLen % 2) ? iDataLen + 1 : iDataLen;
        }
        
        if (iDataLen >= iSize)
        {
            for (iLoop = 0; iLoop < iSize; iLoop++)
                aucTemp[iLoop] = ('=' == pcTemp[iLoop]) ? 'D' : pcTemp[iLoop];
        }
        
        else
        {
            memset (aucTemp, cPadChar, iSize);
            
            if ('L' == cPadPos)
                memcpy (aucTemp + iSize - iDataLen, pcTemp, iDataLen);
            else if ('R' == cPadPos)
                memcpy (aucTemp, pcTemp, iDataLen);
            
            for (iLoop = 0; iLoop < iSize; iLoop++)
                if ('=' == aucTemp[iLoop]) aucTemp[iLoop] = 'D';
        }
        aucTemp[iSize] = 0;

        iRet = iHexToByte ((char *) aucTemp, p_pucBuf + *p_piIdx, &iLen);
        (*p_piIdx) += iLen;
    }
    
    return ulRet;
}

unsigned long	ulForm (unsigned char *p_pucOutput, int *p_piLen, char *p_pcErrMsg)
{
    unsigned long	ulRet = 0;
    int				iIdx = 0, iLoop;
    int				iLen;
    int				iRet;
    char			*pcTemp = 0;
    char			acTemp[MAX_TEMP_BUFFER_SZ];
    unsigned char	aucTemp[MAX_TEMP_BUFFER_SZ];
    unsigned char	aucBuffer[MAX_ISO_MESG_SZ];
    
    //TPDU
    pcTemp = g_acTPDU;
    Print("g_acTPDU=%s\n",pcTemp);
    if (pcTemp && 0 != pcTemp[0])
    {
        if (I_ISO_8583 == g_iStandard)
        {

            iRet = iHexToByte (pcTemp, aucTemp, &iLen);
            memcpy (aucBuffer + iIdx, aucTemp, iLen);

            iIdx += iLen;
        }
        else if (I_ISO_B24 == g_iStandard)
        {
            memcpy (aucBuffer + iIdx, pcTemp, g_iHeader);
            iIdx += g_iHeader;
        }
    }
    else
    {
        if (g_iHeader > 0)
        {
            ulRet = E_MISSING_DATA;
            printf("Missing Header\n");
            goto CleanUp;
        }
    }//end

     //版本号
     pcTemp = "1304";
     if (I_ISO_8583 == g_iStandard)
     {

          iRet = iHexToByte (pcTemp, aucTemp, &iLen);
          memcpy (aucBuffer + iIdx, aucTemp, iLen);

          iIdx += iLen;
     }
     else if (I_ISO_B24 == g_iStandard)
     {
          memcpy (aucBuffer + iIdx, pcTemp, g_iHeader);
          iIdx += g_iHeader;
     }//end

    //消息类型
    pcTemp = g_acMTI;
    if (pcTemp && 0 != pcTemp[0])
    {
        if (I_ISO_8583 == g_iStandard)
        {

            iRet = iHexToByte (pcTemp, aucTemp, &iLen);
            memcpy (aucBuffer + iIdx, aucTemp, iLen);

            iIdx += iLen;
        }
        else if (I_ISO_B24 == g_iStandard)
        {
            iLen = (int)strlen (pcTemp);
            memcpy (aucBuffer + iIdx, pcTemp, iLen);
            iIdx += iLen;
        }
    }
    else
    {
        ulRet = E_MISSING_DATA;
        Print("Missing MTI\n");
        goto CleanUp;
    }//end
    
    //位图
    ulRet = ulGenBitmap (aucTemp, &iLen);
     Print("aucTemp===%s\n",aucTemp);
    if (I_ISO_8583 == g_iStandard)
    {
        memcpy (aucBuffer + iIdx, aucTemp, iLen);

        iIdx += iLen;
        iRet = iByteToHex (aucTemp, iLen, acTemp);
    }
    else if (I_ISO_B24 == g_iStandard)
    {
        iRet = iByteToHex (aucTemp, iLen, acTemp);
        memcpy (aucBuffer + iIdx, acTemp, iLen * 2);
        iIdx += iLen * 2;
    }//end
    
    //根据位图 组 后面 各域的值
    for (iLoop = 2; iLoop <= MAX_ISO_FIELDS; iLoop++)
    {
        if (0 == g_astISOFieldRec[iLoop - 1].cFlag) continue;
        
        // Get the field value.
        pcTemp = g_astISOFieldRec[iLoop - 1].pcVal;
        iLen = g_astISOFieldRec[iLoop - 1].iLen;
        ulRet = ulFormField (iLoop, pcTemp, iLen, aucBuffer, &iIdx, p_pcErrMsg);
    }//end
    
    *p_piLen = iIdx;
    memcpy (p_pucOutput, aucBuffer, iIdx);
    p_pucOutput[iIdx] = 0;
    
CleanUp:
    
    return ulRet;
}


int iPackLenInRequestPacket (int i_iMode, unsigned char *io_puszReqBuf,int *io_puiReqLen)
{
    int iRet = 0;
    int iBytes = 0;
    int iNewLen = 0;
    unsigned char uszAscReqLen [4 + 1];
    unsigned char uszHexReqLen [4 + 1];
    unsigned char uszRequestPacket [MAX_ISO_MSG_SIZE + 1];
    
    iNewLen = *io_puiReqLen;
    
    switch( i_iMode )
    {
        case PACK_BCD:
            memset (uszAscReqLen, 0x00, sizeof (uszAscReqLen));
            sprintf ((char*)uszAscReqLen, "%0.4d", iNewLen);
            break;
        case PACK_HEX:
            //Convert to the ascii format -->e.g if 155 --> uszAscReqLen = 009B
            memset (uszAscReqLen, 0x00, sizeof(uszAscReqLen));
            sprintf ((char*)uszAscReqLen, "%.4X", iNewLen);
            break;
        default:
            iRet = -1;
            goto Exit;
    }
    
    iBytes = (int)strlen ((char *)uszAscReqLen);
    //Convert it to hex format --> 009B will become 0x00 0x9B
    memset (uszHexReqLen, 0x00, sizeof (uszHexReqLen));
    vdStr2HexStr ((char *)uszAscReqLen, (char *)uszHexReqLen, &iBytes);
    uszHexReqLen [iBytes] = 0x00;
    
    //Pack new request packet with 2 bytes of length at front
    memset (uszRequestPacket, 0x00, sizeof(uszRequestPacket));
    memcpy (uszRequestPacket, uszHexReqLen, iBytes);
    memcpy (uszRequestPacket + iBytes, io_puszReqBuf, iNewLen);
    uszRequestPacket [iBytes + iNewLen] = 0x00;
    iNewLen += iBytes;
    
    //Copy to the return packet
    memcpy (io_puszReqBuf, uszRequestPacket, iNewLen);
    io_puszReqBuf [iNewLen] = 0x00;
    *io_puiReqLen = iNewLen;
    
Exit:
    return iRet;
}



unsigned long	ulExtractField (int p_iID, unsigned char *p_pucInput, int p_iLen, int *p_piIdx, char *p_pcOutput, char *p_pcErrMsg, int *o_iLen)
{
    unsigned long	ulRet = 0;
    int				iRet;
    int				iFldLen;
    int				iPos = 0;
    int				iIdx = 0;
    int				iLen = 0;
    char			acTemp[MAX_TEMP_BUFFER_SZ];
    unsigned char	*pucCurPtr = p_pucInput + (*p_piIdx);
    ISOField		stISOField = g_astCUPISOField[p_iID];
    int				iSize = stISOField.iSize;
    char			cType = stISOField.cType;
    char			cPadPos = stISOField.cPadPos;
    char			cFixed = stISOField.cFixed;

    stISOField = g_astCUPISOField[p_iID];


     iSize = stISOField.iSize;
     cType = stISOField.cType;
     cPadPos = stISOField.cPadPos;
     cFixed = stISOField.cFixed;

    
    //if TXN Type is Balance , must reset the field 54
    if ( 53 == p_iID)
    {
        stISOField.iSize	= 120;
        stISOField.iLen		= 2;
        stISOField.cType	= TYPE_ANS;
        stISOField.cFixed	= 'N';
        stISOField.cPadPos	= 'L';
        stISOField.cPadChar	= '0';
        
        iSize = stISOField.iSize;
        cType = stISOField.cType;
        cPadPos = stISOField.cPadPos;
        cFixed = stISOField.cFixed;
    }
    
    if ('N' == cFixed)
    {
        iLen = stISOField.iLen;
        
        if (p_iLen - (*p_piIdx) < iLen)
        {
            ulRet = E_INSUF_DATA;
            sprintf (p_pcErrMsg, "F%d\tInsuf Data (Length) Avail[%d] Required[%d]", p_iID + 1, p_iLen - (*p_piIdx), iLen);
            goto CleanUp;
        }
        
        if (I_ISO_8583 == g_iStandard)
        {
            iRet = iByteToHex (pucCurPtr, iLen, acTemp);
            Print("acTemp1=%s\n",acTemp);
        }
        else if (I_ISO_B24 == g_iStandard)
        {
            memcpy (acTemp, pucCurPtr, iLen);
            acTemp[iLen] = 0;
        }
        iSize = atoi (acTemp);
        if (TYPE_B == cType)
        {
            iSize = iSize * 8;
        }
        (*p_piIdx) += iLen;
    }
    
    // Extract the field value based on the field type
    if (TYPE_A == cType || TYPE_AN == cType || TYPE_ANS == cType)
    {
        if (p_iLen - (*p_piIdx) < iSize)
        {
            ulRet = E_INSUF_DATA;
            Print ("F%d\tInsuf Data Avail[%d] Required[%d]\n", p_iID + 1, p_iLen - (*p_piIdx), iSize);
            goto CleanUp;
        }
        
        memcpy (p_pcOutput, pucCurPtr + iLen, iSize);
        p_pcOutput[iSize] = 0;
        
        *o_iLen = iSize;
        
        (*p_piIdx) += iSize;
    }
    else if (TYPE_N == cType)
    {
        if (p_iLen - (*p_piIdx) < (iSize + 1) / 2)
        {
            ulRet = E_INSUF_DATA;
            sprintf (p_pcErrMsg, "F%d\tInsuf Data Avail[%d] Required[%d]", p_iID + 1, p_iLen, (*p_piIdx) + ((iSize + 1) / 2));
            goto CleanUp;
        }
        
        iRet = iByteToHex (pucCurPtr + iLen, (iSize + 1) / 2, acTemp);
        
        if (0 == iSize % 2)
            memcpy (p_pcOutput, acTemp, iSize);
        else
        {
            if ('L' == cPadPos)
                memcpy (p_pcOutput, acTemp + 1, iSize);
            else if ('R' == cPadPos)
                memcpy (p_pcOutput, acTemp, iSize);
        }
        
        p_pcOutput[iSize] = 0;
        
        (*p_piIdx) += ((iSize + 1) / 2);
    }
    else if (TYPE_B == cType)
    {
        if (p_iLen - (*p_piIdx) < iSize / 8)
        {
            ulRet = E_INSUF_DATA;
            sprintf (p_pcErrMsg, "F%d\tInsuf Data Avail[%d] Required[%d]", p_iID + 1, p_iLen - (*p_piIdx), (iSize / 8));
            goto CleanUp;
        }
        
        iRet = iByteToHex (pucCurPtr + iLen, iSize / 8, acTemp);
        
        memcpy (p_pcOutput, acTemp, iSize / 4);
        p_pcOutput[iSize / 4] = 0;
        
        (*p_piIdx) += (iSize / 8);
    }
    else if (TYPE_Z == cType)
    {
        if (p_iLen - (*p_piIdx) < (iSize + 1) / 2)
        {
            ulRet = E_INSUF_DATA;
            sprintf (p_pcErrMsg, "F%d\tInsuf Data Avail[%d] Required[%d]", p_iID + 1, p_iLen - (*p_piIdx), (iSize + 1) / 2);
            goto CleanUp;
        }
        
        iRet = iByteToHex (pucCurPtr + iLen, (iSize + 1) / 2, acTemp);
        
        iFldLen = (int)strlen (acTemp) - (iSize % 2);
        iPos = 0;
        iIdx = 0;
        
        if (0 != iSize % 2)
        {
            if ('L' == cPadPos)
                iPos = 1;
            else if ('R' == cPadPos)
                iPos = 0;
        }
        
        for (iIdx = 0; iIdx < iFldLen; iIdx++, iPos++)
        {
            p_pcOutput[iIdx] = (68 == acTemp[iPos]) ? 61 : acTemp[iPos];
        }
        p_pcOutput[iIdx] = 0;
        
        if (iSize % 2 != 0) iSize++;
        
        (*p_piIdx) += ((iSize + 1) / 2);
    }
    
CleanUp:
    
    return ulRet;
}


unsigned long	ulParse (unsigned char *p_pucInput, int p_iLen, char *p_pcErrMsg)
{
    unsigned long	ulRet = 0;
    int				iIdx = 2;
    int				iLoop, iLoop2;
    int				iRet;
    int				iSize = 0;
    int				iTemp = 0;
    int				iChar = 0;
    int				iLen = 0;
    char			acTemp[MAX_TEMP_BUFFER_SZ];
    char			acBitmap[MAX_ISO_FIELDS];
    unsigned char	aucTemp[MAX_TEMP_BUFFER_SZ];
    unsigned char	aucBitmap[DEFAULT_BITMAP_SZ * 3];
    int				iFieldLen = 0;
    

    if (!p_pucInput)
    {
        ulRet = E_EMPTY_MESSAGE;
        strcpy (p_pcErrMsg, "Empty ISO Message");
        printf("Empty ISO Message\n");
        goto CleanUp;
    }
    
    // Parse the byte stream to get the TPDU and MTI.
    // Move the index of the byte stream along the parsing.
    if (p_iLen < iIdx + g_iHeader)
    {
        ulRet = E_LEN_TOO_SHORT;
        strcpy (p_pcErrMsg, "ISO Message Too Short (Header)");
        printf("ISO Message Too Short (Header)===\n");
        goto CleanUp;
    }
    
    if (I_ISO_8583 == g_iStandard)
    {
        memcpy (aucTemp, p_pucInput + iIdx, g_iHeader);
        iIdx += g_iHeader;
        
        iRet = iByteToHex (aucTemp, g_iHeader, acTemp);
        Print("acTemp=%s\n",acTemp);
    }
    else if (I_ISO_B24 == g_iStandard)
    {
        memcpy (aucTemp, p_pucInput + iIdx, g_iHeader);
        iIdx += g_iHeader;
        acTemp[g_iHeader] = 0;
    }
    strcpy (g_acTPDU, acTemp);
    Print("g_acTPDU=%s\n",g_acTPDU);

        if (I_ISO_8583 == g_iStandard)
        {
            if (p_iLen < iIdx + g_iMTILen)
            {
                ulRet = E_LEN_TOO_SHORT;
                strcpy (p_pcErrMsg, "ISO Message Too Short (VersionNum)");
                printf("ISO Message Too Short (VersionNum)\n");
                goto CleanUp;
            }
            memcpy (aucTemp, p_pucInput + iIdx, g_iMTILen);
            aucTemp[g_iMTILen + 1] = 0;
            iIdx += g_iMTILen;
            
            iRet = iByteToHex (aucTemp, g_iMTILen, acTemp);
        }
        else if (I_ISO_B24 == g_iStandard)
        {
            if (p_iLen < iIdx + g_iMTILen * 2) 
            {
                ulRet = E_LEN_TOO_SHORT;
                strcpy (p_pcErrMsg, "ISO Message Too Short (MTI)");
                printf("ISO Message Too Short (MTI)\n");
                goto CleanUp;
            }
            strncpy (acTemp, (char *) (p_pucInput + iIdx), g_iMTILen * 2);
            acTemp[g_iMTILen * 2] = 0;
            
            iIdx += g_iMTILen * 2;
        }
        strcpy (g_acVersionNum, acTemp);
    Print("g_acVersionNum=%s\n",g_acVersionNum);

    if (I_ISO_8583 == g_iStandard)
    {
        if (p_iLen < iIdx + g_iMTILen)
        {
            ulRet = E_LEN_TOO_SHORT;
            strcpy (p_pcErrMsg, "ISO Message Too Short (MTI)");
            printf("ISO Message Too Short (MTI)\n");
            goto CleanUp;
        }
        memcpy (aucTemp, p_pucInput + iIdx, g_iMTILen);
        aucTemp[g_iMTILen + 1] = 0;
        iIdx += g_iMTILen;
        
        iRet = iByteToHex (aucTemp, g_iMTILen, acTemp);
    }
    else if (I_ISO_B24 == g_iStandard)
    {
        if (p_iLen < iIdx + g_iMTILen * 2)
        {
            ulRet = E_LEN_TOO_SHORT;
            strcpy (p_pcErrMsg, "ISO Message Too Short (MTI)");
            printf("ISO Message Too Short (MTI)\n");
            goto CleanUp;
        }
        strncpy (acTemp, (char *) (p_pucInput + iIdx), g_iMTILen * 2);
        acTemp[g_iMTILen * 2] = 0;
        
        iIdx += g_iMTILen * 2;
    }
    strcpy (g_acMTI, acTemp);
    Print("g_acMTI=%s\n",g_acMTI);
    
    // Read the bitmap
    // If the first bit of the bitmap is 1 then the bitmap size is 128 bits.
    // If the first bit of the bitmap is 0 then the bitmap size is 64 bits.
    if (p_iLen < iIdx + DEFAULT_BITMAP_SZ)
    {
        ulRet = E_LEN_TOO_SHORT;
        strcpy (p_pcErrMsg, "ISO Message Too Short (Bitmap)");
        printf("ISO Message Too Short (Bitmap)\n");
        goto CleanUp;
    }
    
    if (I_ISO_8583 == g_iStandard)
    {
        iSize = (p_pucInput[iIdx] > 127) ? 128 : 64;
        
        if (p_iLen < iIdx + (iSize / DEFAULT_BITMAP_SZ))
        {
            ulRet = E_LEN_TOO_SHORT;
            strcpy (p_pcErrMsg, "ISO Message Too Short (Bitmap)");
            printf("ISO Message Too Short (Bitmap)\n");
            goto CleanUp;
        }
        
        memcpy (aucTemp, p_pucInput + iIdx, iSize / DEFAULT_BITMAP_SZ);
        memcpy (aucBitmap, p_pucInput + iIdx, iSize / DEFAULT_BITMAP_SZ);
        aucBitmap[iSize / DEFAULT_BITMAP_SZ] = 0;
        
        iRet = iByteToHex (aucTemp, iSize / DEFAULT_BITMAP_SZ, acTemp);
        iIdx += iSize / DEFAULT_BITMAP_SZ;
    }
    else if (I_ISO_B24 == g_iStandard)
    {
        memcpy (acTemp, p_pucInput + iIdx, 2);
        acTemp[2] = 0;
        iRet = iHexToByte ((char *) acTemp, aucBitmap, &iLen);
        
        iSize = (aucBitmap[0] > 127) ? 128 : 64;
        
        if (p_iLen < iIdx + (iSize * 2 / DEFAULT_BITMAP_SZ))
        {
            ulRet = E_LEN_TOO_SHORT;
            strcpy (p_pcErrMsg, "ISO Message Too Short (Bitmap)");
            printf("ISO Message Too Short (Bitmap)\n");
            goto CleanUp;
        }
        
        memcpy (acTemp, p_pucInput + iIdx, iSize * 2 / DEFAULT_BITMAP_SZ);
        acTemp[iSize * 2 / DEFAULT_BITMAP_SZ] = 0;
        
        iRet = iHexToByte (acTemp, aucBitmap, &iLen);
        iIdx += iSize * 2 / DEFAULT_BITMAP_SZ;
    }
    strcpy (g_acBitmap, acTemp);
    Print("g_acBitmap=%s\n",g_acBitmap);
    Print("iIdx=%d\n",iIdx);
    
    for (iLoop = 0; iLoop < iSize / DEFAULT_BITMAP_SZ; iLoop++)
    {
        iChar = aucBitmap[iLoop];
        for (iLoop2 = 0; iLoop2 < DEFAULT_BITMAP_SZ; iLoop2++)
        {
            acBitmap[iTemp++] = ((1 << (DEFAULT_BITMAP_SZ - iLoop2 - 1)) == (iChar & (1 << (DEFAULT_BITMAP_SZ - iLoop2 - 1))));
        }
    }
    
    // For all the '1' in the bitmap, extract the ISO field value.
    // call ulExtractValue to extract the value from the data stream.
    // Return FAILED if the format of the ISO message is wrong
    for (iLoop = 1; iLoop < iSize; iLoop++)
    {
        if (1 == acBitmap[iLoop])
        {
            if (p_iLen == iIdx)
            {
                ulRet = E_INSUF_DATA;
                sprintf (p_pcErrMsg, "Insufficient Data [%d]", p_iLen);
                printf("Insufficient Data [%d]\n",p_iLen);
                goto CleanUp;
            }
            ulRet = ulExtractField (iLoop, p_pucInput, p_iLen, &iIdx, acTemp, p_pcErrMsg, &iFieldLen);
            if (0 != ulRet)
            {
                goto CleanUp;
            }
            
            //if(54 ==iLoop)
            //if(54 ==iLoop || 59 == iLoop)
            if (43 == iLoop || 54 ==iLoop || 59 == iLoop || 55 == iLoop)	//hy 2011-04-11
            {	
                memcpy (g_astISOFieldRec[iLoop].pcVal, acTemp, iFieldLen);
                g_astISOFieldRec[iLoop].iLen = iFieldLen;
            }
            else
            {				
                strcpy (g_astISOFieldRec[iLoop].pcVal, acTemp);
                g_astISOFieldRec[iLoop].iLen = (int)strlen (acTemp);
                
            }
            g_astISOFieldRec[iLoop].cFlag = 1;
        }
    }
    
CleanUp:
				
    return ulRet;
}




long lStr2Long( char *i_pszStr )
{
    long lTemp=0;
    long lTemp2 = 1;
    int iLen;
    int i;
    int j=0;
    
    iLen = (int)strlen(i_pszStr);
    
    for(i=iLen-1; i>=0;i--)
    {
        
        
        if(i_pszStr[i] == '1')
        {
            if((iLen-1)==i)
                lTemp = lTemp+1;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 1;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        
        else if(i_pszStr[i] == '2')
        {
            if((iLen-1)==i)
                lTemp = lTemp+2;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 2;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        else if(i_pszStr[i] == '3')
        {
            if((iLen-1)==i)
                lTemp = lTemp+3;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 3;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        
        else if(i_pszStr[i] == '4')
        {
            if((iLen-1)==i)
                lTemp = lTemp+4;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 4;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        
        else if(i_pszStr[i] == '5')
        {
            if((iLen-1)==i)
                lTemp = lTemp+5;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 5;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        
        
        else if(i_pszStr[i] == '6')
        {
            if((iLen-1)==i)
                lTemp = lTemp+6;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 6;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        
        else if(i_pszStr[i] == '7')
        {
            if((iLen-1)==i)
                lTemp = lTemp+7;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 7;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        
        else if(i_pszStr[i] == '8')
        {
            if((iLen-1)==i)
                lTemp = lTemp+8;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 8;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        
        else if(i_pszStr[i] == '9')
        {
            if((iLen-1)==i)
                lTemp = lTemp+9;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 9;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        
        else if(i_pszStr[i] == '0')
        {
            if((iLen-1)==i)
                lTemp = lTemp+0;
            else if( i >= 0 && i!=(iLen-1))
            {
                lTemp2 = 0;
                
                for(j=iLen-1; j> i; j--)
                    lTemp2 = lTemp2*10;
                
                lTemp = lTemp+lTemp2;
            }
        }
        
    }
    return lTemp;
}

