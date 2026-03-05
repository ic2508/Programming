#include <stdio.h>
#include <stdlib.h>

struct Labirint{
    int **M;
};

void coordonate(struct Labirint *lab,int *p1,int *p2,char c,int n){
            if(lab->M[*p1-1][*p2]==0 && (*p1-1)>=0 && c=='u'){
                lab->M[*p1-1][*p2]=1;
                *p1=*p1-1;
            }
            else if(lab->M[*p1][*p2-1]==0 && (*p2-1)>=0 && c=='l'){
                lab->M[*p1][*p2-1]=1;
                *p2=*p2-1;
            }
            else if(lab->M[*p1+1][*p2]==0 && (*p1+1)<n && c=='d'){
                lab->M[*p1+1][*p2]=1;
                *p1=*p1+1;
            }
            else if(lab->M[*p1][*p2+1]==0 && (*p2+1)<n && c=='r'){
                lab->M[*p1][*p2+1]=1;
                *p2=*p2+1;
            }
          
   }
   
   void coordonate_n(struct Labirint *lab,int *p1,int *p2,char c,int n){
            while(1){
            if(lab->M[*p1-1][*p2]==0 && (*p1-1)>=0){
                lab->M[*p1][*p2]=-1;
                *p1=*p1-1;
            }
            else if(lab->M[*p1][*p2-1]==0 && (*p2-1)>=0){
                lab->M[*p1][*p2]=-1;
                *p2=*p2-1;
            }
            else if(lab->M[*p1+1][*p2]==0 && (*p1+1)<n){
                lab->M[*p1][*p2]=-1;
                *p1=*p1+1;
            }
            else if(lab->M[*p1][*p2+1]==0 && (*p2+1)<n){
                lab->M[*p1][*p2]=-1;
                *p2=*p2+1;
            }else break;
            }
          
   }
   
   void coordonate_f(struct Labirint *lab,int *p1,int *p2,char c,int n,int p1_c,int p2_c){
            while(1){
            printf("%d %d\n",*p1,*p2);
            if(p1_c==*p1 && p2_c==*p2){
            break;
            }
            if(lab->M[*p1-1][*p2]==(-1) && (*p1-1)>=0){
                lab->M[*p1][*p2]=0;
                *p1=*p1-1;
            }
            else if(lab->M[*p1][*p2-1]==(-1) && (*p2-1)>=0){
                lab->M[*p1][*p2]=0;
                *p2=*p2-1;
            }
            else if(lab->M[*p1+1][*p2]==(-1) && (*p1+1)<n){
                lab->M[*p1][*p2]==0;
                *p1=*p1+1;
            }
            else if(lab->M[*p1][*p2+1]==(-1) && (*p2+1)<n){
                lab->M[*p1][*p2]==0;
                *p2=*p2+1;
            }else break;
            }
          
   }
   
void coordonate_2(struct Labirint *lab, int *p1, int *p2, int n) {
    printf("%d %d\n", *p1, *p2);
    while (1) {
        int pas = (lab->M[*p1][*p2] == 2) ? 2 : 1;

        if (*p1 - pas >= 0 && lab->M[*p1 - pas][*p2] != 1) {
            lab->M[*p1][*p2] = 1;
            *p1 -= pas;
            printf("%d %d\n", *p1, *p2);
        }
        else if (*p2 + pas < n && lab->M[*p1][*p2 + pas] != 1) {
            lab->M[*p1][*p2] = 1;
            *p2 += pas;
            printf("%d %d\n", *p1, *p2);
        }
        else if (*p1 + pas < n && lab->M[*p1 + pas][*p2] != 1) {
            lab->M[*p1][*p2] = 1;
            *p1 += pas;
            printf("%d %d\n", *p1, *p2);
        }
        else if (*p2 - pas >= 0 && lab->M[*p1][*p2 - pas] != 1) {
            lab->M[*p1][*p2] = 1;
            *p2 -= pas;
            printf("%d %d\n", *p1, *p2);
        }
        else {
            break;
        }
    }
}

int main(){
    int n,test;
    char c;
    int p1,p2;
    scanf("%d",&n);
    struct Labirint *lab;
    lab = (struct Labirint*)malloc(sizeof(struct Labirint));
    int M[n][n];
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            scanf("%d",&M[i][j]);
        }
    }
    lab->M=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;++i){
        lab->M[i]=(int*)malloc(n*sizeof(int));
    }
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            lab->M[i][j] = M[i][j];
        }
    }
    scanf("%d %d",&p1,&p2);
    int p1_c=p1;
    int p2_c=p2;
    scanf("%d",&test);
    switch(test){
        case 1:
        getchar();
        while(scanf("%c",&c)!=EOF)
        printf("%c",c);
        break;
        case 2:
        while(scanf("%c",&c)!=EOF)
        coordonate(lab,&p1,&p2,c,n);
        printf("%d %d",p1,p2);
        break;
        case 3:
        coordonate_n(lab,&p1,&p2,c,n);
        coordonate_f(lab,&p1,&p2,c,n,p1_c,p2_c);
        break;
        case 4:
        coordonate_2(lab,&p1,&p2,n);
        break;
    }
}