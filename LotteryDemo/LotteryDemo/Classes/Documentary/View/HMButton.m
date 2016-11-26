//
//  HMButton.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/26.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMButton.h"
#import <Availability.h>

@interface HMButton()

@property (nonatomic, strong) UIFont *font;

@end

@implementation HMButton


#pragma 从文件解析一个对象时就会调用
- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super initWithCoder:coder];
    if (self) {
        [self setup];
    }
    return self;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        [self setup];
    }
    return self;
}

-(void)setup
{
    self.font = [UIFont systemFontOfSize:14];
    self.titleLabel.font = self.font;
    
    self.imageView.contentMode = UIViewContentModeCenter;
}

-(CGRect)titleRectForContentRect:(CGRect)contentRect
{
    CGFloat titleX = 0;
    CGFloat titleY = 0;
    NSDictionary *attrs = @{NSFontAttributeName:self.font};
    CGFloat titleW;
    if (IOS7) {
#ifdef __IPHONE_7_0
        titleW = [self.currentTitle boundingRectWithSize:CGSizeMake(MAXFLOAT, MAXFLOAT) options:NSStringDrawingUsesLineFragmentOrigin attributes:attrs context:nil].size.width;
#else
        titleW = [self.currentTitle sizeWithFont:self.font].width;
#endif
    } else {
        titleW = [self.currentTitle sizeWithFont:self.font].width;
    }
    CGFloat titleH = contentRect.size.height;
    
    return CGRectMake(titleX, titleY, titleW, titleH);
}

-(CGRect)imageRectForContentRect:(CGRect)contentRect
{
    CGFloat imageW = 30;
    CGFloat imageX = contentRect.size.width - imageW;
    CGFloat imageY = 0;
    CGFloat imageH = contentRect.size.height;
    
    return CGRectMake(imageX, imageY, imageW, imageH);
}

@end
