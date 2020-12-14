#import <UIKit/UIKit.h>
#import <Cordova/CDV.h>
#import <Cordova/CDVPlugin.h>
#import "AppDelegate.h"
#import "FingerViewController.h"

@interface  EntelFingerPlugin : CDVPlugin

+ (EntelFingerPlugin *)entelFingerPlugin;

- (void)getwsq:(CDVInvokedUrlCommand*)command;
- (void)sendResponseFinger:(NSString *)responseText callbackId:(NSString *)callbackId;
- (void)sendResponseFingerDict:(NSDictionary *)responseDict callbackId:(NSString *)callbackId;

@property (copy, nonatomic) NSString *responseCallbackId;

@end