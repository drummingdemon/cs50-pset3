#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int values[], int n)
{
    for (int i = 0; i < (n - 1); i++)
    {
        bool found = false; 
        
        for (int j = i+1; j < n; j++)
        {
            int min = 0;
            int temp = 0;
            
            if (values[j] < values[i])
            {
                min = values[j];
                found = true;
            }
            
            if (found)
            {
                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }   
           
        }
    }
    return;
}

int main(int argc, string argv[])
{
    int values[4];
    
    values[0] = 100;
    values[1] = 321;
    values[2] = 422;
    values[3] = 9;

    for (int i=0; i<4; i++)
    {
        printf("%d\n", values[i]);
    }        
    
    sort(values, 4);
    
    printf("\n");
    
    for (int i=0; i<4; i++)
    {
        printf("%d\n", values[i]);
    }
    return 0;
}
