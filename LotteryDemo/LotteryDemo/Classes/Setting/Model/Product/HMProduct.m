//
//  HMProduct.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMProduct.h"

@implementation HMProduct


-(instancetype)initWithDict:(NSDictionary *)dict
{
    if (self = [super init]) {
        
        //[self setValuesForKeysWithDictionary:dict];
        self.icon = dict[@"icon"];
        self.title = dict[@"title"];
        self.url = dict[@"url"];
        self.customUrl = dict[@"customUrl"];
        self.ID = dict[@"ID"];
    }
    return self;
}

+(instancetype)productWithDict:(NSDictionary *)dict
{
    return [[self alloc] initWithDict:dict];
}
@end
