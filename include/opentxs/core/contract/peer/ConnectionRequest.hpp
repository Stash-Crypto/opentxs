// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPENTXS_CORE_CONTRACT_PEER_CONNECTIONREQUEST_HPP
#define OPENTXS_CORE_CONTRACT_PEER_CONNECTIONREQUEST_HPP

#include "opentxs/Forward.hpp"

#include "opentxs/core/contract/peer/PeerRequest.hpp"

namespace opentxs
{

class ConnectionRequest : public PeerRequest
{
private:
    typedef PeerRequest ot_super;
    friend class PeerRequest;

    proto::ConnectionInfoType connection_type_;

    proto::PeerRequest IDVersion(const Lock& lock) const override;

    ConnectionRequest(
        const api::Wallet& wallet,
        const ConstNym& nym,
        const proto::PeerRequest& serialized);
    ConnectionRequest(
        const api::Wallet& wallet,
        const ConstNym& nym,
        const Identifier& recipientID,
        const proto::ConnectionInfoType type,
        const Identifier& serverID);
    ConnectionRequest() = delete;

public:
    ~ConnectionRequest() = default;
};
}  // namespace opentxs

#endif
