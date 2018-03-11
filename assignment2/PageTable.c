// PageTable.c ... implementation of Page Table operations
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017

#include <stdlib.h>
#include <stdio.h>
#include "Memory.h"
#include "Stats.h"
#include "PageTable.h"

/*
 * Symbolic constants
 */

#define NOT_USED 0
#define IN_MEMORY 1
#define ON_DISK 2

/*
 * PTE = Page Table Entry
 */

typedef struct pagetable *PTE;
typedef struct pagetable {
	char status;      													//NOT_USED, IN_MEMORY, ON_DISK
	char modified;    													//boolean: changed since loaded
	int frame;       													//memory frame holding this page
	int accessTime;   													//clock tick for last access
	int loadTime;     													//clock tick for last time loaded
	int nPeeks;       													//total number times this page read
	int nPokes;       													//total number times this page modified
	//my own added data in struct
	PTE next;		 													//next node in the doubly linked list
	PTE prev;															//prev node in the doubly linked list
	int inlist;															//checks if the page is already in the frame list
	int page;															//keeps track of the page number
} pagetable;

/*
 * my own adt just for keeping track of list
 * no required ADT for new ADT for nodes
 * using PTE as nodes
 */

typedef struct List *list;
typedef struct List {
	PTE head;
	PTE tail;
	int size;
} List;

/*
 * The virtual address space of the process is managed
 * by an array of Page Table Entries (PTEs)
 * The Page Table is not directly accessible outside
 * this file (hence the static declaration)
 */

static PTE PageTable;     											 	//array of page table entries
static int nPages;         												//# entries in page table
static int replacePolicy;  											    //how to do page replacement
static list l;			  												//frame list

/*
 * Forward refs for private functions
 */

static int findVictim(list l);
list newlist(void);
void insert(list l, PTE entry, int time);
void fifoinsert(list l, PTE entry, int time);
void lruinsert(list l, PTE entry, int time);
int dropList(list l);

/*
 * initPageTable: create/initialise Page Table data structures
 */

void initPageTable(int policy, int np) {
	l = newlist();														//create new frame list
	PageTable = malloc(np * sizeof(struct pagetable));
	if (PageTable == NULL) {
		fprintf(stderr, "Can't initialise Memory\n");
		exit(EXIT_FAILURE);
	}
	replacePolicy = policy;
	nPages = np;
	for (int i = 0; i < nPages; i++) {
		PTE p = &PageTable[i];
		p->status = NOT_USED;
		p->modified = 0;
		p->frame = NONE;
		p->accessTime = NONE;
		p->loadTime = NONE;
		p->nPeeks = p->nPokes = 0;
		//initialising my added data standard doubly linked list for prev next
		p->next = NULL;
		p->prev = NULL;
		p->inlist = 0;													//default for all pages not in list
		p->page = i;													//give the page the right number
	}
}

/*
 * requestPage: request access to page pno in mode
 * returns memory frame holding this page
 * page may have to be loaded
 * PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites,inlist,page)
 */

int requestPage(int pno, char mode, int time) {
	if (pno < 0 || pno > nPages - 1) {
		fprintf(stderr, "Invalid page reference\n");
		exit(EXIT_FAILURE);
	}
	PTE p = &PageTable[pno];
	insert(l, p, time);													//insert the page into our page table;
	int fno; 															//frame number
	switch (p->status) {
		case NOT_USED:
		case ON_DISK:
			countPageFault();											//disk->memory is page fault add to counter
			fno = findFreeFrame();
			if (fno == NONE) {
				int vno = findVictim(l);
#ifdef DBUG
				printf("Evict page %d\n",vno);
#endif
				PTE v = &PageTable[vno];								//victim is the page at the index for page number
				fno = v->frame;											//getting the frame victim was stored in
				if (v->modified == 1)saveFrame(fno);					//if the page was being modified save it first
				v->status = ON_DISK;									//victim is now on disk ... MEMORY->DISK
				v->frame = NONE;										//no frame for the victim anymore
				v->modified = 0;										//no longer being modified its on disk
				v->accessTime = NONE;									//no longer being accessed its on disk
				v->loadTime = NONE;										//no load, load is when disk->memory
				v->inlist = 0;											//no longer in our framelist
			}
#ifdef DBUG			
			printf("Page %d given frame %d\n", pno, fno);
#endif			
			loadFrame(fno, pno, time);									//load the page we requested into the frame of v
			p->frame = fno;												//give the frame of our page same as victim's frame was
			p->status = IN_MEMORY;										//went from disk->memory update status
			p->modified = 0;											//its not yet modified
			break;
		case IN_MEMORY:
			countPageHit();												//if its on memory add to hit
			p->accessTime = time;										//change only access time
			break;
		default:
			fprintf(stderr, "Invalid page status\n");
			exit(EXIT_FAILURE);
	}
	if (mode == 'r')
		p->nPeeks++;
	else if (mode == 'w') {
		p->nPokes++;
		p->modified = 1;
	}
	return p->frame;
}

/*
 * findVictim: find a page to be replaced
 * CHECK THE ADDED FUNCTIONS
 */

static int findVictim(list l) {
	int victim = dropList(l);
	return victim;
}

/*
 * showPageTableStatus: dump page table
 * PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)
 */

void showPageTableStatus(void) {
	char *s;
	printf("%4s %6s %4s %6s %7s %7s %7s %7s\n",
		   "Page", "Status", "Mod?", "Frame", "Acc(t)", "Load(t)", "#Peeks", "#Pokes");
	for (int i = 0; i < nPages; i++) {
		PTE p = &PageTable[i];
		printf("[%02d]", i);
		switch (p->status) {
			case NOT_USED:
				s = "-";
				break;
			case IN_MEMORY:
				s = "mem";
				break;
			case ON_DISK:
				s = "disk";
				break;
		}
		printf(" %6s", s);
		printf(" %4s", p->modified ? "yes" : "no");
		if (p->frame == NONE)
			printf(" %6s", "-");
		else
			printf(" %6d", p->frame);
		if (p->accessTime == NONE)
			printf(" %7s", "-");
		else
			printf(" %7d", p->accessTime);
		if (p->loadTime == NONE)
			printf(" %7s", "-");
		else
			printf(" %7d", p->loadTime);
		printf(" %7d", p->nPeeks);
		printf(" %7d", p->nPokes);
		printf("\n");
	}
}

/*
 * ADDED FUNCTIONS
 * both policies use the same list
 * both policies use the same removal
 * The difference in policies is the storage technique
 */

list newlist(void) {
	list new = malloc(sizeof(List *));									//allocate memory for our frame list
	new->head = NULL;													//head is null for empty list
	new->tail = NULL;													//tail is null for empty list
	new->size = 0;														//size of list initially is 0
	return new;
}

/*
 *	one insert only is needed inserts based on policy
 */

void insert(list l, PTE entry, int time) {
	if (replacePolicy == REPL_LRU)lruinsert(l, entry, time);			//if policy is lru do a lru insert
	if (replacePolicy == REPL_FIFO)fifoinsert(l, entry, time);			//if policy is fifo do a fifo insert
}

/*
 * Fifo insert is purely a queue system, first in first out
 * slightly modified queue to work with fixed size
 * LOAD TIME IS GIVEN WHEN A PAGE IS NOT IN THE LIST ALREADY I.E ON DISK
 * ONLY TIME LOAD TIME IS CHANGED IS IF NOT IN LIST
 * head of our list will be the first page loaded in regardless of how many accesses
 */

void fifoinsert(list l, PTE entry, int time) {
	if (entry->inlist == 1) {											//if the page is already on the list
		entry->accessTime = time;										//update the access time for the page
		return;
	}
	entry->inlist = 1;													//else add it to the list
	if (l->head == NULL) {												//case of empty list
		l->head = l->tail = entry;										//entry is both head and tail of our list
		entry->loadTime = time;											//time the page was initally loaded in the list
		entry->accessTime = time;										//initial access time for our entry
		l->size++;														//update size of our list
	} else {															//every other case
		l->tail->next = entry;											//push the entry to the back of the list
		entry->loadTime = time;											//initialise load time
		entry->accessTime = time;										//initialise access time
		l->tail = entry;												//update the list tail to be our page entry
		l->size++;														//update size of our list
	}
}

/*
 * LRU insert is based on when it is inserted
 * basic principle is, the last accessed element is the head of our list
 * the most recently accessed element will be the tail of the list
 * LOAD TIME IS GIVEN WHEN A PAGE IS NOT IN THE LIST ALREADY I.E ON DISK
 * ONLY TIME LOAD TIME IS CHANGED IS IF NOT IN LIST
 * head of our list will be the first page loaded in regardless of how many accesses
 */

void lruinsert(list l, PTE entry, int time) {
	if (entry->inlist == 1) {											//case of entry is already in list we need to update
		if (l->size == 1 && l->head == entry) {							//if the entry is in the list and its the only element in the list
			entry->accessTime = time;									//update access time only
			return;
		} else if (l->size > 2 && l->head == entry) {					//if there are more than one elements in the list and the entry is the head of list
			entry->prev = l->tail;										//update the link for the entry prev to be the current tail
			l->head = l->head->next;									//shift the head to the page after the head;
			l->tail->next = entry;										//push the entry to the end of the list
			l->tail = entry;											//make the tail of the list the entry
			entry->accessTime = time;
			return;
		} else if (l->tail == entry) {									//if the tail of the list is the entry already
			entry->accessTime = time;									//update access time
			return;
		} else {														//general case is when the entry is in the middle of the list
			//update links to remove it from the middle of its current nodes i.e 1->2->3 ----> 1->3
			entry->prev->next = entry->next;							//change the link behind the entry pointing to the entry to point to the page after
			entry->next->prev = entry->prev;							//change the link infront of the entry pointing to the entry to point to the page before
			entry->prev = l->tail;										//now push the entry to the end as tail so make entry->prev point to list tail
			l->tail->next = entry;										//push the entry to the end
			l->tail = entry;											//update the list tail to be our entry
			entry->accessTime = time;									//update access time
			return;
		}
	}
	entry->inlist = 1;													//if not in list put it in the list
	if (l->size == 0) {													//case of empty list
		l->head = l->tail = entry;										//head and tail are now the entry
		entry->loadTime = time;											//note time when it was loaded in
		entry->accessTime = time;										//update access time
		l->size++;														//update list size
		return;
	} else if (l->size == 1) {											//if the list only has 1 element want to insert infront of the head
		entry->prev = l->head;											//set the previous node of the entry to be the head
		l->head->next = entry;											//head->next which should be the tail is entry
		l->tail = entry;												//update the tail of the list to be the entry
		entry->loadTime = time;											//note time when it was loaded in
		entry->accessTime = time;										//update access time
		l->size++;														//update list size
		return;
	} else {															//every other general case
		entry->prev = l->tail;											//set the previous node of the entry to be the tail
		l->tail->next = entry;											//push the entry to the end of the list
		l->tail = entry;												//update the tail of the list to be the entry
		entry->loadTime = time;											//note time when it was loaded in
		entry->accessTime = time;										//update access time
		l->size++;														//update list size
		return;
	}
}

/*
 * THIS IS WHY REMOVAL IS O(1) BOI
 * the head of the list despite which insertion technique will be either latest accessed/ first page loaded
 * pop the head off the list
 * and set the new head as head->next
 */

int dropList(list l) {
	if (l->head == NULL) return -1;										//invalid call if no head
	int ret = l->head->page;											//return value is the page of the head in our frame list
	l->head = l->head->next;											//shift the head to be the head next
	l->size--;															//decrement list size
	if (l->head == NULL)l->tail = NULL;									//if u remove the head and its next node is null set list size to 0 and tail null
	return ret;
}

