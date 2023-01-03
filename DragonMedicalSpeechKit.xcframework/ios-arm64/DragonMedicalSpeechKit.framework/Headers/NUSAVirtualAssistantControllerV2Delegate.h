//
//  NUSAVirtualAssistantControllerV2Delegate.h
//  DragonMedicalSpeechKit
//
//  Copyright © 2021 Nuance Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NUSAVirtualAssistantTypesV2.h"

/** @brief DMVA controller delegate.
 
 This is the delegate which is used for all callbacks to the DMVA client.  It is registered with the NUSAVirtualAssistantControllerV2 instance. All the methods in the delegate are optional.*/

@protocol NUSAVirtualAssistantControllerV2Delegate <NSObject>
@optional

/** @brief Handles Virtual Assistant events.
 
 This delegate method is used to notify the integrator, of different events received from the DMVA, after a request has been processed. e.g. "Hey Dragon, show me CBC". On recognizing WuW, SDK will send the begin speech audio, to its response, and get vaActive event from the DMVA. It pass the same to the integrator. After this VA command has been processed on the DMVA, vaComplete along with JSON response is received from the DMVA, which is passed to the integrator using this delegate method.
 
 @param event  This is an object which has event description which includes - event type & an additional result message.

 */

- (void)vaEventGenerated:(VAEvent * _Nonnull)event;


/** @brief Receives the state of the Virtual Assistant.
 
 Whenever the state of VA Controller changes this method is called to notify the integrator of the same. This method is called on the delegate provided by the integrator, using the set delegate call.
 
@param state State indicate the state of VA Controller, initialized or closed.
 
@param resultCode It is the result code indicating the result encountered in opening or closing the VA Controller<br>
 
 VAResultCode Values:<br>
 
 VAResultCodeSuccess - The request completed successfully.<br>
 
 VAResultCodeBadRequestError - Invalid parameters were provided to server<br>
 
 VAResultCodeInternalServerError - The server encountered a problem. <br>
 
 VAResultCodeNetworkError - There was a problem with the network or the server is unavailable.<br>
 
@param message An additional result message along with result code providing additional information about the result code and state.
 */

- (void)vaSessionStateChanged:(VAState)state
             resultCode:(VAResultCode)resultCode
               message:(nullable NSString *)message;

@end
