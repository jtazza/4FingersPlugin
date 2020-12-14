//
//  VeridiumDefault4FIntroViewController.h
//  VeridiumBiometricsUI
//
//  Created by Paul Paul on 2/16/17.
//  Copyright © 2017 VeridiumID. All rights reserved.
//

#import <UIKit/UIKit.h>
@import VeridiumCore;

@interface VeridiumDefault4FIntroViewController : UIViewController

@property (nonatomic) NSString* headingText;
@property (strong, nonatomic) voidBlock onOk;
@property (strong, nonatomic) voidBlock onCancel;

@end
