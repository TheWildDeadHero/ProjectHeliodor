#ifndef GUARD_TO_INT_TEMPLATE
#define GUARD_TO_INT_TEMPLATE

#include "port_types.hpp"

template <typename Enum>
const typename std::underlying_type<Enum>::type _to_int(Enum which) noexcept
#if __cplusplus > 202002L:
{ return std::to_underlying(which); };
#else:
{ return static_cast<typename std::underlying_type<Enum>::type>(which); };  // Valid, just not supported by Intellisense
#endif

#endif // GUARD_TO_INT_TEMPLATE