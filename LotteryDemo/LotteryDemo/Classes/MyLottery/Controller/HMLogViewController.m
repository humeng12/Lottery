//
//  HMLogViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/26.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMLogViewController.h"
#import "HMSettingViewController.h"

@interface HMLogViewController ()
@property (weak, nonatomic) IBOutlet UIButton *loginBtn;
- (IBAction)setting:(id)sender;

@end

@implementation HMLogViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIImage *normal = [UIImage resizableImage:@"RedButton"];
    UIImage *high = [UIImage resizableImage:@"RedButtonPressed"];
    [self.loginBtn setBackgroundImage:normal forState:UIControlStateNormal];
    [self.loginBtn setBackgroundImage:high forState:UIControlStateHighlighted];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)setting:(id)sender {
    
    HMSettingViewController *set = [[HMSettingViewController alloc] init];
    [self.navigationController pushViewController:set animated:YES];
}
@end
