//
//  NUSAVirtualAssistantController.h
//  MobileSpeechSDK
//
//  Created by Yan Tran on 11/20/18.
//  Copyright © 2018 Nuance Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NUSAVirtualAssistantControllerDelegate.h"

NS_ASSUME_NONNULL_BEGIN


/**
 @brief The primary object for the DMVA
 */
@interface NUSAVirtualAssistantController : NSObject
{
@protected
    __weak id<NUSAVirtualAssistantControllerDelegate> delegate;
}

//////////////////////////////////////////////////////////////////////////////////////////
/// @name Properties
//////////////////////////////////////////////////////////////////////////////////////////

/** @brief NUSAVirtualAssistantController delegate.

 This delegate receives messages from the virtual assistant instance. Delegates must
 conform to the NUSAVirtualAsssistantController protocol. The delegate will not be
 retained.
 */
@property (nonatomic, weak) id<NUSAVirtualAssistantControllerDelegate> delegate;


/**
@brief Returns the single instance of the NUSAVirtualAssistantController.
 @return The pointer to the controller.
 */
+ (NUSAVirtualAssistantController*) sharedController;

/**
 @brief Initializes the Virtual Assistant. for the specified grammar model.
 
 Initializes the Virtual Assistant for the specified grammar model.  If the SpeechKit session is not open, the application type is not correct,  the DMVA state is not valid, or the parameter value is invalid the request will not be processed and an NUSAVirtualAssistantErrorCode value is returned.  Otherwise, the DMVA will continue to asynchronously validate the user license and initialize for the specified grammar model.  The state will be set to Opening and NUSAVirtualAssistantErrorCodeNoError   is returned. The DMVA will transition to the Opened state when it has asynchronous license and grammar checks have completed successfully.
 
 
 The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - openWithModel has been initiated successfully and the Dragon Medical Virtual Assistant is in the Opening state.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow an Open process to commence (either Opening or Closing)
 
 NUSAVirtualAssistantErrorCodeParameterError - model is null or an empty string, does not start with one of "Administrator", "Physician", or "Nurse".
 
 NUSAVirtualAssistantErrorCodeUnknownError - Process threw an unexpected exception
 
@param model The name of the grammar model to load.
@param options dictionary of objects containing optional parameters.

@return NUSAVirtualAssistantErrorCode
 
 */
- (NUSAVirtualAssistantErrorCode) openWithModel: (NSString*) model options: (nullable NSDictionary <NSString*, NSObject*>*) options;

/**
 @brief Closes the Virtual Assistant.
Closes the Virtual Assistant and frees up resources. It will abort the active dialog and removes any transactions that were scheduled.  Open needs to be called again once Close is called if you want to use the Virtual Assistant again.  Any active dialogs will be canceled. The DMVA will continue the closing process asynchronously and will transition to the Closed state when it is done closing.   If the DMVA is already in the Closing state the request will not be processed and NUSAVirtualAssistantErrorCodeApplicationStateError is returned.
 
 The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - close has completed successfully and the Dragon Medical Virtual Assistant has transitioned into the Closed state
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Attempt to close while in Closing State.
 
@return NUSAVirtualAssistantErrorCode
 */
- (NUSAVirtualAssistantErrorCode) close;

/**
 @brief Stops an active dialog.
 
 If there is an active dialog, the dialog will be canceled and the dialogResult method of the registered NUSAVirtualAssistantController delegate will be called.  The SDK will exit out of DMVA Mode and will return to its previous mode.  Any audio that was recorded while in DMVA Mode will be discarded.
 
 The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow a dialog to be aborted.
 
@return NUSAVirtualAssistantErrorCode:
 

 
 */
- (NUSAVirtualAssistantErrorCode) stopDialog;

/**
 @brief Send dialog text to the DMVA.
 
Sends text to the DMVA to start or continue a dialog.
 
 The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant will continue to process the request asynchronously.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError- Application is in a state which does not allow text to be sent.
 
 NUSAVirtualAssistantErrorCodeParameterError - The text parameter is invalid.
 

@param text The text to send to the DMVA for processing.

 @return NUSAVirtualAssistantErrorCode

 */
- (NUSAVirtualAssistantErrorCode) sendText: (NSString*) text;


/** @brief Uploads concept values for a dynamic concept.
 
 Asynchronously sets the list of literal-value pairs for a dynamic concept.  The specified concept will be overwritten with the contents of the new list for the current user.  This is meant to be used right after the Virtual Assistant has opened  so that the items in the concept are available for all the transactions.   Note that while the command call returns a status synchronously, the upload and processing by the Virtual Assistant server is not.   The registered NUSAVirtualAssistantControllerDelegate's uploadConceptResult method will be called when the upload has occurred.  Items will continue to persist in the Virtual Assistant after it has closed and be available for the current user in subsequent sessions until clearUploadedValuesForConcept is called.  Therefore, if it is not expected that the items will be valid beyond the current session, it may be advisable  to call clearUploadedValuesForConcept before closing Virtual Assistant session.  If you need to update a concept  for immediate use, use setInlineValuesForConcept instead.   If the Virtual Assistant is not open, the request will not be processed and false is returned.
 
 @param conceptName The name of the concept.
 
 @param conceptValuesJSON String representation of an array of JSON objects, where each JSON object contains a single key-value pair of a literal and its corresponding value.
 
 Here is an example value for items:
 @code
 [
 { "literal": "Susan", "value": "Susan Walker"},
 { "literal": "Timothy", "value": "Timothy Walker"},
 { "literal": "Tim", "value": "Timothy Walker"},
 { "literal": "Jonathan", "value": "Jonathan Walker"},
 ]
 @endcode
 
 
  The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant will continue to process the request asynchronously and will call the registered NUSAVirtualAssistantControllerDelegate's conceptResult method when it is finished.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError- Application is in a state which does not allow concept values to be uploaded.
 
 NUSAVirtualAssistantErrorCodeParameterError - The conceptName or conceptValuesJSON parameter is invalid.
 
@return  NUSAVirtualAssistantErrorCode
 
 
 */
- (NUSAVirtualAssistantErrorCode) uploadValuesForConcept: (NSString*) conceptName conceptValues:(NSString*) conceptValuesJSON;

/**
 @brief Uploads concept values for a dynamic concept.
 @param conceptName The name of the concept.
 @param conceptValuesJSON String representation of an array of JSON objects, where each JSON object contains a single key-value pair of a literal and its corresponding value.
 @param completionHandler The completionHandler block invoked when we get the response
 @return NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant will continue to process the request asynchronously and will call the registered NUSAVirtualAssistantControllerDelegate's conceptResult method when it is finished.
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow concept values to be uploaded.
 NUSAVirtualAssistantErrorCodeParameterError - The conceptName or conceptValuesJSON parameter is invalid.
 */

- (NUSAVirtualAssistantErrorCode)uploadValuesForConcept:(NSString*)conceptName
                                          conceptValues:(NSString*)conceptValuesJSON
                                  withCompletionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/** @brief Clears uploaded concept values for a dynamic concept.
 
 Asynchronously clears the specified concept where the items had been set by uploadValuesForConcept.  Note that while the command call returns a status synchronously, the processing of the request by the Virtual Assistant will be asynchronous.  The registered NUSAVirtualAssistantControllerDelegate's conceptResult method will be called when the request has been uploaded.
 
 
  The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant  will continue to process the request asynchronously and call the registered NUSAVirtualAssistantControllerDelegate's conceptResult method when it has finished.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow concept values to be uploaded.
 
 NUSAVirtualAssistantErrorCodeParameterError - The conceptName or conceptValues parameter is invalid.
 
@param conceptName The name of the concept.

@return NUSAVirtualAssistantErrorCode

 */
- (NUSAVirtualAssistantErrorCode) clearUploadedValuesForConcept: (NSString*) conceptName;

/**
 @brief Clears uploaded concept values asynchronously for a dynamic concept.
 @param conceptName The name of the concept.
 @param completionHandler The completionHandler block invoked when we get the response
 @return NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant  will continue to process the request asynchronously and call the registered NUSAVirtualAssistantControllerDelegate's conceptResult method when it has finished.
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow concept values to be uploaded.
 NUSAVirtualAssistantErrorCodeParameterError - The conceptName or conceptValues parameter is invalid.
*/

- (NUSAVirtualAssistantErrorCode)clearUploadedValuesForConcept:(NSString*)conceptName
                                         withCompletionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;


/**@brief Clears uploaded concept values for a dynamic concept.
 
 Asynchronously clears all dynamic concepts for a user that were set with the uploadValuesForConcept method.   Note that while the command call returns a status synchronously, the processing of the request by the Virtual Assistant will be asynchronous.  The registered NUSAVirtualAssistantControllerDelegate's conceptResult method will be called when the request has been uploaded.
 NUSAVirtualAssistantControllerDelegate's conceptResult method will be called when the request has been uploaded.
 
 
 The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant. DM Virtual Assistant  will continue to process the request asynchronously and call the registered NUSAVirtualAssistantControllerDelegate's conceptResult method when it has finished.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow concept values to be cleared.
 
 
@return NUSAVirtualAssistantErrorCode

 */
- (NUSAVirtualAssistantErrorCode) clearAllUploadedConceptValues;


/**@brief Sets inline concept values for dynamic concepts.
 
 Adds a list of literal-value pairs to a dynamic concept for immediate use.  This is meant to be used for a small number of items (50 or fewer) right before they are needed for a particular dialog.  The items in the concept will be available for recognition immediately following this call.  Use clearInlineValuesForConcept to clear the concept when the items are no longer needed, or the items will continue to be available until the Virtual Assistant closes.  Uploading a large number of items with this call will result in degraded performance.  If a concept needs to be overwritten with a large number of items, use uploadValuesForConcept instead.   If the Virtual Assistant is not open, the request will not be processed and NUSAVirtualAssistantErrorCodeApplicationStateError is returned.
 
 
  The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow concept values to be cleared.
 
 NUSAVirtualAssistantErrorCodeParameterError - The conceptName or conceptValues parameter is invalid.
 
 @param conceptName The name of the concept.
 
 @param conceptValuesJSON An array of JSON objects, where each JSON object contains a single key-value pair of a literal and its corresponding value.
 
 Here is an example value for items:
 @code
 [
 { "literal": "Susan", "value": "Susan Walker"},
 { "literal": "Timothy", "value": "Timothy Walker"},
 { "literal": "Tim", "value": "Timothy Walker"},
 { "literal": "Jonathan", "value": "Jonathan Walker"},
 ]
 @endcode
 @return NUSAVirtualAssistantErrorCode

 
 */
- (NUSAVirtualAssistantErrorCode) setInlineValuesForConcept: (NSString*) conceptName conceptValues:(NSString*) conceptValuesJSON;

/** @brief Clears inline concept values for a dynamic concept.
 
 Clears one immediate concept.  The concept is fully cleared once the call returns.   If the Virtual Assistant is not open, the request is ignored and NUSAVirtualAssistantErrorCodeApplicationStateError is returned.

 The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The concept was cleared of inline values.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow inline concept values to be cleared.
 
 NUSAVirtualAssistantErrorCodeParameterError - The conceptName parameter is invalid.
 
@param conceptName The name of the concept.

 @return NUSAVirtualAssistantErrorCode
 */

- (NUSAVirtualAssistantErrorCode) clearInlineValuesForConcept: (NSString*) conceptName;
/** @brief Starts a confirmation prompt.
 
 Initiates a confirmation prompt dialog. The microphone will enter DMVA mode.  The user will be expected to reply either 'Yes' or 'No'.  If the user responds 'yes', the dialogResult method will be called again with the task state set to "confirmed". Otherwise the task state will be "aborted".  The Virtual Assistant will not provide TTS or text prompts for this dialog, so it will be up to the integrator to generate the prompts, call startSpeaking, and wait for didStopSpeaking to be called before calling promptForConfirmation.

Note:  Calling PromptForConfirmation() will cause any active dialog to be aborted.
 
 
 The return value is one of the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow PromptForConfirmation to be called.
 
 
@return NUSAVirtualAssistantErrorCode

 */
- (NUSAVirtualAssistantErrorCode) promptForConfirmation;

/** @brief Starts a Free text prompt.
 
 Initiates Prompt for Free Text dialog.
 
The microphone will enter DMVA mode.   After speaker speaks, the dialogResult method will be called and the JSON result for the intent dmvaPromptForFreeText will have a FREE_TEXT concept populated with the text of the recognized speech from the speaker.  The Virtual Assistant will not provide TTS or text prompts for this dialog, so it will be up to the integrator to generate the prompts, call startSpeaking, and wait for didStopSpeaking to be called before calling promptForFreeText.

 
 The return value is one the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow PromptForFreeText to be called.
 
 @return NUSAVirtualAssistantErrorCode

 */
- (NUSAVirtualAssistantErrorCode) promptForFreeText;

/** @brief Initiates a prompt dialog to make a choice.
 
Starts a dialog where the user is prompted to make a choice.  The microphone will enter DMVA mode.  The items parameter holds a JSON string containing key-value pairs of literals and their corresponding values.  The Virtual Assistant will be waiting for the speaker to say one of the literals from the items parameter.  When the speaker says one of the choices, the dialogResult method will be called  and the JSON result for dmvaPromptForChoice will have a CHOICE concept populated with the value that corresponds to the literal that the speaker provided.  The Virtual Assistant will not provide TTS or text prompts for this dialog, so it will be up to the integrator to generate the prompts, call startSpeaking, and wait for didStopSpeaking to be called before calling promptForChoice.


 
The return value is one the following:
 
 NUSAVirtualAssistantErrorCodeNoError - The request has been accepted by DM Virtual Assistant.
 
 NUSAVirtualAssistantErrorCodeApplicationStateError - Application is in a state which does not allow text transactions.
 
 NUSAVirtualAssistantErrorCodeParameterError - The text parameter is invalid.
 
Here is an example value for items:
@code
[
 { "literal": "save", "value": "save"},
 { "literal": "delete", "value": "delete"},
 ]
@endcode
@param items - a string representing a json array of objects containing "literal" and "value" properties.

@return NUSAVirtualAssistantErrorCode
 */
- (NUSAVirtualAssistantErrorCode) promptForChoice: (NSString*) items;

@end

NS_ASSUME_NONNULL_END
