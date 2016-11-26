//
//  HMSettingViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMSettingViewController.h"
#import "HMArrowItem.h"
#import "HMSettingGroup.h"
#import "HMPushViewController.h"
#import "HMAwardPushViewController.h"
#import "HMAwardAnimViewController.h"
#import "HMScoreTimeViewController.h"

@interface HMPushViewController ()

@end

@implementation HMPushViewController

-(void)setGroup
{
    HMCellItem *push1 = [HMArrowItem itemWithTitle:@"开奖号码推送" vcClass:[HMAwardPushViewController class]];
    HMCellItem *push2 = [HMArrowItem itemWithTitle:@"中奖动画" vcClass:[HMAwardAnimViewController class]];
    HMCellItem *push3 = [HMArrowItem itemWithTitle:@"比分直播提醒" vcClass:[HMScoreTimeViewController class]];
    HMCellItem *push4 = [HMArrowItem itemWithTitle:@"购彩定时提醒" vcClass:[HMPushViewController class]];
    HMSettingGroup *group = [[HMSettingGroup alloc] init];
    group.items = @[push1,push2,push3,push4];
    [self.data addObject:group];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self setGroup];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
