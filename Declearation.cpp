#include "Declearation.h"

const int molecules = 100;

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
float boundry_len = 14.7;
float cutoff = 3;
float sigma = .6;
float scale = 1.1;
int i = 0;
int num = 3000;
int flag = 1;
