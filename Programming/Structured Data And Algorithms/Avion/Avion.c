#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct pasager
{
    char nume[20],prenume[20];
    int locul;
    struct pasager *next;
};
struct pasager *creare_lista(struct pasager *head,char cuvant[20])
{
    struct pasager *nod_curent,*nod_nou;
    if(head==NULL)
    {
        head=malloc(sizeof(struct pasager));
        scanf("%s",head->nume);
        scanf("%s",head->prenume);
        head->next=NULL;
        return head;
    }
    nod_curent=head;
    while(nod_curent->next!=NULL)
    {
        nod_curent=nod_curent->next;
    }
    nod_nou=malloc(sizeof(struct pasager));
    if(nod_nou!=NULL)
    {
        strcpy(nod_nou->nume,cuvant);
        scanf("%s",nod_nou->prenume);
        nod_nou->next=NULL;
    }
    nod_curent->next=nod_nou;
    return head;
}
struct pasager *creare_lista2(struct pasager *head,char cuvant[20])
{
    struct pasager *nod_curent,*nod_nou;
    if(head==NULL)
    {
        head=malloc(sizeof(struct pasager));
        scanf("%s",head->nume);
        scanf("%s",head->prenume);
        scanf("%d",&head->locul);
        head->next=NULL;
        return head;
    }
    nod_curent=head;
    while(nod_curent->next!=NULL)
    {
        nod_curent=nod_curent->next;
    }
    nod_nou=malloc(sizeof(struct pasager));
    if(nod_nou!=NULL)
    {
        strcpy(nod_nou->nume,cuvant);
        scanf("%s",nod_nou->prenume);
        scanf("%d",&nod_nou->locul);
        nod_nou->next=NULL;
    }
    nod_curent->next=nod_nou;
    return head;
}
void afisare(struct pasager *head)
{
    struct pasager *nod_curent=head;
    while(nod_curent!=NULL)
    {
        printf("%s ",nod_curent->nume);
        printf("%s\n",nod_curent->prenume);
        nod_curent=nod_curent->next;
    }
}
void afisare_configuratie(struct pasager *head)
{
    struct pasager *nod_curent=head;
    int nr_pasageri=0,nr=4,locuri_rand,randuri,locuri_bune,randuri_bune;
    while(nod_curent!=NULL)
    {
        nr_pasageri++;
        nod_curent=nod_curent->next;
    }
    locuri_bune=randuri_bune=nr_pasageri;
    while(nr!=0)
    {
        scanf("%d",&locuri_rand);
        scanf("%d",&randuri);
        if(locuri_rand*randuri>=nr_pasageri && locuri_bune*randuri_bune>locuri_rand*randuri)
        {
            locuri_bune=locuri_rand;
            randuri_bune=randuri;
        }
        nr--;
    }
    printf("%d %d\n",locuri_bune,randuri_bune);
}
void afisare_locuri(struct pasager *head,int locuri_rand,int randuri)
{
    struct pasager *nod_curent=head;
    int locuri_geam=randuri*2,loc=1,loc1=1,loc2=locuri_rand*randuri,pas=0,loc3=2;
    while(nod_curent!=NULL)
    {
        if(locuri_geam>0)
        {
            nod_curent->locul=loc;
            pas++;
            if(pas==1)
            {
                loc=loc2;
            }
            else
                if(pas==2)
                {
                    loc1+=locuri_rand-1;
                    loc=loc1;
                }
                else
                    if(pas==3)
                    {
                        loc2-=locuri_rand-1;
                        loc=loc2;
                    }
                    else
                    {
                        pas=0;
                        loc1++;
                        loc2--;
                        loc=loc1;
                    }
            locuri_geam--;
        }
        else
        {
            loc=loc3;
            nod_curent->locul=loc;
            if(loc==locuri_rand-1)
                loc3+=3;
            else
                loc3++;
        }
        nod_curent=nod_curent->next;
    }
    struct pasager *nod_urmator;
    char t_nume[20],t_prenume[20],t_loc;
    for(nod_curent=head;nod_curent!=NULL;nod_curent=nod_curent->next)
        for(nod_urmator=nod_curent->next;nod_urmator!=NULL;nod_urmator=nod_urmator->next)
            if(nod_curent->locul>nod_urmator->locul)
            {
                strcpy(t_nume,nod_curent->nume);
                strcpy(nod_curent->nume,nod_urmator->nume);
                strcpy(nod_urmator->nume,t_nume);
                
                strcpy(t_prenume,nod_curent->prenume);
                strcpy(nod_curent->prenume,nod_urmator->prenume);
                strcpy(nod_urmator->prenume,t_prenume);
                
                t_loc=nod_curent->locul;
                nod_curent->locul=nod_urmator->locul;
                nod_urmator->locul=t_loc;
            }
    nod_curent=head;
    while(nod_curent!=NULL)
    {
        printf("%s ",nod_curent->nume);
        printf("%s ",nod_curent->prenume);
        printf("%d\n",nod_curent->locul);
        nod_curent=nod_curent->next;
    }
}
void afisare_locuri2(struct pasager *head,int locuri_rand,int randuri)
{
    struct pasager *nod_curent=head;
    
    int locuri_geam=randuri*2,loc=1,loc1=1,loc2=locuri_rand*randuri,pas=0,loc3=2;
    
    while(nod_curent!=NULL)
    {
        if(locuri_geam>0)
        {
            nod_curent->locul=loc;
            pas++;
            if(pas==1)
            {
                loc=loc2;
            }
            else
                if(pas==2)
                {
                    loc1+=locuri_rand-1;
                    loc=loc1;
                }
                else
                    if(pas==3)
                    {
                        loc2-=locuri_rand-1;
                        loc=loc2;
                    }
                    else
                    {
                        pas=0;
                        loc1++;
                        loc2--;
                        loc=loc1;
                    }
            locuri_geam--;
        }
        else
        {
            loc=loc3;
            nod_curent->locul=loc;
            if(loc==locuri_rand-1)
                loc3+=3;
            else
                loc3++;
        }
        nod_curent=nod_curent->next;
    }
    struct pasager *nod_urmator;
    char t_nume[20],t_prenume[20],t_loc;
    for(nod_curent=head;nod_curent!=NULL;nod_curent=nod_curent->next)
        for(nod_urmator=nod_curent->next;nod_urmator!=NULL;nod_urmator=nod_urmator->next)
            if(nod_curent->locul>nod_urmator->locul)
            {
                strcpy(t_nume,nod_curent->nume);
                strcpy(nod_curent->nume,nod_urmator->nume);
                strcpy(nod_urmator->nume,t_nume);
                
                strcpy(t_prenume,nod_curent->prenume);
                strcpy(nod_curent->prenume,nod_urmator->prenume);
                strcpy(nod_urmator->prenume,t_prenume);
                
                t_loc=nod_curent->locul;
                nod_curent->locul=nod_urmator->locul;
                nod_urmator->locul=t_loc;
            }
    nod_curent=head;
    while(nod_curent!=NULL)
    {
        printf("%s ",nod_curent->nume);
        printf("%s ",nod_curent->prenume);
        printf("%d\n",nod_curent->locul);
        nod_curent=nod_curent->next;
    }
}
int main()
{
    int locuri_rand,randuri,comanda;
    char oprire[20];
    scanf("%d",&comanda);
    scanf("%d %d",&locuri_rand,&randuri);
    struct pasager *pasageri=NULL;
    switch(comanda)
    {
        case 1:
        {
            while(strcmp(oprire,"STOP")!=0)
            {
                pasageri=creare_lista(pasageri,oprire);
                scanf("%s",oprire);
            }
            afisare(pasageri);
            break;
        }
        case 2:
        {
            while(strcmp(oprire,"STOP")!=0)
            {
                pasageri=creare_lista(pasageri,oprire);
                scanf("%s",oprire);
            }
            afisare_configuratie(pasageri);
            break;
        }
        case 3:
        {
            while(strcmp(oprire,"STOP")!=0)
            {
                pasageri=creare_lista(pasageri,oprire);
                scanf("%s",oprire);
            }
            afisare_locuri(pasageri,locuri_rand,randuri);
        }
        case 4:
        {
            while(strcmp(oprire,"STOP")!=0)
            {
                pasageri=creare_lista2(pasageri,oprire);
                scanf("%s",oprire);
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return 0;
}