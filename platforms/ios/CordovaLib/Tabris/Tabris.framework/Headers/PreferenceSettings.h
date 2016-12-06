//
//  PreferenceSettings.h
//  Tabris
//
//  Created by Jordi Böhme López
//  Copyright (c) 2011-2013 EclipseSource. All rights reserved.
//

@interface PreferenceSettings : NSObject {
}

+ (void)initDefaults;
+ (NSUserDefaults *)userPreferences;

NSURL *preferenceServerURL();
NSInteger preferenceRequestTimeout();

BOOL preferenceSSLStrict();

BOOL preferenceDisplayIdle();

BOOL preferenceAutoCorrection();
BOOL preferenceAutoCapitalization();

BOOL preferenceLogRequests();
BOOL preferenceLogResponses();
BOOL preferenceInfiniteTimeout();
BOOL preferenceDevMenuHint();

@end