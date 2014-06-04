set xlabel "number of elements"
set ylabel "compares per. operation"
set key bottom right

set pointsize 0.5
set logscale x
set yr [-3:3]
set xr [1000.0:10000000.0]

set output "./figures/emplace_comp.ps"
set terminal postscript eps color

plot "./data/magic_push.dat" using 1:3 title 'Magic Binary Queue' w linespoints pointtype 9, \
     "./data/lazy_push.dat" using 1:3 title 'Lazy Binary Queue' w linespoints pointtype 8, \
     "./data/eager_push.dat" using 1:3 title 'Eager Binary Queue' w linespoints pointtype 7, \
     "./data/binomial_emplace.dat" using 1:3 title 'Boost Binomial Queue' w linespoints pointtype 6 linecolor rgb "#008B8B", \
     "./data/fibonacci_emplace.dat" using 1:3 title 'Boost Fibonacci Heap' w linespoints pointtype 5 linecolor rgb "#DAA520", \
     
#pause -1 "cont";
