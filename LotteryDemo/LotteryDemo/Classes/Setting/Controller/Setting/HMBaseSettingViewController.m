//
//  HMBaseSettingViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMBaseSettingViewController.h"
#import "HMArrowItem.h"
#import "HMSwitchItem.h"
#import "HMSettingGroup.h"
#import "HMSettingCell.h"


@interface HMBaseSettingViewController ()

@end

@implementation HMBaseSettingViewController

- (instancetype)init
{
    self = [super initWithStyle:UITableViewStyleGrouped];
    if (self) {
        
    }
    return self;
}

-(instancetype)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:UITableViewStyleGrouped];
    if(self){
        
    }
    
    return self;
}

-(NSArray *)data
{
    if(_data == nil){
    
        _data = [NSMutableArray array];
        
    }
    
    return _data;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //样板图片平铺
    self.tableView.backgroundView = nil;
    self.tableView.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"bg"]];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return self.data.count;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    HMSettingGroup *group = self.data[section];
    return group.items.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    HMSettingCell *cell = [HMSettingCell cellWithTableView:tableView];
    
    HMSettingGroup *group = self.data[indexPath.section];
    HMCellItem *item = group.items[indexPath.row];
    
    cell.lastRowInSection = group.items.count == indexPath.row + 1;
    
    cell.item = item;
    
    return cell;
}


-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    //取消选中这行
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    
    HMSettingGroup *group = self.data[indexPath.section];
    HMCellItem *item = group.items[indexPath.row];
    
    if(item.optton) {
        item.optton();
        
    } else if([item isKindOfClass:[HMArrowItem class]]) {
        
        HMArrowItem *arrowItem = (HMArrowItem *)item;
        if(arrowItem == nil) return;
        
        UIViewController *vc = [[arrowItem.vcClass alloc] init];
        vc.title = arrowItem.title;
        [self.navigationController pushViewController:vc animated:YES];
    }
}


-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    HMSettingGroup *group = self.data[section];
    return group.header;
}


-(NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    HMSettingGroup *group = self.data[section];
    return group.footer;
}

@end
