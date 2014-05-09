set pointsize 0.5
set yr [0:10]
set output "./figures/erase_comp.ps"
set terminal postscript eps color

plot "./data/magic_erase.dat" using 1:3 title 'Magic Binary Queue Erase Comps' w linespoints pointtype 9, \
     "./data/lazy_erase.dat" using 1:3 title 'Lazy Binary Queue Erase Comps' w linespoints pointtype 8, \
     "./data/eager_erase.dat" using 1:3 title 'Eager Binary Queue Erase Comps' w linespoints pointtype 7, \
     
#pause -1 "cont";
