set pointsize 0.5
set logscale x
set xr [1000:10000000]
set yr [0:10]
set output "./figures/erase_comp.ps"
set terminal postscript eps color

plot "./data/magic_erase.dat" using 1:3 title 'Magic Binary Queue Delete Comps' w linespoints pointtype 9 linecolor rgb "#DC143C", \
     "./data/regular_erase.dat" using 1:3 title 'Regular Binary Queue Delete Comps' w linespoints pointtype 4 linecolor rgb "#008000", \
     "./data/lazy_erase.dat" using 1:3 title 'Lazy Binary Queue Delete Comps' w linespoints pointtype 8  linecolor rgb "#808000", \
     "./data/eager_erase.dat" using 1:3 title 'Eager Binary Queue Delete Comps' w linespoints pointtype 7 linecolor rgb "#8A2BE2", \
#pause -1 "cont";
