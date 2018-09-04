#include "float_i2f.h"
#include <stdio.h>

#define Bias 127
#define HalfWay 0x100
float_bits float_i2f(int i) {
  //first get the sign and absolute value of i.
  unsigned j  = (unsigned)i;
  unsigned sign = j >> 31;
  unsigned value;
  if(sign == 0){
    value = i;
  }
  else{
    value = 0x80000000 - ((j << 1) >> 1);
  }

  //check if the value is 0, namely special case of denormalize
  if(value == 0){
    return 0x00000000;
  }

  //calculate the exp and frac
  int E = 0;
  unsigned exp=0, frac=0;
  while(1){
    frac = frac + ((value % 2) << E);
    value = value >> 1;
    E = E + 1;
    if(value == 0)
      break;
  }

 
  
  exp = E - 1 + Bias;
  if(E == 1)
    frac = 0;
  else{
    frac = frac << (32 - E + 1);
  }
 
  //check if need round-to-even
  if(E > 24){
    unsigned last = (frac << 23) >> 23;
    if(last < HalfWay){
      // do nothing
      ;
    }
    else if (last > HalfWay){
      frac = frac + (1 << 9);
      if( (frac >> 9) == 0){
	exp = exp + 1;
      }
    }
    else{
      unsigned least = (frac << 22) >> 31;
      if(least == 0){
	//round down, do nothing
	;
      }
      else{
	//round up
	frac = frac + (1 << 9);
	if( (frac >> 9) == 0){
	exp = exp + 1;
	}
      }
    }
  }

  frac = frac >> 9;
  return (sign << 31) + (exp << 23) + frac;

  
  return value;
  return 0;
}


