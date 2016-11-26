//
//  HMTabBar.h
//  网易彩票
//
//  Created by 胡猛 on 16/10/25.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import <UIKit/UIKit.h>

@class HMTabBar;

@protocol HMTabBarDelegate <NSObject>

@optional

-(void)tabBar:(HMTabBar *)tabBar didSelectBtnFrom:(NSInteger)from to:(NSInteger)to;

@end

@interface HMTabBar : UIView

@property (nonatomic, weak) id<HMTabBarDelegate>delagate;

@end
