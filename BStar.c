#include "BStar.h"
#include <stdlib.h>
#include <stdio.h>

void initializeBStar(PointerType* star){
    (*star) = NULL;
}

void insertBStar(PointerType *ap,ItemType item){
    PageType *apTemp;
    PageType *apReturn;
    short grown_up;
    int return_key;

    ins(item,*ap,&grown_up,&return_key,&apReturn);

    if(grown_up){
        apTemp = (PageType*)malloc(sizeof(PageType));
        apTemp->pt = Internal;
        apTemp->UU.U0.ni = 1;
        apTemp->UU.U0.ri[0] = return_key;
        apTemp->UU.U0.pi[1] = apReturn;
        apTemp->UU.U0.pi[0] = *ap;
        *ap = apTemp;
    }  
}

void ins(ItemType reg,PointerType ap,short*grown_up,int*return_key,PointerType*apReturn){
    int i=1,j;
    PointerType apTemp;

    if(ap==NULL){
        (*grown_up) = TRUE;
        (*return_key) = reg.key;

        apTemp = (PageType*)malloc(sizeof(PageType));
        apTemp->pt = External;
        apTemp->UU.U1.ne = 1;
        apTemp->UU.U1.re[0] = reg;

        (*apReturn) = apTemp;
        return;
    }

    if(ap->pt==Internal){

        while(i<ap->UU.U0.ni && reg.key>ap->UU.U0.ri[i-1])
            i++;

        if(reg.key<ap->UU.U0.ri[i-1])
            ins(reg,ap->UU.U0.pi[i-1],grown_up,return_key,apReturn);
        else
            ins(reg,ap->UU.U0.pi[i],grown_up,return_key,apReturn);

        if(!*grown_up)
            return;

        if(ap->UU.U0.ni<2*ORDEM){
            insertInternal(ap,*return_key,*apReturn);
            (*grown_up) = FALSE;
            return;
        }

        //Create a new page
        apTemp = (PointerType)malloc(sizeof(PageType));
        apTemp->pt = Internal;
        apTemp->UU.U0.ni = 0;
        apTemp->UU.U0.pi[0] = NULL;

       if(i<ORDEM+1){
          insertInternal(apTemp,ap->UU.U0.ri[2*ORDEM-1],ap->UU.U0.pi[2*ORDEM]);
          ap->UU.U0.ni--;
          insertInternal(ap,*return_key,*apReturn);
       }
       else{
          insertInternal(apTemp,*return_key,*apReturn);
       }

       for(j=ORDEM+2;j<=2*ORDEM;j++)
            insertInternal(apTemp,ap->UU.U0.ri[j-1],ap->UU.U0.pi[j]);

        ap->UU.U0.ni = ORDEM;
        apTemp->UU.U0.pi[0] = ap->UU.U0.pi[ORDEM+1];
        (*return_key) = ap->UU.U0.ri[ORDEM];
        (*apReturn) = apTemp;
        return;
    }



    //if external page
    while(i<ap->UU.U1.ne && reg.key > ap->UU.U1.re[i-1].key)
            i++;

    if(reg.key == ap->UU.U1.re[i-1].key){
        printf("Register already in tree!\n");
        (*grown_up) = FALSE;
        return;
    }

    //Caso a página tenha espaço
    if(ap->UU.U1.ne < 2*ORDEM){
        insertExternal(ap,reg);
        (*grown_up) = FALSE;
        return;
    }

    //criando uma nova página
    apTemp = (PointerType)malloc(sizeof(PageType));
    apTemp->pt = External;
    apTemp->UU.U1.ne = 0;

    if(i<ORDEM+1){
        insertExternal(apTemp,ap->UU.U1.re[2*ORDEM-1]);
        ap->UU.U1.ne --;
        insertExternal(ap,reg);
    }
    else{
        insertExternal(apTemp,reg);
    }

    for(j=ORDEM+1;j<=2*ORDEM;j++)
         insertExternal(apTemp,ap->UU.U1.re[j-1]);   

    ap->UU.U1.ne = ORDEM+1;
    
    (*return_key) = ap->UU.U1.re[ORDEM].key;
    (*apReturn) = apTemp;
    
}

void insertInternal(PointerType ap,int key,PointerType apDir){
    
    int k;
    k = ap->UU.U0.ni;

    while(k>0)
    {
        if(key>=ap->UU.U0.ri[k-1])
            break; 
        
        ap->UU.U0.ri[k] = ap->UU.U0.ri[k-1];
        ap->UU.U0.pi[k+1] = ap->UU.U0.pi[k];
        k--;
    }
    ap->UU.U0.ri[k] = key;
    ap->UU.U0.pi[k+1] = apDir;
    ap->UU.U0.ni++;
}

void insertExternal(PointerType ap,ItemType reg){
    
    int k;
    k = ap->UU.U1.ne;

    while(k>0)
    {
        if(reg.key>=ap->UU.U1.re[k-1].key)
            break; 
        
        ap->UU.U1.re[k] = ap->UU.U1.re[k-1];
        k--;
    }
    ap->UU.U1.re[k] = reg;
    ap->UU.U1.ne++;
}

short searchStar(PointerType ap,ItemType*x){
    int i=1;
    if(ap->pt==Internal){
        while(i<ap->UU.U0.ni && x->key > ap->UU.U0.ri[i-1])
            i++;

        if(x->key < ap->UU.U0.ri[i-1])
            searchStar(ap->UU.U0.pi[i-1],x);
        else
            searchStar(ap->UU.U0.pi[i],x);
    }
    else{
         while(i<ap->UU.U1.ne && x->key > ap->UU.U1.re[i-1].key)
            i++;

        if(x->key == ap->UU.U1.re[i-1].key){
            *x = ap->UU.U1.re[i-1];
            return TRUE;
        }            
        else
            return FALSE;
        }
   

}