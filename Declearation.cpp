#include "Declearation.h"

const int molecules = 84;

int number_of_molecules = molecules;
float pos[molecules][3];
float vel[molecules][2];
float acc[molecules][2];
float last_acc[molecules][2];
float dist[molecules];
float potential = 0.0;
float kinetic = 0.0;
float kinetic_print = 0.0;
float temp = 0.0;
float delta_time = .05;
float boundry_len_x = 12.03;
float boundry_len_y = 5.7;
float cutoff = 1.5;
float sigma = .4;
float scale = 1.07;
int i = 0;
int num = 4500;
int flag = 1;
