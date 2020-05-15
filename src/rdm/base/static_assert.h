#pragma once

#define RDM_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)

#define RDM_STATIC_ASSERT_MSG(...) static_assert(__VA_ARGS__)