/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2018. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

#ifndef ANDROID_ML_NN_COMMON_HAL_UTILS_H
#define ANDROID_ML_NN_COMMON_HAL_UTILS_H

#include <stdint.h>

namespace android {
namespace nn {

/**
 * Result codes.
 *
 * One-one mapping to ResultCode in NeuralNetworks.h
 */
typedef enum {
    HAL_UTILS_NO_ERROR = 0,
    HAL_UTILS_OUT_OF_MEMORY = 1,
    HAL_UTILS_INCOMPLETE = 2,
    HAL_UTILS_UNEXPECTED_NULL = 3,
    HAL_UTILS_BAD_DATA = 4,
    HAL_UTILS_OP_FAILED = 5,
    HAL_UTILS_BAD_STATE = 6,
    HAL_UTILS_UNMAPPABLE = 7,
    HAL_UTILS_OUTPUT_INSUFFICIENT_SIZE = 8,
    HAL_UTILS_UNAVAILABLE_DEVICE = 9,
    HAL_UTILS_MISSED_DEADLINE_TRANSIENT = 10,
    HAL_UTILS_MISSED_DEADLINE_PERSISTENT = 11,
    HAL_UTILS_RESOURCE_EXHAUSTED_TRANSIENT = 12,
    HAL_UTILS_RESOURCE_EXHAUSTED_PERSISTENT = 13,
    HAL_UTILS_DEAD_OBJECT = 14,
} ResultCode;

/// M: OEM Operand @{
/**
 * Identify the type and value of the OEM Operand
 * type: The actual type of this operand
 * typeLen: The size(byte) of type.
 * data: The operand value.
 * dataLen: The size(byte) of data.
 */
struct OemOperandValue {
    uint8_t* type;
    uint8_t typeLen;
    uint8_t* data;
    uint32_t dataLen;
};
/// @}

/// M: OEM Operand @{
/**
 * Encode the input type and operand value to raw data.
 * @param operand see OemOperandValue.
 * @param output the converted raw data.
 * @return ANEURALNETWORKS_NO_ERROR if the request completed normally.
 *
 * The format of data will be:
 *  -------------------------------------------------------------------------------
 *  | 1 byte typeLen  | N bytes type     | 4 bytes dataLen  | N bytes data        |
 *  -------------------------------------------------------------------------------
 *  1. The first byte of output is the size(length) of type.
 *      The following N bytes of the output is the string of input type.
 *      For example: int16 will be presented as {5,105,110,116,49,54}
 *
 *  2. The next 4 bytes(Little endian) of output is the size(length) of data.
 *      The following N bytes of the output is the actual data.
 *      For example: uint8_t data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0} will be
 *                         {10, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0}
 *
 *
 */
int encodeOperandValue(OemOperandValue *operand, uint8_t *output);

/**
 * Decode the input raw data to OemOperandValue.
 * @param input the raw data.
 * @param operand the output of this function, will decode raw data into struct.
 * @return ANEURALNETWORKS_NO_ERROR if the request completed normally.
 *
 * Note: This function will allocate memory for type and data, please make
 *          sure to free them when the not used.
 */
int decodeOperandValue(uint8_t *input, OemOperandValue *operand);
/// @}

}  // namespace nn
}  // namespace android

#endif  // ANDROID_ML_NN_COMMON_HAL_UTILS_H
