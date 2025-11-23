#include "custom_math.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct Point {
    int x;
    int y;
    int closest_centroid;
};

struct Point* K_MEANS(struct Point *data, int k, int n);
int EUCLIDEAN_DISTANCE(struct Point p1, struct Point p2);
int main()
{   // Simple test for K_MEANS, nothing really important
    srand(time(NULL));
    int n=100;
    int k=4;
    struct Point data[n];
    for(int i=0;i<n;i++){
        data[i].x=i+(rand()%20-10);
        data[i].y=i+(rand()%30-15);
        data[i].closest_centroid=0;
    }
    printf("Running K_MEANS with %d data points and %d clusters.\n", n, k);
    struct Point* centroids=K_MEANS(data,k,n);
    for (int i=0;i<k;i++){
        printf("Centroid %d: (%d, %d)\n", i, centroids[i].x, centroids[i].y);
    }
    free(centroids);
    return 0;
}

struct Point* K_MEANS(struct Point *data, int k, int n) 
{
    
    struct Point* centroids = (struct Point*)malloc(k * sizeof(struct Point));
    // Initialize centroids to be evenly spaced along the x-axis and average y of segments
    // We assume data is somewhat sorted along x for this simple initialization
    //This wouldn't really work for true KMEANS but its fine for the uses we would see in Botball
    for (int i = 0; i < k; i++) {
        centroids[i].x=(n/(2*k))+i*(n/k);
        centroids[i].y=(data[i*n/k].y+ data[((i+1)*n/k)-1].y)/2;
        centroids[i].closest_centroid = 0;
    }
    struct Point point;
    //Runs 3 iterations of KMEANS
    for (int _ = 0; _ < 3; _++) 
    {
    // Iterates through each point and assigns it to the closest centroid
    for (int i = 0; i < n; i++) 
    {
        //Iterating through each centroid to find the closest one
        for (int j = 0; j < k; j++) 
        {
            point=data[i];
            if (EUCLIDEAN_DISTANCE(point, centroids[j])<EUCLIDEAN_DISTANCE(point, centroids[point.closest_centroid]))
            {
                data[i].closest_centroid=j;
            }
        }
    }
    // Moves centroids to "center of mass" of corresponding points
    for (int j = 0; j < k; j++) 
    {
        int count=0;
        int sumx=0;
        int sumy=0;
        for (int i = 0; i < n; i++) 
        {
            if (data[i].closest_centroid==j)
            {
                sumx+=data[i].x;
                sumy+=data[i].y;
                count++;
            }
        }
        if (count>0)
        {
            centroids[j].x=sumx/count;
            centroids[j].y=sumy/count;
        }
    }
}
    
     return centroids;
}
int EUCLIDEAN_DISTANCE(struct Point p1, struct Point p2) {
    return (int)sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}