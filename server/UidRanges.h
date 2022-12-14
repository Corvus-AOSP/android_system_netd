/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NETD_SERVER_UID_RANGES_H
#define NETD_SERVER_UID_RANGES_H

#include "android/net/INetd.h"

#include <sys/types.h>
#include <utility>
#include <vector>

namespace android {
namespace net {

class UidRanges {
public:
    static constexpr int SUB_PRIORITY_HIGHEST = 0;
    static constexpr int SUB_PRIORITY_LOWEST = 998;
    // "Special" value used for giving UIDs access to a network (by installing explicit and implicit
    // network rules) without automatically making that network default. This rule works in
    // conjunction with the other subpriorities, meaning that the network could still be configured
    // as the app's default using one of the lower values (0-998).
    // Note: SUB_PRIORITY_NO_DEFAULT *must* be SUB_PRIORITY_LOWEST + 1!
    static constexpr int SUB_PRIORITY_NO_DEFAULT = 999;

    UidRanges() {}
    UidRanges(const std::vector<android::net::UidRangeParcel>& ranges);

    bool hasUid(uid_t uid) const;
    const std::vector<UidRangeParcel>& getRanges() const;

    bool parseFrom(int argc, char* argv[]);
    std::string toString() const;

    void add(const UidRanges& other);
    void remove(const UidRanges& other);

    // check if 'mRanges' has uid overlap between elements.
    bool overlapsSelf() const;
    // check if this object has uid overlap with the input object.
    bool overlaps(const UidRanges& other) const;
    bool empty() const { return mRanges.empty(); }

  private:
    // Keep it sorted. The overlaps() implements binary search, which requires a sorted data.
    std::vector<UidRangeParcel> mRanges;
};

}  // namespace net
}  // namespace android

#endif  // NETD_SERVER_UID_RANGES_H
