//
//  Default4FAdditions.h
//  Default4FUI
//
//  Created by Paul Paul on 6/14/16.
//  Copyright © 2016 Veridium. All rights reserved.
//

#import <Foundation/Foundation.h>

@import VeridiumCore;
@import Veridium4FBiometrics;

@interface VeridiumSDK (Default4FAdditions)

-(void) registerDefault4FAuthenticator;

-(void) registerDefault4FEnroller;

-(void) registerDefault4FExporter;

@end
