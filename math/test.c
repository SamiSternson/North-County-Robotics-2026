#include "custom_math.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int* INT_KMEANS(int data[], int n, int k);
int INT_EUCLIDIAN_DISTANCE(int x1, int y1, int x2, int y2);
int* INTEGER_MIN(int arr[], int n);
int main()
{
int n = 100;
int k=2;
int arr1[n];
for (int i=0; i<n; i++)
{
arr1[i]=i;
} 
int* centroids= INT_KMEANS(arr1, n, k);
printf("Centroids:%d, %d\n",centroids[0], centroids[1]);
free(centroids);
return 0;
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
    int distances[n][k];
    for (int i=0; i<k; i++)
    {
        for (int j=0; j<n; j++)
        {
            distances[i][j]=INT_EUCLIDIAN_DISTANCE(centroids[i], data[centroids[i]], j, data[j]);
        }
    }
    //Groups points into clusters based on closest centroid
    int groups[n][2];
    for (int i=0; i<n; i++)
    {
        int minimum[2]=INTEGER_MIN(groups[i], k);
        groups[n][0]=minimum[0];
        groups[n][1]=minimum[1];
        printf("Index:%d, Distance:%d", groups[0], groups[1]);
    }
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