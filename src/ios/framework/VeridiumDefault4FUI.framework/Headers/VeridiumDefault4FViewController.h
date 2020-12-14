//
//  VeridiumDefault4FViewController.h
//  VeridiumDefault4FUI
//
//  Created by Josiah Kane on 23/03/2017.
//  Copyright © Veridium IP Ltd., 2018. All rights reserved
//

#ifndef VeridiumDefault4FViewController_h
#define VeridiumDefault4FViewController_h

@import VeridiumCore;
@import Veridium4FBiometrics;

@interface VeridiumDefault4FViewController : UIViewController <Veridium4FEnrollerUIDelegate, Veridium4FExporterUIDelegate, Veridium4FAuthenticatorUIDelegate>{

    @public BOOL viewControllerIsForAuth;
    @public BOOL viewControllerIsForExport;
    @public BOOL viewControllerIsForEnroll;

}

+(__weak instancetype _Nullable) createFromStoryboard:(UIStoryboard* _Nullable)storyboard withIdentifier:(NSString* _Nonnull)identifier forAuthMode:(bool)isForAuth;

+(instancetype _Nullable) createDefaultAuthenticator;
+(instancetype _Nullable) createDefaultEnroller;
+(instancetype _Nullable) createDefaultExporter;


//New methods to override
+(UIStoryboard* _Nullable) getMain4FStoryboard;

-(UIStoryboard*) getIntro4FStoryboard;

-(UIStoryboard*) getProcessing4FStoryboard;

-(UIStoryboard*) getDialogStoryboard;

-(UIStoryboard*) getIndividualIntroStoryboard;

-(UIStoryboard*) getThumbIntroStoryboard;

-(UIStoryboard*) getLivenessFailedStoryboard;


-(void)handleHandThumbForVideo: (BOOL) isThumbFound forROI:(CGRect)rectThumb forIndividualROI:(CGRect)rectIndividual;

-(void)handleHandFoundForVideo:(Veridium4FFingersInfo *)roisInfo;

-(void) drawROI:(NSInteger) roiIndex inView:(UIView*) view rect:(CGRect) rect withColor:(UIColor*) color;

-(void) drawThumbROI:(UIView *)view forThumbFound:(BOOL) isThumbFound forROI:(CGRect)rect;

-(GuideDesign) handGuideType;


-(BOOL) useMeter;

-(BOOL) useArrows;

-(BOOL) useIndividualFingerIndicatorImage;

@end

#endif /* VeridiumDefault4FViewController_h */
