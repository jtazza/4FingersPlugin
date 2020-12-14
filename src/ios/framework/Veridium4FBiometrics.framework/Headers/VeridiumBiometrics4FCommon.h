//
//  VeridiumBiometrics4FCommon.h
//  Veridium4FBiometrics
//
//  Created by razvan on 11/25/15.
//  Copyright © 2015 Veridium. All rights reserved.
//

#import <VeridiumCore/VeridiumCore.h>
#import "Constants.h"


/*!
 Subprotocol of BiometricsUIDelegate which is the base of 4F UI protocols.
 
 Contains the methods & props common to enrollment, authentication, and export UI delegates */
@protocol Veridium4FUIDelegate <VeridiumBiometricsUIDelegate>

/*!
 Ask UI to provide a view for displaying camera preview
 
 @return an initialized UIView
 */
-(UIView*) fourFPreviewView;

-(GuideDesign) handGuideType;


/*!
 Ask UI to handle the event of a photo beeing captured (by displaying it) and on the same time get from the UI the size of the view that displays the image.
 
 @param photoImage the capture photo UIImage
  */
-(void) handlePhotoCaptureUpdate:(UIImage*) photoImage;

/*!
  Ask UI to handle finger finding.
 
 The most basic implementation should display a message like 'Searching for hand'
 */
-(void) handleSearchingForHand;

/*!
Ask UI to handle the ROI info & assessment for a found hand during finger fingind phase

 In this case the UI should use the information in the roisInfo param to display the finger ROIs and the assessment message
 
   @param fingersInfo ROIsInfo instance that the UI should use to display the found fingers feedback during finger finding
 */
-(void) handleHandFoundForVideo:(Veridium4FFingersInfo*) fingersInfo;


-(void)handleHandThumbForVideo: (BOOL) isThumbFound forROI:(CGRect)rect forIndividualROI:(CGRect)rectIndividual isThumb:(BOOL) isThumb;
-(void)handleHandThumbForPhoto:(CGRect)rect;

/*!
 Ask UI to handle the ROI info & assessment for a found hand during photo capture phase after the photo has been captured and fingers have been found in the captured image
 
 In this case the UI should use the information in the roisInfo param to display the finger ROIs and the assessment message
 
 @param fingersInfo ROIsInfo instance that the UI should use to display the found fingers feedback during photo capture
 */
-(void) handleHandFoundForPhoto:(Veridium4FFingersInfo*) fingersInfo;


-(void) handleRetryCapture;


/*!
 Ask UI to handle the start of 4F photo capturing phase (usually by displaying a message like 'Capturing fingerprints. Please keep your hand still.')
 */
-(void) handleCapturing;
/*!
   Ask UI to handle the image processing event (usually by displaying a message like 'Processing. Please wait.')
 */
-(void) handleProcessing;

/*!
 Ask UI to ask your move their hand for liveness second shot
 */
-(void) handleTakeTwoShotLivnessSecond;

/*!
 Ask UI to update for the left or right hand
 
 @param useLeftHand `true` if user is exporting the left hand `false` otherwise
 @param takeSecondShot `true` if ask user for take second shot image for liveness
 @param targetFinger suitable enum value for target finger.
 @param canSwitch   `true` if the user can still switch hands `false` otherwise
 */
//-(void) handleUpdateUIForLeftHand:(BOOL)useLeftHand takeLivenessSecondShot:(BOOL) takeLivenessShiftShot targetFinger:(VeridiumFingerTargets)targetFinger canStillSwitch:(BOOL) canSwitch;

/*!
 Ask UI to update for the left or right hand
 
 @param guide image to display for the hand guide
 @param useLeftHand `true` if user is exporting the left hand `false` otherwise
 @param canSwitch   `true` if the user can still switch hands `false` otherwise
 */
-(void) handleUpdateUIWithHandGuide:(UIImage*)guide isLeftHand:(BOOL)useLeftHand canStillSwitch:(BOOL) canSwitch;

-(void) turnOnThumbOverlaysForIsLeftHand:(BOOL)useLeftHand;

-(void) turnOnIndividualOverlaysFoIsLeftHand:(BOOL)useLeftHand forIndividualFingerCode:(int)fingerCode;

@optional

-(void)handleShowProcessingScreen;

-(void)handleEndProcessingScreen: (voidBlock) completeBlock;

@end

/*!
 The Veridium4FUIDelegate subprotocol with UI delegate methods & props specific to 4F enrollment
 */
@protocol Veridium4FEnrollerUIDelegate <Veridium4FUIDelegate>

/*!
 By calling this function the engine provides a callback block to be called by the UI when the user wants to switch between left and right hand (e.g. when the user taps on switch button).
 
 This method is called during the initialization of the engine (inside the enroll function)
 
 The block is to be stored by the implementor of the protocol and used later when the user performs that action.

 This will only have effect before the first template has been captured. Afterwards it will be ignored (because all templates must be from the same hand)
 
 @param userWantsToUseLeftHandActionBlock The callback block to be stored by the UI and called when the user wants to switch hands (eg. taps on a button)
 */
-(void) connectSwitchHandActionBlock:(boolBlock) userWantsToUseLeftHandActionBlock;

/*!
 Ask the to confirm the captured picture
 
 @param accepted  boolBlock to be called with `true`/`false` if the user accepted or not the capture
 */
-(void) handleTakeVerifyPicture:(boolBlock)accepted;


/*!
 Ask the user to confirm enrollment completion
 
 @param accepted  boolBlock to be called with `true`/`false` if the user accepted or not
 */
-(void) handleEnrollDone:(boolBlock)accepted;

/*!
 Ask UI to update the progress of the enrolled 4F templates over the total number of 4F templates to enroll
 
 @param numberOfEnrolledTEmplates the number of enrolled templates
 @param total                     the total number of templates to enroll
 */
-(void) handleEnrollProgress:(NSInteger)numberOfEnrolledTEmplates totalNumberOfTemplates:(NSInteger) total;

@optional

/*!
 Ask UI to prompt the user to decide what action to continue with in case of a enrollment validation failure (ie. on of the enrolled templates failed to verify against the already enrolled ones)
 
 The UI should present a 3-way choice: 
 1. Retry - for retrying the last validation
 2. Restart - for restarting the entire enrollment process
 3. Cancel - for cancelling the enrollment
 
 @param retryBlock   callback for when the user decides to retry the validation
 @param restartBlock callback for when the user decides to restart enrollment
 @param cancelBlock  callback for when the user decides to cancel the enrollment
 */
-(void) handleVerifyFailDecisionWithRetry:(voidBlock) retryBlock restart:(voidBlock) restartBlock cancel:(voidBlock) cancelBlock;
- (NSString *) className;

@end


/*!
 The Veridium4FUIDelegate subprotocol with UI delegate methods & props specific to 4F authentication
 */
@protocol Veridium4FAuthenticatorUIDelegate <Veridium4FUIDelegate>

@optional
- (NSString *) className;
@end


/*!
 The Veridium4FUIDelegate subprotocol with UI delegate methods & props specific to 4F export
 */
@protocol Veridium4FExporterUIDelegate <Veridium4FUIDelegate>
    
    /*!
     By calling this function the engine provides a callback block to be called by the UI when the user wants to switch between left and right hand (e.g. when the user taps on switch button).
     
     This method is called during the initialization of the engine (inside the export function)
     
     The block is to be stored by the implementor of the protocol and used later when the user performs that action.
     
     This will only have effect before the first template has been captured. Afterwards it will be ignored (because all templates must be from the same hand)
     
     @param userWantsToUseLeftHandActionBlock The callback block to be stored by the UI and called when the user wants to switch hands (eg. taps on a button)
     */
-(void) connectSwitchHandActionBlock:(boolBlock) userWantsToUseLeftHandActionBlock;

    /*
     Ask the UI to instruct the user to switch hand.
     */
-(void) handleRequestUserSwitchHand:(voidBlock)onNext onCancel:(voidBlock)onCancel;

    /*!
     
     Ask the user to confirm exportment completion
     
     @param accepted  boolBlock to be called with `true`/`false` if the user accepted or not
     */
-(void) handleExportDone:(boolBlock)accepted;



-(void)handleShowIndividualFingerNextWithFingerCode:(int)fingerCode andBlock:(voidBlock)blockToProgress;
    
    /*!
     Ask UI to update the progress of the exported 4F templates over the total number of 4F templates to export
     
     @param numberOfExportedTEmplates the number of exported templates
     @param total                     the total number of templates to export
     */
-(void) handleExportProgress:(NSInteger)numberOfExportedTemplates totalNumberOfTemplates:(NSInteger) total;
    
    @optional

- (NSString *) className;

    @end


typedef enum : NSUInteger{
    Veridium4FAnalyzeHandDefaultLeft = 0,
    Veridium4FAnalyzeHandDefaultRight,
    Veridium4FAnalyzeHandForceLeft,
    Veridium4FAnalyzeHandForceRight
} Veridium4FAnalyzeHand;

/*!
 Common abstract class parent for the VeridiumBiometrics4FAuthenticator & VeridiumBiometrics4FEnroller
 */
@interface VeridiumBiometrics4FCommon : NSObject

+(NSString*)libVersion;

@property NSMutableDictionary* _Nullable resourceDict;

@end
