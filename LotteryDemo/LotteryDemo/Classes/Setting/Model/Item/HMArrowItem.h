//
//  HMArrowItem.h
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMCellItem.h"

@interface HMArrowItem : HMCellItem

//点击cell需要跳转的控制器
@property (nonatomic, assign) Class vcClass;


+(instancetype)itemWithIcon:(NSString *)icon title:(NSString *)title vcClass:(Class)vcClass;

+(instancetype)itemWithTitle:(NSString *)title vcClass:(Class)vcClass;

@end
