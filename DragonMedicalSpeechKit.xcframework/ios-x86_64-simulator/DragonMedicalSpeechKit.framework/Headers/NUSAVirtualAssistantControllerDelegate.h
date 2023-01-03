//
//  NUSAVirtualAssistantControllerDelegate.h
//  MobileSpeechSDK
//
//  Created by Yan Tran on 11/20/18.
//  Copyright © 2018 Nuance Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NUSAVirtualAssistantTypes.h"

/** @brief DMVA controller delegate.
 
 This is the delegate which is used for all callbacks to the DMVA client.  It is registered with the NUSAVirtualAssistantController instance through the openWithModel method.  All the methods in the delegate are optional.*/
@protocol NUSAVirtualAssistantControllerDelegate <NSObject>
@optional
/** @brief Handles dialog results.
 
 This is called when the DMVA wants to send dialog results to the client.
 
 @param result A string containing json that follows the format described in the section Dialog Result Format.
 
 @param errorCode  The error code<br>
 
 NUSAVirtualAssistantErrorCode Values:<br>
 
 NUSAVirtualAssistantErrorCodeNoError - The request completed successfully.<br>
 
 NUSAVirtualAssistantErrorCodeConfigurationError - Invalid parameters were provided to server.<br>
 
 NUSAVirtualAssistantErrorCodeServerError - The server encountered a problem.<br>
 
 NUSAVirtualAssistantErrorCodeNetworkError - There was a problem with the network or the server is unavailable.<br>
 
 @param message  A description of the status that for logging and debugging.  The information in the message is not appropriate for presentation to the speaker.
 */
- (void) dialogResult: (NSString*) result errorCode : (NUSAVirtualAssistantErrorCode) errorCode message: (NSString*) message;

/** @brief Receives the state of the Virtual Assistant.
 
 A NUSAVirtualAssistantErrorCodeNoError value will be given when the Virtual Assistant has encountered a unrecoverable error.  When this happens the state will be Closed.
 
@param errorCode The status code<br>
 
 NUSAVirtualAssistantErrorCode Values:<br>
 
 NUSAVirtualAssistantErrorCodeNoError - The request completed successfully.<br>
 
 NUSAVirtualAssistantErrorCodeConfigurationError - Invalid parameters were provided to server<br>
 
 NUSAVirtualAssistantErrorCodeServerError - The server encountered a problem. <br>
 
 NUSAVirtualAssistantErrorCodeNetworkError - There was a problem with the network or the server is unavailable.<br>
 
@param message A description of the status that for logging and debugging.  The information in the message is not appropriate for presentation to the speaker.
 */
- (void) stateChanged:(NUSAVirtualAssistantState) state errorCode: (NUSAVirtualAssistantErrorCode) errorCode message: (NSString*) message;

/** @brief Receives concept upload results.
 
This is called when a concept upload or clear call has been received and processed by the DMVA.
@param errorCode  The error code

@param message A description of the status that for logging and debugging.  The information in the message is not appropriate for presentation to the speaker.*/

- (void) conceptResult:(NUSAVirtualAssistantErrorCode) errorCode message: (NSString*) message;

/** @brief Received when the Virtual Assistant has begun a speech conversation.
 */
-(void) didStartDialog;

/** @brief Received when the Virtual Assistant has begun a speech conversation.
 */

-(void) didStopDialog;

@end

