// Refering to the Fifth point in the First Milestone 
// editing from the first method to this method as we know that the gps result will be in degrees
#include "tm4c123gh6pm.h"
#include <math.h>
#define M_PI 3.14159265359

double distance_calc (double lat12, double lon12)
 {
   double distance = 0;
   int counter = 1;
   double xpoints [300];                                                 // array for storing the latitude values of points of path 
   double ypoints [300];                                                 // array for storing the longitude values of points of path
           
           if (xpoints[counter - 1] != lat12 || ypoints[counter - 1] != lon12) {
            xpoints[counter] = lat12;                                 //to save the values of latitude in array 
            ypoints[counter] = lon12;                                //to save the values of longitude in array
            counter++;    
            if (counter != 2)                                            // to start calculations on the second and third elements in the array 
              {
          double x1 = xpoints[counter-2] * (M_PI/180);                   // convert first point latitude from degree to radian 
          double x2 = xpoints[counter-1] * (M_PI/180);                   // convert second point latitude from degree to radian 
          double deltax = (xpoints[counter-1] - xpoints[counter-2]) * (M_PI/180);          // convert differenc  latitude between two points from degree to radian
          double deltay = (ypoints[counter-1] - ypoints[counter-2]) * (M_PI/180);          // convert differenc  longitude between two points from degree to radian
          double a = sin(deltax/2) * sin(deltax/2) + cos(x1) * cos (x2) * sin (deltay/2) * sin (deltay/2);      // using haversine formula to calculate the distance between two points
          double c = 2 * atan2 (sqrt (a) , sqrt (1-a));
          distance += c * 6371 * 1000;                                                                          // overall distance will equal the sum of the displacements between the two points.
              }
                 }
          return distance;   
 }
