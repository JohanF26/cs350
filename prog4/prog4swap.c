#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define PAGE_ACCESSES 10000
#define PAGES 100

struct page{
  int pageNum;
  int lastAccessed;
};

void noLocality(int* pagesToAccess);
void lru(int* pagesToAccess, struct page* mainMem, int* retHits, int memSize);

int main(int argc, char** argv){
  //parse the input from the command line
  opterr = 0;


  char* repPolicy;
  char* workload;
  int* pagesToAccess = malloc(PAGE_ACCESSES * sizeof(int));
  int memSize;
  int hits = 0;


  int currArg;
  //switch statement to get command line arguments
  while((currArg = getopt(argc, argv, "m:r:w:")) != -1)
    switch(currArg){
      case 'm':
        memSize = atoi(optarg);
        break;
      case 'r':
        repPolicy = optarg;
        break;
      case 'w':
        workload = optarg;
        break;
      case '?':
        if(optopt == 'm'){
          fprintf (stderr, "-m is missing an argument.\nprog4swap [-m <memory-size>] [-r <replacement-policy>] [-w <workload>]\n");
        } else if(optopt == 'r'){
          fprintf (stderr, "-r is missing an argument.\nprog4swap [-m <memory-size>] [-r <replacement-policy>] [-w <workload>]\n");
        } else if(optopt == 'w'){
          fprintf (stderr, "-w is missing an argument.\nprog4swap [-m <memory-size>] [-r <replacement-policy>] [-w <workload>]\n");
        } else{
          fprintf(stderr, "Unknown option character %d.\nprog4swap [-m <memory-size>] [-r <replacement-policy>] [-w <workload>]\n", optopt);
        }
        exit(1);
      default:
        abort();
    }
    //end of while loop

    //switch statement to generate pages based on workload

    if(strcmp(workload, "No-locality") == 0){
      noLocality(pagesToAccess);
    } else if(strcmp(workload, "80-20") == 0){
      //Alan's code
    } else if(strcmp(workload, "Looping") == 0){
      //Alan's code
    } else{
      return 0;
    }

    //declare and initialize the main memory which is a page pointer
    struct page* mainMem = malloc(memSize * sizeof(struct page));
    for(int i = 0; i < memSize; i++){
      //there is no page 0
      //access time 0 means not accessed yet
      mainMem[i].pageNum = 0;
      mainMem[i].lastAccessed = 0;
    }

    //switch statement to choose between the different page replacement algorithms
    printf("%s\n", repPolicy);

    if(strcmp(repPolicy, "OPT") == 0){
      //Alan's function
    } else if(strcmp(repPolicy, "LRU") == 0){
      lru(pagesToAccess, mainMem, &hits, memSize);
    } else if(strcmp(repPolicy, "FIFO") == 0){

    } else if(strcmp(repPolicy, "Rand") == 0){

    } else if(strcmp(repPolicy, "Clock") == 0){

    } else{
      return 0;
    }

//    fprintf(stderr, "prog4swap [-m %d] [-r %s] [-w %s]\n", memSize, repPolicy, workload);
    printf("hits: %d\n", hits);
    return 0;
}

//////////         WORKLOADS         //////////

void noLocality(int* pagesToAccess){
  //seed the random with the time
  srand(time(0));
  for(int i = 0; i < PAGE_ACCESSES; i++){
    //keeps pages between 0-99 so we add 1
    pagesToAccess[i] = (rand() % PAGES) + 1;
  }
}

//////////         REPLACEMENT POLICIES         //////////

void lru(int* pagesToAccess, struct page* mainMem, int* retHits, int memSize){
  int hits = 0;
  struct page leastRecent;
  int lrIndex;
  int h = 0;

  //p stands for page and m stands for memory
  //p index of page we are looking for
  //m index of current page in main memory
  for(int p = 0; p < PAGE_ACCESSES; p++){
    //printf("looking for %d\n", pagesToAccess[p]);
    leastRecent.lastAccessed = p + 1;
    h = 0;
    for(int m = 0; m < memSize; m++){
      //printf("Value at %d: page: %d, time: %d\n" , m, mainMem[m].pageNum, mainMem[m].lastAccessed);
      if(p == 0){
        //load first value into main memory
        mainMem[0].pageNum = pagesToAccess[0];
        mainMem[0].lastAccessed = 1;
        break;
      } else{
        if(mainMem[m].pageNum == pagesToAccess[p]){
          //increase hits and update the acess time
          hits += 1;
          //printf("found %d\n", mainMem[m].pageNum);
          mainMem[m].lastAccessed = p + 1;
          h = 1;
          //printf("hits %d\n", hits);
          break;
        } else if(mainMem[m].lastAccessed < leastRecent.lastAccessed){
          //if last time a page was accessed is less than the previous
          //smallest access time recorded then this is the least recent
          lrIndex = m;
          leastRecent.pageNum = mainMem[m].pageNum;
          leastRecent.lastAccessed = mainMem[m].lastAccessed;
        }
      }

    }
    //move to the next page if there was a hit
    if(h == 1){
      continue;
    } else{
      //change last recently used to page asked to access
      //printf("Replaced page %d with page %d\n", mainMem[lrIndex].pageNum, pagesToAccess[p]);
      mainMem[lrIndex].pageNum = pagesToAccess[p];
      mainMem[lrIndex].lastAccessed = p + 1;
    }

  }
  //update the amount of hits
  *retHits = hits;

}













//////
