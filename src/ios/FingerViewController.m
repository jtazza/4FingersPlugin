

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
    VeridiumLicenseStatus* sdkStatus = [VeridiumSDK setup:@"wsPU+4kxbhKdCREQ3aT7pLyzN56ttrmn0MWhutM7Usva6wwlfzzuxgm85v/BRH/LQTEXBIu4OOPXo4xAfkHOCHsiZGV2aWNlRmluZ2VycHJpbnQiOiJFYTNkY2MrVkVsakJhL1JWb3E0NWI1U2x4ejdndC9FTHlvVXBvSjBPOWk0PSIsImxpY2Vuc2UiOiJ0a2hHWThOMkZTamJFRlZQOWhVdlU5NTJPNzJCNUhjYnc1VDZZRUh1ekc3eWZiVTdvR204ZndNdnl0ZjNrMjgvbmxBOEFpelJXZ2ZiSVVDVGF0T1JBM3NpZEhsd1pTSTZJbE5FU3lJc0ltNWhiV1VpT2lKVFJFc2lMQ0pzWVhOMFRXOWthV1pwWldRaU9qRTFPVFExTURFME9EQXNJbU52YlhCaGJubE9ZVzFsSWpvaVJXNTBaV3dnZG1saElFbHVjMjlzZFhScGIyNXpJaXdpWTI5dWRHRmpkRWx1Wm04aU9pSkZiblJsYkNCQmRYUnZVMkZzWlNCUWNtOXFaV04wSUMwZ05FWkZJQzBnZGpRZ0lDMGdZMjl0TG1WdWRHVnNMbTF2ZG1sc0lpd2lZMjl1ZEdGamRFVnRZV2xzSWpvaWJXbG5kV1ZzTG1obGNtNWhibVJsZWtCcGJuTnZiSFYwYVc5dWN5NXdaU0lzSW5OMVlreHBZMlZ1YzJsdVoxQjFZbXhwWTB0bGVTSTZJbk54VldwSGIxRnJNWEo0ZGpReGQzRmpUM3BUZEVSdmIwNDBSUzlqYTBwU01EUkdTVTl4ZG1ORlVVMDlJaXdpYzNSaGNuUkVZWFJsSWpveE5UZzNNREE1TmpBd0xDSmxlSEJwY21GMGFXOXVSR0YwWlNJNk1UWXlNRGsyTkRnd01Dd2laM0poWTJWRmJtUkVZWFJsSWpveE5qSXhNVE0zTmpBd0xDSjFjMmx1WjFOQlRVeFViMnRsYmlJNlptRnNjMlVzSW5WemFXNW5SbkpsWlZKQlJFbFZVeUk2Wm1Gc2MyVXNJblZ6YVc1blFXTjBhWFpsUkdseVpXTjBiM0o1SWpwbVlXeHpaU3dpWW1sdmJHbGlSbUZqWlVWNGNHOXlkRVZ1WVdKc1pXUWlPbVpoYkhObExDSnlkVzUwYVcxbFJXNTJhWEp2Ym0xbGJuUWlPbnNpYzJWeWRtVnlJanBtWVd4elpTd2laR1YyYVdObFZHbGxaQ0k2Wm1Gc2MyVjlMQ0psYm1admNtTmxJanA3SW5CaFkydGhaMlZPWVcxbGN5STZXeUpqYjIwdVpXNTBaV3d1Ylc5MmFXd2lYU3dpYzJWeWRtVnlRMlZ5ZEVoaGMyaGxjeUk2VzExOWZRPT0ifQ=="];


    // Check the result of the license system
    if(!sdkStatus.initSuccess){
        [VeridiumUtils alert: @"Your SDK license is invalid" title:@"Licence"];
        return ;
    }
    
    if(sdkStatus.isInGracePeriod) {
        [VeridiumUtils alert: @"Your SDK license will expire soon. Please contact your administrator for a new license." title:@"Licence"];
    }
    
    // Fill in your 4F TouchlessID license key here.
    VeridiumLicenseStatus* touchlessIDStatus = [VeridiumSDK.sharedSDK setupTouchlessID:@"t1Sh/uKCkOxrym5hFGhZB1m6GL2amRuPmigOL/gr0HnT7S5gf8xoM6sF5Bjj7sYpyaDV4UXkH9sKxmvO7CW9AHsiZGV2aWNlRmluZ2VycHJpbnQiOiJFYTNkY2MrVkVsakJhL1JWb3E0NWI1U2x4ejdndC9FTHlvVXBvSjBPOWk0PSIsImxpY2Vuc2UiOiJoaUZKNElvMlhWSEhzcWcydnhmOVJ5WnkzVkNhdlBTbWhhbWwwcVltV3F2ai9aTEFKeXN5VjVBTC9DbXd0WkdZT0lGOVhwOWJvUHFQUzhudWR1c3VEWHNpZEhsd1pTSTZJa0pKVDB4SlFsTWlMQ0p1WVcxbElqb2lORVlpTENKc1lYTjBUVzlrYVdacFpXUWlPakUxT1RRMU1ERTBPREEwTmpZc0ltTnZiWEJoYm5sT1lXMWxJam9pUlc1MFpXd2dkbWxoSUVsdWMyOXNkWFJwYjI1eklpd2lZMjl1ZEdGamRFbHVabThpT2lKRmJuUmxiQ0JCZFhSdlUyRnNaU0JRY205cVpXTjBJQzBnTkVaRklDMGdkalFnSUMwZ1kyOXRMbVZ1ZEdWc0xtMXZkbWxzSWl3aVkyOXVkR0ZqZEVWdFlXbHNJam9pYldsbmRXVnNMbWhsY201aGJtUmxla0JwYm5OdmJIVjBhVzl1Y3k1d1pTSXNJbk4xWWt4cFkyVnVjMmx1WjFCMVlteHBZMHRsZVNJNkluTnhWV3BIYjFGck1YSjRkalF4ZDNGalQzcFRkRVJ2YjA0MFJTOWphMHBTTURSR1NVOXhkbU5GVVUwOUlpd2ljM1JoY25SRVlYUmxJam94TlRnM01EQTVOakF3TURBd0xDSmxlSEJwY21GMGFXOXVSR0YwWlNJNk1UWXlNRGsyTkRnd01EQXdNQ3dpWjNKaFkyVkZibVJFWVhSbElqb3hOakl4TVRNM05qQXdNREF3TENKMWMybHVaMU5CVFV4VWIydGxiaUk2Wm1Gc2MyVXNJblZ6YVc1blJuSmxaVkpCUkVsVlV5STZabUZzYzJVc0luVnphVzVuUVdOMGFYWmxSR2x5WldOMGIzSjVJanBtWVd4elpTd2lZbWx2YkdsaVJtRmpaVVY0Y0c5eWRFVnVZV0pzWldRaU9tWmhiSE5sTENKeWRXNTBhVzFsUlc1MmFYSnZibTFsYm5RaU9uc2ljMlZ5ZG1WeUlqcG1ZV3h6WlN3aVpHVjJhV05sVkdsbFpDSTZabUZzYzJWOUxDSm1aV0YwZFhKbGN5STZleUppWVhObElqcDBjblZsTENKemRHVnlaVzlNYVhabGJtVnpjeUk2ZEhKMVpTd2laWGh3YjNKMElqcDBjblZsZlN3aVpXNW1iM0pqWldSUWNtVm1aWEpsYm1ObGN5STZleUp0WVc1a1lYUnZjbmxNYVhabGJtVnpjeUk2Wm1Gc2MyVjlMQ0oyWlhKemFXOXVJam9pTkM0cUluMD0ifQ=="];

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