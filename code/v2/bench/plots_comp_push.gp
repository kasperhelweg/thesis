set pointsize 0.5
set yr [0:5]
set output "./figures/push_comp.ps"
set terminal postscript eps color

plot "./data/magic_push.dat" using 1:3 title 'Magic Binary Queue Push Comps' w linespoints pointtype 9, \
     "./data/lazy_push.dat" using 1:3 title 'Lazy Binary Queue Push Comps' w linespoints pointtype 8, \
     "./data/eager_push.dat" using 1:3 title 'Eager Binary Queue Push Comps' w linespoints pointtype 7, \
     
#pause -1 "cont";
