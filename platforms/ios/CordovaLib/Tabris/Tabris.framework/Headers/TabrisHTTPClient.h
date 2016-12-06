//
//  TabrisHTTPClient.h
//  Tabris
//
//  Created by Jordi Böhme López on 10.06.13.
//  Copyright (c) 2013 EclipseSource. All rights reserved.
//

#import <Foundation/Foundation.h>

@class TabrisClient;

#define TabrisReachabilityDidChangeNotification @"com.eclipsesource.tabris.notifications.ReachabilityDidChange"
#define TabrisReachabilityDidChangeNotificationKey @"com.eclipsesource.tabris.notifications.ReachabilityDidChangeKey"

typedef enum {
    TabrisReachabilityStatusUnknown          = -1,
    TabrisReachabilityStatusNotReachable     = 0,
    TabrisReachabilityStatusReachableViaWWAN = 1,
    TabrisReachabilityStatusReachableViaWiFi = 2,
} TabrisReachabilityStatus;

@interface TabrisHTTPClient : NSObject

- (id)initWithURL:(NSURL *)url andClient:(TabrisClient *)client;
- (NSMutableURLRequest *)requestWithURL:(NSURL *)url;
- (NSOperation *)newGetJsonOperationWithSuccess:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response))success
                                        failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error))failure
                                      andOutput:(NSOutputStream *)outputStream;
- (NSOperation *)newPostJsonOperationWith:(NSString *)json
                                  success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response))success
                                  failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error))failure
                                andOutput:(NSOutputStream *)outputStream;
- (NSOperation *)newFileDownloadOperationWithFile:(NSURL *)from
                                               to:(NSURL *)to
                                          success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response))success
                                          failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error))failure
                                      andProgress:(void (^)(NSInteger totalBytesWritten, NSInteger totalBytesExpectedToWrite))progress;
- (NSOperation *)newFileUploadOperationWithFile:(NSURL *)file
                                             to:(NSString *)path
                                        success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response))success
                                        failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error))failure
                                    andProgress:(void (^)(NSInteger totalBytesWritten, NSInteger totalBytesExpectedToWrite))progress;
- (NSOperation *)newOperationWithRequest:(NSURLRequest *)request
                                 success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response))success
                                 failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error))failure
                               andOutput:(NSOutputStream *)outputStream;
- (NSOperation *)newOperationWithRequest:(NSURLRequest *)request
                                 success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSString *responseString))success
                                 failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error))failure
                             andProgress:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSInteger totalBytesWritten, NSInteger totalBytesExpectedToWrite))progress;
- (NSOperation *)newOperationFromOperation:(NSOperation *)operation
                                 success:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response))success
                                 failure:(void (^)(NSURLRequest *request, NSHTTPURLResponse *response, NSError *error))failure
                               andOutput:(NSOutputStream *)outputStream;
- (UIImage *)imageFromPath:(NSString *)path;
- (TabrisReachabilityStatus)reachabilityStatus;
- (void)deleteCookies;
- (void)clearCache;
- (void)cancelAllOperations;
- (void)reset;
- (NSURL *)relativeURLToServer:(NSString *)urlString;
@property (nonatomic,strong) NSURL *baseURL;
@property (nonatomic,strong) NSMutableDictionary *options;

@end
