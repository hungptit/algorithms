#pragma once

#include <algorithm>
#include <string>

namespace cci {
    int edit_distance(const char *beg1, const char *end1, const char *beg2,
                      const char *end2) {
        if (beg1 == end1) return (end2 - beg2);
        if (beg2 == end2) return (end1 - beg1);
        if (*beg1 == *beg2)
            return edit_distance(beg1 + 1, end1, beg2 + 1, end2);
        return 1 +
               std::min(edit_distance(beg1 + 1, end1, beg2 + 1, end2),
                        std::min(edit_distance(beg1 + 1, end1, beg2, end2),
                                 edit_distance(beg1, end1, beg2 + 1, end2)));
    }

    template <typename Iter>
    int edit_distance1(Iter beg1, Iter end1, Iter beg2, Iter end2) {
        if (beg1 == end1) return (end2 - beg2);
        if (beg2 == end2) return (end1 - beg1);
        if (*beg1 == *beg2)
            return edit_distance1(beg1 + 1, end1, beg2 + 1, end2);
        return 1 +
               std::min(edit_distance1(beg1 + 1, end1, beg2 + 1, end2),
                        std::min(edit_distance1(beg1 + 1, end1, beg2, end2),
                                 edit_distance1(beg1, end1, beg2 + 1, end2)));
    }
} // namespace cci
