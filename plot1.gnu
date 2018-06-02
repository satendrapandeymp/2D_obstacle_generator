set size ratio -1

plot 'data1.txt' using 1:2:($3*0+.2) with circle title 'Variable goal', '' using 1:2:(column(0)) with labels offset 0,char 0
