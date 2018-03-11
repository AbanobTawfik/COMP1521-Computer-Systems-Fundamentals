// ADT for Bit-strings
// COMP1521 17s2 Week02 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Bits.h"

// assumes that an unsigned int is 32 bits
#define BITS_PER_WORD 32

// A bit-string is an array of unsigned ints (each a 32-bit Word)
// The number of bits (hence Words) is determined at creation time
// Words are indexed from right-to-left
// words[0] contains the most significant bits
// words[nwords-1] contains the least significant bits
// Within each Word, bits are indexed right-to-left
// Bit position 0 in the Word is the least significant bit
// Bit position 31 in the Word is the most significant bit

typedef unsigned int Word;

struct BitsRep {
   int nwords;   // # of Words
   Word *words;  // array of Words
};

// make a new empty Bits with space for at least nbits
// rounds up to nearest multiple of BITS_PER_WORD
Bits makeBits(int nbits)
{
   Bits new;
   new = malloc(sizeof(struct BitsRep));
   assert(new != NULL);
   int  nwords;
   if (nbits%BITS_PER_WORD == 0)
      nwords = nbits/BITS_PER_WORD;
   else
      nwords = 1+nbits/BITS_PER_WORD;
   new->nwords = nwords;
   // calloc sets to all 0's
   new->words = calloc(nwords, sizeof(Word));
   assert(new->words != NULL);
   return new;
}

// release space used by Bits
void  freeBits(Bits b)
{
   assert(b != NULL && b->words != NULL);
   free(b->words);
   free(b);
}

// form bit-wise AND of two Bits a,b
// store result in res Bits
void andBits(Bits a, Bits b, Bits res)
{
   //making sure you are not anding with  null Bits
   assert(b !=NULL && b->words != NULL && a !=NULL && a->words != NULL);
   assert(b->nwords==a->nwords);
   int count = 0;
   while(count < res->nwords){
      res->words[count] = a->words[count]&&b->words[count];
      count++;
   }
}

// form bit-wise OR of two Bits a,b
// store result in res Bits
void orBits(Bits a, Bits b, Bits res)
{
   assert(b !=NULL && b->words != NULL && a !=NULL && a->words != NULL);
   int count = 0;
   while(count < res->nwords){
      res->words[count] = a->words[count]||b->words[count];
      count++;
   }
}

// form bit-wise negation of Bits a,b
// store result in res Bits
void invertBits(Bits a, Bits res)
{
   assert(a != NULL && a->words != NULL);
   int count = 0;
   while(count< res->nwords){
      res->words[count]= ~a->words[count];
      count++;
   }
}

// left shift Bits
void leftShiftBits(Bits b, int shift, Bits res)
{
   // challenge problem
}

// right shift Bits
void rightShiftBits(Bits b, int shift, Bits res)
{
   // challenge problem
}

// copy value from one Bits object to another
void setBitsFromBits(Bits from, Bits to)
{
   assert(from !=NULL && from->words != NULL && to !=NULL && to->words != NULL);
   to->words = from->words;
}

// assign a bit-string (sequence of 0's and 1's) to Bits
// if the bit-string is longer than the size of Bits, truncate higher-order bits
void setBitsFromString(Bits b, char *bitseq)
{
   assert(b != NULL && b->words!= NULL);
   int count = strlen(bitseq)-1;
   int wordcounter = 0;
   int iterations = 0;
   unsigned int mask = 1u;
   while(count>=0){
      if(iterations%BITS_PER_WORD==0)
         wordcounter++;
      if(bitseq[count]=='1')
         b->words[wordcounter]=b->words[wordcounter]||mask;
      mask<<=1;
      count--;
      iterations++;
   }
}

// display a Bits value as sequence of 0's and 1's
void showBits(Bits b)
{
   assert(b != NULL && b->words!= NULL);
   int count = 0;
   while(count<b->nwords){
      printf("%u",b->words[count]);
      count++; 
   }
}
