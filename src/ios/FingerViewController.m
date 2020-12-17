

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
    VeridiumLicenseStatus* sdkStatus = [VeridiumSDK setup:@"6NmAGmevRQ7CPsDZSFd8wZp580cRoAFW97oz8SMtF4NFZxgwLY3QwcUEmNldBBhjATp5LMz76C+IWWnu+cBuBnsiZGV2aWNlRmluZ2VycHJpbnQiOiJFYTNkY2MrVkVsakJhL1JWb3E0NWI1U2x4ejdndC9FTHlvVXBvSjBPOWk0PSIsImxpY2Vuc2UiOiJvMEo0V2R3ZUl4alpwak9UT1RIakN3ZVpLTlhMellVVkladGt2VXdMbTE5YmRpVGdqNG5WY2c4d0VyM3A3ZE12VnVvQVVQN1dOUmdyRXE4alA5eElEWHNpZEhsd1pTSTZJbE5FU3lJc0ltNWhiV1VpT2lKVFJFc2lMQ0pzWVhOMFRXOWthV1pwWldRaU9qRTFPVFExTURFeU5UQXNJbU52YlhCaGJubE9ZVzFsSWpvaVJXNTBaV3dnZG1saElFbHVjMjlzZFhScGIyNXpJaXdpWTI5dWRHRmpkRWx1Wm04aU9pSkZiblJsYkNCQmRYUnZVMkZzWlNCUWNtOXFaV04wSUMwZ05FWkZJQzBnZGpVZ1kyOXRMbTkxZEhONWMzUmxiWE5sYm5SbGNuQnlhWE5sTG1WdWRHVnNMbEJGVFdsRmJuUmxiRnh1WVc1a0lHTnZiUzVsYm5SbGJDNXRiM1pwYkNJc0ltTnZiblJoWTNSRmJXRnBiQ0k2SW0xcFozVmxiQzVvWlhKdVlXNWtaWHBBYVc1emIyeDFkR2x2Ym5NdWNHVWlMQ0p6ZFdKTWFXTmxibk5wYm1kUWRXSnNhV05MWlhraU9pSXlha0p5ZVVWTmVVZGplV2cxVmtkaU5YRndPR3QyT1ROVWJubEVjVGx3WjBjM1lqWk9WVmRFTmxCelBTSXNJbk4wWVhKMFJHRjBaU0k2TVRVNE16Y3lOalF3TUN3aVpYaHdhWEpoZEdsdmJrUmhkR1VpT2pFMk1qQTVOalE0TURBc0ltZHlZV05sUlc1a1JHRjBaU0k2TVRZeU1URXpOell3TUN3aWRYTnBibWRUUVUxTVZHOXJaVzRpT21aaGJITmxMQ0oxYzJsdVowWnlaV1ZTUVVSSlZWTWlPbVpoYkhObExDSjFjMmx1WjBGamRHbDJaVVJwY21WamRHOXllU0k2Wm1Gc2MyVXNJbUpwYjJ4cFlrWmhZMlZGZUhCdmNuUkZibUZpYkdWa0lqcG1ZV3h6WlN3aWNuVnVkR2x0WlVWdWRtbHliMjV0Wlc1MElqcDdJbk5sY25abGNpSTZabUZzYzJVc0ltUmxkbWxqWlZScFpXUWlPbVpoYkhObGZTd2laVzVtYjNKalpTSTZleUp3WVdOcllXZGxUbUZ0WlhNaU9sc2lZMjl0TG05MWRITjVjM1JsYlhObGJuUmxjbkJ5YVhObExtVnVkR1ZzTGxCRlRXbEZiblJsYkNJc0ltTnZiUzVsYm5SbGJDNXRiM1pwYkNKZExDSnpaWEoyWlhKRFpYSjBTR0Z6YUdWeklqcGJYWDE5In0="];


    // Check the result of the license system
    if(!sdkStatus.initSuccess){
        [VeridiumUtils alert: @"Your SDK license is invalid" title:@"Licence"];
        return ;
    }
    
    if(sdkStatus.isInGracePeriod) {
        [VeridiumUtils alert: @"Your SDK license will expire soon. Please contact your administrator for a new license." title:@"Licence"];
    }
    
    // Fill in your 4F TouchlessID license key here.
    VeridiumLicenseStatus* touchlessIDStatus = [VeridiumSDK.sharedSDK setupTouchlessID:@"LM47FCQVDRvU1LxACM6KEIj3U4/sz1XxMc0jHV0mXdsfIDC6FU6uCHkK5C1/CEcUvqpYk2TnWmnza7kzoPNzC3siZGV2aWNlRmluZ2VycHJpbnQiOiJFYTNkY2MrVkVsakJhL1JWb3E0NWI1U2x4ejdndC9FTHlvVXBvSjBPOWk0PSIsImxpY2Vuc2UiOiJtMUVFN2ZIRVBvMm5mQnJpeGlKeWNIZnVMTVlhMU16YWs5blBzRDRQZGJuMTBYdFJ0b3M4Rml5Z0VEODJFZkM4TmM0ZXdPZTVqd01UV3M2alY0V1NESHNpZEhsd1pTSTZJa0pKVDB4SlFsTWlMQ0p1WVcxbElqb2lORVlpTENKc1lYTjBUVzlrYVdacFpXUWlPakUxT1RRMU1ERXlOVEEzTmpNc0ltTnZiWEJoYm5sT1lXMWxJam9pUlc1MFpXd2dkbWxoSUVsdWMyOXNkWFJwYjI1eklpd2lZMjl1ZEdGamRFbHVabThpT2lKRmJuUmxiQ0JCZFhSdlUyRnNaU0JRY205cVpXTjBJQzBnTkVaRklDMGdkalVnWTI5dExtOTFkSE41YzNSbGJYTmxiblJsY25CeWFYTmxMbVZ1ZEdWc0xsQkZUV2xGYm5SbGJGeHVZVzVrSUdOdmJTNWxiblJsYkM1dGIzWnBiQ0lzSW1OdmJuUmhZM1JGYldGcGJDSTZJbTFwWjNWbGJDNW9aWEp1WVc1a1pYcEFhVzV6YjJ4MWRHbHZibk11Y0dVaUxDSnpkV0pNYVdObGJuTnBibWRRZFdKc2FXTkxaWGtpT2lJeWFrSnllVVZOZVVkamVXZzFWa2RpTlhGd09HdDJPVE5VYm5sRWNUbHdaMGMzWWpaT1ZWZEVObEJ6UFNJc0luTjBZWEowUkdGMFpTSTZNVFU0TXpjeU5qUXdNREF3TUN3aVpYaHdhWEpoZEdsdmJrUmhkR1VpT2pFMk1qQTVOalE0TURBd01EQXNJbWR5WVdObFJXNWtSR0YwWlNJNk1UWXlNVEV6TnpZd01EQXdNQ3dpZFhOcGJtZFRRVTFNVkc5clpXNGlPbVpoYkhObExDSjFjMmx1WjBaeVpXVlNRVVJKVlZNaU9tWmhiSE5sTENKMWMybHVaMEZqZEdsMlpVUnBjbVZqZEc5eWVTSTZabUZzYzJVc0ltSnBiMnhwWWtaaFkyVkZlSEJ2Y25SRmJtRmliR1ZrSWpwbVlXeHpaU3dpY25WdWRHbHRaVVZ1ZG1seWIyNXRaVzUwSWpwN0luTmxjblpsY2lJNlptRnNjMlVzSW1SbGRtbGpaVlJwWldRaU9tWmhiSE5sZlN3aVptVmhkSFZ5WlhNaU9uc2lZbUZ6WlNJNmRISjFaU3dpYzNSbGNtVnZUR2wyWlc1bGMzTWlPblJ5ZFdVc0ltVjRjRzl5ZENJNmRISjFaWDBzSW1WdVptOXlZMlZrVUhKbFptVnlaVzVqWlhNaU9uc2liV0Z1WkdGMGIzSjVUR2wyWlc1bGMzTWlPbVpoYkhObGZTd2lkbVZ5YzJsdmJpSTZJalV1S2lKOSJ9"];

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