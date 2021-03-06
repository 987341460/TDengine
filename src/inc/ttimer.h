/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TDENGINE_TTIMER_H
#define TDENGINE_TTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void *tmr_h;

extern uint32_t tmrDebugFlag;
extern int taosTmrThreads;

#define tmrError(...)                                 \
  if (tmrDebugFlag & DEBUG_ERROR) {                   \
    tprintf("ERROR TMR ", tmrDebugFlag, __VA_ARGS__); \
  }
#define tmrWarn(...)                                  \
  if (tmrDebugFlag & DEBUG_WARN) {                    \
    tprintf("WARN  TMR ", tmrDebugFlag, __VA_ARGS__); \
  }
#define tmrTrace(...)                           \
  if (tmrDebugFlag & DEBUG_TRACE) {             \
    tprintf("TMR ", tmrDebugFlag, __VA_ARGS__); \
  }

#define MAX_NUM_OF_TMRCTL 512
#define MSECONDS_PER_TICK 5

void *taosTmrInit(int maxTmr, int resoultion, int longest, char *label);

tmr_h taosTmrStart(void (*fp)(void *, void *), int mseconds, void *param1, void *handle);

void taosTmrStop(tmr_h tmrId);

void taosTmrStopA(tmr_h *timerId);

void taosTmrReset(void (*fp)(void *, void *), int mseconds, void *param1, void *handle, tmr_h *pTmrId);

void taosTmrCleanUp(void *handle);

void taosTmrList(void *handle);

#ifdef __cplusplus
}
#endif

#endif  // TDENGINE_TTIMER_H
