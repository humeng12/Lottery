//
//  HMCellItem.h
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//


typedef void (^HMCellItemOption)();

#import <Foundation/Foundation.h>

@interface HMCellItem : NSObject
//图标
@property (nonatomic, copy) NSString *icon;
//标题
@property (nonatomic, copy) NSString *title;

@property (nonatomic, copy) NSString *subtitle;

//储存信息的key
@property (nonatomic, copy) NSString *key;


//点击cell作什么事情
@property (nonatomic, copy) HMCellItemOption optton;

+(instancetype)itemWithIcon:(NSString *)icon title:(NSString *)title;

+(instancetype)itemWithTitle:(NSString *)title;

@end
