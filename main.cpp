using namespace std;
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "Declearation.h"
#include "Multiparticle.h"

// To calculate force Brute_force for now
int force_cal(float posx, float posy, float * accx, float * accy);

// To update pos and velocity
void update_all(float * posx, float * posy,  float * velx, float  * vely, float accx, float accy, float last_accx, float last_accy, float delta_time);
// clearing matrix
void clearing();
void scaling();

int main(int argc, char *argv[])
{
    if (argc == 2) number_of_molecules = atoi(argv[1]);

    // Reading from file
    declearation("data.txt");

    // To calculate force on each atom
    for ( i = 0; i<number_of_molecules; i++)
    {
      force_cal(pos[i][0], pos[i][1], &acc[i][0], &acc[i][1]);
      //cout <<   pos[i][0]  << " " << pos[i][1] << " " << acc[i][0]  << " " << acc[i][1] << " " << i << endl;
    }

    // Now starting the real loop
    // for 100 time steps
    for (int step = 0; step < num; step++)
    {
      for (i = 0; i<number_of_molecules; i++)
      {
            last_acc[i][0] =acc[i][0];
            last_acc[i][1] =acc[i][1];
            flag = force_cal(pos[i][0], pos[i][1], &acc[i][0], &acc[i][1]);
            if (flag == 0) break;
      }

      for (i = 0; i<number_of_molecules; i++)
      {
            update_all(&pos[i][0], &pos[i][1], &vel[i][0], &vel[i][1] , acc[i][0], acc[i][1], last_acc[i][0], last_acc[i][1], delta_time);
      }

      // For output
      if (step % 200 == 0 && step != 0) scaling();
      if (step % 1000 == 0 && step != 0) scale = scale - .01;

      if (flag == 0) break;
      clearing();
    }

    // To making it in range
    scale = 1.02;
    scaling();

    for ( i = 0; i<number_of_molecules; i++)
    {
        if (flag == 0) break;
        cout <<   pos[i][0]  << " " << pos[i][1] << " " << "0.2" << endl;
    }

return 0;

}


void update_all(float * posx, float * posy,  float * velx, float  * vely, float accx, float accy, float last_accx, float last_accy, float delta_time)
{
  *posx = *posx + *velx * delta_time + accx * delta_time * delta_time /2;
  *posy = *posy + *vely * delta_time + accy * delta_time * delta_time /2;

  // update position with periodic box condition
  if (*posx > boundry_len_x) *posx = *posx - (2*boundry_len_x);
  else if (*posx + boundry_len_x < 0) *posx = *posx + (2*boundry_len_x);
  if (*posy > boundry_len_y) *posy = *posy - (2*boundry_len_y);
  else if (*posy + boundry_len_y < 0) *posy = *posy + (2*boundry_len_y);

  *velx = *velx + (accx + last_accx) * delta_time /2;
  *vely = *vely + (accy + last_accy) * delta_time /2;

}


// Force calculation
int force_cal(float posx, float posy, float * accx, float * accy)
{
int flagsx = 0;
int flagsy = 0;
if ((boundry_len_x-posx) < cutoff) flagsx++;
if ((posx + boundry_len_x ) < cutoff) flagsx--;
if ((boundry_len_y-posy) < cutoff) flagsy++;
if ((posy + boundry_len_y ) < cutoff) flagsy--;

//cout << flagsx << " " << flagsy << " ";

int val = abs(flagsy) + abs(flagsx);
float dot = 0.0;

for (int i = 0; i<9; i++)
{
    // Mapping to 2D
    int num = i;
    int cor_x, cor_y, val1, flag;
    cor_x = (num/3)-1;
    cor_y = (num%3)-1;
    val1 = abs(cor_x) + abs(cor_y);
    flag = ((cor_x*flagsx) >= 0 && (cor_y*flagsy) >= 0 )? 1 : 0;
    dot = cor_x*flagsx + cor_y*flagsy;

    if ((val1 == 0) || ((dot > 0) && (flag == 1) && (val1 <= val)))
    {

      for (int j = 0; j<number_of_molecules; j++)
              {
                  float r = pow( pow( (pos[j][0] + cor_x * 2 * boundry_len_x )- posx, 2) + pow((pos[j][1] + cor_y * 2 * boundry_len_y )- posy, 2) , .5);
                  if (r < cutoff && r > sigma/100)
                  {
                      float force = 1 * ( pow((sigma/r),13) * 12  - pow((sigma)/r,7) * 6)/ sigma;
                      *accx = *accx + force * ((pos[j][0] + cor_x * 2 * boundry_len_x)-posx)/r;
                      *accy = *accy + force * ((pos[j][1] + cor_y * 2 * boundry_len_y)-posy)/r;
                   }
                  else if (r > 4 * boundry_len_x) return 0;
                }
    }
}
return 1;
}

// Scaling everything

void scaling()
{
  boundry_len_x = boundry_len_x/scale;
  boundry_len_y = boundry_len_y/scale;
  for (int i=0; i<number_of_molecules; i++)
  {
    for (int j = 0; j<2; j++)
    {
      pos[i][j] = pos[i][j]/scale;
      vel[i][j] = vel[i][j]/scale;
    }
  }
}


// clearing attraction matrix
void clearing()
{
  for (int i=0; i<number_of_molecules; i++)
  {
    for (int j = 0; j<2; j++)
    {
      acc[i][j] = 0;
    }
  }
}
