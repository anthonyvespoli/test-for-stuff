//
//  TabrisClient.h
//  Tabris
//
//  Created by Jordi Boehme Lopez and Holger Staudacher on 10.05.12.
//  Copyright (c) 2012-2013 EclipseSource. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TabrisClientDelegates.h"

@interface TabrisClient : NSObject

@property (strong,readonly) UIView *view;
@property (weak) id <TabrisClientDelegate>delegate;
@property (weak) id <TabrisClientErrorDelegate>errorDelegate;

/**
 Initialize the client with your applications main UIWindow.

 @note After initialization the delegate property should be set.

 @since 1.0
 */
- (id)initWithWindow:(UIWindow *)window;

/**
 Starts a new session by using the configuration parameters provided by the TabrisClientDelegate.
 Calling this method while the client is active will start a new session which behaves like a reset.

 @since 1.0
 */
- (void)load;

/**
 Suspends the current session when e.g. the application moves to the background.

 @since 1.0
 */
- (BOOL)suspend;

/**
 Resumes the client and its session after the app returns from the background.

 @since 1.0
 */
- (BOOL)resume;

/**
 Retries to re-establish the current session after a connection error occured.

 @since 1.0
 */
- (void)retry;

/**
 Forces the current session to be terminated.

 @since 1.1
 */
- (void)terminate;

/**
 * Whether the Tabris client is initialized, started and currently running a session or not.

 @since 1.0
 */
- (BOOL)isActive;

/**
 This method must be called from your AppDelegate method:
 @code
 - (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
 @endcode
 It is needed to enable OpenWith, X-Callback and other Tabris features.

 @since 1.1
 */
- (BOOL)openURL:(NSURL *)url fromSourceApplication:(NSString *)sourceApplication withAnnotation:(id)annotation;

/**
 This method must be called from your AppDelegate method:
 @code
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 @endcode
 It is needed to enable CloudPush (APNS) and other future Tabris features.

 @since 1.4.1
 */
- (void)didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;

/**
 This method must be called from your AppDelegate method:
 @code
 - (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
 @endcode
 It is needed to enable CloudPush (APNS) and other future Tabris features.

 @since 1.4.1
 */
- (void)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

/**
 This method must be called from your AppDelegate method:
 @code
 - (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
 @endcode
 It is needed to enable CloudPush (APNS) and other future Tabris features.

 @since 1.4.1
 */
- (void)didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

/**
 This method must be called from your AppDelegate method:
 @code
 - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
 @endcode
 It is needed to enable CloudPush (APNS) and other future Tabris features.

 @since 1.4.1
 */
- (void)didReceiveRemoteNotification:(NSDictionary *)userInfo;

- (void)statusBarBackgroundVisible:(BOOL)visible;

@end
