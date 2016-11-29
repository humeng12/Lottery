//
//  ILCircleView.h
//  01-ItcastLottery
//
//  Created by mj on 13-12-26.
//  Copyright (c) 2013年 itcast. All rights reserved.
//

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