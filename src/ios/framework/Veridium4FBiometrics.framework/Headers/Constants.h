//
//  Constants.h
//  Veridium4FBiometrics
//
//  Created by razvan on 9/12/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

#import <Foundation/Foundation.h>

#define kVeridiumBiometricEngineName4F @"4F"

typedef enum : NSUInteger {
    FINGERS_WHITE = 0,
    FINGERS_DARK,
    MITTEN_DARK,
    MITTEN_DARK_LARGE
} GuideDesign;

/*!
 Defines the 4F fingers assessment comming from the 4F library on each frame and capture
 */
typedef enum : NSUInteger {
  Veridium4FFingersAssessmentNotOK = 0,
  Veridium4FFingersAssessmentOutOfFocus,
  Veridium4FFingersAssessmentStable,
  Veridium4FFingersAssessmentTooClose,
  Veridium4FFingersAssessmentTooFar,
  Veridium4FFingersAssessmentTooFarApart,
  Veridium4FFingersAssessmentTooHigh,
  Veridium4FFingersAssessmentTooLow,
  Veridium4FFingersAssessmentTooFarLeft,
  Veridium4FFingersAssessmentTooFarRight
} Veridium4FFingersAssessment;

typedef enum : NSUInteger {
    FORMAT_VERID = 0,
    FORMAT_NIST = 1,
    FORMAT_INTERPOL = 2,
    FORMAT_ZIP = 3,
    FORMAT_JSON = 4,
    FORMAT_ISO2005_2 = 5,
    FORMAT_ISO2005_4 = 6
} VeridiumTemplateFormat;

typedef enum : NSUInteger {
    ThumbNone = 0,  // no thumbs are captured
    Thumb2F = 1,    // capture thumbs exclusively
    Thumb10F = 2    // capture thumbs after capturing both hands first
} VeridiumThumbMode;

typedef enum : NSUInteger {
    LivenessNoLiveness,
    LivenessTwoShotFirst,
    LivenessTwoShotSecond
} VeridiumLiveness;

typedef enum : NSUInteger {
    TargetFingerNone = 0,
    TargetFingerInvalid = 1,
    TargetFingerIndexMiddle = 2,
    TargetFingerRingLittle= 3,
    TargetFingerMiddleRing = 4,
    TargetFingerThumb = 5,
    TargetFingerIndividual = 6
} VeridiumFingerTargets;

typedef enum : NSUInteger {
    CoarseGrainSweep,
    FineGrainSweep
} VeridiumFocusSweepStage;

#define ffRS_CENTRE_LEFT @"ffRS_CENTRE_LEFT"
#define ffRS_CENTRE2_LEFT @"ffRS_CENTRE2_LEFT" // for enroll verify, it might need two palm image
#define ffRS_SHIFT_LEFT @"ffRS_SHIFT_LEFT"
#define ffRS_LITTLE_LEFT @"ffRS_LITTLE_LEFT"
#define ffRS_INDEX_LEFT @"ffRS_INDEX_LEFT"
#define ffRS_THUMB_LEFT @"ffRS_THUMB_LEFT"
#define ffRS_INDIVIDUAL_INDEX_LEFT @"ffRS_INDIVIDUAL_INDEX_LEFT"
#define ffRS_INDIVIDUAL_MIDDLE_LEFT @"ffRS_INDIVIDUAL_MIDDLE_LEFT"
#define ffRS_INDIVIDUAL_RING_LEFT @"ffRS_INDIVIDUAL_RING_LEFT"
#define ffRS_INDIVIDUAL_LITTLE_LEFT @"ffRS_INDIVIDUAL_LITTLE_LEFT"
#define ffRS_INDIVIDUAL_THUMB_LEFT @"ffRS_INDIVIDUAL_THUMB_LEFT"

#define ffRS_CENTRE_RIGHT @"ffRS_CENTRE_RIGHT"
#define ffRS_CENTRE2_RIGHT @"ffRS_CENTRE2_RIGHT" // for enroll verify, it might need two palm image
#define ffRS_SHIFT_RIGHT @"ffRS_SHIFT_RIGHT"
#define ffRS_LITTLE_RIGHT @"ffRS_LITTLE_RIGHT"
#define ffRS_INDEX_RIGHT @"ffRS_INDEX_RIGHT"
#define ffRS_THUMB_RIGHT @"ffRS_THUMB_RIGHT"
#define ffRS_INDIVIDUAL_INDEX_RIGHT @"ffRS_INDIVIDUAL_INDEX_RIGHT"
#define ffRS_INDIVIDUAL_MIDDLE_RIGHT @"ffRS_INDIVIDUAL_MIDDLE_RIGHT"
#define ffRS_INDIVIDUAL_RING_RIGHT @"ffRS_INDIVIDUAL_RING_RIGHT"
#define ffRS_INDIVIDUAL_LITTLE_RIGHT @"ffRS_INDIVIDUAL_LITTLE_RIGHT"
#define ffRS_INDIVIDUAL_THUMB_RIGHT @"ffRS_INDIVIDUAL_THUMB_RIGHT"



#define ffMSG_HAS_PASSED_LIVENESS_PROCESS @"ffMSG_HAS_PASSED_LIVENESS_PROCESS"
#define ffMSG_ENROLL_NAME_1 @"ffMSG_ENROLL_NAME_1"
#define ffMSG_ENROLL_NAME_2 @"ffMSG_ENROLL_NAME_2"

NSString* _Nonnull getDefaultExtension(VeridiumTemplateFormat format);
NSString* _Nonnull getDefaultFormatNames(VeridiumTemplateFormat format);

#define Veridium4FFingersAssessmentStrings @[\
@"Please keep your hand still with the fingers inside the guide",\
@"Your fingers are out of focus.\nPlease adjust your hand distance from the camera",\
@"Perfect.\nKeep your hand still.",\
@"Your hand is too close to the camera.\nPlease move your hand farther.",\
@"Your hand is too far from the camera.\nPlease move you hand closer.",\
@"Please keep your fingers closer together.",\
@"Your hand is too high.\nPlease move your hand down.",\
@"Your hand is too low.\nPlease move your hand up.",\
@"Your hand is too far to the left.\nPlease move your hand towards the right.",\
@"Your hand is too far to the right.\nPlease move your hand towards the left."]

#define Veridium4FFingersAssessmentColors @[\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5],\
[UIColor colorWithWhite:0 alpha:0.5],\
[UIColor colorWithRed:0 green:1 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5],\
[UIColor colorWithRed:1 green:0 blue:0 alpha:0.5]]

@interface Veridium4FFingerCoordinates: NSObject

/*!
 The 2D coordinates for the 1st finger.
 */
@property CGRect finger1;
/*!
 The 2d coordinates for the 2nd finger.
 */
@property CGRect finger2;
/*!
 The 2d coordinates for the 3rd finger.
 */
@property CGRect finger3;
/*!
 The 2d coordinates for the 4th finger.
 */
@property CGRect finger4;

@end

/*!
 Data class used by 4F to send the finger ROIs (Region Of Interest) and additional info during the finger finding phase and in the capture phase to its UI delegate.
 
 The UI should use this information to display the fingers information and display finger overlays
 
 */

@interface Veridium4FFingersInfo: NSObject

/*!
 The recommended color for the finger rectangles ROI display.
 */
@property (nonnull) UIColor* color;
/*!
 Finger ROIs assesment mesage to provide hints to the user (hand to close, hand too far, etc.)
 */
@property (nullable) NSString* assessmentMessage;

/*!
 A constant value of finger finder assessment on the capture
 */
@property Veridium4FFingersAssessment assessment;

/*!
 The size of the image the finger data is based upon
 */
@property CGSize handPictureSize;

@property NSInteger distanceInfo;

-(instancetype _Nonnull)initWithFingerROIs:(int[16]) rois
                         fingersAssessment:(Veridium4FFingersAssessment) assessment
                           handPictureSize:(CGSize) handPictureSize
                            distanceInfo:(NSInteger)distance;


/*!
 Returns the finger rects converted from the coordinates of the source picture (handPictureSize) to coordinates in the frame of the target view size (i.e. the view that displays the picture and the finger overlays)
 
 This method should be used by the UI delegates to display the finger overlays on both video and picture updates.
 
 @param targetSize the size of the target view's frame
 
 @return an instance of the Veridium4FFingerCoordinates with the finger rects coordinates in the target view's frame
 */
-(Veridium4FFingerCoordinates* _Nonnull) fingerCoordinatesForTargetSize:(CGSize) targetSize;

@end

@interface Veridium4FLicenseStatus : VeridiumLicenseStatus

/*!
 Whether the 4F library licence hsa expired
 */
@property (readonly) BOOL isExpired;

/*!
 Whether the 4F library licence is corrupted.
 */
@property (readonly) BOOL isCorrupt;

/*!
 Whether the 4F library is allowed to perform liveness authentication.
 */
@property (readonly) BOOL isLivnessCapabile;

/*!
 Whether the 4F library has liveness mandatory.
 */
@property (readonly) BOOL isLivenessMandatory;

@end


#endif /* Constants_h */
