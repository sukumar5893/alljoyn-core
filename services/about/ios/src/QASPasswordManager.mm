/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#import "QASPasswordManager.h"
#import "QASConvertUtil.h"
#import "alljoyn/PasswordManager.h"

@implementation QASPasswordManager

/**
 Set credentials used for the authentication of thin clients.
 @param authMechanism  Mechanism to use for authentication.
 @param password       Password to use for authentication.
 @return   Returns ER_OK if the credentials was successfully set.
 */
+ (QStatus)setCredentialsWithAuthMechanism:(NSString *)authMechanism andPassword:(NSString *)password
{
	return (ajn::PasswordManager::SetCredentials(([QASConvertUtil convertNSStringToQCCString:(authMechanism)]), ([QASConvertUtil convertNSStringToQCCString:(password)])));
}

/** internal Get the password set by the user/app
 @return Returns the password set by the user/app.
 */
+ (NSString *)password
{
	return ([QASConvertUtil convertQCCStringtoNSString:(ajn::PasswordManager::GetPassword())]);
}

/**
 Get the authMechanism set by the user/app
 @return Returns the authMechanism set by the user/app.
 */
+ (NSString *)authMechanism
{
	return ([QASConvertUtil convertQCCStringtoNSString:(ajn::PasswordManager::GetAuthMechanism())]);
}

@end