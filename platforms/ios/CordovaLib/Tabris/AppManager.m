//
//  ScriptURLManager.m
//  Tabris
//
//  Created by Jordi Böhme López on 06.11.14.
//  Copyright (c) 2014 EclipseSource. All rights reserved.
//

#import <Cordova/AppManager.h>
#import <Cordova/AppManagerStore.h>

@implementation AppManager

- (id)init {
    self = [super init];
    if (self) {
        [self registerSelector:@selector(home:) forCall:@"home"];
    }
    return self;
}

+ (NSString *)remoteObjectType {
    return @"tabris.AppManager";
}

+ (NSMutableSet *)remoteObjectProperties {
    NSMutableSet *set = [super remoteObjectProperties];
    [set addObject:@"current"];
    return set;
}

- (void)home:(NSDictionary *)properties {
    NSString *homeUrl = [properties objectForKey:@"url"];
    if( homeUrl && ![homeUrl isEqualToString:@""] ) {
        [AppManagerStore sharedStore].home = [NSURL URLWithString:homeUrl];
    }
    self.current = [[AppManagerStore sharedStore].home absoluteString];
}

- (void)setCurrent:(NSString *)current {
    NSURL *resolvedURL = [self.client.httpClient relativeURLToServer:current];
    [AppManagerStore sharedStore].current = [resolvedURL absoluteString];
    [self.client load];
}

- (NSString *)current {
    return [[AppManagerStore sharedStore].url absoluteString];
}

- (void)synchronize {
}

@end