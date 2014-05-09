set logscale x
set logscale y
set pointsize 0.5
set xr [1000.0:10000000.0]
set output "./figures/emplace.ps"
set terminal postscript eps color

plot "./data/magic_emplace.dat" using 1:2 title 'Magic Binary Queue Emplace' w linespoints pointtype 9, \
     "./data/lazy_emplace.dat" using 1:2 title 'Lazy Binary Queue Emplace' w linespoints pointtype 8, \
     "./data/eager_emplace.dat" using 1:2 title 'Eager Binary Queue Emplace' w linespoints pointtype 7, \
     "./data/binomial_emplace.dat" using 1:2 title 'Boost Binomial Queue Emplace' w linespoints pointtype 6, \
     "./data/fibonacci_emplace.dat" using 1:2 title 'Boost Fibonacci Heap Emplace' w linespoints pointtype 5, \
     
#pause -1 "cont";
