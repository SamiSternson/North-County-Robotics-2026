#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "custom_math.h"

int INT_AVG(int arr[],int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum / n;
}

float FLOAT_AVG(float arr[],int n)
{
    float sum = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum / n;
}

float STDEV(float arr[], int n)
{
    float mean = FLOAT_AVG(arr, n);
    float sum_sq_diff = 0.0;
    for (int i = 0; i < n; i++)
    {
        sum_sq_diff += (arr[i] - mean) * (arr[i] - mean);
    }
    return sqrt(sum_sq_diff / n);
}

int* INT_KMEANS(int data[], int n, int k)
{
    // Initializes Centroids to be evenly spaced values in data
    //This asumes that the data is sorted
    int* centroids = (int*)malloc(k * sizeof(int));
    int partition_size=n/k;
    //Sets initial centroid 
    centroids[0] = data[partition_size/2];
    //Extrapolates to rest of centroids
    for (int i = 1; i <k; i++)
    {
        centroids[i] = data[centroids[i-1]+partition_size];
    }
    //Calculates distances from each point to each centroid
    int distances[k][n];
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<n; j++)
        {
            distances[i][j]=INT_EUCLIDIAN_DISTANCE(centroids[i], data[centroids[i]], j, data[j]);
            printf("%d", distances[i][j]);
        }
    }
    //Groups points into clusters based on closest centroid
    /*int clusters[k][n];
    for (int i=0; i<k; i++)
    {
    
    }*/
    return centroids;
}

int INT_EUCLIDIAN_DISTANCE(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x1-x2), 2)+pow((y1-y2), 2));
}

int* INTEGER_MIN(int arr[], int n)
{
    int* mins = (int*)malloc(2 * sizeof(int));
    mins[0]=0;
    mins[1]=arr[0];
    for (int i=1; i<n; i++)
    {
        if (arr[i]<mins[1])
        {
            mins[0]=i;
            mins[1]=arr[i];
        }
    }
    return mins;

}