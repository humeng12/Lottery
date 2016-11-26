//
//  HMHtml.h
//  网易彩票
//
//  Created by 胡猛 on 16/10/28.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface HMHtml : NSObject

/**
 *  网页标题
 */
@property (nonatomic, copy) NSString *title;
/**
 *  网页文件名
 */
@property (nonatomic, copy) NSString *html;
@property (nonatomic, copy) NSString *ID;

-(instancetype)initWithDict:(NSDictionary *)dict;
+(instancetype)htmlWithDict:(NSDictionary *)dict;

@end
