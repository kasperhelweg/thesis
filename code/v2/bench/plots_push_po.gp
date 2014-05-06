set logscale x
#set logscale y
set pointsize 0.5
set xr [1000.0:10000000.0]
set output "./figures/push_po.ps"
set terminal postscript eps color

plot "./data/magic_push.dat" using 1:($2/$1) title 'Magic Binary Queue Push' w linespoints pointtype 9, \
     "./data/lazy_push.dat" using 1:($2/$1) title 'Lazy Binary Queue Push' w linespoints pointtype 8, \
     "./data/eager_push.dat" using 1:($2/$1) title 'Eager Binary Queue Push' w linespoints pointtype 7, \

#pause -1 "cont";
