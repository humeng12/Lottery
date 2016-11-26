//
//  HMHtmlViewController.m
//  网易彩票
//
//  Created by 胡猛 on 16/10/28.
//  Copyright © 2016年 HuMeng. All rights reserved.
//

#import "HMHtmlViewController.h"
#import "HMHtml.h"

@interface HMHtmlViewController ()<UIWebViewDelegate>

@end

@implementation HMHtmlViewController

-(void)loadView
{
    self.view = [[UIWebView alloc] init];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = self.html.title;
    
    UIWebView *webView= (UIWebView *)self.view;
    webView.delegate = self;
    
    NSURL *url = [[NSBundle mainBundle] URLForResource:self.html.html withExtension:nil];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    [webView loadRequest:request];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"关闭" style:UIBarButtonItemStylePlain target:self action:@selector(close)];
}

-(void)close{
    [self dismissViewControllerAnimated:YES completion:nil];
}


-(void)webViewDidFinishLoad:(UIWebView *)webView
{
    NSString *js = [NSString stringWithFormat:@"window.location.href = '#%@';", self.html.ID];
    [webView stringByEvaluatingJavaScriptFromString:js];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
