#ifndef ESTRELA_H
#define ESTRELA_H

#define ORDEM 2

#define TRUE 1
#define FALSE 0

 typedef struct{
        int key;
        //example of data items
        long int data1;
        char data2[1000];
        char data3[5000];
    }ItemType;

 typedef enum{Internal,External} TypeIntExt;

 typedef struct PageType* PointerType;

 typedef struct PageType{
    TypeIntExt pt;
    union{
        struct{
            int ni;
            int ri[2*ORDEM];
            PointerType pi[2*ORDEM+1];
        }U0;

        struct {
            int ne;
            ItemType re[2*ORDEM];
        }U1;
    }UU;
 }PageType;

 void initializeBStar(PointerType*);

 void insertBStar(PointerType*,ItemType);

 void ins(ItemType,PointerType,short*,int*,PointerType*);

 void insertInternal(PointerType,int,PointerType);

 void insertExternal(PointerType,ItemType);

 short searchStar(PointerType,ItemType*);

#endif