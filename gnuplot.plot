set title 'bzero'

plot 'bzero.amd64.dat' using 1:(5/$2) with lines, 'bzero.amd64.dat' using 1:(5/$3) with lines
plot 'bzero.amd64.dat' using 1:(5*$2*$1) with lines, 'bzero.amd64.dat' using 1:(5*$3*$1) with lines
