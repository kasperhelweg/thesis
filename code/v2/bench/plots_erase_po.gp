set logscale x
#set logscale y
set pointsize 0.5
set xr [1000.0:10000000.0]
set output "./figures/erase_po.ps"
set terminal postscript eps color

plot "./data/magic_erase.dat" using 1:($2/$1) title 'Magic Binary Queue Erase' w linespoints pointtype 9, \
     "./data/regular_erase.dat" using 1:($2/$1) title 'Regular Binary Queue Erase' w linespoints pointtype 4, \
     "./data/lazy_erase.dat" using 1:($2/$1) title 'Lazy Binary Queue Erase' w linespoints pointtype 8, \
     "./data/eager_erase.dat" using 1:($2/$1) title 'Eager Binary Queue Erase' w linespoints pointtype 7;
     
          
#pause -1 "cont";
