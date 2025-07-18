// Copyright (c) 2012- PPSSPP Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0 or later versions.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official git repository and contact information can be found at
// https://github.com/hrydgard/ppsspp and http://www.ppsspp.org/.

#pragma once

#include <cstdint>
#include <functional>

class PointerWrap;

typedef std::function<void()> VblankCallback;
// Listen for vblank events. Callbacks are cleared in DisplayHWShutdown().
void __DisplayListenVblank(VblankCallback callback);
typedef void (*FlipCallback)(void *userdata);
void __DisplayListenFlip(FlipCallback callback, void *userdata);
void __DisplayForgetFlip(FlipCallback callback, void *userdata);

int __DisplayGetFlipCount();
int __DisplayGetNumVblanks();
int __DisplayGetVCount();
bool DisplayIsVblank();
uint64_t DisplayFrameStartTicks();
uint32_t __DisplayGetCurrentHcount();
uint32_t __DisplayGetAccumulatedHcount();
void DisplayAdjustAccumulatedHcount(uint32_t diff);

void __DisplayGetDebugStats(char *stats, size_t bufsize);
void __DisplayGetAveragedFPS(float *out_vps, float *out_fps);
void __DisplayGetFPS(float *out_vps, float *out_fps, float *out_actual_fps);
void __DisplayGetVPS(float *out_vps);
float *__DisplayGetFrameTimes(int *out_valid, int *out_pos, float **out_sleep);
int DisplayGetSleepPos();
void DisplayNotifySleep(double t, int pos = -1);
bool DisplayIsRunningSlow();

void DisplayFireVblankStart();
void DisplayFireVblankEnd();
void DisplayFireFlip();
void DisplayFireActualFlip();

int DisplayCalculateFrameSkip();

void DisplayHWInit();
void DisplayHWReset();
void DisplayHWShutdown();
void DisplayHWDoState(PointerWrap &p, int hleCompatV2);
