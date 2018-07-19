// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENTXS_NETWORK_ZEROMQ_PULLSOCKET_IMPLEMENTATION_HPP
#define OPENTXS_NETWORK_ZEROMQ_PULLSOCKET_IMPLEMENTATION_HPP

#include "opentxs/Forward.hpp"

#include "opentxs/network/zeromq/PullSocket.hpp"

#include "Receiver.hpp"
#include "Socket.hpp"

namespace opentxs::network::zeromq::implementation
{
class PullSocket : virtual public zeromq::PullSocket, public Socket, Receiver
{
public:
    bool Start(const std::string& endpoint) const override;

    ~PullSocket();

private:
    friend opentxs::network::zeromq::PullSocket;
    typedef Socket ot_super;

    const bool client_{false};
    const ListenCallback& callback_;

    PullSocket* clone() const override;
    bool have_callback() const override;

    void process_incoming(const Lock& lock, Message& message) override;

    PullSocket(
        const zeromq::Context& context,
        const bool client,
        const zeromq::ListenCallback& callback,
        const bool startThread);
    PullSocket(
        const zeromq::Context& context,
        const bool client,
        const zeromq::ListenCallback& callback);
    PullSocket(const zeromq::Context& context, const bool client);
    PullSocket() = delete;
    PullSocket(const PullSocket&) = delete;
    PullSocket(PullSocket&&) = delete;
    PullSocket& operator=(const PullSocket&) = delete;
    PullSocket& operator=(PullSocket&&) = delete;
};
}  // namespace opentxs::network::zeromq::implementation
#endif  // OPENTXS_NETWORK_ZEROMQ_PULLSOCKET_IMPLEMENTATION_HPP
