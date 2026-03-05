#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Texas{
    char *nume;
    int *carti;
};

void afisare(struct Texas *p_texas, int *v,int n){
    for(int i=0;i<n;++i){
        printf("%s\n",(p_texas+i)->nume);
        for(int j=0;j<2;++j){
        printf("%d ",(p_texas+i)->carti[j]);
        }
        printf("\n");
    }
    for(int i=0;i<5;++i){
        printf("%d ",*(v+i));
    }    
}

void sort(int nr_elemente, int* ptr) 
{ 
    int i, j, temp; 
  
    // Sortare folosind pointeri catre elemente
    for (i = 0; i < nr_elemente - 1; i++) { 
  
        for (j = i + 1; j < nr_elemente; j++) { 
  
            if (*(ptr + j) < *(ptr + i)) { 
  
                temp = *(ptr + i); 
                *(ptr + i) = *(ptr + j); 
                *(ptr + j) = temp; 
            } 
        } 
    } 
}


void ordonare(struct Texas *p_texas, int *v,int n){
    int val=0;
    int ct=0;
    v = (int*)realloc(v, 7 * sizeof(int));
    for(int i=0;i<n;++i){
        for(int j=0;j<2;++j){
            for(int k=0;k<5;++k){
            if(v[k]!=(p_texas+i)->carti[j] && v[k]<(p_texas+i)->carti[j])
            ++val;
            if(val==5){
                v[5+ct]=v[k];
                ++ct;
                val=0;
            }
            }
        }
        //sort(n,v);
        for(int k1=0;k1<7;++k1){
            printf("%d ",v[k1]);
    }
    printf("\n");
    }
}


int main(){
    int n,*v,*v_copie,c;
    v = (int*)calloc(5,sizeof(int));
    v_copie = (int*)calloc(5,sizeof(int));
    scanf("%d",&n);
    struct Texas *p_texas;
    p_texas=(struct Texas*)malloc(n*sizeof(struct Texas));
    for(int i=0;i<n;++i){
        (p_texas+i)->nume=(char*)calloc(128,sizeof(char));
        (p_texas+i)->carti=(int*)calloc(2,sizeof(int));
        scanf("%s",(p_texas+i)->nume);
        for(int j=0;j<2;++j){
        scanf("%d",&(p_texas+i)->carti[j]);
        }
    }
    for(int i=0;i<5;++i){
        scanf("%d",(v+i));
    }
    for(int i=0;i<5;++i){
        *(v_copie+i)=*(v+i);
    }
    scanf("%d",&c);
    switch(c){
        case 1:
        afisare(p_texas,v,n);
        break;
        case 2:
        //sort(n,v);
        ordonare(p_texas,v,n);
        break;
    }
    
    
    
    
    
    
    
    return 0;
}