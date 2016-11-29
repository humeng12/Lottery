

#import "ILCircleBgView.h"

@implementation ILCircleBgView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    // 1.绘制底部托盘
    CGContextSaveGState(ctx);
    CGFloat xy = 8;
    CGFloat wh = rect.size.width - 2 * xy;
    CGRect circle = CGRectMake(xy, xy, wh, wh);
    CGContextAddEllipseInRect(ctx, circle);
    CGContextClip(ctx);
    [[UIImage imageNamed:@"LuckyBaseBackground"] drawInRect:rect];
    CGContextRestoreGState(ctx);
    
    // 绘制顶部图片
    [[UIImage imageNamed:@"LuckyRotateWheel"] drawInRect:rect];
}

@end
