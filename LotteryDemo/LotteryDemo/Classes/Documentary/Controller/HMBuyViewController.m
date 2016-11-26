//
//  HMBuyViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/26.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMBuyViewController.h"
#import "HMButton.h"

@interface HMBuyViewController ()
- (IBAction)titleClick:(HMButton *)sender;

@end

@implementation HMBuyViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)titleClick:(HMButton *)sender {
    
    [UIView animateWithDuration:0.25 animations:^{
        
        sender.imageView.transform = CGAffineTransformMakeRotation(M_PI);
    }];
}
@end
