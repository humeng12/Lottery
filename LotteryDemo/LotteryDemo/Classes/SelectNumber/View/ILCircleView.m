//
//  ILCircleView.m
//  01-ItcastLottery
//
//  Created by mj on 13-12-26.
//  Copyright (c) 2013年 itcast. All rights reserved.
//

#import "ILCircleView.h"
#import "ILCircleItemView.h"
#import <QuartzCore/QuartzCore.h>

#define ILCircleRotateSpeed (M_PI / 10.0)
#define ILTransform2Angle(t) (atan2(t.b, t.a))

@interface ILCircleView()
{
    ILCircleItemView *_selectedItem;
    CADisplayLink *_timer;
    NSMutableArray *_items;
}
@property (weak, nonatomic) IBOutlet UIView *bgView;
- (IBAction)startChoose;
@end

@implementation ILCircleView

+ (instancetype)circleView
{
    return [[NSBundle mainBundle] loadNibNamed:@"ILCircleView" owner:nil options:nil][0];
}

- (void)awakeFromNib
{
    // 1.12个按钮
    _items = [NSMutableArray array];
    for (int i = 0; i<12; i++) {
        ILCircleItemView *item = [[ILCircleItemView alloc] init];
        CGFloat posX = self.frame.size.width * 0.5;
        CGFloat posY = item.frame.size.height;
        item.layer.position = CGPointMake(posX, posY);
        item.tag = i;
        item.transform = CGAffineTransformMakeRotation(i * M_PI / 6.0);
        UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(itemClick:)];
        [item addGestureRecognizer:tap];
        [_bgView addSubview:item];
        [_items addObject:item];
        
        if (i == 0) {
            [self itemClick:tap];
        }
    }
    
    // 2.设置类型
    self.circleType = ILCircleTypeAstrology;
}

#pragma mark 选中了某个Item
- (void)itemClick:(UITapGestureRecognizer *)tap
{
    ILCircleItemView *item = (ILCircleItemView *)tap.view;
    _selectedItem.selected = NO;
    item.selected = YES;
    _selectedItem = item;
}

#pragma mark 设置类型
- (void)setCircleType:(ILCircleType)circleType
{
    _circleType = circleType;
    
    // 1.文件名
    NSString *normal = @"LuckyAstrology";
    NSString *selected = @"LuckyAstrologyPressed";
    if (circleType == ILCircleTypeAnimal) {
        normal = @"LuckyAnimal";
        selected = @"LuckyAnimalPressed";
    }
    UIImage *nImage = [UIImage imageNamed:normal];
    UIImage *sImage = [UIImage imageNamed:selected];
    
    // 2.裁剪图片
    int itemCount = _items.count;
    for (int i = 0; i<itemCount; i++) {
        ILCircleItemView *item = _items[i];
        
        // 2.1.尺寸
        CGFloat w = nImage.size.width / 12.0;
        if (isRetina) {
            w *= 2;
        }
        CGFloat h = nImage.size.height * 2;
        CGRect rect = CGRectMake(i * w, 0, w, h);
        // 2.2.普通
        CGImageRef nRef = CGImageCreateWithImageInRect(nImage.CGImage, rect);
        item.normalImage = [UIImage imageWithCGImage:nRef];
        
        // 2.3.选中
        CGImageRef sRef = CGImageCreateWithImageInRect(sImage.CGImage, rect);
        item.selectedImage = [UIImage imageWithCGImage:sRef];
    }
}

#pragma mark 开始旋转
- (void)startRotate
{
    if (_timer.isPaused) {
        _timer.paused = NO;
    } else {
        [_timer invalidate];
        _timer = [CADisplayLink displayLinkWithTarget:self selector:@selector(rotating)];
        [_timer addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];
    }
}

- (void)rotating
{
    CGFloat angle = ILCircleRotateSpeed * _timer.duration;
    _bgView.transform = CGAffineTransformRotate(_bgView.transform, angle);
}

#pragma mark 暂停旋转
- (void)pauseRotate
{
    _timer.paused = YES;
}

#pragma mark 停止旋转
- (void)stopRotate
{
    [_timer invalidate];
    _timer = nil;
    
    _bgView.transform = CGAffineTransformMakeRotation(-ILTransform2Angle(_selectedItem.transform));
}

#pragma mark 开始选号
- (IBAction)startChoose {
    self.userInteractionEnabled = NO;
    
    // 1.停止转动
    [self stopRotate];
    
    // 2.旋转动画
    CABasicAnimation *anim = [CABasicAnimation animationWithKeyPath:@"transform.rotation"];
    anim.duration = 1.5;
    CGFloat end = ILTransform2Angle(_bgView.transform);
    anim.toValue = @(M_PI * 10 + end);
    anim.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseOut];
    anim.delegate = self;
    [_bgView.layer addAnimation:anim forKey:nil];
}

- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag
{
    self.userInteractionEnabled = YES;
    
    double delayInSeconds = 2.0;
    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
        [self startRotate];
    });
}
@end
