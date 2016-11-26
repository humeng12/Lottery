//
//  HMAboutViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/28.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMAboutViewController.h"
#import "HMCellItem.h"
#import "HMArrowItem.h"
#import "HMSettingGroup.h"

@interface HMAboutViewController ()

@end

@implementation HMAboutViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    UIWebView *webView = [[UIWebView alloc] init];
    webView.frame = CGRectZero;
    [self.view addSubview:webView];
    
    HMCellItem *score = [HMArrowItem itemWithTitle:@"评分支持" vcClass:nil];
    score.optton = ^{
        
        NSString *appid = @"";
        NSString *str = [NSString stringWithFormat:
                         @"itms-apps://itunes.apple.com/cn/app/id%@?mt=8",appid];
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];
    };
    HMCellItem *call = [HMArrowItem itemWithTitle:@"客服电话" vcClass:nil];
    call.subtitle = @"1000000";
    call.optton = ^{
        
        NSURL *url = [NSURL URLWithString:@"tel://"];
//        NSURL *url = [NSURL URLWithString:@"telprompt://"];
        [[UIApplication sharedApplication] openURL:url];
        
//        [webView loadRequest:[NSURLRequest requestWithURL:url]];
    };
    
    HMSettingGroup *group = [[HMSettingGroup alloc] init];
    group.items = @[score,call];
    [self.data addObject:group];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
