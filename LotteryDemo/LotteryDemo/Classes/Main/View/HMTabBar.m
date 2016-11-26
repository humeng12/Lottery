//
//  HMTabBar.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/25.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMTabBar.h"
#import "HMTabBarButton.h"


#define BUTTONCOUNT     5

@interface HMTabBar()

@property (nonatomic, weak) HMTabBarButton *selectedBtn;

@end

@implementation HMTabBar

-(instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if(self){
        
        [self addUpButtons];
    }
    
    return self;
}


-(void)addUpButtons
{
    for (int i = 0; i < BUTTONCOUNT; i++) {
        
        HMTabBarButton *btn = [HMTabBarButton buttonWithType:UIButtonTypeCustom];
        
        NSString *name = [NSString stringWithFormat:@"TabBar%d",i+1];
        NSString *selectName = [NSString stringWithFormat:@"TabBar%dSel",i+1];
        [btn setBackgroundImage:[UIImage imageNamed:name] forState:UIControlStateNormal];
        [btn setBackgroundImage:[UIImage imageNamed:selectName] forState:UIControlStateSelected];
        btn.tag = i;
        
        
        [btn addTarget:self action:@selector(buttonClick:) forControlEvents:UIControlEventTouchDown];
        
        [self addSubview:btn];
        
        if(i == 0){
            [self buttonClick:btn];
        }
    }
}


-(void)layoutSubviews
{
    for (int i =0; i < BUTTONCOUNT; i++) {
        
        HMTabBarButton *btn = self.subviews[i];
        
        CGFloat buttonY = 0;
        CGFloat buttonW = self.frame.size.width / BUTTONCOUNT;
        CGFloat buttonH = self.frame.size.height;
        CGFloat buttonX= i * buttonW;
        btn.frame = CGRectMake(buttonX, buttonY, buttonW, buttonH);
    }
}


-(void)buttonClick:(HMTabBarButton *)btn
{
    
    if([self.delagate respondsToSelector:@selector(tabBar:didSelectBtnFrom:to:)]){
        
        [self.delagate tabBar:self didSelectBtnFrom:self.selectedBtn.tag to:btn.tag];
    }
    
    self.selectedBtn.selected = NO;
    btn.selected = YES;
    self.selectedBtn = btn;
    
}


@end
