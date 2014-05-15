set logscale x
#set logscale y
set pointsize 0.5
set xr [1000.0:10000000.0]
set output "./figures/pop_po.ps"
set terminal postscript eps color

plot "./data/magic_pop.dat" using 1:($2/$1) title 'Magic Binary Queue Pop' w linespoints pointtype 9, \
     "./data/regular_pop.dat" using 1:($2/$1) title 'Regular Binary Queue Pop' w linespoints pointtype 4, \
     "./data/lazy_pop.dat" using 1:($2/$1) title 'Lazy Binary Queue Pop' w linespoints pointtype 8, \
     "./data/eager_pop.dat" using 1:($2/$1) title 'Eager Binary Queue Pop' w linespoints pointtype 7, \
     "./data/binomial_pop.dat" using 1:($2/$1) title 'Boost Binomial Queue Pop' w linespoints pointtype 6, \
     "./data/fibonacci_pop.dat" using 1:($2/$1) title 'Boost Fibonacci Heap Pop' w linespoints pointtype 5, \
     
#pause -1 "cont";
