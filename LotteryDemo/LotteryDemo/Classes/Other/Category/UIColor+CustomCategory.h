//
//  UIColor+CustomCategory.h
//  merchant
//
//  Created by HRT on 15/11/3.
//  Copyright © 2015年 Hrtpayment. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIColor(CustomCategory)

/**
 *  @brief  字符串转颜色
 *
 *  @param stringToConvert(如#55555)
 */
+(UIColor *) colorWithHexString: (NSString *) stringToConvert;
@end
