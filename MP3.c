//
//  Maxheapify.c
//  
//
//  
//

#include <stdio.h>
#include <stdlib.h>

typedef struct newstruct {
    int size;
    int array[100];
}heap;


void printHEAP(heap * A)
{
    for(int i =0; i<A->size; i++){
        printf("%d ",A->array[i]);
    }
    printf("\n\n");
}

int parent(int i){
    return (i-1)/2;
}
int left_child(int i){
    return 2*i+1;
}
int right_child(int i){
    return 2*i+2;
}
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void maxheapify(heap *A, int index){
    printf("in maxheapify\n");
    int left = left_child(index);
    int right = right_child(index);
    int largest=index;
    
    if (left<=A->size && A->array[left]>A->array[index]) {
        largest=left;
    }
    if( right<=A->size && A->array[right]>A->array[largest]){
        largest=right;
    }
    if(largest!=index){
        int buffer;
        
        buffer=A->array[index];
        A->array[index]=A->array[largest];
        A->array[largest]=buffer;
        
        maxheapify(A,largest);
        printf("finished maxheapify \n");
    }
}

void buildmaxheap(heap *A){
    printf("In buildmax-heap\n");
    int i;
    for (i= ((A->size)/2)-1;i>=0;i--) {
        maxheapify(A,i);
    }
    printf("finished buildmax-heap\n");
}

void insertkey(heap *A, int new){
    printf("in Insertkey\n");
    A->array[A->size]=new;
    A->size=A->size+1;
    printf("the size is %d\n",A->size);
    
    buildmaxheap(A);
    maxheapify(A,A->size/2);
    printf("finished insertkey \n");
}

void extractmax(heap *A){
    printf("in extractmax \n");
    printf("Extracting the MAX value Which is %d\n",A->array[0]);
    A->array[0]=A->array[A->size-1];
    A->array[A->size-1]=0;
    A->size=A->size-1;
    
    
    buildmaxheap(A);
    maxheapify(A,0);
    printf("The new MAX value is %d\n",A->array[0]);
    printf("finsihed extractmax\n");
}

void changekey(heap *A, int key,  int new){
    printf("in changekey\n");
    printf("Chaning the value of %d to %d\n",A->array[key],new);
    A->array[key]=new;
    buildmaxheap(A);
    maxheapify(A,key);
    printf("finished changekey\n");
}

void deletekey( heap *A, int key){
    printf("in Deletekey\n");
    printf("Delteing the following key which is %d\n",A->array[key]);
    int last=A->array[A->size-1];
    A->array[A->size-1]=0;
    A->size=A->size-1;


    changekey(A,key, last);

    
    buildmaxheap(A);
    maxheapify(A,key);
    printf("finished deletekey\n");
}

heap* filescan(FILE *f){
    printf("in filescan\n");
    if (!f) {
        printf("File not found\n");
        exit(0);
    }else{
        heap  * A=malloc(sizeof(heap));
        int size;
        
        fscanf(f, "%d", &size);
        
        A->size=size;
        for(int j =0; j<100;j++)
        {
            A->array[j]=0;
        }
        
        for(int i=0; i<size;i++){
            fscanf(f,"%d", &A->array[i]);
        }
        printf("in filescan\n");
        
        buildmaxheap(A);
        
        char letter;
        int firstp;
        int secondp;
        
        while(!feof(f)){
            fscanf(f,"%c", &letter);
            
            if (A->size == 0) {
                break;
            }
            
            switch (letter) {
                case 'I':
                    fscanf(f,"%d", &firstp);
                    printf("The value of the key that is being inserted is %d\n",firstp);
                    insertkey(A,firstp);
                    printHEAP(A);
                    
                    break;
                    
                case 'E':
                    extractmax(A);
                    printHEAP(A);
                    break;
                    
                case 'C':
                    fscanf(f,"%d %d", &firstp, &secondp);
                    printf("The key that is being changed is %d and is being changed with %d\n",firstp,secondp);
                    changekey(A,firstp-1, secondp);
                    printHEAP(A);
                    break;
                    
                case 'D':
                    fscanf(f,"%d", &firstp);
                    printf("The key that is being deleted is %d\n",firstp);
                    deletekey(A,firstp-1);
                    printHEAP(A);
                    break;
                    
                default:
                    break;
            }
        }
        
        return A;
    }
}



int main(void){
    FILE *f;
    
    f=fopen("file.txt", "r");
    
    heap * A=filescan(f);
    
    fclose(f);
    printf("\n");


    printf("FINAL ANS:\n");
    printHEAP(A);
    printf("\n");
    return 0;
}
