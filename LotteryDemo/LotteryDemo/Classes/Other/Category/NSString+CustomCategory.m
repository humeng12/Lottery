//
//  NSString+CustomCategory.m
//  HrtMerchantEnd
//
//  Created by wingsmm on 14-4-3.
//  Copyright (c) 2014年 whp. All rights reserved.
//

#import "NSString+CustomCategory.h"
#import <CommonCrypto/CommonDigest.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#import "GTMBase64.h"
#import "PublicMethod.h"
#import "EncrypteAndDecrypte.h"
#import "SSKeychain.h"


BOOL isNumber (char ch)
{
    if (!(ch >= '0' && ch <= '9')) {
        return FALSE;
    }
    return TRUE;
}


@implementation NSString (CustomCategory)

+(NSString *)getAppPath
{
    NSArray * documentPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    return [documentPaths objectAtIndex:0];
}

-(BOOL)ifInvolveStr:(NSString *)str
{
    return [self rangeOfString:str options:NSCaseInsensitiveSearch].length > 0;
}

- (NSString *) stringFromMD5{
    
    if(self == nil || [self length] == 0)
        return nil;
    
    const char *value = [self UTF8String];
    
    unsigned char outputBuffer[CC_MD5_DIGEST_LENGTH];
    CC_MD5(value, (int)strlen(value), outputBuffer);
    
    NSMutableString *outputString = [[NSMutableString alloc] initWithCapacity:CC_MD5_DIGEST_LENGTH * 2];
    for(NSInteger count = 0; count < CC_MD5_DIGEST_LENGTH; count++){
        [outputString appendFormat:@"%02x",outputBuffer[count]];
    }
    
    return outputString;
}

+(NSString *)TripleDES:(NSString *)plainText encryptOrDecrypt:(CCOperation)encryptOrDecrypt encryptOrDecryptKey:(NSString *)encryptOrDecryptKey
{
    const void *vplainText;
    size_t plainTextBufferSize;
    
    if (encryptOrDecrypt == kCCDecrypt)//解密
    {
        NSData *EncryptData = [GTMBase64 decodeData:[plainText dataUsingEncoding:NSUTF8StringEncoding]];
        plainTextBufferSize = [EncryptData length];
        vplainText = [EncryptData bytes];
    }
    else //加密
    {
        NSData* data = [plainText dataUsingEncoding:NSUTF8StringEncoding];
        plainTextBufferSize = [data length];
        vplainText = (const void *)[data bytes];
    }
    
    CCCryptorStatus ccStatus;
    uint8_t *bufferPtr = NULL;
    size_t bufferPtrSize = 0;
    size_t movedBytes = 0;
    
    bufferPtrSize = (plainTextBufferSize + kCCBlockSize3DES) & ~(kCCBlockSize3DES - 1);
    bufferPtr = malloc( bufferPtrSize * sizeof(uint8_t));
    memset((void *)bufferPtr, 0x0, bufferPtrSize);
    // memset((void *) iv, 0x0, (size_t) sizeof(iv));
    
   const void *vkey = (const void *)[encryptOrDecryptKey UTF8String];
    // NSString *initVec = @"init Vec";
    //    const void *vinitVec = (const void *) [gIv UTF8String];
    //  Byte iv[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    ccStatus = CCCrypt(encryptOrDecrypt,
                       kCCAlgorithm3DES,
                       kCCOptionECBMode|kCCOptionPKCS7Padding,
                       vkey,
                       kCCKeySize3DES,
                       nil,
                       vplainText,
                       plainTextBufferSize,
                       (void *)bufferPtr,
                       bufferPtrSize,
                       &movedBytes);
    //if (ccStatus == kCCSuccess) NSLog(@"SUCCESS");
    /*else if (ccStatus == kCC ParamError) return @"PARAM ERROR";
     else if (ccStatus == kCCBufferTooSmall) return @"BUFFER TOO SMALL";
     else if (ccStatus == kCCMemoryFailure) return @"MEMORY FAILURE";
     else if (ccStatus == kCCAlignmentError) return @"ALIGNMENT";
     else if (ccStatus == kCCDecodeError) return @"DECODE ERROR";
     else if (ccStatus == kCCUnimplemented) return @"UNIMPLEMENTED"; */
    
    NSString *result;
    
    if (encryptOrDecrypt == kCCDecrypt)
    {
        result = [[NSString alloc] initWithData:[NSData dataWithBytes:(const void *)bufferPtr
                                                               length:(NSUInteger)movedBytes]
                                       encoding:NSUTF8StringEncoding]
        ;
    }
    else
    {
        NSData *myData = [NSData dataWithBytes:(const void *)bufferPtr length:(NSUInteger)movedBytes];
        result = [GTMBase64 stringByEncodingData:myData];
    }
    
    return result;
}


+(NSString *)TripleDESVC:(NSString *)password encryptOrDecryptKey:(NSString *)key
{
    char pwd[17]={0};
    vdHex2Str((char *)[password UTF8String],8,pwd);
    
    unsigned char buf[17];
    DecryptPassWord((char *)[key UTF8String],pwd,buf);
    
    char keyPwd[17]={0};
    HexToString(buf,keyPwd,8);
    
    return [NSString stringWithUTF8String:keyPwd];
}


// 是否是手机号
+ (BOOL) validateUserPhone:(NSString *)str
{
    NSRegularExpression *regularexpression = [[NSRegularExpression alloc]
                                              initWithPattern:@"^1[3|4|5|7|8][0-9][0-9]{8}$"
                                              options:NSRegularExpressionCaseInsensitive
                                              error:nil];
	
	
	
    NSUInteger numberofMatch = [regularexpression numberOfMatchesInString:str
                                                                  options:NSMatchingReportProgress
                                                                    range:NSMakeRange(0, str.length)];
	
	
    if(numberofMatch > 0)
	{
        return YES;
	}
    return NO;
}

+(BOOL)isParent
{
    
    NSUserDefaults * userDefaults = [NSUserDefaults standardUserDefaults];
    NSString * parentID = [userDefaults objectForKey:@"parentID"];

    if ([parentID isEqualToString:@"0"]) {
        return YES;
    }
    
    return NO;
}

+(BOOL)isPermmision
{
    NSUserDefaults * userDefaults = [NSUserDefaults standardUserDefaults];
    NSString * permmisionValue = [userDefaults objectForKey:@"permmisionValue"];
    
    if ([permmisionValue isEqualToString:@"2"]) {
        return YES;
    }
    
    return NO;
}

+(NSString *) getMerchantID
{
    NSUserDefaults * userDefaults = [NSUserDefaults standardUserDefaults];
    NSString * merchantID = [userDefaults objectForKey:@"merchantID"];
    return merchantID;
}

+(NSString *) getMID
{
    NSUserDefaults * userDefaults = [NSUserDefaults standardUserDefaults];
    NSString * mid = [userDefaults objectForKey:@"mid"];
    return mid;
}

+(NSString *) getMerchantName
{
    NSUserDefaults * userDefaults = [NSUserDefaults standardUserDefaults];
    NSString * merchantID = [userDefaults objectForKey:@"merchantName"];
    return merchantID;
}

+(NSString *) getPhoneNumber
{
    NSUserDefaults * userDefaults = [NSUserDefaults standardUserDefaults];
    NSString * PhoneNumber = [userDefaults objectForKey:@"phoneNumber"];
    return PhoneNumber;
}

+(void)setMpos:(NSString *)leiXing
{
     NSUserDefaults * userDefaults = [NSUserDefaults standardUserDefaults];
     [userDefaults setObject:leiXing forKey:@"LeiXing"];
}
+(NSString *)getMpos
{
     NSUserDefaults * userDefaults = [NSUserDefaults standardUserDefaults];
     NSString *leiXing = [userDefaults objectForKey:@"LeiXing"];
     return leiXing;
}
// 是否是邮箱
+(BOOL)isValidateEmail:(NSString *)email
{
    NSString *emailRegex = @"[A-Z0-9a-z._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}";
    NSPredicate *emailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", emailRegex];
    return [emailTest evaluateWithObject:email];
}


+ (BOOL) isValid:(IdentifierType) type value:(NSString*) value
{
    return YES;
}

// 验证是不是整数数字
+ (BOOL) isValidNumber:(NSString*)value
{
    const char *cvalue = [value UTF8String];
    int len = (int)strlen(cvalue);
    
    if (len==0) {
        return false;
    }
    
    for (int i = 0; i < len; i++) {
        if(!isNumber(cvalue[i])){
            return FALSE;
        }
    }
    return TRUE;
}

// 验证是不是浮点型
+ (BOOL)isPureFloat:(NSString *)string{
    NSScanner* scan = [NSScanner scannerWithString:string];
    float val;
    return [scan scanFloat:&val] && [scan isAtEnd];
}

+ (UIImageView*)getbgImgView{
    
    UIImageView *bgImgView = [[UIImageView alloc]initWithFrame:CGRectMake(0, 0,320,568)];
    bgImgView.userInteractionEnabled = YES;
    bgImgView.image = [UIImage imageNamed:@"bg.png"];
    
    return bgImgView;
}


+(NSString *)PinYinFromCharacter:(NSString *)aString
{
     //转成了可变字符串
     NSMutableString *str = [NSMutableString stringWithString:aString];
     //先转换为带声调的拼音
     CFStringTransform((CFMutableStringRef)str,NULL, kCFStringTransformMandarinLatin,NO);
     //再转换为不带声调的拼音
     CFStringTransform((CFMutableStringRef)str,NULL, kCFStringTransformStripDiacritics,NO);
     NSString *pinYin = str;
     NSString *string = [pinYin stringByReplacingOccurrencesOfString:@" " withString:@""];
     return string;
}

+(NSString *)stringByChinaese:(NSString *)string
{
     if (string.length <= 0)
     {
          return nil;
     }
     NSMutableString *source = [string mutableCopy];
     CFStringTransform((__bridge CFMutableStringRef)source, NULL, kCFStringTransformMandarinLatin, NO);
     CFStringTransform((__bridge CFMutableStringRef)source, NULL, kCFStringTransformStripDiacritics, NO);
     return [source uppercaseString];
}

+(NSString *)hexStringFromString:(NSData *)string{
     //    NSData *myD = [string dataUsingEncoding:NSUTF8StringEncoding];
     Byte *bytes = (Byte *)[string bytes];
     //下面是Byte 转换为16进制。
     NSString *hexStr=@"";
     for(int i=0;i<[string length];i++)

     {
          NSString *newHexStr = [NSString stringWithFormat:@"%x",bytes[i]&0xff];///16进制数

          if([newHexStr length]==1)

               hexStr = [NSString stringWithFormat:@"%@0%@",hexStr,newHexStr];

          else

               hexStr = [NSString stringWithFormat:@"%@%@",hexStr,newHexStr];
     }
     return hexStr;
}


+(BOOL)IsChinese:(NSString *)str
{
     for(int i=0; i< [str length];i++)
     {
          int a = [str characterAtIndex:i];
          if( a > 0x4e00 && a < 0x9fff)
          {
               return YES;
          }
     }
     return NO;
}


+(NSString *)findNumFromStr:(NSString *)str
{
     // Intermediate
     NSMutableString *numberString = [[NSMutableString alloc] init];
     NSString *tempStr;
     NSScanner *scanner = [NSScanner scannerWithString:str];
     NSCharacterSet *numbers = [NSCharacterSet characterSetWithCharactersInString:@"0123456789."];

     while (![scanner isAtEnd])
     {
          // Throw away characters before the first number.
          [scanner scanUpToCharactersFromSet:numbers intoString:NULL];

          // Collect numbers.
          [scanner scanCharactersFromSet:numbers intoString:&tempStr];
          [numberString appendString:tempStr];
          tempStr = @"";
     }
     return numberString;
}

+(NSString *)stringFromHexString:(NSString *)hexString
{
     char *myBuffer = (char *)malloc((int)[hexString length] / 2 + 1);
     bzero(myBuffer, [hexString length] / 2 + 1);
     for (int i = 0; i < [hexString length] - 1; i += 2)
     {
          unsigned int anInt;
          NSString * hexCharStr = [hexString substringWithRange:NSMakeRange(i, 2)];
          NSScanner * scanner = [[NSScanner alloc] initWithString:hexCharStr];
          [scanner scanHexInt:&anInt];
          myBuffer[i / 2] = (char)anInt;
     }
     NSString *unicodeString = [NSString stringWithCString:myBuffer encoding:4];
     //NSLog(@"------字符串=======%@",unicodeString);
     return unicodeString;
}



//将卡号加密
+(NSString *)kaHaoCHuLi:(NSString *)str
{
     NSString *strOne=[str substringWithRange:NSMakeRange(0,6)];
     int len=(int)[str length];
     NSString *strTwo=[str substringWithRange:NSMakeRange(len-4,4)];
     NSString *strThree=@"******";
     NSString *strKaHao=[NSString stringWithFormat:@"%@%@%@",strOne,strThree,strTwo];
     return strKaHao;
}

//处理日期格式
+(NSString *)dateCHuLi:(NSString *)str
{
     NSString *strJIeQu=[str substringWithRange:NSMakeRange(0,10)];
     NSString *strRiQi=[strJIeQu stringByReplacingOccurrencesOfString:@"/" withString:@""];
     return strRiQi;
}


//--------------------何阳  2015-06-04---------------------
//获取今天日期
+(NSString *)getTodayDate
{
    NSDate * dateToday=[[NSDate alloc]init];
    NSDateFormatter *format = [[NSDateFormatter alloc]init];
    format.dateFormat = @"yyyy-MM-dd";
    NSString * todayDate = [format stringFromDate:dateToday];
    return todayDate;
}

//获取前10天的日期
+(NSString *)getBeforeDate
{
    NSDate *beforeDay = [NSDate dateWithTimeIntervalSinceNow:-(24*60*60*9)];
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyy-MM-dd"];
    NSString *beforeDayDate = [formatter stringFromDate:beforeDay];
    return beforeDayDate;
}

+(NSString *)getCheckFlag
{
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString *checkFlag = [userDefaults objectForKey:@"checkFlag"];
    
    return checkFlag;
}

// 获取电商唯一标示
+(NSString *)getMerchantEshopNo
{
    NSUserDefaults *userDefault = [NSUserDefaults standardUserDefaults];
    NSString *EshopNo = [userDefault objectForKey:@"getMerchantEshopNo"];
    return EshopNo;
}

// UUID 设备唯一标识符
+ (NSString *)getCurrentDeviceUUID
{
    // 20151012 dcj 改写
    
    
    NSString *retrieveUUID = [SSKeychain passwordForService:@"com.hrtpaymentQY.HrtMerchantEnd" account:@"user"];
    
    if (retrieveUUID == nil) {
        
        UIDevice * curDev = [UIDevice currentDevice];
        NSString *  UUIDstr = curDev.identifierForVendor.UUIDString;
        
        [SSKeychain setPassword: [NSString stringWithFormat:@"%@", UUIDstr]
                     forService:@"com.hrtpaymentQY.HrtMerchantEnd" account:@"user"];
        
        retrieveUUID = UUIDstr;
    }
    
    return retrieveUUID;
}

//获得设备型号
+ (NSString *)getCurrentDeviceModel
{
    int mib[2];
    size_t len;
    char *machine;
    
    mib[0] = CTL_HW;
    mib[1] = HW_MACHINE;
    sysctl(mib, 2, NULL, &len, NULL, 0);
    machine = malloc(len);
    sysctl(mib, 2, machine, &len, NULL, 0);
    
    NSString *platform = [NSString stringWithCString:machine encoding:NSASCIIStringEncoding];
    free(machine);
    
    if ([platform isEqualToString:@"iPhone1,1"]) return @"iPhone 2G (A1203)";
    if ([platform isEqualToString:@"iPhone1,2"]) return @"iPhone 3G (A1241/A1324)";
    if ([platform isEqualToString:@"iPhone2,1"]) return @"iPhone 3GS (A1303/A1325)";
    if ([platform isEqualToString:@"iPhone3,1"]) return @"iPhone 4 (A1332)";
    if ([platform isEqualToString:@"iPhone3,2"]) return @"iPhone 4 (A1332)";
    if ([platform isEqualToString:@"iPhone3,3"]) return @"iPhone 4 (A1349)";
    if ([platform isEqualToString:@"iPhone4,1"]) return @"iPhone 4S (A1387/A1431)";
    if ([platform isEqualToString:@"iPhone5,1"]) return @"iPhone 5 (A1428)";
    if ([platform isEqualToString:@"iPhone5,2"]) return @"iPhone 5 (A1429/A1442)";
    if ([platform isEqualToString:@"iPhone5,3"]) return @"iPhone 5c (A1456/A1532)";
    if ([platform isEqualToString:@"iPhone5,4"]) return @"iPhone 5c (A1507/A1516/A1526/A1529)";
    if ([platform isEqualToString:@"iPhone6,1"]) return @"iPhone 5s (A1453/A1533)";
    if ([platform isEqualToString:@"iPhone6,2"]) return @"iPhone 5s (A1457/A1518/A1528/A1530)";
    if ([platform isEqualToString:@"iPhone7,1"]) return @"iPhone 6 Plus (A1522/A1524)";
    if ([platform isEqualToString:@"iPhone7,2"]) return @"iPhone 6 (A1549/A1586)";
    if ([platform isEqualToString:@"iPhone8,1"]) return @"iPhone 6s ";
    if ([platform isEqualToString:@"iPhone8,2"]) return @"iPhone 6s Plus";

    if ([platform isEqualToString:@"iPod1,1"])   return @"iPod Touch 1G (A1213)";
    if ([platform isEqualToString:@"iPod2,1"])   return @"iPod Touch 2G (A1288)";
    if ([platform isEqualToString:@"iPod3,1"])   return @"iPod Touch 3G (A1318)";
    if ([platform isEqualToString:@"iPod4,1"])   return @"iPod Touch 4G (A1367)";
    if ([platform isEqualToString:@"iPod5,1"])   return @"iPod Touch 5G (A1421/A1509)";
    
    if ([platform isEqualToString:@"iPad1,1"])   return @"iPad 1G (A1219/A1337)";
    
    if ([platform isEqualToString:@"iPad2,1"])   return @"iPad 2 (A1395)";
    if ([platform isEqualToString:@"iPad2,2"])   return @"iPad 2 (A1396)";
    if ([platform isEqualToString:@"iPad2,3"])   return @"iPad 2 (A1397)";
    if ([platform isEqualToString:@"iPad2,4"])   return @"iPad 2 (A1395+New Chip)";
    if ([platform isEqualToString:@"iPad2,5"])   return @"iPad Mini 1G (A1432)";
    if ([platform isEqualToString:@"iPad2,6"])   return @"iPad Mini 1G (A1454)";
    if ([platform isEqualToString:@"iPad2,7"])   return @"iPad Mini 1G (A1455)";
    
    if ([platform isEqualToString:@"iPad3,1"])   return @"iPad 3 (A1416)";
    if ([platform isEqualToString:@"iPad3,2"])   return @"iPad 3 (A1403)";
    if ([platform isEqualToString:@"iPad3,3"])   return @"iPad 3 (A1430)";
    if ([platform isEqualToString:@"iPad3,4"])   return @"iPad 4 (A1458)";
    if ([platform isEqualToString:@"iPad3,5"])   return @"iPad 4 (A1459)";
    if ([platform isEqualToString:@"iPad3,6"])   return @"iPad 4 (A1460)";
    
    if ([platform isEqualToString:@"iPad4,1"])   return @"iPad Air (A1474)";
    if ([platform isEqualToString:@"iPad4,2"])   return @"iPad Air (A1475)";
    if ([platform isEqualToString:@"iPad4,3"])   return @"iPad Air (A1476)";
    if ([platform isEqualToString:@"iPad4,4"])   return @"iPad Mini 2G (A1489)";
    if ([platform isEqualToString:@"iPad4,5"])   return @"iPad Mini 2G (A1490)";
    if ([platform isEqualToString:@"iPad4,6"])   return @"iPad Mini 2G (A1491)";
    
    if ([platform isEqualToString:@"i386"])      return @"iPhone Simulator";
    if ([platform isEqualToString:@"x86_64"])    return @"iPhone Simulator";
    return platform;
}


/**
 *	@brief	验证固定电话区号是否正确（e.g. 010正确，030错误）
 *
 *	@return	返回固定电话区号是否正确
 */
- (BOOL)isAreaCode
{
     NSString *regex = [NSString stringWithFormat:@"^%@|%@$",[NSString regex_areaCode_threeDigit],[NSString regex_areaCode_fourDigit]];
     NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",regex];
     if([predicate evaluateWithObject:@""])
     {
          return YES;
     }

     return NO;
}



/**
 *	@brief	获取三位数区号的正则表达式（三位数区号形如 010）
 */
+(NSString*)regex_areaCode_threeDigit
{
     return @"010|02[0-57-9]";
}
/**
 *	@brief	获取四位数区号的正则表达式（四位数区号形如 0311）
 */
+(NSString*)regex_areaCode_fourDigit
{
     // 03xx
     NSString *fourDigit03 = @"03([157]\\d|35|49|9[1-68])";
     // 04xx
     NSString *fourDigit04 = @"04([17]\\d|2[179]|[3,5][1-9]|4[08]|6[4789]|8[23])";
     // 05xx
     NSString *fourDigit05 = @"05([1357]\\d|2[37]|4[36]|6[1-6]|80|9[1-9])";
     // 06xx
     NSString *fourDigit06 = @"06(3[1-5]|6[0238]|9[12])";
     // 07xx
     NSString *fourDigit07 = @"07(01|[13579]\\d|2[248]|4[3-6]|6[023689])";
     // 08xx
     NSString *fourDigit08 = @"08(1[23678]|2[567]|[37]\\d)|5[1-9]|8[3678]|9[1-8]";
     // 09xx
     NSString *fourDigit09 = @"09(0[123689]|[17][0-79]|[39]\\d|4[13]|5[1-5])";

     return [NSString stringWithFormat:@"%@|%@|%@|%@|%@|%@|%@",fourDigit03,fourDigit04,fourDigit05,fourDigit06,fourDigit07,fourDigit08,fourDigit09];
     
}



// 正则判断手机号码地址格式
+(BOOL)isMobileNumber:(NSString *)mobileNum
{
     /**
      * 手机号码
      * 移动：134[0-8],135,136,137,138,139,150,151,157,158,159,182,187,188
      * 联通：130,131,132,152,155,156,185,186
      * 电信：133,1349,153,180,189
      */
     NSString * MOBILE = @"^1(3[0-9]|5[0-35-9]|8[025-9])\\d{8}$";
     /**
      10         * 中国移动：China Mobile
      11         * 134[0-8],135,136,137,138,139,150,151,157,158,159,182,187,188
      12         */
     NSString * CM = @"^1(34[0-8]|(3[5-9]|5[017-9]|8[278])\\d)\\d{7}$";
     /**
      15         * 中国联通：China Unicom
      16         * 130,131,132,152,155,156,185,186
      17         */
     NSString * CU = @"^1(3[0-2]|5[256]|8[56])\\d{8}$";
     /**
      20         * 中国电信：China Telecom
      21         * 133,1349,153,180,189
      22         */
     NSString * CT = @"^1((33|53|8[09])[0-9]|349)\\d{7}$";
     /**
      25         * 大陆地区固话及小灵通
      26         * 区号：010,020,021,022,023,024,025,027,028,029
      27         * 号码：七位或八位
      28         */
     NSString * PHS = @"^0(10|2[0-5789]|\\d{3})\\d{7,8}$";

     NSPredicate *regextestmobile = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", MOBILE];
     NSPredicate *regextestcm = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", CM];
     NSPredicate *regextestcu = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", CU];
     NSPredicate *regextestct = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", CT];
     NSPredicate *regextestphs = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", PHS];

     if (([regextestmobile evaluateWithObject:mobileNum] == YES)
         || ([regextestcm evaluateWithObject:mobileNum] == YES)
         || ([regextestct evaluateWithObject:mobileNum] == YES)
         || ([regextestcu evaluateWithObject:mobileNum] == YES)
         || ([regextestphs evaluateWithObject:mobileNum] == YES))
     {
          return YES;
     }
     else
     {
          return NO;
     }
}



//判断是否为整形：
+(BOOL)isPureInt:(NSString*)string{

     NSScanner* scan = [NSScanner scannerWithString:string];
     int val;
     return[scan scanInt:&val] && [scan isAtEnd];
}


+(BOOL)judgeIDCard:(NSString *)IDCard
{
     BOOL flag;
     if (IDCard.length <= 0)
     {
          flag = NO;
          return flag;
     }

     NSString *regex2 = @"^(^[1-9]\\d{7}((0\\d)|(1[0-2]))(([0|1|2]\\d)|3[0-1])\\d{3}$)|(^[1-9]\\d{5}[1-9]\\d{3}((0\\d)|(1[0-2]))(([0|1|2]\\d)|3[0-1])((\\d{4})|\\d{3}[Xx])$)$";
     NSPredicate *identityCardPredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",regex2];
     flag = [identityCardPredicate evaluateWithObject:IDCard];

     //如果通过该验证，说明身份证格式正确，但准确性还需计算
     if(flag)
     {
          if(IDCard.length==18)
          {
               //将前17位加权因子保存在数组里
               NSArray * idCardWiArray = @[@"7", @"9", @"10", @"5", @"8", @"4", @"2", @"1", @"6", @"3", @"7", @"9", @"10", @"5", @"8", @"4", @"2"];

               //这是除以11后，可能产生的11位余数、验证码，也保存成数组
               NSArray * idCardYArray = @[@"1", @"0", @"10", @"9", @"8", @"7", @"6", @"5", @"4", @"3", @"2"];

               //用来保存前17位各自乖以加权因子后的总和

               NSInteger idCardWiSum = 0;
               for(int i = 0;i < 17;i++)
               {
                    NSInteger subStrIndex = [[IDCard substringWithRange:NSMakeRange(i, 1)] integerValue];
                    NSInteger idCardWiIndex = [[idCardWiArray objectAtIndex:i] integerValue];

                    idCardWiSum+= subStrIndex * idCardWiIndex;

               }

               //计算出校验码所在数组的位置
               NSInteger idCardMod=idCardWiSum%11;

               //得到最后一位身份证号码
               NSString * idCardLast= [IDCard substringWithRange:NSMakeRange(17, 1)];

               //如果等于2，则说明校验码是10，身份证号码最后一位应该是X
               if(idCardMod==2)
               {
                    if([idCardLast isEqualToString:@"X"]||[idCardLast isEqualToString:@"x"])
                    {
                         return flag;
                    }else
                    {
                         flag =  NO;
                         return flag;
                    }
               }else
               {
                    //用计算出的验证码与最后一位身份证号码匹配，如果一致，说明通过，否则是无效的身份证号码
                    if([idCardLast isEqualToString: [idCardYArray objectAtIndex:idCardMod]])
                    {
                         return flag;
                    }
                    else
                    {
                         flag =  NO;
                         return flag;
                    }
               }
          }
          else
          {
               flag =  NO;
               return flag;
          }
     }
     else
     {
          return flag;
     }
}


/**
 *  快速计算出文本的真实尺寸
 *
 *  @param font    文字的字体
 *  @param maxSize 文本的最大尺寸
 *
 *  @return 快速计算出文本的真实尺寸
 */
- (CGSize)sizeWithFont:(UIFont *)font andMaxSize:(CGSize)maxSize
{
     NSDictionary *arrts = @{NSFontAttributeName:font};

     return [self boundingRectWithSize:maxSize options:NSStringDrawingUsesLineFragmentOrigin attributes:arrts context:nil].size;
}

/**
 *  快速计算出文本的真实尺寸
 *
 *  @param text    需要计算尺寸的文本
 *  @param font    文字的字体
 *  @param maxSize 文本的最大尺寸
 *
 *  @return 快速计算出文本的真实尺寸
 */
+ (CGSize)sizeWithText:(NSString *)text andFont:(UIFont *)font andMaxSize:(CGSize)maxSize
{
     return [text sizeWithFont:font andMaxSize:maxSize];
}

/**
 *  判断银行卡号是否规范
 *
 *  @param cardNo 卡号
 *
 *  @return 是yes 不是no
 */
+ (BOOL)checkCardNo:(NSString*) cardNo
{
    int oddsum = 0;     //奇数求和
    int evensum = 0;    //偶数求和
    int allsum = 0;
    int cardNoLength = (int)[cardNo length];
    int lastNum = [[cardNo substringFromIndex:cardNoLength-1] intValue];
    
    cardNo = [cardNo substringToIndex:cardNoLength - 1];
    for (int i = cardNoLength -1 ; i>=1;i--) {
        NSString *tmpString = [cardNo substringWithRange:NSMakeRange(i-1, 1)];
        int tmpVal = [tmpString intValue];
        if (cardNoLength % 2 ==1 ) {
            if((i % 2) == 0){
                tmpVal *= 2;
                if(tmpVal>=10)
                    tmpVal -= 9;
                evensum += tmpVal;
            }else{
                oddsum += tmpVal;
            }
        }else{
            if((i % 2) == 1){
                tmpVal *= 2;
                if(tmpVal>=10)
                    tmpVal -= 9;
                evensum += tmpVal;
            }else{
                oddsum += tmpVal;
            }
        }
    }
    
    allsum = oddsum + evensum;
    allsum += lastNum;
    if((allsum % 10) == 0)
        return YES;
    else
        return NO;
}

/**
 *  银行卡日期判断
 *
 *  @param cardDate 日期字符串
 *
 *  @return 是yes 不是no
 */
+ (BOOL)checkCardDate:(NSString *)cardDate
{
//    if (![cardDate containsString:@"/"])
//    {
//        return NO;
//    }else
//    {
        NSArray *arrDate = [cardDate componentsSeparatedByString:@"/"];
    if (arrDate.count < 2) {
        return NO;
    }
        NSDate *dateCurrent= [NSDate date];
        NSDateFormatter *format = [[NSDateFormatter alloc]init];
        format.dateFormat = @"yyyy";
        NSString *todayDateYear = [format stringFromDate:dateCurrent];
        if ([todayDateYear integerValue] > [arrDate[0] integerValue])
        {
            return NO;
        }else if ([arrDate[1] integerValue]>12)
        {
            return NO;
        }
//    }
    return YES;
}

@end
