

#import "HMChooseView.h"
#import "HMWheelButton.h"

@interface HMChooseView ()
@property (weak, nonatomic) IBOutlet UIImageView *centerImage;
@property (nonatomic, weak) HMWheelButton *selectBtn;

- (IBAction)startSelect:(id)sender;

@property (nonatomic, strong) CADisplayLink *link;
@end

@implementation HMChooseView

+(instancetype)wheel
{
    return [[[NSBundle mainBundle] loadNibNamed:@"HMChooseView" owner:nil options:nil] lastObject];
}


-(void)awakeFromNib
{
    [super awakeFromNib];
    
    self.centerImage.userInteractionEnabled = YES;
    
    UIImage *bigImage = [UIImage imageNamed:@"LuckyAstrology"];
    UIImage *bigSeleImage = [UIImage imageNamed:@"LuckyAstrologyPressed"];
    CGFloat smallW = bigImage.size.width / 12 * [UIScreen mainScreen].scale;
    CGFloat smallH = bigImage.size.height * [UIScreen mainScreen].scale;
    
    for (int index = 0; index < 12; index ++) {
        
        HMWheelButton *btn = [HMWheelButton buttonWithType:UIButtonTypeCustom];
        
        CGRect smallRect = CGRectMake(index * smallW, 0, smallW, smallH);
        CGImageRef smallImage = CGImageCreateWithImageInRect(bigImage.CGImage, smallRect);
        CGImageRef smallSelImage = CGImageCreateWithImageInRect(bigSeleImage.CGImage, smallRect);
        [btn setImage:[UIImage imageWithCGImage:smallImage] forState:UIControlStateNormal];
        [btn setImage:[UIImage imageWithCGImage:smallSelImage] forState:UIControlStateSelected];
        
        [btn setBackgroundImage:[UIImage imageNamed:@"LuckyRototeSelected"] forState:UIControlStateSelected];
        //btn.backgroundColor = [UIColor colorWithRed:arc4random_uniform(255)/255.0 green:arc4random_uniform(255)/255.0 blue:arc4random_uniform(255)/255.0 alpha:1];
        btn.bounds = CGRectMake(0, 0, 68, 143);
        
        btn.layer.anchorPoint = CGPointMake(0.5, 1);
        btn.layer.position = CGPointMake(self.centerImage.frame.size.width * 0.5, self.centerImage.frame.size.height * 0.5);
        
        // 设置旋转角度(绕着锚点进行旋转)
        CGFloat angle = (30 * index) / 180.0 * M_PI;
        btn.transform = CGAffineTransformMakeRotation(angle);
        
        [btn addTarget:self action:@selector(btnClick:) forControlEvents:UIControlEventTouchDown];
        
        [self.centerImage addSubview:btn];
        
        if (index ==0) {
            [self btnClick:btn];
        }
    }
}


-(void)btnClick:(HMWheelButton *)btn
{
    self.selectBtn.selected = NO;
    btn.selected = YES;
    self.selectBtn = btn;
}

-(void)startRotating
{
//    CABasicAnimation*anim = [CABasicAnimation animation];
//    
//    anim.keyPath = @"transform.rotation";
//    anim.toValue = @[@(M_PI * 2)];
//    anim.duration = 5.0;
//    
//    anim.repeatCount = MAXFLOAT;
//    
//    [self.centerImage.layer addAnimation:anim forKey:nil];
    
    if (self.link) {
        return;
    }
    CADisplayLink *link = [CADisplayLink displayLinkWithTarget:self selector:@selector(update)];
    self.link = link;
    [link addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];
}


-(void)update
{
    self.centerImage.transform = CGAffineTransformRotate(self.centerImage.transform, M_PI/400);
}


-(void)stopRotating
{
    [self.link invalidate];
    self.link = nil;
}


- (IBAction)startSelect:(id)sender {
    
    [self stopRotating];
    
    CABasicAnimation*anim = [CABasicAnimation animation];
    
    anim.keyPath = @"transform.rotation";
    anim.toValue = @[@(M_PI * 2 *3)];
    anim.duration = 1.5;
    
    anim.delegate = self;
    
    anim.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    
    [self.centerImage.layer addAnimation:anim forKey:nil];
    
    self.userInteractionEnabled = NO;
}

- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag
{
    self.userInteractionEnabled = YES;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self startRotating];
    });
}

@end
