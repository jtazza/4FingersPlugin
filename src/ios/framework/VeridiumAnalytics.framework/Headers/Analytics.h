//
//  Analytics.h
//  VeridiumAnalytics
//
//  Created by Lewis Carney on 08/08/2017.
//  Copyright © 2017 veridium. All rights reserved.
//

typedef enum analyticsVerbosity
{
    VERBOSE_MODE,
    DEBUG_MODE,
    ERROR_MODE
} Verbosity;

@interface Analytics : NSObject

+siAnalytics;

+(NSString *) NSStringFromVerbosity:(Verbosity) verbosity;

+(void)sendAnalyticsEvents:(Verbosity)verbosityLevel andCategoryName:(NSString *)category andEventName:(NSString *)event;

+(void)sendAnalyticsDataWithVerbosity:(Verbosity) verbosityLevel andData:(NSData *) data andTag:(NSString*) tag andMessage:(NSString*) message;

+(void)provideServerCredentialsWithServerID:(NSString*) serverID andPassword:(NSString*) serverPassword;

+(void)logAnalyticsFileData:(Verbosity) verbosityLevel andTag:(NSString*) tag andMessage:(NSString*) message;

@end

