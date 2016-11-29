//
//  ILTreeButton.m
//  01-ItcastLottery
//
//  Created by mj on 13-12-26.
//  Copyright (c) 2013年 itcast. All rights reserved.
//

#import "ILThreeButton.h"

@interface ILThreeButton()
- (IBAction)selectType;
- (IBAction)selectCount;
- (IBAction)selectCategory;
@end

@implementation ILThreeButton

+ (instancetype)threeButton
{
    return [[NSBundle mainBundle] loadNibNamed:@"ILThreeButton" owner:nil options:nil][0];
}

- (IBAction)selectType {
}

- (IBAction)selectCount {
}

- (IBAction)selectCategory {
}
@end
