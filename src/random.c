
/*
 *<SOURCE_HEADER>
 *
 *  <NAME>
 *    random.c
 *  </NAME>
 *  <AUTHOR>
 *    Anthony R. Cassandra
 *  </AUTHOR>
 *  <CREATE_DATE>
 *    July, 1998
 *  </CREATE_DATE>
 *
 *  <RCS_KEYWORD>
 *    $RCSfile: random.c,v $
 *    $Source: /u/cvs/proj/pomdp-solve/src/random.c,v $
 *    $Revision: 1.1 $
 *    $Date: 2003/05/13 21:46:40 $
 *  </RCS_KEYWORD>
 *
 *  <COPYRIGHT>
 *
 *    1994-1997, Brown University
 *    1998-2003, Anthony R. Cassandra
 *
 *    All Rights Reserved
 *                          
 *    Permission to use, copy, modify, and distribute this software and its
 *    documentation for any purpose other than its incorporation into a
 *    commercial product is hereby granted without fee, provided that the
 *    above copyright notice appear in all copies and that both that
 *    copyright notice and this permission notice appear in supporting
 *    documentation.
 * 
 *    ANTHONY CASSANDRA DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 *    INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR ANY
 *    PARTICULAR PURPOSE.  IN NO EVENT SHALL ANTHONY CASSANDRA BE LIABLE FOR
 *    ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *  </COPYRIGHT>
 *
 *</SOURCE_HEADER>
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "global.h"
#include "random.h"

struct timeval barf_o_ghetti;

/* Globally keep the seed */
static unsigned short random_seed48[SEED_SIZE];
/* static short random_seed48[SEED_SIZE]; */

/* To keep track of whether we have initialized the psuedo random 
   number generator. */
int seeded = 0;
/* static int seeded = 0; */

/**********************************************************************/
static int create(int maxnum) {
  return rand() % Max(1, maxnum);
}  /* create */
/**********************************************************************/
static void init_randomizer() {
  unsigned long seed;
  // Combine current time and process ID for the seed
  seed = (unsigned long)time(NULL) ^ (unsigned long)getPid();
  srand(seed);

  int i;
  for (i=0;i<87;++i)            /* exercise out any startup transients */
    create(10);

  seeded = 1;
}  /* init_randomizer */
/**********************************************************************/
void randomize() {
/*
  Seeds the psuedo-random number generated if it has not already been
  seeded. 
*/
  if( !seeded ) 
    init_randomizer();
}  /* randomize */
/**********************************************************************/
double fran() { 
  /* Returns a uniform psuedo-random number between 0 and 1 */

  if( !seeded ) {
    init_randomizer();
  }

  return (double)rand() / (double)RAND_MAX;
}  /* fran */
/**********************************************************************/
void 
getRandomSeed( unsigned short seed[SEED_SIZE] ) 
{
  /* Returns the current random seed.  Useful if you want to reproduce 
     the sequence (e.g., debugging) */
  int i;

  for( i = 0; i < SEED_SIZE; i++ )
    seed[i] = random_seed48[i];

}  /* getRandomSeed */
/**********************************************************************/
void 
setRandomSeed( unsigned short seed[SEED_SIZE] ) 
{
  /* Allows you to reproduce a psuedo-random sequence by explicitly 
     setting the seed value for the random number generator */
  int i;

  for( i = 0; i < SEED_SIZE; i++ )
    random_seed48[i] = seed[i];

  /* Assume SEED_SIZE = 3 */
  unsigned int seed_temp = seed[0] ^ seed[1] ^ seed[2];
  srand(seed_temp);
  
  seeded = 1;
}  /* getRandomSeed */
/**********************************************************************/
void setRandomSeedFromString(char *str) 
{
  unsigned short s[SEED_SIZE];
  int temp[SEED_SIZE];
  int i;

  sscanf(str, "%d:%d:%d", &temp[0], &temp[1], &temp[2]);	

  for(i = 0; i < SEED_SIZE; i++)
    s[i] = (unsigned short)temp[i];

  setRandomSeed(s);
} /* setRandomSeedFromString  */
/**********************************************************************/
void 
displayRandomSeed( FILE *file ) 
{
  /* 
     Display random seed to file stream. 
  */
  int i;
  
  fprintf( file, "%d", (int) random_seed48[0] );
  for( i = 1; i < SEED_SIZE; i++ )
    fprintf( file, ":%d", (int) random_seed48[i] );

}  /* displayRandomSeed */
/**********************************************************************/
void 
showRandomSeed(  ) 
{
  /* 
     Display random seed to stdout. 
  */
  fprintf( stdout, "\t" );
  displayRandomSeed( stdout );
  fprintf( stdout, "\n" );

}  /* showRandomSeed */
/**********************************************************************/
double 
getRandomDouble( double min, double max ) 
{
  /* Returns a uniform psuedo-random number between min and max in the 
     form of a double precision number */
  return( fran() * (max - min) + min );
}  /* getRandomDouble */
/**********************************************************************/
int 
getRandomInt( int min, int max ) 
{
  /* Returns a uniform psuedo-random number between min and max in the 
     form of an integer */
  return( ((int) (fran() * (max - min + 1 ))) + min );
} /* getRandomInt */
/**********************************************************************/
/* This routine sets the discrete probability distribution so that
   each belief state is equally likely.  */
void 
setRandomDistribution( double *x, int num_probs ) 
{
  /* This routine sets the discrete probability distribution so that
     each distribution is equally likely.  */
  int i, j;

   x[0] = 1.0;

   for( i = 1; i < num_probs; i++ ) {
      x[i] = 1.0 - exp( 1.0/i * log( getRandomDouble( 0.0, 1.0)) );
      
      for( j = 0; j < i; j++ )
         x[j] *= 1.0 - x[i];
   }  /* for i */

}  /* setRandomDistribution */
/**********************************************************************/
void 
setRandomDoubleVector( double *vect, int num, 
		       double min, double max ) 
{
  /*
    Sets the given vector of doubles with random values  betwen the min
    and max values given.  'num' is the number of elements in the
    vector.
  */
  int i;

  for ( i = 0; i < num; i++ )
    vect[i] = getRandomDouble(min, max );

}  /* setRandomDoubleVector */
/**********************************************************************/
