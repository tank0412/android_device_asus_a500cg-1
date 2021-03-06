/* Telephony Config Selector (TCS) - mmgr data
**
** Copyright (C) Intel 2013
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
*/

#ifndef __TCS_MMGR_HEADER__
#define __TCS_MMGR_HEADER__

#include <limits.h>
#include "stdbool.h"
#include "tcs_config.h"

#define SYSFS_CMD_LEN 16

#define MCDR_PROTOCOL \
    X(UNKNOWN), \
    X(LCDP), \
    X(YMODEM), \

#define MCD_CTRL \
    X(UNKNOWN), \
    X(IOCTL), \
    X(NETLINK), \

typedef enum e_mcdr_protocol {
#undef X
#define X(a) E_MCDR_ ## a
    MCDR_PROTOCOL
} e_mcdr_protocol_t;

typedef enum e_mdm_ctrl {
#undef X
#define X(a) E_MCD_ ## a
    MCD_CTRL
} e_mdm_ctrl_t;

typedef struct link_uart {
    char device[PATH_MAX];
    int baudrate;
} link_uart_t;

typedef struct link_hsi {
    char device[PATH_MAX];
} link_hsi_t;

typedef struct link_usb {
    char device[PATH_MAX];
    int pid;
    int vid;
} link_usb_t;

typedef struct link_shm {
    char device[PATH_MAX];
} link_shm_t;

typedef struct power {
    char device[PATH_MAX];
    char on[SYSFS_CMD_LEN];
    char off[SYSFS_CMD_LEN];
} power_t;

typedef struct link_ctrl {
    char device[PATH_MAX];
    char on[SYSFS_CMD_LEN];
    char off[SYSFS_CMD_LEN];
    char reset[SYSFS_CMD_LEN];
} link_ctrl_t;

typedef struct mux {
    int frame_size;
    int retry;
} mux_t;

typedef struct link {
    e_link_t type;
    union {
        link_uart_t uart;
        link_hsi_t hsi;
        link_usb_t usb;
        link_shm_t shm;
    };
} link_t;

typedef struct mcdr_gnl {
    bool enable;
    e_mcdr_protocol_t protocol;
    char path[PATH_MAX];
    int timeout;
} mcdr_gnl_t;

typedef struct mcdr_info {
    mcdr_gnl_t gnl;
    link_t link;
    power_t power;
    link_ctrl_t ctrl;
} mcdr_info_t;

typedef struct mmgr_mdm_link {
    link_t flash;
    link_t baseband;
    power_t power;
    link_ctrl_t ctrl;
} mmgr_mdm_link_t;

typedef struct mmgr_fl_bkup {
    char nvm_cal[PATH_MAX];
} mmgr_fl_bkup_t;

typedef struct mmgr_fl_run {
    char path[PATH_MAX];
    char mdm_fw[PATH_MAX];
    char mdm_inj_fw[PATH_MAX];
    char nvm_sta[PATH_MAX];
    char nvm_dyn[PATH_MAX];
    char nvm_cal[PATH_MAX];
    char rnd[PATH_MAX];
} mmgr_fl_run_t;

typedef struct mmgr_flashless {
    mmgr_fl_bkup_t bkup;
    mmgr_fl_run_t run;
} mmgr_flashless_t;

typedef struct mmgr_com {
    /* @TODO: for future platform without MUX, an enum and union should be used
     * here */
    mux_t mux;
} mmgr_com_t;

typedef struct mmgr_recovery {
    bool enable;
    int cold_reset;
    int reboot;
    int reset_delay;
    int reboot_delay;
    int cold_timeout;
    int shtdwn_timeout;
} mmgr_recovery_t;

typedef struct mmgr_timings {
    int ipc_ready;
    int cd_ipc_reset;
    int cd_ipc_ready;
    int mdm_flash;
    int fmmo;
} mmgr_timings_t;

typedef struct mmgr_clients {
    int max;
} mmgr_clients_t;

typedef struct mmgr_mcd {
    e_mdm_ctrl_t interface;
    bool ipc_ready_present;
} mmgr_mcd_t;

typedef struct mmgr_info {
    mmgr_mdm_link_t mdm_link;
    mmgr_mcd_t mcd;
    mmgr_flashless_t flash;
    mmgr_com_t com;
    mmgr_timings_t timings;
    mmgr_recovery_t recov;
    mmgr_clients_t cli;
    mcdr_info_t mcdr;
} mmgr_info_t;

#endif                          // __TCS_MMGR_HEADER__
