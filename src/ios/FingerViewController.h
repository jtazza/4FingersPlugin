#import <UIKit/UIKit.h>
#import "EntelFingerPlugin.h"
@import VeridiumCore;
@import Veridium4FBiometrics;
@import VeridiumDefault4FUI; 

@interface FingerViewController : UIViewController

+ (instancetype)sharedHelper:(NSString *)callbackid;
- (void)onExportFingerWithLeftCode:(int)leftCode andRightCode:(int)rightCode;
- (void)startConfig;

@property (strong, nonatomic) NSString *callbackId;
@property int leftCodeFinger;
@property int rightCodeFinger;
@end