//
//  HMAwardAnimViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMAwardAnimViewController.h"
#import "HMCellItem.h"
#import "HMSettingGroup.h"
#import "HMSwitchItem.h"

@interface HMAwardAnimViewController ()

@end

@implementation HMAwardAnimViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    HMCellItem *anim = [HMSwitchItem itemWithTitle:@"中奖动画"];
    HMSettingGroup *group = [[HMSettingGroup alloc] init];
    group.items = @[anim];
    group.header = @"当您有新中奖订单，启动程序时通过动画提醒您。为避免过于频繁，高频彩不会提醒。";
    [self.data addObject:group];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
