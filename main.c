#include "BStar.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    PointerType star;
    ItemType item;
    ItemType toSearch;
    toSearch.key = 76;
    short found;
    initializeBStar(&star);
    srand(time(NULL));

    for(int i=0;i<100;i++){
        item.key = i;
        item.data1 = rand()%1000;
        insertBStar(&star,item);
    }

    found = searchStar(star,&toSearch);

    if(found)
        printf("register found: key: %d data1: %li \n",toSearch.key,toSearch.data1);
    else
        printf("register not found\n");
    
    return 0;
}