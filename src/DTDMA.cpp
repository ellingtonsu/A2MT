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
#include <util/delay.h>
#include "DTDMA.h"

bool DTDMAClass::isStarted;
int DTDMAClass::totalTask;
int DTDMAClass::totalTaskList;

extern "C" {

typedef struct TaskList {
	int totalTask;
	struct TaskNode* head;
	struct TaskNode* curr;
	struct TaskNode* tail;
	struct TaskList* next;
};

typedef struct TaskNode {
	int delay;
	int count;
	SchedulerTask task;
	struct TaskNode* next;
};

static TaskList *tl_head = 0;
static TaskList *tl_curr = 0;

//static TaskNode *head = 0;
//static TaskNode *curr = 0;


DTDMAClass::DTDMAClass() {
	DTDMAClass::isStarted = false;
	DTDMAClass::totalTask = 0;
	DTDMAClass::totalTaskList = 0;
}

bool DTDMAClass::getStarted() {return isStarted;}
void DTDMAClass::setStarted(bool state) {isStarted = state;}
int DTDMAClass::getTaskListSize() {return totalTaskList;};
int DTDMAClass::getTaskSize() {return totalTask;}

int DTDMAClass::addTaskList() {
	TaskList *tl = reinterpret_cast<TaskList *>(malloc(sizeof(TaskList)));
	
	totalTaskList++;
	
	// First task list is added.
	if(totalTaskList == 1) {
		tl_head = tl;
		tl_curr = tl;
	}	
	
	tl->totalTask = 0;
	tl->head = NULL;
	tl->curr = NULL;
	tl->tail = NULL;
	
	tl->next = NULL;
	tl_curr->next = tl;
	tl_curr = tl;

	return 0;
}

int DTDMAClass::addTask(SchedulerTask task, uint32_t delay) {
	
	// Task cannot be added after scheduler has been started.
	if(getStarted() == true) {
		// TODO: Print message
		return -1;
	}
	
	TaskNode *tn = reinterpret_cast<TaskNode *>(malloc(sizeof(TaskNode)));
	tn->delay = delay;
	tn->task = task;
	tn->count = 0;
	
	totalTask++;
	tl_curr->totalTask++;
	
	// First task is added.
	if(tl_curr->totalTask == 1) {
		tl_curr->head = tn;
		tl_curr->curr = tn;
		tl_curr->tail = tn;
	}	
	
	tn->next = NULL;
	tl_curr->tail->next = tn;
	tl_curr->tail = tn;

	return 0;
}


int DTDMAClass::start() {
			
	setStarted(true);
	
	TaskList *tl_ptr;
	TaskNode *ptr;
	
	while(true){
		tl_ptr = tl_head;		
		while(tl_ptr != NULL) {
			ptr = tl_ptr->curr;
			ptr->count++;
			if(ptr->count == ptr->delay) {
				ptr->task();
				ptr->count = 0;
				if(ptr->next != NULL)
					tl_ptr->curr = ptr->next;
				else
					tl_ptr->curr = tl_ptr->head;
			}
			tl_ptr = tl_ptr->next;
			_delay_ms(1);
		}
	}
}

}