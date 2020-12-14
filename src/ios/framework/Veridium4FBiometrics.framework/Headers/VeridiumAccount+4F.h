//
//  Veridium4FSDK.h
//  Veridium4FBiometrics
//
//  Created by razvan on 11/24/15.
//  Copyright © 2015 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>

@import VeridiumCore;
/*!
 Entension for 4F
 */
@interface VeridiumAccount (FourFAdditions)

/*!
 Returns `true` if the account has 4F enrolled
 */
-(BOOL) is4FEnrolled;

@end
