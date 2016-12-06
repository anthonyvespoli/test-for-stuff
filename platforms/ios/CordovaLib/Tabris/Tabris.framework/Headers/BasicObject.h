//
//  BasicObject.h
//  Tarbis
//
//  Created by Jordi Böhme López on 09.01.12.
//  Copyright (c) 2012-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RemoteObject.h"
#import "Notifications.h"

@interface BasicObject : NSObject <RemoteObject>
+ (id<RemoteObject>)newObjectWithId:(NSString *)objectId properties:(NSDictionary *)properties andClient:(TabrisClient *)client __deprecated_msg("Use [[BasicObject alloc] initWithObjectId:properties:andClient:] instead.");
- (instancetype)initWithObjectId:(NSString *)objectId andClient:(TabrisClient *)client NS_REQUIRES_SUPER NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithObjectId:(NSString *)objectId properties:(NSDictionary *)properties andClient:(TabrisClient *)client;
@property (strong, readonly) NSString *objectId;
@property (strong, readonly) NSMutableArray *objects;
@property (assign, readonly) BOOL creationPhase;
@property (assign, readonly) BOOL isDisposed;
@property (strong) Class notifications;
@property (assign) BOOL omitDestroy;
- (void)registerSelector:(SEL)selector forCall:(NSString *)method;

/**
 Called when a batch of operations has been executed.
 This method should only be called by the framework.

 @return YES if this Object wants to continue listening on operation executions.
 @since 1.4
 @
 */
- (BOOL)processingFinished NS_REQUIRES_SUPER;

/**
 Called when a destroy operation on this object instance is executed.

 @since 1.0
 */
- (void)destroy NS_REQUIRES_SUPER;
@end
