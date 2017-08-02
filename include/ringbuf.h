/*
  RingBuf.h - Library for implementing a simple Ring Buffer on Arduino boards.
  Created by D. Aaron Wisner (daw268@cornell.edu)
  January 17, 2015.
  Released into the public domain.
*/
#ifndef RingBuf_h
#define RingBuf_h
#include "stdint.h"
#include "stdlib.h"

#define TOPIC_SIZE 50
#define MAX_MSG_LENGTH 256

#ifndef bool
    #define bool uint8_t
#endif


typedef struct RingBuf RingBuf;

struct MgStruct
{
	char topic[TOPIC_SIZE];
	char msg[MAX_MSG_LENGTH];
	int msglen;
};

typedef struct RingBuf
{
  // Invariant: end and start is always in bounds
  unsigned char *buf;
  unsigned int len, size, start, end, elements;
  
  
  ///Function Point to function outsite this struct
  int (*next_end_index) (RingBuf *);
  int (*incr_end_index) (RingBuf *);
  int (*incr_start_index) (RingBuf *);
  // Returns true if full
  bool (*isFull) (RingBuf *);
  // Returns true if empty
  bool (*isEmpty) (RingBuf *);
  // Returns number of elemnts in buffer
  unsigned int (*numElements)(RingBuf *);
  // Add Event, Returns index where added in buffer, -1 on full buffer
  int (*add) (RingBuf *, const void*);
  // Returns pointer to nth element, NULL when nth element is empty
  void *(*peek) (RingBuf *, unsigned int);
  // Removes element and copies it to location pointed to by void *
  // Returns pointer passed in, NULL on empty buffer
  void *(*pull) (RingBuf *, void *);

} RingBuf;


RingBuf *RingBuf_new(int size, int len);
int RingBuf_init(RingBuf *self, int size, int len);
int RingBuf_delete(RingBuf *self);
int RingBufNextEndIndex(RingBuf *self);
int RingBufIncrEnd(RingBuf *self);
int RingBufIncrStart(RingBuf *self);
int RingBufAdd(RingBuf *self, const void *object);
void *RingBufPeek(RingBuf *self, unsigned int num);
void *RingBufPull(RingBuf *self, void *object);
uint8_t RingBufIsFull(RingBuf *self);
uint8_t RingBufIsEmpty(RingBuf *self);
unsigned int RingBufNumElements(RingBuf *self);

#endif
