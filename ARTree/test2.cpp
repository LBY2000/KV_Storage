#include <iostream>
#include "art.h"
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include <unistd.h>
using namespace std;
void clear_cache() {
    int* dummy = new int[1024*1024*256];
    for (int i=0; i<1024*1024*256; i++) {
	dummy[i] = i;
    }

    for (int i=100;i<1024*1024*256;i++) {
	dummy[i] = dummy[i-rand()%100] + dummy[i+rand()%100];
    }

    delete[] dummy;
}

/*
int main(int argc,char **argv){
      art_tree *new_art = new art_tree; 
      init_art_tree(new_art);
      unsigned char a[11]={'a','b','c','d','e','f','g','h','i','j','\0'},c[11]="dsdwea";
      int *b=new int,*t=new int;
      *b=10;
      *t=111;
      art_insert(new_art,a,11,b);
      art_insert(new_art,c,11,t);
      int *d=new int,*e=new int;
      d=(int *)art_search(new_art,a,11);
      e=(int *)art_search(new_art,c,11);
      cout<<"d="<<*d<<endl;
      cout<<"e="<<*e<<endl;
      art_tree_destroy(new_art);
    
    return 0;
}
*/
int main(int argc,char **argv){
    if(argc < 3){
      cerr << "Usage: " << argv[0] << " path & numData" << endl;
      exit(1);
    }
    struct timespec start, end;
    uint64_t elapsed;
    art_tree *new_art = new art_tree; 
    init_art_tree(new_art);
    char path[32];
    strcpy(path, argv[1]);
    int numData = atoi(argv[2]);
    string** keys = new string*[numData];
    int **values = new int*[numData];
    int **value_test = new int*[numData];
    for(int i=0;i<numData;i++){
      keys[i]=new string;
      values[i]=new int;
      value_test[i]=new int;
    }
    ifstream ifs;
    ifs.open(path);
    if (!ifs){
      cerr << "No file." << endl;
      exit(1);
    }
    else{
      for(int i=0; i<numData; i++){
        ifs >> *keys[i];
        *values[i]=2*i+1;
        }
      ifs.close();
      cout << path << " is used." << endl;
    }
    cout << "Start Insertion" << endl;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i=0; i<numData; i++){
		  art_insert(new_art,(const unsigned char *)keys[i],8,values[i]);
	  }
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
	  cout << elapsed/1000 << "\tusec\t" << (uint64_t)(1000000*(numData/(elapsed/1000.0))) << "\tOps/sec\tInsertion" << endl;
    //clear_cache();
    clock_gettime(CLOCK_MONOTONIC, &start);
    for(int i=0;i<numData;i++){
      value_test[i]=(int *)art_search(new_art,(const unsigned char *)keys[i],8);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = (end.tv_sec - start.tv_sec)*1000000000 + (end.tv_nsec - start.tv_nsec);
	  cout << elapsed/1000 << "\tusec\t" << (uint64_t)(1000000*(numData/(elapsed/1000.0))) << "\tOps/sec\tSearch" << endl;

    bool is_true=true;
    for(int i=0;i<numData;i++){
      if(*value_test[i]!=2*i+1){
         is_true=false;
         cout<<*value_test[i]<<endl;
      }
    }
    if(is_true){
      cout<<"True"<<endl;
    }else{
      cout<<"false"<<endl;
    }


  return 0;
}