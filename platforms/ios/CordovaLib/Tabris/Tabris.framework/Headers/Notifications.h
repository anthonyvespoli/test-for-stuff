//
//  Notifications.h
//  Tabris
//
//  Created by Jordi Böhme López on 09.11.12.
//  Copyright (c) 2012-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RemoteObject.h"
#import "NotificationsProtocols.h"
#import "Message.h"

@interface Notifications : NSObject
+ (Message<HeadNotification> *)forHead;
+ (Message<Notification> *)forObject:(id <RemoteObject>)target;
+ (Message<Notification> *)forType:(NSString *)target;

@end
