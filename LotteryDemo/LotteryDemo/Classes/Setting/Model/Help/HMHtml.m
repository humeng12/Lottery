//
//  HMHtml.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/28.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMHtml.h"

@implementation HMHtml

-(instancetype)initWithDict:(NSDictionary *)dict
{
    if (self = [super init]) {
        self.html = dict[@"html"];
        self.title = dict[@"title"];
        self.ID = dict[@"id"];
    }
    return self;
}


+(instancetype)htmlWithDict:(NSDictionary *)dict
{
    return [[self alloc] initWithDict:dict];
}


@end
