
// Refering to the Fifth point in the First Milestone 
#include "tm4c123gh6pm.h"
#include <math.h>



double distance_calc (void)
 {
 double pinx = 0 , piny=0 , distance = 0;
int counter = 1;
double  xpoints [300] ;
double  ypoints [300] ;
for (int i = 0 ; i < xpoints.length; i++ )
        {
            xpoints[i]=0;
            ypoints[i]=0;
         }
           
           if (xpoints[counter-1]!=pinx || ypoints [counter-1]!=piny){
             xpoints[counter]=pinx;
             ypoints[counter]=piny;
	         counter++;
	                      if(counter!=2){
	                             distance += sqrt (((xpoints[counter-1]-xpoints[counter-2])(xpoints[counter-1]-xpoints[counter-2])) + ((ypoints[counter-1]-ypoints[counter-2])(ypoints[counter-1]-ypoints[counter-2])));
                                         }
            }
                                 return distance;   
            }
   

