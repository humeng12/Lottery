//
//  NSString+CustomCategory.h
//  HrtMerchantEnd
//
//  Created by wingsmm on 14-4-3.
//  Copyright (c) 2014年 whp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonCryptor.h>
#import <CommonCrypto/CommonDigest.h>

typedef enum
{
    IdentifierTypeKnown = 0,
    IdentifierTypeZipCode,      //1
    IdentifierTypeEmail,        //2
    IdentifierTypePhone,        //3
    IdentifierTypeUnicomPhone,  //4
    IdentifierTypeQQ,           //5
    IdentifierTypeNumber,       //6
    IdentifierTypeString,       //7
    IdentifierTypeIdentifier,   //8
    IdentifierTypePassort,      //9
    IdentifierTypeCreditNumber, //10
    IdentifierTypeBirthday,     //11
}IdentifierType;



@interface NSString (CustomCategory)
+(NSString *)getAppPath;
-(BOOL)ifInvolveStr:(NSString *)str;
- (NSString *) stringFromMD5;
+ (BOOL) validateUserPhone:(NSString *)str;
+(BOOL) isValidateEmail:(NSString *)email;
+(BOOL)isParent;
+(NSString *) getMerchantID;
+(NSString *) getMID;
+(NSString *) getPhoneNumber;

+(void)setMpos:(NSString *)leiXing;
+(NSString *)getMpos;

// 验证是不是整数数字
+ (BOOL) isValidNumber:(NSString*)value;

// 验证是不是浮点型
+ (BOOL)isPureFloat:(NSString *)string;

+   (NSString * )getMerchantName;

+ (UIImageView*)getbgImgView;

// 获取电商唯一标示
+(NSString *)getMerchantEshopNo;
// UUID 设备唯一标识符
+ (NSString *)getCurrentDeviceUUID;
//获得设备型号
+ (NSString *)getCurrentDeviceModel;

+(BOOL)isPureInt:(NSString*)string;

//获取今天日期
+(NSString *)getTodayDate;
//获取前10天的日期
+(NSString *)getBeforeDate;

+(NSString *)getCheckFlag;

// 3DES加密解密
+(NSString *)TripleDES:(NSString *)plainText encryptOrDecrypt:(CCOperation)encryptOrDecrypt encryptOrDecryptKey:(NSString *)encryptOrDecryptKey;

+(NSString *)TripleDESVC:(NSString *)password encryptOrDecryptKey:(NSString *)key;

//汉字转拼音 add 胡猛 20151010
+(NSString *)PinYinFromCharacter:(NSString *)aString;
/**
 *  @brief  把汉字转成 拼音
 */
+(NSString *)stringByChinaese:(NSString *)string;
+(NSString *)kaHaoCHuLi:(NSString *)str;
+(NSString *)dateCHuLi:(NSString *)str;
+(NSString *)hexStringFromString:(NSData *)string;
+(NSString *)stringFromHexString:(NSString *)hexString;
+(BOOL)IsChinese:(NSString *)str;
/**
 *  @brief  去除字符串中的非数字
 *
 *  @param str
 *
 *  @return 处理后的字符串
 */
+(NSString *)findNumFromStr:(NSString *)str;


+(NSString*)regex_areaCode_threeDigit;

+(NSString*)regex_areaCode_fourDigit;

+(BOOL)isMobileNumber:(NSString *)mobileNum;

+(BOOL)judgeIDCard:(NSString *)IDCard;



/**
 *  快速计算出文本的真实尺寸
 *
 *  @param font    文字的字体
 *  @param maxSize 文本的最大尺寸
 *
 *  @return 快速计算出文本的真实尺寸
 */
- (CGSize)sizeWithFont:(UIFont *)font andMaxSize:(CGSize)maxSize;

/**
 *  快速计算出文本的真实尺寸
 *
 *  @param text    需要计算尺寸的文本
 *  @param font    文字的字体
 *  @param maxSize 文本的最大尺寸
 *
 *  @return 快速计算出文本的真实尺寸
 */
+ (CGSize)sizeWithText:(NSString *)text andFont:(UIFont *)font andMaxSize:(CGSize)maxSize;

/**
 *  判断银行卡号是否规范
 *
 *  @param cardNo 卡号
 *
 *  @return 是yes 不是no
 */
+ (BOOL)checkCardNo:(NSString*) cardNo;

/**
 *  银行卡日期判断
 *
 *  @param cardDate 日期字符串
 *
 *  @return 是yes 不是no
 */
+ (BOOL)checkCardDate:(NSString *)cardDate;

@end
