//
//  JSBinding.h
//  Tabris
//
//  Created by Jordi Böhme López on 09.01.2014.
//  Copyright (c) 2014 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TabrisClient.h"
#import "NotificationsProtocols.h"
#import <JavaScriptCore/JavaScriptCore.h>

@class JSBridge;

@interface JSBinding : NSObject<Binding>
- (id)initWithClient:(TabrisClient *)client;
- (JSValue *)execute:(NSString *)code fromSourceURL:(NSURL *)sourceURL;
- (void)flushOperationsQueue;
@end
