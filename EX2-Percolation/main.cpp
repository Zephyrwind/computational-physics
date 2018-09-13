#include "latticeview.h"
#include <stdlib.h>

#define N 15             //Lateral number of cells
#define ImageWidth 1000  //image width
#define ImageHeight 1000 //image height


using namespace std;

main ()
{
  int lat[N*N];  //create lattice
  int icounter, jcounter; //counters

  //Several examples: define states and print lattice
  for (icounter=0; icounter<N*N; icounter++) lat[icounter]=0;
  Print_lattice (lat, N, N, ImageWidth, ImageHeight, "allwhite.ppm");

  for (icounter=0; icounter<N*N; icounter++) lat[icounter]=1;
  Print_lattice (lat, N, N, ImageWidth, ImageHeight, "allgreen.ppm");

  for (icounter=0; icounter<N*N; icounter++) lat[icounter]=2;
  Print_lattice (lat, N, N, ImageWidth, ImageHeight, "allred.ppm");

  for (icounter=0; icounter<N*N; icounter++) lat[icounter]=3;
  Print_lattice (lat, N, N, ImageWidth, ImageHeight, "allback.ppm");

  for (icounter=0; icounter<N*N; icounter++) lat[icounter]=4;
  Print_lattice (lat, N, N, ImageWidth, ImageHeight, "allblue.ppm");

  for (icounter=0; icounter<N*N; icounter++)
    lat[icounter]= (int)(drand48()*5.0);
  Print_lattice (lat, N, N, ImageWidth, ImageHeight, "randomcolor.ppm");

  for (icounter=0; icounter<N; icounter++)
    for (jcounter=0; jcounter <N; jcounter++)
      lat[icounter+jcounter*N]= jcounter%5;
  Print_lattice (lat, N, N, ImageWidth, ImageHeight, "colorrow.ppm");

  // for a series of pictures, you would need varying filenames
  char filename[160];
  int img_no=1;
  sprintf(filename,"test%d.ppm",img_no); // now same as "colorrow.ppm"
  Print_lattice (lat, N, N, ImageWidth, ImageHeight,filename);

  for (icounter=0; icounter<N; icounter++)
    for (jcounter=0; jcounter <N; jcounter++)
      lat[icounter+jcounter*N]= icounter%5;
  Print_lattice (lat, N, N, ImageWidth, ImageHeight, "colorcolumn.ppm");
  
  // the next image of the series
  img_no++;
  sprintf(filename,"test%d.ppm",img_no); // now same as "colorcolumn.ppm"
  Print_lattice (lat, N, N, ImageWidth, ImageHeight,filename);
}
