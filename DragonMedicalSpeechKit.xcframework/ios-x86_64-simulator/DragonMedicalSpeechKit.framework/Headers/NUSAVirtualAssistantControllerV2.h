//
//  NUSAVirtualAssistantControllerV2.h
//  DragonMedicalSpeechKit
//
//  Copyright © 2021 Nuance Communications, Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "NUSAVirtualAssistantControllerV2Delegate.h"

NS_ASSUME_NONNULL_BEGIN

/**
 @brief The primary object for the DMVA
 */
@interface NUSAVirtualAssistantControllerV2 : NSObject
{
@protected
    __weak id<NUSAVirtualAssistantControllerV2Delegate> delegate;
}

//////////////////////////////////////////////////////////////////////////////////////////
/// @name Properties
//////////////////////////////////////////////////////////////////////////////////////////

/** @brief NUSAVirtualAssistantControllerV2 delegate.

 This delegate receives messages from the virtual assistant instance. Delegates must
 conform to the NUSAVirtualAsssistantControllerV2 protocol. The delegate will not be
 retained.
 */

@property (nonatomic, weak) id<NUSAVirtualAssistantControllerV2Delegate> delegate;


/**
@brief Returns the single instance of the NUSAVirtualAssistantControllerV2.
 @return The pointer to the controller.
 */

+ (NUSAVirtualAssistantControllerV2*) sharedController;

/**
 @brief Open the Virtual Assistant, for the specified grammar model.
 
 Open the Virtual Assistant for the specified grammar model. If the SpeechKit session is not open, the application type is not correct, the DMVA state is not valid, or the parameter value is invalid the request will not be processed and VAResultCode value is returned. Otherwise, the DMVA will continue to asynchronously validate the user license and initialize for the specified grammar model. The state will be set to Opening and VAResultCodeSuccess is returned. The DMVA will transition to the Opened state when it has license and grammar checks have completed successfully.
 
 The return value is one of the following:
 
 VAResultCodeSuccess - openVA has been initiated successfully and the Dragon Medical Virtual Assistant is in the Opening state.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
 VAResultCodeApplicationStateError - Application is in a state which does not allow an Open process to commence (either Opening or Closing).
 
 VAResultCodeBadRequestError - A bad request to server, like Model is null or an empty string, does not start with one of "Administrator", "Physician", or "Nurse".
 
 VAResultCodeInternalSDKError - Process threw an unexpected exception.
 
@param model The name of the grammar model to load.
 
@param options Dictionary of objects containing optional parameters.

@return VAResultCode
 */

- (VAResultCode) openVA: (nonnull NSString*) model options: (nullable NSDictionary <NSString*, NSObject*>*) options;

/**
@brief Closes the Virtual Assistant.
 Closes the Virtual Assistant and frees up resources. openVA needs to be called again, once closeVA is called, and if you want to use the Virtual Assistant again.  The DMVA will continue the closing process asynchronously and will transition to the Closed state when it is done closing. If the DMVA is already in the Closing state, the request will not be processed and VAResultCodeApplicationStateError is returned.
 
 The return value is one of the following:
 
 VAResultCodeSuccess - Close has completed successfully and the Dragon Medical Virtual Assistant has transitioned into the Closed state.
 
 VAResultCodeApplicationStateError - Attempt to close while in Closing State.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
@return VAResultCode
 */

- (VAResultCode) closeVA;

/**
@brief Stops an active VA state.
 
 This API aborts the ongoing VA requests like prompt etc and returns back the microphone to previous mode. Any audio that was recorded while in VA Mode will be discarded.
 
 The return value is one of the following:
 
 VAResultCodeSuccess - The request has been accepted by DM Virtual Assistant.
 
 VAResultCodeApplicationStateError - Application is in a state which does not allow a VA Active state to be aborted.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
@return VAResultCode:
 */

- (VAResultCode) stopVA;

/**
@brief Send text to the DMVA.
 
 Sends text to the DMVA to start a VA request.
 
 The return value is one of the following:
 
 VAResultCodeSuccess - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant will continue to process the request asynchronously.
 
 VAResultCodeApplicationStateError- Application is in a state which does not allow text to be sent.
 
 VAResultCodeBadRequestError - The text parameter is invalid.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
@param text The text to send to the DMVA for processing.

@return VAResultCode
 */

- (VAResultCode) sendText: (nonnull NSString*) text;


/**
 @brief Uploads entity values for a dynamic entity.
 
 This API uploads dynamic entity values to the DMVA server. These values are used as part of VA commands. e.g. Call Dr. Jones. "Dr. Jones" is not part of the grammar but a dynamic entity value upload using this API. A call to this method returns immediately and the values are uploaded asynchronously. Once the upload completes, completion handler passed as part of the parameter is called.
 
 The return value is one of the following:
 
 VAResultCodeSuccess - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant will continue to process the request asynchronously.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
 VAResultCodeBadRequestError - The entityName or entityValuesJSON parameter is invalid.
 
 @param entityName The name of the entity.
 
 @param entityValuesJSON String representation of an array of JSON objects, where each JSON object contains a single key-value pair of a literal and its corresponding value.
 
 @param completionHandler This is the block to be invoked once the dynamic data for the given entity is uploaded. This parameter can be null if the integrator doesn't require a response to their upload request. No other delegate method will be invoked.
 
 @return VAResultCode
 */

- (VAResultCode)uploadEntityValues:(nonnull NSString*)entityName
                         entityValues:(nonnull NSString*)entityValuesJSON
                withCompletionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;


/**
 @brief Clears uploaded entity values asynchronously for a dynamic entity.
 
 This API clears the uploaded dynamic entity values. A call to this method returns immediately and the clear request is sent asynchronously. Once the response is received, the completion handler passed as part of the parameter is called.
 
 The return value is one of the following:
 
 VAResultCodeSuccess - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant will continue to process the request asynchronously.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.

 VAResultCodeBadRequestError - The entityName parameter is invalid.
 
 @param entityName The name of the entity.
 
 @param completionHandler This is the block to be invoked once the dynamic data for the given entity is cleared. This parameter can be null if the integrator doesn't require a response to their clear request. No other delegate method will be invoked.

 @return VAResultCode
 */

- (VAResultCode)clearUploadedEntityValues:(nonnull NSString*)entityName
                       withCompletionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;


/**@brief Clears all uploaded entity values.
 
 This API clears all the uploaded dynamic entity values for the current user. A call to this method returns immediately and the clear request is sent asynchronously. Once the response is received, the completion handler passed as part of the parameter is called.
 
 The return value is one of the following:
 
 VAResultCodeSuccess - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant will continue to process the request asynchronously.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
 @param completionHandler This is the block to be invoked once all the dynamic data uploaded earlier is cleared. This parameter can be null if the integrator doesn't require a response to their clear request. No other delegate method will be invoked.
 
 @return VAResultCode
 */

- (VAResultCode) clearAllUploadedEntityValues:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;


/** @brief Starts a confirmation prompt.
 
 This API starts the prompting for confirmation. This prompt is for confirmation i.e. YES or NO and their common synonyms. Call to this method returns immediately and a request is sent to the DMVA asynchronously. On receiving a successful response the microphone is put in the VA Active mode.
 
 The return value is one of the following:
 
 VAResultCodeSuccess - The request has been accepted by DM Virtual Assistant.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
 VAResultCodeApplicationStateError - Application is in a state which does not allow PromptForConfirmation to be called.
 
 VAResultCodeBadRequestError - When the parameters are not properly provided. This can happen in scenarios like items is not a correctly formatted JSON.
 
 @param prompt A prompt message to be played before the microphone turns to VA Active. This message is optional if integrator wants to play a message. This can be set to empty or null if not required.
 
 @return VAResultCode
 */

- (VAResultCode) promptForConfirmation:(nullable NSString *)prompt;


/** @brief Initiates Prompt for Free Text VA request.
 
 This API starts the prompting for free form text. This prompt is for a user to provide free form text, e.g. "to review CBC". Call to this method returns immediately and a request is sent to the DMVA asynchronously. On receiving a successful response the microphone is put in the VA Active mode.
 
 The return value is one the following:
 
 VAResultCodeSuccess - The request has been accepted by DM Virtual Assistant.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
 VAResultCodeApplicationStateError - Application is in a state which does not allow PromptForFreeText to be called.
 
 VAResultCodeBadRequestError - When the parameters are not properly provided. This can happen in scenarios like items is not a correctly formatted JSON.
 
 @param prompt A prompt message to be played before the microphone turns to VA Active. This message is optional if integrator wants to play a message. This can be set to empty or null if not required.
 
 @return VAResultCode
 */

- (VAResultCode) promptForFreeText:(nullable NSString *)prompt;

/** @brief Initiates a prompt to make a choice.
 
 This API starts the prompting for choice. This prompt is for user's choice. User makes a choice from the specified list of choices. This list of choices is provided in JSON format as part of the parameter. Call to this method returns immediately and a request is sent to the DMVA asynchronously. On receiving a successful response the microphone is put in the VA Active mode.

 The return value is one the following:
 
 VAResultCodeSuccess - The request has been accepted by DM Virtual Assistant.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
 VAResultCodeApplicationStateError - Application is in a state which does not allow text transactions.
 
 VAResultCodeBadRequestError - The text parameter is invalid.
 
 Here is an example value for items:
 
 @code
 [
  { "literal": "save", "value": "save"},
  { "literal": "delete", "value": "delete"},
 ]
 @endcode
 
 @param choices A string representing a json array of objects containing "literal" and "value" properties.

 @param prompt A prompt message to be played before the microphone turns to VA Active. This message is optional if integrator wants to play a message. This can be set to empty or null if not required.

 @return VAResultCode
 */

- (VAResultCode) promptForChoice:(nonnull NSString *)choices withPrompt:(nullable NSString *)prompt;


/** @brief Initiates a prompt for entities.
 
 This API starts the prompting for specified entities. Call to this method returns immediately and a request is sent to the DMVA asynchronously. On receiving a successful response the microphone is put in the VA Active mode.
 
 The return value is one the following:
 
 VAResultCodeSuccess - The request has been accepted by DM Virtual Assistant.
 
 VAResultCodeNoSessionError - Request can not be processed because session is not initialised.
 
 VAResultCodeApplicationStateError - Application is in a state which does not allow prompt for an entity.
 
 VAResultCodeBadRequestError - The text parameter is invalid.
 
 @param entities The list of entities, for which, integrator needs to provide the data for. e.g. with [ "TASK_DATE" ] passed as the parameter, the SDK is expecting the user to provide a data/time as input.
 
 @param prompt A prompt message to be played before the microphone turns to VA Active. This message is optional if integrator wants to play a message. This can be set to empty or null if not required.
 
 @param allow This parameter allows starting new intent when a prompt is already in progress.
 
 @return VAResultCode
 */

- (VAResultCode) promptForEntities:(nonnull NSArray *)entities withPrompt:(nullable NSString *)prompt allowNewIntent:(BOOL)allow;

@end

NS_ASSUME_NONNULL_END
