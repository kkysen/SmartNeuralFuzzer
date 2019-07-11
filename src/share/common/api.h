//
// Created by Khyber on 3/14/2019.
//

#pragma once

#define CAT_I(a, b) a##b
#define CAT(a, b) CAT_I(a, b)

#define API(api, name) CAT(__, CAT(api, CAT(_, name)))

#define API_rt() if (!rt.isDestructed()) rt()
