//
//  HMSettingGroup.h
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface HMSettingGroup : NSObject
//头部标题
@property (nonatomic, copy) NSString *header;
//尾部标题
@property (nonatomic, copy) NSString *footer;
//存放这组所有行的模型数据(都是HMCellItem对象)
@property (nonatomic, strong) NSArray *items;
@end
