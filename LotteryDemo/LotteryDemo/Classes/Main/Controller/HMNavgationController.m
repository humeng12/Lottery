//
//  HMNavgationController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/26.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMNavgationController.h"

@interface HMNavgationController ()

@end

@implementation HMNavgationController


//系统在第一次使用时调用
+ (void)initialize
{
    //设置导航栏主题
    UINavigationBar *navBar = [UINavigationBar appearance];
    navBar.tintColor = [UIColor whiteColor];
    
    if(IOS7){
        [navBar setBackgroundImage:[UIImage imageNamed:@"NavBar64"] forBarMetrics:UIBarMetricsDefault];
    } else {
        
        [navBar setBackgroundImage:[UIImage imageNamed:@"NavBar"] forBarMetrics:UIBarMetricsDefault];
    }
    
    //设置标题文字颜色
    NSMutableDictionary *dic = [NSMutableDictionary dictionary];
    dic[NSForegroundColorAttributeName] = [UIColor whiteColor];
    dic[NSFontAttributeName] = [UIFont systemFontOfSize:16];
    [navBar setTitleTextAttributes:dic];
    
    
    UIBarButtonItem *item = [UIBarButtonItem appearance];
    NSMutableDictionary *itemDic = [NSMutableDictionary dictionary];
    itemDic[NSForegroundColorAttributeName] = [UIColor whiteColor];
    itemDic[NSFontAttributeName] = [UIFont systemFontOfSize:14];
    [item setTitleTextAttributes:itemDic forState:UIControlStateNormal];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



-(void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated
{
    viewController.hidesBottomBarWhenPushed = YES;
    [super pushViewController:viewController animated:YES];
}


@end
