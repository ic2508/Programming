#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct navigare
{
    char directie[11];
    struct navigare *next;
};

struct navigare *creare_data()
{
    struct navigare *nod = NULL;
    nod = malloc(sizeof(struct navigare));
    if( nod == NULL )
    {
        return NULL;
    }
    scanf("%s", nod->directie);
    nod->next = NULL;
    return nod;
}

struct navigare *inserare_date(struct navigare *head)
{
    struct navigare *curent, *nou;
    if( head == NULL )
    {
        head = creare_data();
        return head;
    }
    curent = head;
    while( curent != NULL )
    {
        if( curent->next == NULL )
        {
            nou = creare_data();
            curent->next = nou;
            return head;
        }
        curent = curent->next;
    }
}

struct navigare *adaugare_nod(struct navigare *head)
{
    head = inserare_date( head );
    return head;
}

void home(struct navigare *head, int n)
{
    for( int i = 0; i < n; ++i )
    {
        struct navigare *curent = head;
        for( int j = 0; j < n-i-1; ++j )
        {
            curent = curent->next;
        }
        if( strcmp(curent->directie, "sus")==0 )
        {
            printf("jos\n");
        }
        if( strcmp(curent->directie, "jos")==0 )
        {
            printf("sus\n");
        }
        if( strcmp(curent->directie, "stanga")==0 )
        {
            printf("dreapta\n");
        }
        if( strcmp(curent->directie, "dreapta")==0 )
        {
            printf("stanga\n");
        }
    }
}

void position( struct navigare *head, int x, int y )
{
    while( head!= NULL )
    {
        if( strcmp(head->directie, "sus")==0 )
        {
            x++;
        }
        if( strcmp(head->directie, "jos")==0 )
        {
            x--;
        }
        if( strcmp(head->directie, "stanga")==0 )
        {
            y--;
        }
        if( strcmp(head->directie, "dreapta")==0 )
        {
            y++;
        }
        head = head->next;
    }
    printf("%d %d\n", x, y);
}
/*
void obstacol(struct navigare *head, int x, int y)
{
    
}
*/
void display( struct navigare *head )
{
    while( head != NULL )
    {
        printf("%s\n", head->directie);
        head = head->next;
    }
}

int main()
{
    int m, n;
    int x, y;
    int test, c = 0;
    struct navigare *comenzi = NULL;
    
    scanf("%d%d", &m, &n);
    scanf("%d%d", &x, &y);
    
    while( 1 )
    {
        scanf("%d", &test);
        switch( test )
        {
            case 1:
            {
                c++;
                comenzi = adaugare_nod( comenzi );
                break;
            }
            case 2:
            {
                display( comenzi );
                break;
            }
            case 3:
            {
                home( comenzi, c );
                break;
            }
            case 4:
            {
                position( comenzi, x, y );
                break;
            }
            case 5:
            {
                //obstacol( position, x, y );
                break;
            }
            default:
            {
                exit(0);
            }
        }
        if( test!= 1 )
        {
            break;
        }
    }
    return 0;
}