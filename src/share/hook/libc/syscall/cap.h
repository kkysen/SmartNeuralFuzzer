//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include <linux/capability.h>

extern "C"
int capget(__user_cap_header_struct* header, __user_cap_data_struct* data) noexcept;

extern "C"
int capset(__user_cap_header_struct* header, const __user_cap_data_struct* data) noexcept;
