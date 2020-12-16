

#import "FingerViewController.h"

@interface FingerViewController () {
    int saveCount;
}


@end

@implementation FingerViewController
@synthesize callbackId = _callbackId;

VeridiumExportService* exportService;
VeridiumBiometrics4FConfig* exportConfig;
VeridiumTemplateFormat exportFormat = FORMAT_JSON;

VeridiumThumbMode thumbMode = ThumbNone;
static int const kThumbRightCode = 1;
static int const kThumbLeftCode = 6;

static int const kLeftHand = 2;
static int const kRightHand = 3;

+ (instancetype)sharedHelper:(NSString *)callbackid
{
    
    static FingerViewController *sharedClass = nil;
    
    static dispatch_once_t onceToken;
    
    dispatch_once(&onceToken, ^{
        sharedClass = [[self alloc] init];
        sharedClass.callbackId = callbackid;
    });
    
    return sharedClass;
}

-(void)startConfig{
    // Fill in your license key here.
    VeridiumLicenseStatus* sdkStatus = [VeridiumSDK setup:@"E9IHd1R/H6afHI3mq5cMGkpp9WdF+cL7+v3yiBA+hJTWbllnhKb6/BzZ1CoPOhEfxR6eJ05GYpjdiZx+35zvA3siZGV2aWNlRmluZ2VycHJpbnQiOiJFYTNkY2MrVkVsakJhL1JWb3E0NWI1U2x4ejdndC9FTHlvVXBvSjBPOWk0PSIsImxpY2Vuc2UiOiJnK0ZiUitRUllzSWgySi9uTEVyQnp2aEZqT3Y5dU1Cell4aG9GYkRYTit2eUdLd1pHam4vcEJHZXJVMU05ZFBBUzl1K1pqU0w2dHp6bW44Q3E3QTdEWHNpZEhsd1pTSTZJbE5FU3lJc0ltNWhiV1VpT2lKVFJFc2lMQ0pzWVhOMFRXOWthV1pwWldRaU9qRTJNRGd3TlRjeE16WXNJbU52YlhCaGJubE9ZVzFsSWpvaVJXNTBaV3dnZG1saElFbHVjMjlzZFhScGIyNXpJaXdpWTI5dWRHRmpkRWx1Wm04aU9pSkZiblJsYkNCQmRYUnZVMkZzWlNCUWNtOXFaV04wSUMwZ05FWkZJQzBnZGpRbU5TQmpiMjB1Wlc1MFpXd3ViVzkyYVd3c0lHTnZiUzVsYm5SbGJDNXRiM1pwYkM1aGRYUnZZV04wYVhaaFkybHZiaUlzSW1OdmJuUmhZM1JGYldGcGJDSTZJbTFwWjNWbGJDNW9aWEp1WVc1a1pYcEFhVzV6YjJ4MWRHbHZibk11Y0dVaUxDSnpkV0pNYVdObGJuTnBibWRRZFdKc2FXTkxaWGtpT2lKNk16ZEZjM2gzUkVKMVlVMDVjWEJSUTJsS1NFMVBlbTlaZUZFck5pdFROVVZRVFdndlpsSXZhalZuUFNJc0luTjBZWEowUkdGMFpTSTZNVFU0TXpjeU5qUXdNQ3dpWlhod2FYSmhkR2x2YmtSaGRHVWlPakUyTWpBNU5qUTRNREFzSW1keVlXTmxSVzVrUkdGMFpTSTZNVFl5TVRFek56WXdNQ3dpZFhOcGJtZFRRVTFNVkc5clpXNGlPbVpoYkhObExDSjFjMmx1WjBaeVpXVlNRVVJKVlZNaU9tWmhiSE5sTENKMWMybHVaMEZqZEdsMlpVUnBjbVZqZEc5eWVTSTZabUZzYzJVc0ltSnBiMnhwWWtaaFkyVkZlSEJ2Y25SRmJtRmliR1ZrSWpwbVlXeHpaU3dpY25WdWRHbHRaVVZ1ZG1seWIyNXRaVzUwSWpwN0luTmxjblpsY2lJNlptRnNjMlVzSW1SbGRtbGpaVlJwWldRaU9tWmhiSE5sZlN3aVpXNW1iM0pqWlNJNmV5SndZV05yWVdkbFRtRnRaWE1pT2xzaVkyOXRMbVZ1ZEdWc0xtMXZkbWxzTG1GMWRHOWhZM1JwZG1GamFXOXVJaXdpWTI5dExtVnVkR1ZzTG0xdmRtbHNJbDBzSW5ObGNuWmxja05sY25SSVlYTm9aWE1pT2x0ZGZYMD0ifQ=="];


    // Check the result of the license system
    if(!sdkStatus.initSuccess){
        [VeridiumUtils alert: @"Your SDK license is invalid" title:@"Licence"];
        return ;
    }
    
    if(sdkStatus.isInGracePeriod) {
        [VeridiumUtils alert: @"Your SDK license will expire soon. Please contact your administrator for a new license." title:@"Licence"];
    }
    
    // Fill in your 4F TouchlessID license key here.
    VeridiumLicenseStatus* touchlessIDStatus = [VeridiumSDK.sharedSDK setupTouchlessID:@"kZMvQP26P5AarUh3ZO0al+FySMfBqfLnsaEP5ZRG83oqx9MKYEOSmQKoH9/fEu66Kqwfh7TAfQiViu/8rOVHA3siZGV2aWNlRmluZ2VycHJpbnQiOiJFYTNkY2MrVkVsakJhL1JWb3E0NWI1U2x4ejdndC9FTHlvVXBvSjBPOWk0PSIsImxpY2Vuc2UiOiJZd2YvZDNkcmVPeEN0Q285VDdJczZPaUZpayt0TTNOcW93VHVLRjBWNDhBL3ljUXZVTW1ZdG02TVpFNWd0Zk1wMThNNmJ3Q2xFL29BdC9aZ0RTdEVEbnNpZEhsd1pTSTZJa0pKVDB4SlFsTWlMQ0p1WVcxbElqb2lORVlpTENKc1lYTjBUVzlrYVdacFpXUWlPakUyTURnd05UY3hNell6TnpRc0ltTnZiWEJoYm5sT1lXMWxJam9pUlc1MFpXd2dkbWxoSUVsdWMyOXNkWFJwYjI1eklpd2lZMjl1ZEdGamRFbHVabThpT2lKRmJuUmxiQ0JCZFhSdlUyRnNaU0JRY205cVpXTjBJQzBnTkVaRklDMGdkalFtTlNCamIyMHVaVzUwWld3dWJXOTJhV3dzSUdOdmJTNWxiblJsYkM1dGIzWnBiQzVoZFhSdllXTjBhWFpoWTJsdmJpSXNJbU52Ym5SaFkzUkZiV0ZwYkNJNkltMXBaM1ZsYkM1b1pYSnVZVzVrWlhwQWFXNXpiMngxZEdsdmJuTXVjR1VpTENKemRXSk1hV05sYm5OcGJtZFFkV0pzYVdOTFpYa2lPaUo2TXpkRmMzaDNSRUoxWVUwNWNYQlJRMmxLU0UxUGVtOVplRkVyTml0VE5VVlFUV2d2WmxJdmFqVm5QU0lzSW5OMFlYSjBSR0YwWlNJNk1UVTRNemN5TmpRd01EQXdNQ3dpWlhod2FYSmhkR2x2YmtSaGRHVWlPakUyTWpBNU5qUTRNREF3TURBc0ltZHlZV05sUlc1a1JHRjBaU0k2TVRZeU1URXpOell3TURBd01Dd2lkWE5wYm1kVFFVMU1WRzlyWlc0aU9tWmhiSE5sTENKMWMybHVaMFp5WldWU1FVUkpWVk1pT21aaGJITmxMQ0oxYzJsdVowRmpkR2wyWlVScGNtVmpkRzl5ZVNJNlptRnNjMlVzSW1KcGIyeHBZa1poWTJWRmVIQnZjblJGYm1GaWJHVmtJanBtWVd4elpTd2ljblZ1ZEdsdFpVVnVkbWx5YjI1dFpXNTBJanA3SW5ObGNuWmxjaUk2Wm1Gc2MyVXNJbVJsZG1salpWUnBaV1FpT21aaGJITmxmU3dpWm1WaGRIVnlaWE1pT25zaVltRnpaU0k2ZEhKMVpTd2ljM1JsY21WdlRHbDJaVzVsYzNNaU9uUnlkV1VzSW1WNGNHOXlkQ0k2ZEhKMVpYMHNJbVZ1Wm05eVkyVmtVSEpsWm1WeVpXNWpaWE1pT25zaWJXRnVaR0YwYjNKNVRHbDJaVzVsYzNNaU9tWmhiSE5sZlN3aWRtVnljMmx2YmlJNklpb3VLaUo5In0="];

    if(!touchlessIDStatus.initSuccess){
        [VeridiumUtils alert: @"Your TouchlessID license is invalid" title:@"Licence"];
        return ;
    }
    
    if(touchlessIDStatus.isInGracePeriod) {
        [VeridiumUtils alert: @"Your TouchlessID license will expire soon. Please contact your administrator for a new license." title:@"Licence"];
    }
  
  
    [VeridiumSDK.sharedSDK registerDefault4FExporter]; // Alternatively use [VeridiumSDK.sharedSDK registerCustom4FExporter]; if working from a custom ui.
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    exportService =  [[VeridiumExportService alloc] init];
    exportConfig = [VeridiumBiometrics4FConfig new];
    
    self->saveCount = 0;
}

- (void)didReceiveMemoryWarning
{
  [super didReceiveMemoryWarning];
  // Dispose of any resources that can be recreated.
}

- (void)showThumbScanWithHand:(int)handCode{
    exportConfig.individualThumb = false;
    exportConfig.individualIndex = true;
    exportConfig.individualMiddle = true;
    exportConfig.individualRing = true;
    exportConfig.individualLittle = true;
    exportConfig.individualCapture = true;
    exportConfig.chosenHand = handCode;
}

- (void)onExportFingerWithLeftCode:(int)leftCode andRightCode:(int)rightCode {
    
    [self startConfig];
    
    self.leftCodeFinger = leftCode;
    self.rightCodeFinger = rightCode;
    
    //Initialize class
    exportService =  [[VeridiumExportService alloc] init];
    exportConfig = [VeridiumBiometrics4FConfig new];
    
    if (rightCode == kThumbRightCode) {
        [self showThumbScanWithHand:kRightHand];
        [self commonExport:NO withTargetIndex:NO andTargetLittle:NO];
    }else if (leftCode == kThumbLeftCode){
        [self showThumbScanWithHand:kLeftHand];
        [self commonExport:NO withTargetIndex:NO andTargetLittle:NO];
    }else{
        exportConfig.chosenHand = Veridium4FAnalyzeHandDefaultRight;
        exportConfig.individualCapture = false;
        [self commonExport:NO withTargetIndex:YES andTargetLittle:NO];
    }
}



-(void)commonExport:(bool)record8F withTargetIndex:(bool)target_index andTargetLittle:(bool)target_little {
  NSLog(@" format : %lu record8F %s", (unsigned long)exportFormat, record8F ? "true":"false");
    
    thumbMode = ThumbNone;
    exportConfig.record8F = record8F;
    exportConfig.exportFormat = FORMAT_JSON;
    exportConfig.targetIndexFinger = target_index;
    exportConfig.targetLittleFinger = target_index && target_little;
    exportConfig.wsq_compression_ratio = COMPRESS_10to1;
    exportConfig.pack_debug_data = NO;
    exportConfig.calculate_nfiq = NO;
    exportConfig.background_remove = YES;
    exportConfig.twoShotLiveness = NO;
    exportConfig.extra_scaled_image = YES;
    exportConfig.fixed_print_width = 0;
    exportConfig.fixed_print_height = 0;
    exportConfig.pack_audit_image = YES;
    exportConfig.reliability_mask = NO;
//    exportConfig.padding_width = 500;
//    exportConfig.padding_height = 500;
    exportConfig.keepResource = NO;
    exportConfig.captureThumb = ThumbNone;
    exportConfig.nist_type = Nist_type_T14_9;
    
    [VeridiumBiometrics4FService exportTemplate:exportConfig
                         onSuccess:^(VeridiumBiometricVector * _Nonnull biometricVector) {
                             // Generate a file path in which to save the fingerprints.
//                             NSString* basefilename = @"fingerprints_";
                             
                             NSDictionary * arr = [NSJSONSerialization JSONObjectWithData:biometricVector.biometricData options:NSJSONReadingMutableContainers error:nil];
                             
                             NSArray* fingerPrints = [[arr objectForKey:@"SCALE085"] objectForKey:@"Fingerprints"];
                             
                             int bestFinger = 0;
                             for (NSDictionary* finger in fingerPrints) {
                                 int positionCode = [[finger objectForKey:@"FingerPositionCode"] intValue];
                                 if (positionCode == self.leftCodeFinger || positionCode == self.rightCodeFinger) {
                                     break;
                                 }
                                 bestFinger++;
                             }
                             
                             int fingerPositionCode = [[[fingerPrints objectAtIndex:bestFinger] objectForKey:@"FingerPositionCode"] intValue];
                             NSString * wsq = [[[fingerPrints objectAtIndex:bestFinger] objectForKey:@"FingerImpressionImage"] objectForKey:@"BinaryBase64ObjectWSQ"];
                             
                             NSString * hand;
                             if (fingerPositionCode == self.leftCodeFinger) {
                                 hand = @"LEFT";
                             }else if (fingerPositionCode == self.rightCodeFinger){
                                 hand = @"RIGHT";
                             }
                             
                            NSMutableDictionary * dict = [NSMutableDictionary new];
                            [dict setObject:wsq forKey:@"wsq"];
                            [dict setObject:hand forKey:@"hand"];
                            NSLog(@"Successful export");

                            [EntelFingerPlugin.entelFingerPlugin sendResponseFingerDict:dict callbackId:self.callbackId];
                        } onFail:^(NSString * _Nullable message) {
                            [EntelFingerPlugin.entelFingerPlugin sendResponseFinger:@"FAIL" callbackId:self.callbackId];  
                        } onCancel:^{
                            [EntelFingerPlugin.entelFingerPlugin sendResponseFinger:@"CANCEL" callbackId:self.callbackId];  
                        } onError:^(NSString * _Nullable message) {
                            [EntelFingerPlugin.entelFingerPlugin sendResponseFinger:@"ERROR" callbackId:self.callbackId];  
                        }];
}



@end