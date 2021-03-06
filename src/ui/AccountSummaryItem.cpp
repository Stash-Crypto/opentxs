// Copyright (c) 2018 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "stdafx.hpp"

#include "opentxs/api/client/Issuer.hpp"
#include "opentxs/api/client/Manager.hpp"
#include "opentxs/api/storage/Storage.hpp"
#include "opentxs/api/Wallet.hpp"
#include "opentxs/core/contract/UnitDefinition.hpp"
#include "opentxs/core/Identifier.hpp"
#include "opentxs/core/Lockable.hpp"
#include "opentxs/network/zeromq/Context.hpp"
#include "opentxs/network/zeromq/FrameIterator.hpp"
#include "opentxs/network/zeromq/FrameSection.hpp"
#include "opentxs/network/zeromq/Frame.hpp"
#include "opentxs/network/zeromq/ListenCallback.hpp"
#include "opentxs/network/zeromq/Message.hpp"
#include "opentxs/network/zeromq/SubscribeSocket.hpp"
#include "opentxs/ui/AccountSummaryItem.hpp"

#include "InternalUI.hpp"
#include "Row.hpp"

#include <atomic>

#include "AccountSummaryItem.hpp"

template class opentxs::SharedPimpl<opentxs::ui::AccountSummaryItem>;

namespace opentxs
{
ui::implementation::IssuerItemRowInternal* Factory::AccountSummaryItem(
    const ui::implementation::IssuerItemInternalInterface& parent,
    const api::client::Manager& api,
    const network::zeromq::PublishSocket& publisher,
    const ui::implementation::IssuerItemRowID& rowID,
    const ui::implementation::IssuerItemSortKey& sortKey,
    const ui::implementation::CustomData& custom)
{
    return new ui::implementation::AccountSummaryItem(
        parent, api, publisher, rowID, sortKey, custom);
}
}  // namespace opentxs

namespace opentxs::ui::implementation
{
AccountSummaryItem::AccountSummaryItem(
    const IssuerItemInternalInterface& parent,
    const api::client::Manager& api,
    const network::zeromq::PublishSocket& publisher,
    const IssuerItemRowID& rowID,
    const IssuerItemSortKey& sortKey,
    const CustomData& custom)
    : AccountSummaryItemRow(parent, api, publisher, rowID, true)
    , account_id_{std::get<0>(row_id_).get()}
    , currency_{std::get<1>(row_id_)}
    , balance_{extract_custom<Amount>(custom)}
    , name_{sortKey}
    , contract_{api_.Wallet().UnitDefinition(
          api_.Storage().AccountContract(account_id_))}
{
}

std::string AccountSummaryItem::DisplayBalance() const
{
    if (false == bool(contract_)) {
        eLock lock(shared_lock_);
        contract_ = api_.Wallet().UnitDefinition(
            api_.Storage().AccountContract(account_id_));
    }

    sLock lock(shared_lock_);

    if (contract_) {
        const auto amount = balance_.load();
        std::string output{};
        const auto formatted =
            contract_->FormatAmountLocale(amount, output, ",", ".");

        if (formatted) { return output; }

        return std::to_string(amount);
    }

    return {};
}

std::string AccountSummaryItem::Name() const
{
    sLock lock(shared_lock_);

    return name_;
}

void AccountSummaryItem::reindex(
    const IssuerItemSortKey& key,
    const CustomData& custom)
{
    balance_.store(extract_custom<Amount>(custom));
    eLock lock(shared_lock_);
    name_ = key;
}
}  // namespace opentxs::ui::implementation
