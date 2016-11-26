//
//  HMScoreTimeViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMScoreTimeViewController.h"
#import "HMCellItem.h"
#import "HMSettingGroup.h"
#import "HMSwitchItem.h"
#import "HMSettingLabelItem.h"

@interface HMScoreTimeViewController ()

@end

@implementation HMScoreTimeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    HMCellItem *notice = [HMSwitchItem itemWithTitle:@"提醒我关注的比赛"];
    HMSettingGroup *group0 = [[HMSettingGroup alloc] init];
    group0.items = @[notice];
    group0.footer = @"当我关注的比赛比分发生变化时，通过小弹窗或推送进行提醒";
    [self.data addObject:group0];
    
    HMCellItem *start = [HMSettingLabelItem itemWithTitle:@"起始时间"];
    HMSettingGroup *group1 = [[HMSettingGroup alloc] init];
    group1.items = @[start];
    group1.header = @"只在以下时间接受比分直播";
    [self.data addObject:group1];
    
    HMCellItem *end = [HMSettingLabelItem itemWithTitle:@"结束时间"];
    HMSettingGroup *group2 = [[HMSettingGroup alloc] init];
    group2.items = @[end];
    [self.data addObject:group2];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
