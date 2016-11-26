//
//  HMSelectViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/30.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMSelectViewController.h"
#import "HMChooseView.h"

@interface HMSelectViewController ()
@property (weak, nonatomic) IBOutlet UIView *selectView;

@end

@implementation HMSelectViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //self.view.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"LuckyBackground@2x.jpg"]];
   
    HMChooseView *choose = [HMChooseView wheel];
    [self.selectView addSubview:choose];
    
    [choose startRotating];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
