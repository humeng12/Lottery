//
//  HMTabBarController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/25.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMTabBarController.h"
#import "HMTabBar.h"

@interface HMTabBarController ()<HMTabBarDelegate>


@end

@implementation HMTabBarController

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    [self.tabBar removeFromSuperview];
    
    HMTabBar *myTabBar = [[HMTabBar alloc] init];
    myTabBar.delagate = self;
    myTabBar.frame = self.tabBar.bounds;
    [self.tabBar addSubview:myTabBar];

}


-(void)tabBar:(HMTabBar *)tabBar didSelectBtnFrom:(NSInteger)from to:(NSInteger)to
{
    self.selectedIndex = to;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
