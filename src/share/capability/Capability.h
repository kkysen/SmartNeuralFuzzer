//
// Created by Khyber on 6/4/2019.
//

#pragma once

namespace capability {
    
    struct Capability {
    
        #define _(field) bool field: 1
        
        // order of these bit fields must match <linux/capability.h>
        
        union {
            struct {
                /*01*/ _(CHOWN);
                /*02*/ _(DAC_OVERRIDE);
                /*03*/ _(DAC_READ_SEARCH);
                /*04*/ _(FOWNER);
                /*05*/ _(FSETID);
                /*06*/ _(KILL);
                /*07*/ _(SETUID);
                /*08*/ _(SETPCAP);
                /*09*/ _(LINUX_IMMUTABLE);
                /*10*/ _(NET_BIND_SERVICE);
                /*11*/ _(NET_BROADCAST);
                /*12*/ _(NET_ADMIN);
                /*13*/ _(NET_RAW);
                /*14*/ _(IPC_LOCK);
                /*15*/ _(IPC_OWNER);
                /*16*/ _(SYS_MODULE);
                /*17*/ _(SYS_RAWIO);
                /*18*/ _(SYS_CHROOT);
                /*19*/ _(SYS_PTRACE);
                /*20*/ _(SYS_PACCT);
                /*21*/ _(SYS_ADMIN);
                /*22*/ _(SYS_BOOT);
                /*23*/ _(SYS_NICE);
                /*24*/ _(SYS_RESOURCE);
                /*25*/ _(SYS_TIME);
                /*26*/ _(SYS_TTY_CONFIG);
                /*27*/ _(MKNOD);
                /*28*/ _(LEASE);
                /*29*/ _(AUDIT_WRITE);
                /*30*/ _(AUDIT_CONTROL);
                /*31*/ _(SETFCAP);
                /*32*/ _(MAC_OVERRIDE);
                /*33*/ _(MAC_ADMIN);
                /*34*/ _(SYSLOG);
                /*35*/ _(WAKE_ALARM);
                /*36*/ _(BLOCK_SUSPEND);
                /*37*/ _(AUDIT_READ);
            };
            struct {
                /*01*/ _(changeOwner);
                /*02*/ _(dacOverride);
                /*03*/ _(dacReadSearch);
                /*04*/ _(fileOwner);
                /*05*/ _(fileSetId);
                /*06*/ _(kill);
                /*07*/ _(setUid);
                /*08*/ _(setProcessCapabilities);
                /*09*/ _(linuxImmutable);
                /*10*/ _(netBindService);
                /*11*/ _(netBroadcast);
                /*12*/ _(netAdmin);
                /*13*/ _(netRaw);
                /*14*/ _(ipcLock);
                /*15*/ _(ipcOwner);
                /*16*/ _(sysModule);
                /*17*/ _(sysRawIO);
                /*18*/ _(changeRoot);
                /*19*/ _(sysProcessTrace);
                /*20*/ _(sysProcessAccounting);
                /*21*/ _(sysAdmin);
                /*22*/ _(sysBoot);
                /*23*/ _(sysNice);
                /*24*/ _(sysResource);
                /*25*/ _(sysTime);
                /*26*/ _(sysTerminalConfig);
                /*27*/ _(mknod);
                /*28*/ _(lease);
                /*29*/ _(auditWrite);
                /*30*/ _(auditControl);
                /*31*/ _(setFileCapabilities);
                /*32*/ _(macOverride);
                /*33*/ _(macAdmin);
                /*34*/ _(sysLog);
                /*35*/ _(wakeAlarm);
                /*36*/ _(blockSuspend);
                /*37*/ _(auditRead);
            };
        };
    
        #undef _
        
    };
    
}
