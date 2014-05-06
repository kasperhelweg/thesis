set pointsize 1.5
#set output "emplace.ps"
#set terminal postscript eps color

plot "./data/magic_pop.dat" using 1:3 title 'Magic Binary Queue Pop Comps' w linespoints pointtype 9, \
     "./data/lazy_pop.dat" using 1:3 title 'Lazy Binary Queue Pop Comps' w linespoints pointtype 8, \
     "./data/eager_pop.dat" using 1:3 title 'Eager Binary Queue Pop Comps' w linespoints pointtype 7, \
     
pause -1 "cont";

