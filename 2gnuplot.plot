set title 'bzero'
set ylabel 'bytes/second'
set xlabel 'Size in Bytes'
set key autotitle columnheader left
#x	"stosb aligned"	"sse2 aligned"	stosb	sse2
set format y '%.2s%cB'

#plot 'bzero.dat' using 1:(5/$2) with lines, 'bzero.dat' using 1:(5/$3) with lines
plot 'bzero.dat' using 1:(5*$2*$1) with lines, \
'bzero.dat' using 1:(5*$3*$1) with lines,\
'bzero.dat' using 1:(5*$4*$1) with lines,\
'bzero.dat' using 1:(5*$5*$1) with lines
#'bzero.dat' using 1:(5*$6*$1) with lines

#'bzero.dat2' using 1:(5*$2*$1) with lines
