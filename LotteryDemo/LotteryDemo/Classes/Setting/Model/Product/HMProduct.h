//
//  HMProduct.h
//  网易彩票
//
//  Created by 胡猛 on 16/10/27.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

//"title": "网易微博",
//"id": "com.netease.microblogging",
//"url": "http://itunes.apple.com/app/id383629309?mt=8",
//"icon": "newb@2x.png",
//"customUrl": "microblogging"

#import <Foundation/Foundation.h>

@interface HMProduct : NSObject

@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *url;
@property (nonatomic, copy) NSString *icon;
@property (nonatomic, copy) NSString *customUrl;
@property (nonatomic, copy) NSString *ID;

-(instancetype)initWithDict:(NSDictionary *)dict;
+(instancetype)productWithDict:(NSDictionary *)dict;

@end
