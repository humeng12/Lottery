//
//  ILCircleItemView.m
//  01-ItcastLottery
//
//  Created by mj on 13-12-26.
//  Copyright (c) 2013年 itcast. All rights reserved.
//

#import "ILCircleItemView.h"
#import <QuartzCore/QuartzCore.h>

@implementation ILCircleItemView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setup];
    }
    return self;
}

- (void)awakeFromNib
{
    [super awakeFromNib];
    [self setup];
}

- (void)setFrame:(CGRect)frame
{
    frame.size = CGSizeMake(68, 143);
    [super setFrame:frame];
}

- (void)setup
{
    self.layer.anchorPoint = CGPointMake(0.5, 1);
    self.backgroundColor = [UIColor clearColor];
}

- (void)setSelected:(BOOL)selected
{
    _selected = selected;
    
    [self setNeedsDisplay];
}

- (void)drawRect:(CGRect)rect
{
    // 1.裁剪
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    CGFloat centerX = rect.size.width * 0.5;
    CGContextMoveToPoint(ctx, centerX, 0);
    
    CGFloat midY = 20;
    CGContextAddLineToPoint(ctx, 0, midY);
    CGContextAddLineToPoint(ctx, centerX, rect.size.height);
    CGContextAddLineToPoint(ctx, rect.size.width, midY);
    CGContextClosePath(ctx);
    
    CGContextClip(ctx);
    
    // 2.背景
    CGFloat scale = 0.5;
    CGFloat w = _normalImage.size.width * scale;
    CGFloat h = _normalImage.size.height * scale;
    CGFloat x = (rect.size.width - w) * 0.5;
    CGFloat y = (rect.size.height - h) * 0.5 - 25;
    CGRect imgRect = CGRectMake(x, y, w, h);
    if (_selected) {
        [[UIImage imageNamed:@"LuckyRototeSelected"] drawInRect:rect];
        [_selectedImage drawInRect:imgRect];
    } else {
        [_normalImage drawInRect:imgRect];
    }
}
@end
