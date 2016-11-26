//
//  HMProductCell.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMProductCell.h"
#import "HMProduct.h"

@interface HMProductCell()
@property (weak, nonatomic) IBOutlet UIImageView *iconImage;
@property (weak, nonatomic) IBOutlet UILabel *iconName;

@end


@implementation HMProductCell


-(void)awakeFromNib
{
    [super awakeFromNib];
    self.iconImage.layer.cornerRadius = 10;
    self.iconImage.clipsToBounds = YES;
}

-(void)setProduct:(HMProduct *)product
{
    _product = product;
    
    self.iconImage.image = [UIImage imageNamed:product.icon];
    self.iconName.text = product.title;
}


@end
