// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENTXS_NETWORK_ZEROMQ_ZAP_CALLBACK_HPP
#define OPENTXS_NETWORK_ZEROMQ_ZAP_CALLBACK_HPP

#include "opentxs/Forward.hpp"

#include <functional>

namespace opentxs
{
namespace network
{
namespace zeromq
{
namespace zap
{
class Callback
{
public:
    using ReceiveCallback = std::function<OTZMQZAPReply(const Request&)>;

    enum class Policy : bool { Accept = true, Reject = false };

    EXPORT static OTZMQZAPCallback Factory(
        const std::string& domain,
        const ReceiveCallback& callback);
    EXPORT static OTZMQZAPCallback Factory();

    EXPORT virtual OTZMQZAPReply Process(const Request& request) const = 0;
    EXPORT virtual bool SetDomain(
        const std::string& domain,
        const ReceiveCallback& callback) const = 0;
    EXPORT virtual bool SetPolicy(const Policy policy) const = 0;

    EXPORT virtual ~Callback() = default;

protected:
    Callback() = default;

private:
    friend OTZMQZAPCallback;

    virtual Callback* clone() const = 0;

    Callback(const Callback&) = delete;
    Callback(Callback&&) = default;
    Callback& operator=(const Callback&) = delete;
    Callback& operator=(Callback&&) = default;
};
}  // namespace zap
}  // namespace zeromq
}  // namespace network
}  // namespace opentxs
#endif
