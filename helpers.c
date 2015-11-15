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
 * Does Linear Search
 *
 * Checked all green with check50: 
 * https://sandbox.cs50.net/checks/a814b06b7c644323b4540a91cc2cde4d
 */
bool searchLinear(int value, int values[], int n)
{
    while (n > 0) 
    {
        int mid = round(n/2);
        
        if (values[mid] == value) return true;
        
        else if (values[mid] > value)
        {
            for (int i = mid; i > 0; i--)
            {
                if (values[i] == value) return true;
            }
        }
            
        else if (values[mid] < value)
        {
            for (int i = mid; i < n; i++)
            {
                if (values[i] == value) return true;
            }
        }
        
        n--;
    }
    return false;
} 

/*
 * Returns true if value is in array of n values, else false.
 * Does Binary Search
 *
 * Checked all green with check50:
 * https://sandbox.cs50.net/checks/362b3a508b12429ab2bada945152a231
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
        return false;
    }
    
    do
    {
        if (values[(n/2)] == value)
        {
            return true;
        }
        else if (values[(n/2)] > value)
        {
            int stack[(n/2)];
            for (int i = 0; i < n/2; i++)
            {
                stack[i] = values[i];
            }
            return search(value, stack, n/2);
        }
        else
        {
            int length = n - (n/2) - 1;
            int stack[length];
            for (int i = 0; i < length; i++)
            {
                stack[i] = values[(n/2)+1+i];
            }
            return search(value, stack, length);
        }
    }
    while (n > 0);
    
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
