#ifndef __USERPROG__
#define __USERPROG__


typedef struct cir_buff {
  int head;
  int tail;
  char c[BUFFERSIZE];

} cir_buff;

#define PRODUCER "producer.dlx.obj"
#define CONSUMER "consumer.dlx.obj"

#endif
