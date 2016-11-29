

#import <UIKit/UIKit.h>

typedef enum {
    ILCircleTypeAstrology, // 星座
    ILCircleTypeAnimal // 生肖
} ILCircleType;

@interface ILCircleView : UIView
@property (nonatomic, assign) ILCircleType circleType;

+ (instancetype)circleView;
- (void)startRotate;
- (void)pauseRotate;
- (void)stopRotate;
@end
