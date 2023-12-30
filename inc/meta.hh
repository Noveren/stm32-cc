#pragma once

namespace meta {
    template <bool, typename T=void>
    struct enable_if { };

    template <typename T>
    struct enable_if<true, T> {
        using type = T;
    };

    template <typename T, typename U>
    struct is_same {
        static constexpr bool value = false;
    };

    template <typename T>
    struct is_same<T, T> {
        static constexpr bool value = true;
    };
}