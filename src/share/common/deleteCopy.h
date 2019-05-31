//
// Created by Khyber on 5/31/2019.
//

#pragma once

#define deleteCopyConstructor(T) T(const T&) = delete

#define deleteCopyAssignment(T) T& operator=(const T&) = delete

#define deleteCopy(T) \
    deleteCopyConstructor(T); \
    deleteCopyAssignment(T)
