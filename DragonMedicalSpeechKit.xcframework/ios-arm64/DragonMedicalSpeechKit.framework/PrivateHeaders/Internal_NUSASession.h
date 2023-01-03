//
//  Internal_NUSASession.h
//  Dragon Medical SpeechKit
//
//  Copyright (c) 2014 Nuance Communications, Inc. All rights reserved.
//
//  SDK version: 0.0.0.0
//

#import <Foundation/Foundation.h>
#import "Internal_NUSATypes.h"
#import "NUSASession.h"
#import "Internal_NUSASessionDelegate.h"
#import "Internal_NMVirtualAssistantAudioDelegate.h"
#import <WebKit/WebKit.h>

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/** @brief NUSASession extension for internal use only.
 
	@xmlonly<nmFramework>NuanceSpeechAnywhere</nmFramework>@endxmlonly
	@since 1.6 SR9
 
	This interface adds functionality for internal use only.
 */
@interface Internal_NUSASession : NUSASession {
    BOOL guiEnabled;
}
NS_ASSUME_NONNULL_BEGIN
//////////////////////////////////////////////////////////////////////////////////////////
/// @name Properties
//////////////////////////////////////////////////////////////////////////////////////////

/** @brief Specifies whether to enable the Nuance GUI.
	@since 1.6 SR9
 
    When set to NO, SAS GUI element are disabled.
    This affects the red border around the speech-enabled controls during recording, the flame inside the speech-enabled controls and the speech bar,
    and the hosted view will not be displayed if no custom web view is set.
    Must be set before the first vui controller is created and before the first session is opened.
    Default value: YES
*/
@property (nonatomic, assign) BOOL guiEnabled;

/**	@brief Enable Correction Mode
	@since 3.2

	bool to turn on Correction Mode--enables the correction commands and UI.
	Default value: NO, YES if guiEnabled is NO
*/
@property (nonatomic) bool correctionModeEnabled;

/** @brief NUSASessionDelegateInternal delegate.
	@since 1.6 SR9
 
	This delegate receives messages from the session instance. Delegates must conform to the Internal_NUSASessionDelegate protocol.
*/
@property (nonatomic, assign) id<Internal_NUSASessionDelegate> delegateInternal;

/** @brief Set a custom web view for displaying WCIS/help/... content.
	@since 1.6 SR13
 
    If no web view is set for any of the content pages, the builtin webview is used.
    If no web view is set for one of the content pages, the first one (alphabetically) is used as default.
*/

@property (nonatomic, assign) id<Internal_NMVirtualAssistantAudioDelegate> vaAudioDelegate;

- (void)setWebView: (WKWebView*)webView forContent: (NSString*)content;

/** @brief Show view with specified content.
	@since 1.6 SR13
 
    Displays a web view with specified content, either using builtin full screen web view with speechbar or the web view specified via property setWebView:forContent:.
    sessionDidReceiveShowView: of Internal_NUSASessionDelegate is called in response when the html page is received from the server.
 
    @param content content to be displayed, see Internal_NUSATypes.h for possible values
*/
- (void) showView: (NSString*) content;

/** @brief Hide WCIS/help/... view.
	@since 1.6 SR13
 
    Must be called to notify SAS that the web view for displaying WCIS/help/... has been closed.
    sessionDidReceiveHideView of Internal_NUSASessionDelegate is called in response.
*/
- (void) hideView;

/** @brief Deprecated, Set a custom CSS for displaying WCIS content.
    @deprecated As of release 4.1
 
    Must be called before session is opened.
 
    @param cssContent	content of custom CSS
*/

- (void) setCustomCSS: (NSString*) cssContent DEPRECATED_MSG_ATTRIBUTE("A new HostedView customization feature is available");

/** @brief Sets the specified value to a property having the specified name
    @since 3.0 SR7
 
    @param name  The property name
    @param value The property value
*/
- (void) setPropertyWithName: (NSString*) name andValue: (NSString*) value;

/** @brief Navigates to the next embedded field in the current edit control
 @since 3.1
 */
- (void) selectNextEmbeddedField;

/** @brief Navigates to the previous embedded field in the current edit control
 @since 3.1
 */
- (void) selectPreviousEmbeddedField;

/** @brief Navigates to the first embedded field in the current edit control
 @since 3.1
 */
- (void) selectFirstEmbeddedField;

/** @brief Navigates to the last embedded field in the current edit control
 @since 3.1
 */
- (void) selectLastEmbeddedField;

/** @brief Accept default value of all embedded fields in an edit control
 @since 3.1
 */
- (void) acceptDefaults;

/** @brief Accept default value of single embedded field
 @since 3.1
 */
- (void) fieldComplete;

/** @brief For Clock sync testing
 @since 3.?
 */
- (void) syncClocks;

/** @brief For enable Theia testing
 @since 3.?
 */
- (void) enableTheia:(BOOL) enabled;

/** @brief Enable DMVA
 @since 3.?
 */
- (void) enableDMVA:(BOOL) enabled;

/** @brief is DMVA enabled?
 @since 3.?
 */
- (BOOL) isDMVAEnabled;

/** @brief For Set Client Mode
 @since 3.?
 */
- (void) setClientMode:(NSUInteger) value;

/** @brief For get current session id
 @since 3.?
 */
- (NSString*) currentSessionId;

/** @brief For PowerMic Mobile (Theia) to send button events
 @since 3.?
 */
- (void) sendEventToTargetClient:(int) buttonEvent;

/** @brief For start configuration retrieval.
 @since 3.?
 */
- (void) startConfigRetrieval:(nonnull NSString*) partnerToken;

/** @brief For start configuration retrieval with default UI.
 @since 3.?
 */
- (void) startDefaultConfigRetrieval:(nonnull UIViewController*) parentVC partnerToken:(nonnull NSString*) partnerToken;

/** @brief For cancel configuration retrieval.
 @since 3.?
 */
- (void) cancelConfigRetrieval;

/** @brief For share configuration.
 @since 3.?
 */
- (void) shareConfiguration:(nonnull NSString*) identifier;

/** @brief For sending client logs to DMS.
 @since 3.?
 */
- (void) sendClientLogMessage:(nonnull NSString*)message className:(nonnull NSString*)className methodName:(nonnull NSString*)methodName sourceLine:(UInt32)sourceLine;

- (void) abortPendingAudio;

/** @brief For starting VA mode without wakeup word
 @since 3.?
 */
- (BOOL) startVARecordingWithoutWakeupWord: (NSError * _Nullable*_Nullable) outError checkTTSState: (BOOL) checkTTSState;

NS_ASSUME_NONNULL_END
@end

