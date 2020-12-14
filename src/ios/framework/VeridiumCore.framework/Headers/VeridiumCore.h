//
//  VeridiumCore.h
//  VeridiumCore
//
//  Created by razvan on 11/23/15.
//  Copyright © 2015 Veridium. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for VeridiumCore.
FOUNDATION_EXPORT double VeridiumCoreVersionNumber;

//! Project version string for VeridiumCore.
FOUNDATION_EXPORT const unsigned char VeridiumCoreVersionString[];

#import "VeridiumObjCFSM.h"
#import "VeridiumBiometricsProtocols.h"
#import "VeridiumUtils.h"
#import "VeridiumSDK.h"
#import "VeridiumPushHandlerProtocol.h"
#import "VeridiumAccountService.h"
#import "VeridiumAccount.h"
#import "VeridiumExportService.h"
#import "VeridiumVCrypt.h"
#import "VeridiumNSData+NSString+CommonCrypto.h"
#import "VeridiumKeyValueStore.h"
#import "VeridiumKeychainKeyValueStore.h"
#import "VeridiumUserDefaultsKeyValueStore.h"
#import "VeridiumMemoryKeyValueStore.h"
#import "VeridiumBiometricVector.h"
#import "VeridiumAggregationHelpers.h"

///New license imports
#import "VeridiumLicenseStatus.h"

/// end new license imports
