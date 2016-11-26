//
//  HMHelpViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/28.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMHelpViewController.h"
#import "HMArrowItem.h"
#import "HMSettingGroup.h"
#import "HMHtmlViewController.h"
#import "HMHtml.h"

@interface HMHelpViewController ()

@property (nonatomic, strong) NSArray *htmls;
@end

@implementation HMHelpViewController


-(NSArray *)htmls
{
    if (_htmls == nil) {
        
        NSMutableArray *htmlArray = [NSMutableArray array];
        NSString *path = [[NSBundle mainBundle] pathForResource:@"help.json" ofType:nil];
        NSData *data = [NSData dataWithContentsOfFile:path];
        NSArray *dictArray = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:nil];
        
        
        for (NSDictionary *dict in dictArray) {
            
            HMHtml *product = [HMHtml htmlWithDict:dict];
            [htmlArray addObject:product];
        }
        
        _htmls = htmlArray;
    }
    
    return _htmls;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSMutableArray *items = [NSMutableArray array];
    for (HMHtml *html in self.htmls) {
        
        HMCellItem *item = [HMArrowItem itemWithTitle:html.title vcClass:nil];
        [items addObject:item];
    }
    
    HMSettingGroup *group = [[HMSettingGroup alloc] init];
    group.items = items;
    [self.data addObject:group];
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    HMHtmlViewController *html = [[HMHtmlViewController alloc] init];
    html.html = self.htmls[indexPath.row];
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:html];
    [self presentViewController:nav animated:YES completion:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
