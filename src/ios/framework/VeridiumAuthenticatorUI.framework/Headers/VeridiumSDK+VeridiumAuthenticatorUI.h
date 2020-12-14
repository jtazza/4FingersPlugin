//
//  VeridiumSDK+VeridiumAuthenticatorUI.h
//  VeridiumAuthenticatorUI
//
//  Created by Lewis Carney on 13/04/2018.
//  Copyright © 2018 veridium. All rights reserved.
//

#import <Foundation/Foundation.h>

@import VeridiumCore;
@import Veridium4FBiometrics;

@interface VeridiumSDK (Custom4FAdditions)

-(void) registerCustom4FAuthenticator;

-(void) registerCustom4FEnroller;

-(void) registerCustom4FExporter;

@end


