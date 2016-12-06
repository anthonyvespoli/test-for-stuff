//
//  TabrisClientDelegates.h
//  Tabris
//
//  Created by Jordi Böhme López on 11.05.12.
//  Copyright (c) 2012-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>

@class TabrisClient;

@protocol TabrisClientDelegate <NSObject>
@required

/**
 Called when the Tabris client did become ready and will start a new session.

 @since 1.0
 */
- (void)clientDidBecomeReady;

/**
 The absolute HTTP(S) URL of the entrypoint on the tabris server.

 @since 1.0
 */
- (NSURL *)serverURL;

@optional

/**
 An Array of root directories to look for resources.
 Before loading resources with relative paths from a remote location,
 the Tabris client will try to load the resources in the provided local directories.

 @return NSArray of NSStrings. The default value is nil.
 @since 2.0
 */
- (NSArray *)localResourceRoots;

/**
 Whether the HTTP responses in the client-server communication should be logged to the console
 and a file in the application document folder.

 @return The default value is NO.
 @since 1.0
 */
- (BOOL)logResponses;

/**
 Whether the HTTP requests in the client-server communication should be logged to the console
 and a file in the application document folder.

 @return The default value is NO.
 @since 1.0
 */
- (BOOL)logRequests;

/**
 Whether to perform strict validations on SSL connections to the server.

 Strict validations include: Certificate expiration, domain name match,
 and if the certificate is trusted by a CA.
 @note Only applies if HTTPS is used.

 @return The default value is YES.
 @since 1.0
 */
- (BOOL)useSSLStrict;

/**
 Whether the Tabris client should wait infinitely for HTTP requests to return.
 If set to YES, the number returned by requestTimeout is ignored.
 Use this during development for debugging. It is not recommended to us this during production.

 @return The default value is NO.
 @since 1.0
 */
- (BOOL)useInfiniteRequestTimeout;

/**
 The time to wait for a response for an HTTP request, given in seconds.
 If the time is over, the request is cancelled with a timeout.
 @note Only relevant if useInfiniteRequestTimeout returns NO.

 @return The default value is 90.
 @since 1.0
 */
- (NSInteger)requestTimeout;

/**
 Whether to enable auto capitalization for all text widgets in the client.
 If this method is not implemented, the value in the global preferences applies.
 @note Auto capitalization can be overridden for individual text widgets as well.

 @since 1.0
 */
- (BOOL)useAutoCapitalization;

/**
 Whether to enable auto correction for all text widgets in the client.
 If this method is not implemented, the value in the global preferences applies.
 @note Auto correction can be overridden for individual text widgets as well.

 @since 1.0
 */
- (BOOL)useAutoCorrection;

/**
 The ID to check for the client binding.
 If set, the client can only connect to servers with the same ID.
 If set to nil, the client can connect to any server (if no ID is set there).

 @return The default value is nil.
 @since 1.3
 */
- (NSString *)requiredServerId;

/**
 Provides a UI to manually reload the session and display the log.
 It can be accessed via a right bezel-swipe.

 This method has been deprecated. Use -enableDeveloperConsole instead.
 @return The default value is NO.
 @since 1.4
 */
- (BOOL)enableReload;

/**
 Provides a UI to manually reload the session and display the log.
 It can be accessed via a right bezel-swipe.

 @return The default value is NO.
 @since 1.5
 */
- (BOOL)enableDeveloperConsole;

/**
 Whether the StatusBar on top of the screen is hidden or not..

 @return The default value is NO.
 @since 1.4.5
 */
- (BOOL)statusBarHidden;

@end

@protocol TabrisClientErrorDelegate <NSObject>

/**
 Called when an error occured. This might open a dialog for the user
 or silently restart the session.

 @since 1.0
 */
- (void)errorOccured:(NSError *)error onClient:(TabrisClient *)client;

/**
 Called to close possibly open dialogs when the tabris client is restarted or reset.

 @since 1.0
 */
- (void)close;

@end
