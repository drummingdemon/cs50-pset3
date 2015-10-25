/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"
#include <stdio.h>
#include <math.h>

/**
 * Returns true if value is in array of n values, else false.
 * Does Binary Search
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    
    if (fmod(n, 2) != 0)
    {
        do
        {   
            if (values[n/2] == value)
            {
                return true;
            }
            
            else if (values[n/2] < value)
            {   
                int stack[(n/2)-1];
                
                for (int i=0; i<(n/2); i++)
                {
                    stack[i] = values[(n/2)+i+1];
                }
             
                return search(value, stack, (n/2));
            }
            
            else if (values[n/2] > value)
            {   
                int stack[n/2];
                
                for (int i=0; i<(n/2); i++)
                {
                    stack[i] = values[i];
                }
               
                return search(value, stack, (n/2));
            }
            
            else return false;
        }
        while (n > 0);
    }
    else
    {
        do
        {   
            if (values[n/2] == value) return true;
            
            else if (values[n/2] < value)
            {   
                int stack[n/2];
                
                for (int i=0; i<(n/2); i++)
                {
                    stack[i] = values[(n/2)+i];
                }
             
                return search(value, stack, (n/2));
            }
            
            else if (values[n/2] > value)
            {   
                int stack[n/2];
                
                for (int i=0; i<(n/2); i++)
                {
                    stack[i] = values[i];
                }
               
                return search(value, stack, (n/2));
            }
            
            else return false;
        }
        while (n > 0);    
    }

    return false;
} 
 
/**
 * Sorts array of n values using Selection Sort
 */
void sort(int values[], int n)
{
    for (int i = 0; i < (n - 1); i++)
    {
        bool found = false;
        int min = values[i];
        int minPos = 0;
        int temp = 0;
                           
        for (int j = i + 1; j < n; j++)
        {           
            if (values[j] < min)
            {
                min = values[j];
                minPos = j;
                found = true;
            }
        }
        
        if (found)
        {
            temp = values[i];
            values[i] = values[minPos];
            values[minPos] = temp;
        }  
    }
}
