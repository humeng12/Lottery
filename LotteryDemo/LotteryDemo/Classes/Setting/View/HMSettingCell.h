//
//  HMSettingCell.h
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import <UIKit/UIKit.h>

@class HMCellItem;

@interface HMSettingCell : UITableViewCell

@property (nonatomic, strong) HMCellItem *item;

@property (nonatomic, assign, getter=isLastRowInSection) BOOL lastRowInSection;

+(instancetype)cellWithTableView:(UITableView *)tableView;

@end
