/*
 Licensed to the Apache Software Foundation (ASF) under one
 or more contributor license agreements.  See the NOTICE file
 distributed with this work for additional information
 regarding copyright ownership.  The ASF licenses this file
 to you under the Apache License, Version 2.0 (the
 "License"); you may not use this file except in compliance
 with the License.  You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing,
 software distributed under the License is distributed on an
 "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, either express or implied.  See the License for the
 specific language governing permissions and limitations
 under the License.
 */

//
//  AppDelegate.m
//  TestApp
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//

#import "AppDelegate.h"

#import <Cordova/CDVPlugin.h>
#import <Cordova/CordovaPluginBridge.h>
#import <Cordova/AppManager.h>
#import <Cordova/AppManagerStore.h>
#import <Cordova/CordovaConfig.h>

@interface AppDelegate ()
@property (retain) TabrisClient *client;
@end

@interface TabrisClient ()
- (id)initWithWindow:(UIWindow *)window andBindings:(NSArray *)bindings;
@end

@implementation AppDelegate

@synthesize client = _client;
@synthesize window = _window;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [application setStatusBarHidden:NO];
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    self.window = [[UIWindow alloc] initWithFrame:screenBounds];
    [self.window makeKeyAndVisible];
    self.window.autoresizesSubviews = YES;
    self.window.userInteractionEnabled = YES;
    self.window.contentMode = UIViewContentModeScaleToFill;
    self.client = [[TabrisClient alloc] initWithWindow:self.window andBindings:@[NSClassFromString(@"JSBinding")]];
    [AppManagerStore sharedStore].home = [self packageJsonUrl];
    [self.client addRemoteObject:[AppManager class]];
    [self.client addRemoteObject:[CordovaPluginBridge class]];
    self.client.delegate = self;
    return YES;
}

- (NSURL *)packageJsonUrl {
    return [[[[NSBundle mainBundle] resourceURL] URLByAppendingPathComponent:@"www" isDirectory:YES] URLByAppendingPathComponent:[CordovaConfig config].packageJsonPath];
}

#pragma mark UIApplicationDelegate implementation

- (NSURL *)serverURL {
    return [AppManagerStore sharedStore].url;
}

- (NSArray *)localResourceRoots {
    return @[@"www"];
}

- (BOOL)useSSLStrict {
    id sslSetting = [[CordovaConfig config].settings objectForKey:@"usestrictssl"];
    if( sslSetting ) {
        return [sslSetting boolValue];
    }
    return YES;
}

- (BOOL)prefersStatusBarHidden {
  id fullscreenSetting = [[CordovaConfig config].settings objectForKey:@"fullscreen"];
  if( fullscreenSetting ) {
      return [fullscreenSetting boolValue];
  }
}

- (BOOL)enableDeveloperConsole {
    return [[[CordovaConfig config].settings objectForKey:@"enabledeveloperconsole"] boolValue];
}

- (void)clientDidBecomeReady {
    /*
     Called when the Tabris client did become ready and will start a new session.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    if( [self.client isActive] ) {
        [self.client resume];
    } else {
        [self.client load];
    }
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
    [self.client terminate];
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
    [self.client suspend];
}


// this happens while we are running ( in the background, or from within our own app )
// only valid if HelloCordova-Info.plist specifies a protocol to handle
/* This method is used to handle incoming URLs for x-callback-url support
 */
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    // all plugins will get the notification, and their handlers will be called
    [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:CDVPluginHandleOpenURLNotification object:url]];
    return [self.client openURL:url fromSourceApplication:sourceApplication withAnnotation:annotation];
}

// repost all remote and local notification using the default NSNotificationCenter so multiple plugins may respond
- (void)application:(UIApplication*)application
    didReceiveLocalNotification:(UILocalNotification*)notification
{
    // re-post ( broadcast )
    [[NSNotificationCenter defaultCenter] postNotificationName:CDVLocalNotification object:notification];
}

#ifndef DISABLE_PUSH_NOTIFICATIONS

    - (void)                                 application:(UIApplication*)application
        didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken
    {
        // re-post ( broadcast )
        NSString* token = [[[[deviceToken description]
            stringByReplacingOccurrencesOfString:@"<" withString:@""]
            stringByReplacingOccurrencesOfString:@">" withString:@""]
            stringByReplacingOccurrencesOfString:@" " withString:@""];
        [[NSNotificationCenter defaultCenter] postNotificationName:CDVRemoteNotification object:token];
    }

    - (void)                                 application:(UIApplication*)application
        didFailToRegisterForRemoteNotificationsWithError:(NSError*)error
    {
        // re-post ( broadcast )
        [[NSNotificationCenter defaultCenter] postNotificationName:CDVRemoteNotificationError object:error];
    }
#endif

- (UIInterfaceOrientationMask)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window {
    UIInterfaceOrientationMask orientations = 0;
    NSArray *supportedOrientations = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"UISupportedInterfaceOrientations"];
    for (NSString *orientation in supportedOrientations) {
        if ([orientation isEqualToString:@"UIInterfaceOrientationPortrait"]) {
            orientations |= UIInterfaceOrientationMaskPortrait;
        } else if ([orientation isEqualToString:@"UIInterfaceOrientationPortraitUpsideDown"]) {
            orientations |= UIInterfaceOrientationMaskPortraitUpsideDown;
        } else if ([orientation isEqualToString:@"UIInterfaceOrientationLandscapeLeft"]) {
            orientations |= UIInterfaceOrientationMaskLandscapeLeft;
        } else if ([orientation isEqualToString:@"UIInterfaceOrientationLandscapeRight"]) {
            orientations |= UIInterfaceOrientationMaskLandscapeRight;
        }
    }
    return orientations;
}

- (void)applicationDidReceiveMemoryWarning:(UIApplication*)application
{
    [[NSURLCache sharedURLCache] removeAllCachedResponses];
}

#if !__has_feature(objc_arc)
- (void)dealloc {
    [self->client release];
    [self->window release];
    [super dealloc];
}
#endif

@end
