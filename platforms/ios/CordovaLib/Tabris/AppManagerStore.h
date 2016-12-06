//
//  AppManagerStore.h
//  Tabris
//
//  Created by Jordi Böhme López on 06.11.14.
//  Copyright (c) 2014 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AppManagerStore : NSObject
+ (instancetype)sharedStore;
@property (strong) NSString *current;
@property (strong) NSURL *home;
@property (readonly) NSURL *url;
@end
