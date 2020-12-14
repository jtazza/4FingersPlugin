//
//  VeridiumDefault4FViewController.h
//  VeridiumDefault4FUI
//
//  Created by Josiah Kane on 23/03/2017.
//  Copyright © Veridium IP Ltd., 2018. All rights reserved
//

#ifndef VeridiumDefault4FViewController_h
#define VeridiumDefault4FViewController_h

@import VeridiumDefault4FUI;

@interface VeridiumAuthenticatorViewController : VeridiumDefault4FViewController

+(__weak instancetype _Nullable) createFromStoryboard:(UIStoryboard* _Nullable)storyboard withIdentifier:(NSString* _Nonnull)identifier forAuthMode:(bool)isForAuth;

+(instancetype _Nullable) createCustomAuthenticator;
+(instancetype _Nullable) createCustomEnroller;
+(instancetype _Nullable) createCustomExporter;

    
@end

#endif /* VeridiumDefault4FViewController_h */
