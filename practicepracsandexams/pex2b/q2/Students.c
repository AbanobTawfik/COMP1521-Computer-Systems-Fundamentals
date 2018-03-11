// Students.c ... implementation of Students datatype

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "Students.h"

typedef struct _stu_rec {
	int   id;
	char  name[20];
	int   degree;
	float wam;
} sturec_t;

typedef struct _students {
    int    nstu;
    StuRec recs;
} students_t;

// build a collection of student records from a file descriptor
Students getStudents(int in)
{

	Students new = malloc(sizeof(struct _students));
	new->nstu = 0;
	size_t size = (sizeof(struct _stu_rec));
	sturec_t t;
	while(read(in,&t,size)==size)new->nstu++;
	new->recs = malloc(size*new->nstu);

	lseek(in, 0, SEEK_SET);
	for(int i = 0;i<new->nstu;i++)
	   read(in,&(new->recs[i]),size);
	return new;  
	
	// TODO ... replace this by your code
}

// show a list of student records pointed to by ss
void showStudents(Students ss)
{
	assert(ss != NULL);
	for (int i = 0; i < ss->nstu; i++)
		showStuRec(&(ss->recs[i]));
}

// show one student record pointed to by s
void showStuRec(StuRec s)
{
	printf("%7d %s %4d %0.1f\n", s->id, s->name, s->degree, s->wam);
}
