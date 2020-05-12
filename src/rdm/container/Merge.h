#pragma once

#include <algorithm>

namespace rdm {

/**
 * 功能类似 std::merge 函数
 * 不同的地方，
 */
template<typename InputIt1, typename InputIt2, typename OutputIt, typename Compare>
OutputIt merge(
        InputIt1 first1,
        InputIt1 last1,
        InputIt2 first2,
        InputIt2 last2,
        OutputIt d_first,
        Compare comp) {
    for (; first1 != last1; ++d_first) {
        if (first2 == last2) {
            return std::copy(first1, last1, d_first);
        }
        if (comp(*first2, *first1)) {
            *d_first = *first2;
            ++first2;
        } else {
            *d_first = *first1;
            ++first1;
        }
    }
    return std::copy(first2, last2, d_first);
}

template<class InputIt1, class InputIt2, class OutputIt>
OutputIt merge(
        InputIt1 first1,
        InputIt1 last1,
        InputIt2 first2,
        InputIt2 last2,
        OutputIt d_first) {
    for (; first1 != last1; ++d_first) {
        if (first2 == last2) {
            return std::copy(first1, last1, d_first);
        }
        if (*first2 < *first1) {
            *d_first = *first2;
            ++first2;
        } else {
            *d_first = *first1;
            ++first1;
        }
    }
    return std::copy(first2, last2, d_first);
}

} // namespace rdm