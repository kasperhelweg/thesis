set xlabel "number of elements( log-scale )"
set ylabel "time in micro-seconds per. element"
set key bottom right

set logscale x 
#set logscale y
set pointsize 0.7
set xr [1000.0:10000000.0]
#set yr [0.0:2.0]
set output "./figures/pop_po.ps"
set terminal postscript eps color

plot "./data/magic_pop.dat" using 1:($2/$1) title 'Magic Binary Queue' w linespoints pointtype 9 linecolor rgb "#DC143C", \
     "./data/regular_pop.dat" using 1:($2/$1) title 'Regular Binary Queue' w linespoints pointtype 4 linecolor rgb "#008000", \
     "./data/lazy_vec_pop.dat" using 1:($2/$1) title 'Lazy Binary Queue' w linespoints pointtype 8 linecolor rgb "#808000", \
     "./data/binomial_pop.dat" using 1:($2/$1) title 'Boost Binomial Queue' w linespoints pointtype 6 linecolor rgb "#008B8B", \
     "./data/eager_pop.dat" using 1:($2/$1) title 'Eager Binary Queue' w linespoints pointtype 7 linecolor rgb "#8A2BE2", \
     "./data/fibonacci_pop.dat" using 1:($2/$1) title 'Boost Fibonacci Heap' w linespoints pointtype 5 linecolor rgb "#DAA520", \

#pause -1 "cont";
