#include "test_endian.h"
// this function returns 1 if the store function
// actually stores value in little endian order.
// otherwise returns 0.
int is_little_endian(void (*store)(int*,int)) {
  int x;
  unsigned char *byte_ptr = (unsigned char*)(&x);
  //this is how you call store function
  //after the function call, value 1234 is stored
  //in the four bytes x is referring to in some order.
  if(*byte_ptr){
    store(&x,1);
  }
  else{
    store(&x,0);
    return 0;
  }

  return 1;
  store(&x, 305419896); 
    return 0;
  //  if(byte_ptr[0] == 0x78 && byte_ptr[1] == 0x56 && byte_ptr[2] == 0x34 && byte_ptr[3] == 0x12)  
  //  return 1;  

  return 0;
}
