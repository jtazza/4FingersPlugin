//
//  VeridiumDefault4FUICustomization.h
//  VeridiumDefault4FUI
//
//  Created by Josiah Kane on 05/04/2017.
//  Copyright © Veridium IP Ltd., 2018. All rights reserved
//

#ifndef VeridiumDefault4FUICustomization_h
#define VeridiumDefault4FUICustomization_h

@class VeridiumDefault4FUICustomization;


@interface VeridiumDefault4FUICustomization : NSObject
+ (UIColor *)getBackgroundColor;
+ (UIColor *)getForegroundColor;
+ (UIColor *)getDialogColor;
+ (UIColor *)getDialogTextColor;
+ (UIImage *)getBackgroundImage;


+ (UIColor *)defaultBackgroundColor;
+ (UIColor *)defaultForegroundColor;
+ (UIColor *)defaultDialogColor;
+ (UIColor *)defaultDialogTextColor;


+ (void)setBackgroundColor:(UIColor *)newColor;
+ (void)setForegroundColor:(UIColor *)newColor;
+ (void)setDialogColor:(UIColor *)newColor;
+ (void)setDialogTextColor:(UIColor *)newColor;
+ (void)setBackgroundImage:(UIImage *)newImage;

@end

#endif /* VeridiumDefault4FUICustomization_h */
