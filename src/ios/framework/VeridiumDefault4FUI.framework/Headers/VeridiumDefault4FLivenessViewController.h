//
//  VeridiumDefault4FLivenessViewController.h
//  VeridiumDefault4FUI
//
//  Created by Lewis Carney on 12/04/2017.
//  Copyright © Veridium IP Ltd., 2018. All rights reserved
//
#import <UIKit/UIKit.h>
@import VeridiumCore;

@interface VeridiumDefault4FLivenessViewController : UIViewController

@property (strong, nonatomic) voidBlock onOk;
@property (strong, nonatomic) voidBlock onCancel;
@property BOOL isHorz;
@end
