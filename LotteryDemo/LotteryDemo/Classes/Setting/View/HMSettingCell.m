//
//  HMSettingCell.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMSettingCell.h"
#import "HMCellItem.h"
#import "HMArrowItem.h"
#import "HMSwitchItem.h"
#import "HMSettingLabelItem.h"

@interface HMSettingCell()

@property (nonatomic, strong) UIImageView *arrow;
@property (nonatomic, strong) UISwitch *switchView;
@property (nonatomic, strong) UILabel *labelView;

@property (nonatomic, weak) UIView *divider;
@end

@implementation HMSettingCell

-(UIImageView *)arrow
{
    if(_arrow == nil) {
        
        _arrow = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"CellArrow"]];
    }
    return _arrow;
}

-(UISwitch *)switchView
{
    if(_switchView == nil) {
        
        _switchView = [[UISwitch alloc] init];
        
        [_switchView addTarget:self action:@selector(switchChange) forControlEvents:UIControlEventValueChanged];
    }
    return _switchView;
}


-(void)switchChange
{
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    if(self.item.key) {
        
        [defaults setBool:self.switchView.on forKey:self.item.key];
    } else {
        
        [defaults setBool:self.switchView.on forKey:self.item.title];
    }
    [defaults synchronize];
}



-(UILabel *)labelView
{
    if(_labelView == nil) {
        
        _labelView = [[UILabel alloc] init];
        _labelView.bounds = CGRectMake(0, 0, 100, 30);
    }
    return _labelView;
}

+(instancetype)cellWithTableView:(UITableView *)tableView
{
    static NSString *ID = @"setting";
    HMSettingCell *cell = [tableView dequeueReusableCellWithIdentifier:ID];
    if (cell == nil) {
        cell = [[HMSettingCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:ID];
    }
    
    return cell;
}

-(instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        
        //设置普通背景
        UIView *cusBackView = [[UIView alloc] init];
        cusBackView.backgroundColor = [UIColor whiteColor];
        self.backgroundView = cusBackView;
        
        //设置选中时的背景
        UIView *backView = [[UIView alloc] init];
        backView.backgroundColor = HMColor(237, 233, 218);
        self.selectedBackgroundView = backView;
        
        
        self.textLabel.backgroundColor = [UIColor clearColor];
        self.detailTextLabel.backgroundColor = [UIColor clearColor];
        
        if (!IOS7) {
            
            UIView *divider = [[UIView alloc] init];
            divider.backgroundColor = [UIColor blackColor];
            divider.alpha = 0.5;
            [self.contentView addSubview:divider];
            self.divider = divider;
        }

    }
    
    return self;
}


-(void)setFrame:(CGRect)frame
{
    if(IOS7){
        frame.size.width += 20;
        frame.origin.x = -10;
    }
    
    [super setFrame:frame];
}


-(void)layoutSubviews
{
    [super layoutSubviews];
    
    if (IOS7) {
        return;
    }
    
    CGFloat divX = 0;
    CGFloat divW = [UIScreen mainScreen].bounds.size.width;
    CGFloat divH = 1;
    CGFloat divY = self.contentView.frame.size.height - divH;
    
    self.divider.frame = CGRectMake(divX, divY, divW, divH);
    
}

-(void)setLastRowInSection:(BOOL)lastRowInSection
{
    _lastRowInSection = lastRowInSection;
    
    self.divider.hidden = lastRowInSection;
}


-(void)setItem:(HMCellItem *)item
{
    _item = item;
    
    [self setupData];
    
    [self setRightContent];
}

-(void)setupData
{
    self.textLabel.text = self.item.title;
    if(self.item.icon)
        self.imageView.image = [UIImage imageNamed:self.item.icon];
    
    self.detailTextLabel.text = self.item.subtitle;
}

-(void)setRightContent
{
    if([self.item isKindOfClass:[HMArrowItem class]]) {
        
        self.accessoryView = self.arrow;
        self.selectionStyle = UITableViewCellSelectionStyleDefault;
    } else if ([self.item isKindOfClass:[HMSwitchItem class]]) {
        self.accessoryView = self.switchView;
        self.selectionStyle = UITableViewCellSelectionStyleNone;
        
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        if(self.item.key) {
            self.switchView.on = [defaults boolForKey:self.item.key];
        } else {
            self.switchView.on = [defaults boolForKey:self.item.title];
        }
        
    } else if ([self.item isKindOfClass:[HMSettingLabelItem class]]) {
        
        self.selectionStyle = UITableViewCellSelectionStyleDefault;
        self.accessoryView = self.labelView;
    }else {
        
        self.selectionStyle = UITableViewCellSelectionStyleDefault;
        self.accessoryView = nil;
    }
}


@end
