//
//  HMSettingViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMSettingViewController.h"
#import "HMArrowItem.h"
#import "HMSwitchItem.h"
#import "HMSettingGroup.h"
#import "HMSettingCell.h"
#import "HMPushViewController.h"
#import "HMProductViewController.h"
#import "HMHelpViewController.h"
#import "HMShareViewController.h"
#import "HMAboutViewController.h"

@interface HMSettingViewController ()

@end

@implementation HMSettingViewController


-(void)setGroup0
{
    HMCellItem *pushNotice = [HMArrowItem itemWithIcon:@"MorePush" title:@"推送和提醒" vcClass:[HMPushViewController class]];
    HMCellItem *handShake = [HMSwitchItem itemWithIcon:@"handShake" title:@"摇一摇机选"];
    HMCellItem *soundEffect = [HMSwitchItem itemWithIcon:@"sound_Effect" title:@"声音效果"];
    HMSettingGroup *group0 = [[HMSettingGroup alloc] init];
    group0.items = @[pushNotice,handShake,soundEffect];
    [self.data addObject:group0];
    
}


-(void)setGroup1
{
    HMCellItem *update = [HMArrowItem itemWithIcon:@"MoreUpdate" title:@"检查新版本" vcClass:[HMPushViewController class]];
    update.optton = ^{
        
        [MBProgressHUD showMessage:@"正在检测...."];
        
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            
            [MBProgressHUD hideHUD];
            
        });
    };

    
    HMCellItem *help = [HMArrowItem itemWithIcon:@"MoreHelp" title:@"帮助" vcClass:[HMHelpViewController class]];
    HMCellItem *share = [HMArrowItem itemWithIcon:@"MoreShare" title:@"分享" vcClass:[HMShareViewController class]];
    HMCellItem *message = [HMArrowItem itemWithIcon:@"MoreMessage" title:@"查看消息" vcClass:[HMPushViewController class]];
    HMCellItem *product = [HMArrowItem itemWithIcon:@"MoreNetease" title:@"产品推荐" vcClass:[HMProductViewController class]];
    HMCellItem *about = [HMArrowItem itemWithIcon:@"MoreAbout" title:@"关于" vcClass:[HMAboutViewController class]];
    HMSettingGroup *group1 = [[HMSettingGroup alloc] init];
    group1.items = @[update,help,share,message,product,about];
    [self.data addObject:group1];
}


- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"设置";
    
    [self setGroup0];
    [self setGroup1];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


-(void)dealloc
{
    NSLog(@"dddddd");
}
@end
