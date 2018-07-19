// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENTXS_CORE_CRYPTO_OTCALLER_HPP
#define OPENTXS_CORE_CRYPTO_OTCALLER_HPP

#include "opentxs/Forward.hpp"

#include "opentxs/core/crypto/OTPassword.hpp"

#include <cstdint>

namespace opentxs
{
class OTCaller
{
protected:
    OTPassword m_Password;  // The password will be stored here by the Java
    // dialog, so that the C callback can retrieve it and
    // pass it to OpenSSL
    OTPassword m_Display;  // A display string is set here before the Java
                           // dialog
                           // is shown. (OTPassword used here only for
                           // convenience.)

    OTCallback* _callback{nullptr};

public:
    OTCaller()
        : _callback(nullptr)
    {
    }
    EXPORT ~OTCaller();

    EXPORT bool GetPassword(OTPassword& theOutput) const;  // Grab the password
                                                           // when it is needed.
    EXPORT void ZeroOutPassword();  // Then ZERO IT OUT so copies aren't
                                    // floating
                                    // around...

    EXPORT const char* GetDisplay() const;
    EXPORT void SetDisplay(const char* szDisplay, std::int32_t nLength);

    EXPORT void delCallback();
    EXPORT void setCallback(OTCallback* cb);
    EXPORT bool isCallbackSet() const;

    EXPORT void callOne();  // Asks for password once. (For authentication when
                            // using the Nym's private key.)
    EXPORT void callTwo();  // Asks for password twice. (For confirmation during
                            // nym creation and password change.)
};
}  // namespace opentxs
#endif  // OPENTXS_CORE_CRYPTO_OTCALLER_HPP
