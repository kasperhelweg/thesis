set pointsize 0.5
set yr [0:100]
set output "./figures/comp_pop.ps"
set terminal postscript eps color

plot "./data/magic_pop.dat" using 1:3 title 'Magic Binary Queue Pop Comps' w linespoints pointtype 9, \
     "./data/lazy_pop.dat" using 1:3 title 'Lazy Binary Queue Pop Comps' w linespoints pointtype 8, \
     "./data/eager_pop.dat" using 1:3 title 'Eager Binary Queue Pop Comps' w linespoints pointtype 7, \
     
#pause -1 "cont";

