//
//  VeridiumBiometrics4FExporter.h
//  Veridium4FBiometrics
//
//  Created by TingWeiHsu on 07/12/2016.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import "VeridiumBiometrics4FCommon.h"

#import "VeridiumBiometrics4FConfig.h" // Import to get WSQCompressionRatio definition

/*!
 Data class for holding the 4F authentication config params
 */
@interface Veridium4FExportConfig : NSObject<VeridiumBiometricExportConfig>


@property (nonatomic, nonnull) NSString* engineName;

/*!
 Whether to use the left or right hand (defaults to Veridium4FExportHandDefaultLeft)
 */
@property Veridium4FAnalyzeHand exportHand;

/*!
 The allowed number of retries in case the authentication fails (defaults to 0)
 */
@property NSInteger numberOfRetries;

/*!
 Overall timeout in seconds (defaults to 30 seconds)
 */
@property float timeoutSeconds;

/*!
 Whether to start the process automatically or ask UI to wait for the user's input
 (defaults to TRUE)
 */
@property BOOL autostart;



/*!
 Whether to use capture the picture using Torch (defaults to FALSE)
 */
@property BOOL useTorchForPictureCapture;

@property VeridiumTemplateFormat exportFormat;

@property BOOL record8F;

@property BOOL keepResource;


@property BOOL pack_debug_data;

@property BOOL pack_wsq;

@property WSQCompressRatio wsq_compression_ratio;

@property BOOL pack_raw;

@property BOOL pack_png;

@property BOOL calculate_nfiq;
@property BOOL background_remove;
@property BOOL extra_scaled_image;
@property int fixed_print_width;
@property int fixed_print_height;
@property BOOL pack_audit_image;
@property BOOL reliability_mask;
@property int nist_type; // choose to output either Type-14 records or type-4 for NIST.

@property BOOL twoShotLiveness;
@property BOOL passiveLiveness;
@property BOOL livenessIsHorizontal;
@property BOOL laxLiveness;

@property int padding_width;
@property int padding_height;

@property BOOL targetIndexFinger;
@property BOOL targetLittleFinger;
@property int captureThumb; //TODO: should be an enum ie. VeridiumThumbMode

@property BOOL individualThumb;
@property BOOL individualIndex;
@property BOOL individualMiddle;
@property BOOL individualRing;
@property BOOL individualLittle;

@property BOOL individualCapture;


@property (nonnull) NSMutableDictionary *formatConfig;

-(BOOL) supports4F;
-(BOOL) supports8F;
-(NSString* _Nonnull) formatName;
-(NSString* _Nonnull) formatExtension;

/*!
 The UI
 */
@property (nullable) id<Veridium4FExporterUIDelegate> uiDelegate;



@end

/*!
 The 4F biometric exporter.
 */
@interface VeridiumBiometrics4FExporter : VeridiumBiometrics4FCommon <VeridiumBioExporter> //is it necessary to add method in the core?




/*!
 Configure the exporter
 
 @param config the Veridium4FExportConfig instance
 
 @return self (useful for call chaining)
 */
-(instancetype _Nonnull)configure:(Veridium4FExportConfig * _Nonnull)config;

/*!
Configure export setting of the exporter

@param config the Veridium4FExportConfig instance

@return self (useful for call chaining)
*/
-(instancetype _Nonnull)configureExport:(Veridium4FExportConfig * _Nonnull)config;

/*!
 Check the export setting is valid
 
 @param config the Veridium4FExportConfig instance
 
 @return BOOL  is valid for not
 */
//-(BOOL) verifyConfigure:(Veridium4FExportConfig* _Nonnull)config;

/*!
 The configured Authenticate4FBioEngineConfig instance (can be used to alter the current configuration without setting a new one)
 */
@property(readonly, nonnull) Veridium4FExportConfig* config;

//-(void) doSelectPathAndConfig:(NSString*) tr;


/*!
Check weather has left or right hand record for enroller
 */
-(BOOL) recordHasLeft;

-(BOOL) recordHasRight;

@end


