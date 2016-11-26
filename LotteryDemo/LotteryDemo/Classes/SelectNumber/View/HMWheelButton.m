//
//  HMWheelButton.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/30.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMWheelButton.h"

@implementation HMWheelButton

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
    }
    return self;
}

-(CGRect)imageRectForContentRect:(CGRect)contentRect
{
    CGFloat imageW = 40;
    CGFloat imageH = 47;
    CGFloat imageX = (contentRect.size.width - imageW) * 0.5;
    CGFloat imageY = 20;
    
    return CGRectMake(imageX, imageY, imageW, imageH);
}

-(void)setHighlighted:(BOOL)highlighted
{

}
@end
