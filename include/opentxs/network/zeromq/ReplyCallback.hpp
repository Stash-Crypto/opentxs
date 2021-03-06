// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENTXS_NETWORK_ZEROMQ_REPLYCALLBACK_HPP
#define OPENTXS_NETWORK_ZEROMQ_REPLYCALLBACK_HPP

#include "opentxs/Forward.hpp"

#include <functional>

#ifdef SWIG
// clang-format off
%ignore opentxs::network::zeromq::ReplyCallback::Factory;
%ignore opentxs::Pimpl<opentxs::network::zeromq::ReplyCallback>::Pimpl(opentxs::network::zeromq::ReplyCallback const &);
%ignore opentxs::Pimpl<opentxs::network::zeromq::ReplyCallback>::operator opentxs::network::zeromq::ReplyCallback&;
%ignore opentxs::Pimpl<opentxs::network::zeromq::ReplyCallback>::operator const opentxs::network::zeromq::ReplyCallback &;
%rename(assign) operator=(const opentxs::network::zeromq::ReplyCallback&);
%rename(ZMQReplyCallback) opentxs::network::zeromq::ReplyCallback;
%template(OTZMQReplyCallback) opentxs::Pimpl<opentxs::network::zeromq::ReplyCallback>;
// clang-format on
#endif  // SWIG

namespace opentxs
{
namespace network
{
namespace zeromq
{
class ReplyCallback
{
public:
    using ReceiveCallback = std::function<OTZMQMessage(const Message&)>;

    EXPORT static OTZMQReplyCallback Factory(ReceiveCallback callback);

    EXPORT virtual Pimpl<opentxs::network::zeromq::Message> Process(
        const Message& message) const = 0;

    EXPORT virtual ~ReplyCallback() = default;

protected:
    ReplyCallback() = default;

private:
    friend OTZMQReplyCallback;

    virtual ReplyCallback* clone() const = 0;

    ReplyCallback(const ReplyCallback&) = delete;
    ReplyCallback(ReplyCallback&&) = default;
    ReplyCallback& operator=(const ReplyCallback&) = delete;
    ReplyCallback& operator=(ReplyCallback&&) = default;
};
}  // namespace zeromq
}  // namespace network
}  // namespace opentxs
#endif
