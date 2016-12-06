//
//  Message.h
//  Tabris
//
//  Created by Jordi Böhme López on 14.11.12.
//  Copyright (c) 2012-2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Message : NSObject
@property (assign) BOOL result;
- (BOOL)store;
- (BOOL)schedule;

@end
