//
//  RemoteObject.h
//  Tabris
//
//  Created by Jordi Böhme López on 09.01.12.
//  Copyright (c) 2012-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TabrisClient.h"
#import "TabrisHTTPClient.h"

@protocol RemoteObject <NSObject>

+ (id<RemoteObject>)newObjectWithId:(NSString *)objectId properties:(NSDictionary *)properties andClient:(TabrisClient *)client __deprecated_msg("Use [[BasicObject alloc] initWithObjectId:properties:andClient:] instead.");
- (instancetype)initWithObjectId:(NSString *)objectId properties:(NSDictionary *)properties andClient:(TabrisClient *)client;
+ (NSString *)remoteObjectType;
+ (NSMutableSet *)remoteObjectProperties;

@property (readonly, strong) NSString *objectId;
@property (weak) id<RemoteObject> parent;
@property (assign) BOOL omitDestroy;

- (void)addObject:(id<RemoteObject>)object;
- (void)removeObject:(id<RemoteObject>)object;
- (void)childObjectChanged:(id<RemoteObject>)object;
- (void)notifyObjectChange;

- (TabrisClient *)client;
- (NSObject *)dispatchType:(NSString *)type method:(NSString *)method properties:(NSDictionary *)properties;
- (void)registered;
- (void)destroy;

@end

@protocol ServiceObject <RemoteObject>
- (void)synchronize;
@end

@interface TabrisClient ()

- (void)addRemoteObject:(Class <RemoteObject>)remoteObject;
- (id<RemoteObject>)objectById:(NSString *)objectId;
@property (strong,readonly) TabrisHTTPClient *httpClient;
- (UIViewController *)viewController;
- (id)initWithWindow:(UIWindow *)window andBindings:(NSArray *)bindings;
- (NSSet *)bindings;

@end
