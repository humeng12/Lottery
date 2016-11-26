//
//  HMArrowItem.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMArrowItem.h"

@implementation HMArrowItem


+(instancetype)itemWithIcon:(NSString *)icon title:(NSString *)title vcClass:(__unsafe_unretained Class)vcClass
{
    HMArrowItem *item = [self itemWithIcon:icon title:title];
    item.vcClass = vcClass;
    return item;
}

+(instancetype)itemWithTitle:(NSString *)title vcClass:(Class)vcClass
{
    return [self itemWithIcon:nil title:title vcClass:vcClass];
}

@end
