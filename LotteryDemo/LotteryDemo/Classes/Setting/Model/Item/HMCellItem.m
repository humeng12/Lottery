//
//  HMCellItem.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMCellItem.h"

@implementation HMCellItem

+(instancetype)itemWithIcon:(NSString *)icon title:(NSString *)title
{
    HMCellItem *item = [[self alloc] init];
    item.icon = icon;
    item.title = title;
    return item;
}


+(instancetype)itemWithTitle:(NSString *)title
{
    return [self itemWithIcon:nil title:title];
}

@end
