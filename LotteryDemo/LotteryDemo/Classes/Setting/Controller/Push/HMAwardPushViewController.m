//
//  HMAwardPushViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMAwardPushViewController.h"
#import "HMCellItem.h"
#import "HMSettingGroup.h"
#import "HMSwitchItem.h"

@interface HMAwardPushViewController ()

@end

@implementation HMAwardPushViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    HMCellItem *ball = [HMSwitchItem itemWithTitle:@"双色球"];
    HMCellItem *letou = [HMSwitchItem itemWithTitle:@"大乐透"];
    HMSettingGroup *group = [[HMSettingGroup alloc] init];
    group.items = @[ball,letou];
    group.header = @"打开设置即可在开奖后立即收到推送消息，获知开奖号码";
    [self.data addObject:group];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



@end
