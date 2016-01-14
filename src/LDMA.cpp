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
#include "LDMA.h"

bool LDMAClass::isStarted;
int LDMAClass::totalTask;
int LDMAClass::totalLoop;

extern "C" {

typedef struct TaskNode {
	int loopSlot;
	SchedulerTask task;
	struct TaskNode* next;
};

static TaskNode *head = 0;
static TaskNode *cur = 0;


LDMAClass::LDMAClass() {
	LDMAClass::isStarted = false;
	LDMAClass::totalTask = 0;
	LDMAClass::totalLoop = 0;
}

bool LDMAClass::getStarted() {return isStarted;}
void LDMAClass::setStarted(bool state) {isStarted = state;}
int LDMAClass::getTaskSize() {return totalTask;}
int LDMAClass::getLoopSize() {return totalLoop;}

int LDMAClass::addTask(SchedulerTask task, uint32_t loopSlot) {
	
	// Task cannot be added after scheduler has been started.
	if(getStarted() == true) {
		// TODO: Print message
		return -1;
	}
	
	TaskNode *tn = reinterpret_cast<TaskNode *>(malloc(sizeof(TaskNode)));
	tn->loopSlot = loopSlot;
	tn->task = task;
	
	totalTask++;
	totalLoop += loopSlot;
	
	// First task is added.
	if(totalTask == 1) {
		head = tn;
		cur = tn;
	}	
	
	tn->next = NULL;
	cur->next = tn;
	cur = tn;

	return 0;
}


int LDMAClass::start() {
	
	// Scheduler will not be started if there is no task in task queue.
	if(getTaskSize() == 0) {
		// TODO: Print message
		return -1;
	}
		
	setStarted(true);
	
	TaskNode *ptr;
	
	while(true){
		ptr = head;
		while(ptr != NULL) {
			for(int i=0;i<ptr->loopSlot;i++){
			ptr->task();				
			}
			ptr = ptr->next;
		}
	}
}

}