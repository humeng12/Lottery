//
//  HMSelectViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/30.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMSelectViewController.h"
#import "HMChooseView.h"
#import "ILCircleView.h"
#import "ILThreeButton.h"

@interface HMSelectViewController ()

{
    ILThreeButton *_three;
    ILCircleView *_circle;
}

@property (weak, nonatomic) IBOutlet UIView *selectView;

@end

@implementation HMSelectViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // 1.设置背景
    [self addBg];
    
    // 2.添加3个按钮
    [self addThreeButton];
    
    // 3.添加转盘
    [self addCircle];
   
//    HMChooseView *choose = [HMChooseView wheel];
//    [self.selectView addSubview:choose];
//    
//    [choose startRotating];
}


- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    
    [_circle pauseRotate];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [_circle startRotate];
}


#pragma mark 添加转盘
- (void)addCircle
{
    ILCircleView *circle = [ILCircleView circleView];
    CGFloat centerX = self.view.frame.size.width * 0.5;
    CGFloat centerY = CGRectGetMaxY(_three.frame) + circle.frame.size.height * 0.5;
    if (!is4Inch) {
        centerY -= 20;
    }
    circle.center = CGPointMake(centerX, centerY);
    [self.view addSubview:circle];
    _circle = circle;
}


#pragma mark 设置背景
- (void)addBg
{
    UIImageView *bgView = [[UIImageView alloc] init];
    bgView.frame = self.view.bounds;
    bgView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    bgView.image = [UIImage imageNamed:is4Inch?@"LuckyBackground-568h.jpg":@"LuckyBackground.jpg"];
    [self.view addSubview:bgView];
}


#pragma mark 添加三个按钮
- (void)addThreeButton
{
    ILThreeButton *tb = [ILThreeButton threeButton];
    CGFloat tbCenterX = self.view.frame.size.width * 0.5;
    CGFloat tbCenterY = tb.frame.size.height * 0.5 + 100;
    tb.center = CGPointMake(tbCenterX, tbCenterY);
    [self.view addSubview:tb];
    _three = tb;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
