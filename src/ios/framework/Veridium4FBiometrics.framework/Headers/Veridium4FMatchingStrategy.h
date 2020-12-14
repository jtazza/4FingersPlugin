//
//  Veridium4FMatchingStrategy.h
//  Veridium4FBiometrics
//
//  Created by razvan on 11/17/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>
@import VeridiumCore;

@protocol Veridium4FMatchingStategy <VeridiumBiometricMatchingStrategy>

@property (readonly) BOOL useLeftHand;

@property (readonly, nullable) UIImage* customGuide;

@end
