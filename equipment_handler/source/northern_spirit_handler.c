/*
 * Copyright (C) 2021  University of Alberta
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/**
 * @file northern_spirit_handler.c
 * @author Thomas Ganley
 * @date 2021-10-22
 */

#define IS_YUKONSAT
#define IS_AURORASAT

#if defined(IS_YUKONSAT) && defined(IS_AURORASAT)
#error Cannot have both IS_YUKONSAT and IS_AURORASAT defined
#endif


// Functions fulfilling functionality common to AuroraSat and YukonSat



#ifdef IS_YUKONSAT
// Functions fulfilling functionality specific to YukonSat

#endif

#ifdef IS_AURORASAT
// Functions fulfilling functionality specific to AuroraSat
NS_return ARI_get_heartbeat(uint8_t* heartbeat){
    uint8_t command = 'h';
    uint8_t answer[ARI_HEARTBEAT_ANS_LEN] = 0;

    send_NS_command(&command, sizeof(command), answer, sizeof(answer));
}

#endif
