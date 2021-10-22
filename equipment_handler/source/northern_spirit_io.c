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
 * @file northern_spirit_io.c
 * @author Thomas Ganley
 * @date 2021-10-22
 */

/**
 * @brief
 *      Sends a command to the Northern SPIRIT payload over UART
 * @param command
 *      Pointer to command array
 * @param length
 *      Length of the command array
 * @return
 *      NS_return
 */

NS_return send_NS_command(uint8_t* command, uint32_t command_length, uint8_t* answer, uint8_t answer_length);

NS_return send_NS_command(uint8_t* command, uint32_t command_length, uint8_t* answer, uint8_t answer_length) {
    xSemaphoreTake(uart_mutex, portMAX_DELAY); //  TODO: make this a reasonable timeout
    sciSend(PAYLOAD_SCI, command, command_length);
    xSemaphoreTake(tx_semphr, portMAX_DELAY); // TODO: make a reasonable timeout

    int received = 0;
    uint8_t reply[answer_length];

    while (received < answer_length) {
        xQueueReceive(adcsQueue, reply[received], portMAX_DELAY); // TODO: make a reasonable timeout
        received++;
    }

    memcpy(answer, reply, answer_length);

    xSemaphoreGive(uart_mutex);
    // TODO: Error handling for the semaphores
    return NS_OK;
}
