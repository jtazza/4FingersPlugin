#import "EntelFingerPlugin.h"

@implementation EntelFingerPlugin

@synthesize responseCallbackId = _responseCallbackId;

static NSString * const kLeftFingerCode = @"leftFingerCode";
static NSString * const kRightFingerCode = @"righFingerCode";

EntelFingerPlugin* entelFingerPlugin;

+ (EntelFingerPlugin *) entelFingerPlugin {
    return entelFingerPlugin;
}

- (void)pluginInitialize {
    NSLog(@"EntelFingerPlugin - Starting plugin");
    entelFingerPlugin = self;
}

- (void)getwsq:(CDVInvokedUrlCommand*)command{
    NSDictionary* args = [command.arguments objectAtIndex:0];
    
    int leftFingerCode = [[args objectForKey:kLeftFingerCode] intValue];
    int rightFingerCode = [[args objectForKey:kRightFingerCode] intValue];
    
    self.responseCallbackId = command.callbackId;
    if (self.responseCallbackId != nil) {
        //Logic FingerViewController
        FingerViewController *fvc = [FingerViewController sharedHelper:self.responseCallbackId];
        fvc.leftCodeFinger = leftFingerCode;
        fvc.rightCodeFinger = rightFingerCode;
        [fvc onExportFingerWithLeftCode:leftFingerCode andRightCode:rightFingerCode];
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_NO_RESULT];
        [pluginResult setKeepCallback:[NSNumber numberWithBool:YES]];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];

    } else {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)sendResponseFinger:(NSString *)responseText callbackId:(NSString *)callbackId{
    if (callbackId != nil) {
        NSLog(@"In response = %@",self.responseCallbackId);
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:responseText];
        [pluginResult setKeepCallbackAsBool:NO];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.responseCallbackId];
    }
}

- (void)sendResponseFingerDict:(NSDictionary *)responseDict callbackId:(NSString *)callbackId{
    if (callbackId != nil) {
        NSLog(@"In response = %@",self.responseCallbackId);
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:responseDict];
        [pluginResult setKeepCallbackAsBool:NO];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.responseCallbackId];
    }
}

@end