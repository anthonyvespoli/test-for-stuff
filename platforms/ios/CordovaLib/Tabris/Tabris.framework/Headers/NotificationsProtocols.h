//
//  NotificationsProtocols.h
//  Tabris
//
//  Created by Jordi Böhme López on 14.11.12.
//  Copyright (c) 2012-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Message, TabrisClient;

@protocol Notification <NSObject>
- (Message<Notification> *)attributeChanged:(id)value forKey:(NSString *)key;
- (Message<Notification> *)call:(NSString *)methodName withAttributes:(NSDictionary *)attributes;
- (Message<Notification> *)fireEvent:(NSString *)eventName withAttributes:(NSDictionary *)attributes;
- (Message<Notification> *)fireSelection;
- (Message<Notification> *)fireDefaultSelection;
- (NSArray *)getMessageOperations;
- (NSString *)getTarget;
@end

@protocol HeadNotification <NSObject>
- (Message<HeadNotification> *)setAttribute:(id)value forKey:(NSString *)key;
- (Message<HeadNotification> *)rwtInitialize;
- (Message<HeadNotification> *)shutdown;
- (Message<HeadNotification> *)ping;
- (NSDictionary *)getAttributes;
@end

@protocol Binding <NSObject>
- (id)initWithClient:(TabrisClient *)client;
- (void)start;
- (void)suspend;
- (void)resume;
- (void)retry;
- (void)stop;
- (BOOL)sendMessage:(Message *)message;
- (BOOL)scheduleMessage:(Message *)message;
- (BOOL)storeMessage:(Message *)message;
- (void)reset;
- (BOOL)isActive;
- (BOOL)isProcessing;
- (void)receivedRequestCounter:(NSInteger)value;
- (BOOL)supportsCustomDrawer;
@end

