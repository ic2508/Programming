#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct joc
{
    char nume[20];
    int echipa, hitpoint;
    struct joc *next;
};

struct joc *creare_date()
{
    struct joc *nod = NULL;
    nod = malloc(sizeof(struct joc));
    if( nod == NULL )
    {
        return NULL;
    }
    scanf("%s", nod->nume);
    scanf("%d", &nod->echipa);
    scanf("%d", &nod->hitpoint);
    nod->next = NULL;
    return nod;
}

struct joc *inserare_date(struct joc *head)
{
    struct joc *curent, *nou;
    if( head == NULL )
    {
        head = creare_date();
        return head;
    }
    curent = head;
    while( curent != NULL )
    {
        if( curent->next == NULL )
        {
            nou = creare_date();
            curent->next = nou;
            return head;
        }
        curent = curent->next;
    }
}

struct joc *populare(struct joc *head, int n)
{
    for( int i = 0; i < n; ++i )
    {
        head = inserare_date(head);
    }
    return head;
}


int verificare(struct joc *head, int n)
{
    int e1 = 0, e2 = 0;
    struct joc *copie = NULL;
    for( int i = 0; i < n; ++i )
    {
        if( head->echipa == 1)
        {
            e1 += head->hitpoint;
        }
        else
        {
            e2 += head->hitpoint;
        }
    }
    
    return ( e1>e2 ? printf("2\n"): printf("1\n") );
}

void hit(struct joc *head)
{
    int hit, contor = 0;
    int e1 = 0, e2 = 0;
    while( true )
    {
        scanf("%d", &hit);
        if( hit != 100 )
        {
            contor++;
            if( hit != -1 )
            {
                if( contor%2 == 1 )
                {
                    e1++;
                }
                else
                {
                    e2++;
                }
            }
        }
        else
        {
            break;
        }
    }
    printf("%d\n%d\n", e1, e2);
}

void hp(struct joc *head)
{
    
}

void display(struct joc *head)
{
    struct joc *copie = head;
    for( int i = 1; i <= 2; ++i )
    {
        copie = head;
        while( copie != NULL )
        {
            if( copie->echipa == i)
            {
                printf("%s %d %d\n", copie->nume, copie->echipa, copie->hitpoint);
            }
            copie = copie->next;
        }
    }
}

int main()
{
    int nr_player, test;
    struct joc *jucatori = NULL;
    
    scanf("%d", &nr_player);
    jucatori = populare( jucatori, nr_player );
    scanf("%d", &test);
    
    switch( test )
    {
        case 1:
        {
            display( jucatori );
            break;
        }
        case 2:
        {
            verificare( jucatori, nr_player);
            break;
        }
        case 3:
        {
            hit( jucatori );
            break;
        }
        case 4:
        {
            hp( jucatori );
            break;
        }
    }
    return 0;
}