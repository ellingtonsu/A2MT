/*
 * Copyright (C) 2016 Wei-Tsung Su
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _LDMA_H_
#define _LDMA_H_

#include <Arduino.h>

extern "C" {
	typedef void (*SchedulerTask)(void);
}

class LDMAClass {
protected:
	static bool isStarted;
	static int totalTask;
	static int totalLoop;

public:
	LDMAClass();	
	static int addTask(SchedulerTask task, uint32_t loopSlot = 1);
	static int start();
	static int getTaskSize();
	static int getLoopSize();
	static bool getStarted();
	static void setStarted(bool);
};

extern LDMAClass LDMA;

#endif

