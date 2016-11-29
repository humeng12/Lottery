//
//  ILCircleItemView.h
//  01-ItcastLottery
//
//  Created by mj on 13-12-26.
//  Copyright (c) 2013年 itcast. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ILCircleItemView : UIView
@property (nonatomic, strong) UIImage *normalImage;
@property (nonatomic, strong) UIImage *selectedImage;
@property (nonatomic, assign) BOOL selected;
@end