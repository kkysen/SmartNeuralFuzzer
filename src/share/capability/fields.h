//
// Created by Khyber on 6/4/2019.
//

#pragma once

#include <linux/capability.h>

#define COMMA ,
#define SEMICOLON ;

// order of these bit fields must match <linux/capability.h>

#define Capability_old(delim) \
    /*00*/ _(CHOWN) delim \
    /*01*/ _(DAC_OVERRIDE) delim \
    /*02*/ _(DAC_READ_SEARCH) delim \
    /*03*/ _(FOWNER) delim \
    /*04*/ _(FSETID) delim \
    /*05*/ _(KILL) delim \
    /*06*/ _(SETGID) delim \
    /*07*/ _(SETUID) delim \
    /*08*/ _(SETPCAP) delim \
    /*09*/ _(LINUX_IMMUTABLE) delim \
    /*10*/ _(NET_BIND_SERVICE) delim \
    /*11*/ _(NET_BROADCAST) delim \
    /*12*/ _(NET_ADMIN) delim \
    /*13*/ _(NET_RAW) delim \
    /*14*/ _(IPC_LOCK) delim \
    /*15*/ _(IPC_OWNER) delim \
    /*16*/ _(SYS_MODULE) delim \
    /*17*/ _(SYS_RAWIO) delim \
    /*18*/ _(SYS_CHROOT) delim \
    /*19*/ _(SYS_PTRACE) delim \
    /*20*/ _(SYS_PACCT) delim \
    /*21*/ _(SYS_ADMIN) delim \
    /*22*/ _(SYS_BOOT) delim \
    /*23*/ _(SYS_NICE) delim \
    /*24*/ _(SYS_RESOURCE) delim \
    /*25*/ _(SYS_TIME) delim \
    /*26*/ _(SYS_TTY_CONFIG) delim \
    /*27*/ _(MKNOD) delim \
    /*28*/ _(LEASE) delim \
    /*29*/ _(AUDIT_WRITE) delim \
    /*30*/ _(AUDIT_CONTROL) delim \
    /*31*/ _(SETFCAP) delim \
    /*32*/ _(MAC_OVERRIDE) delim \
    /*33*/ _(MAC_ADMIN) delim \
    /*34*/ _(SYSLOG) delim \
    /*35*/ _(WAKE_ALARM) delim \
    /*36*/ _(BLOCK_SUSPEND) delim \
    /*37*/ _(AUDIT_READ)

#define Capability_new(delim) \
    /*00*/ $(changeOwner) delim \
    /*01*/ $(dacOverride) delim \
    /*02*/ $(dacReadSearch) delim \
    /*03*/ $(fileOwner) delim \
    /*04*/ $(fileSetId) delim \
    /*05*/ $(kill) delim \
    /*06*/ $(setGroupId) delim \
    /*07*/ $(setUserId) delim \
    /*08*/ $(setProcessCapabilities) delim \
    /*09*/ $(linuxImmutable) delim \
    /*10*/ $(netBindService) delim \
    /*11*/ $(netBroadcast) delim \
    /*12*/ $(netAdmin) delim \
    /*13*/ $(netRaw) delim \
    /*14*/ $(ipcLock) delim \
    /*15*/ $(ipcOwner) delim \
    /*16*/ $(sysModule) delim \
    /*17*/ $(sysRawIO) delim \
    /*18*/ $(changeRoot) delim \
    /*19*/ $(sysProcessTrace) delim \
    /*20*/ $(sysProcessAccounting) delim \
    /*21*/ $(sysAdmin) delim \
    /*22*/ $(sysBoot) delim \
    /*23*/ $(sysNice) delim \
    /*24*/ $(sysResource) delim \
    /*25*/ $(sysTime) delim \
    /*26*/ $(sysTerminalConfig) delim \
    /*27*/ $(mknod) delim \
    /*28*/ $(lease) delim \
    /*29*/ $(auditWrite) delim \
    /*30*/ $(auditControl) delim \
    /*31*/ $(setFileCapabilities) delim \
    /*32*/ $(macOverride) delim \
    /*33*/ $(macAdmin) delim \
    /*34*/ $(sysLog) delim \
    /*35*/ $(wakeAlarm) delim \
    /*36*/ $(blockSuspend) delim \
    /*37*/ $(auditRead)
    
#define Capability_fields() \
union { \
    struct { \
        Capability_old(SEMICOLON); \
    }; \
    struct { \
        Capability_new(SEMICOLON); \
    }; \
};
