#include <kipr/wombat.h>
#include "movement.h"
#include "sensors.h"
#include <stdlib.h>
int CHECK_BARREL_COLOR()
{

    int color=-1;
    camera_update();
    camera_update();
    // Check if it is pink :o
    if ((get_object_count(0) > 0) && get_object_area(0, 0)>1000){
        color=1;
    }
    else if ((get_object_count(1) > 0) && get_object_area(1, 0)>1000){
        color=0;
    }

    return color;
}
void OPEN_CAMERA()
{
    camera_open();
    if (camera_load_config("colors") == 0 && camera_load_config("colors.conf") == 0) {
        camera_close();
        printf("CAMERA DIDNT OPEN!!!!!!!!\n");
    }   
}

struct Point {
    int x;
    int y;
    int closest_centroid;
};
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
int CALCULATE_THRESHOLD_KMEANS(int motor1, int motor2, int sensor)
{
    //creates an initial list to store datapoints
    int num_data_points=0;
    struct Point data[100000];
    double start_time=seconds();
    while ((seconds()-start_time)<1)
    {
        //adds data to the list for one second, so the list might not be totally filled
        mav(motor1, 1000);
        mav(motor2, 1000);
        data[num_data_points].x=num_data_points;
        data[num_data_points].y=analog(sensor);
        data[num_data_points].closest_centroid=0;
        num_data_points+=1;

    }
    //only takes entries that actually have values
    struct Point pruned_data[num_data_points];
    for (int i=0; i<num_data_points; i++)
    {

        pruned_data[i]=data[i];
    }
    //calculates the center of each data cluster using a stupid semi-kmeans like algorithm
    struct Point* centroids= K_MEANS(pruned_data, 2, num_data_points) ;
    //calculates threshold by taking the average between the sensor values of each centroid
    return (centroids[0].y+centroids[1].y)/2;

}