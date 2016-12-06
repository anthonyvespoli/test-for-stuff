//
//  AppManagerStore.m
//  Tabris
//
//  Created by Jordi Böhme López on 06.11.14.
//  Copyright (c) 2014 EclipseSource. All rights reserved.
//

#import <Cordova/AppManagerStore.h>

@implementation AppManagerStore

@synthesize current = _current;
@synthesize home = _home;

+ (instancetype)sharedStore {
    static AppManagerStore *_sharedStore = nil;
    static dispatch_once_t oncePredicate;
    dispatch_once(&oncePredicate, ^{
        _sharedStore = [[super alloc] init];
    });
    return _sharedStore;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        _home = nil;
        _current = nil;
    }
    return self;
}

- (void)setHome:(NSURL *)home {
    _home = home;
    if( !self.current ) {
        self.current = [home absoluteString];
    }
}

- (NSURL *)home {
    return _home;
}

- (void)setCurrent:(NSString *)current {
    if( current ) {
        _current = current;
    } else {
        _current = [self.home absoluteString];
    }
}

- (NSString *)current {
    return _current;
}

- (NSURL *)url {
    NSAssert(self.home, @"AppManagerStore property 'home' url must be set.");
    NSURL *url = nil;
    if( self.current ) {
        return [NSURL URLWithString:self.current];
    } else {
        return self.home;
    }
    return url;
}

@end