//
//  HMShareViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/28.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMShareViewController.h"
#import "HMCellItem.h"
#import "HMArrowItem.h"
#import "HMSettingGroup.h"
#import <MessageUI/MessageUI.h>

@interface HMShareViewController ()<MFMailComposeViewControllerDelegate,MFMessageComposeViewControllerDelegate>

@end

@implementation HMShareViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    __unsafe_unretained typeof(self) selfVc = self;
    
    HMCellItem *sina = [HMArrowItem itemWithIcon:@"WeiboSina" title:@"浪" vcClass:nil];
    HMCellItem *sms = [HMArrowItem itemWithIcon:@"SmsShare" title:@"短信分享" vcClass:nil];
    sms.optton = ^{
        if (![MFMessageComposeViewController canSendText]) return;
        
        MFMessageComposeViewController *vc = [[MFMessageComposeViewController alloc] init];
        // 设置短信内容
        vc.body = @"吃饭了没？";
        // 设置收件人列表
        vc.recipients = @[@"10010", @"02010010"];
        // 设置代理
        vc.messageComposeDelegate = selfVc;
        
        // 显示控制器
        [selfVc presentViewController:vc animated:YES completion:nil];
        
        //        self.age = 10;
        
        //        NSURL *url = [NSURL URLWithString:@"sms://10010"];
        //        [[UIApplication sharedApplication] openURL:url];
    };
    
    //    __unsafe_unretained MJShareViewController *share = self;
    
    
    HMCellItem *mail = [HMArrowItem itemWithIcon:@"MailShare" title:@"邮件分享" vcClass:nil];
    mail.optton = ^{
        // 不能发邮件
        if (![MFMailComposeViewController canSendMail]) return;
        
        MFMailComposeViewController *vc = [[MFMailComposeViewController alloc] init];
        
        // 设置邮件主题
        [vc setSubject:@"会议"];
        // 设置邮件内容
        [vc setMessageBody:@"今天下午开会吧" isHTML:NO];
        // 设置收件人列表
        [vc setToRecipients:@[@"643055866@qq.com"]];
        // 设置抄送人列表
        [vc setCcRecipients:@[@"1234@qq.com"]];
        // 设置密送人列表
        [vc setBccRecipients:@[@"56789@qq.com"]];
        
        // 添加附件（一张图片）
        UIImage *image = [UIImage imageNamed:@"lufy.png"];
        NSData *data = UIImagePNGRepresentation(image);
        [vc addAttachmentData:data mimeType:@"image/png" fileName:@"lufy.png"];
        
        // 设置代理
        vc.mailComposeDelegate = selfVc;
        // 显示控制器
        [selfVc presentViewController:vc animated:YES completion:nil];
    };
    
    HMSettingGroup *group = [[HMSettingGroup alloc] init];
    group.items = @[sina, sms, mail];
    [self.data addObject:group];
}

/**
 *  点击取消按钮会自动调用
 */
- (void)messageComposeViewController:(MFMessageComposeViewController *)controller didFinishWithResult:(MessageComposeResult)result
{
    [controller dismissViewControllerAnimated:YES completion:nil];
}

- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error
{
    [controller dismissViewControllerAnimated:YES completion:nil];
}

- (void)dealloc
{
    NSLog(@"----MJShareViewController----");
}

@end
