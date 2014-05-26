set logscale x
#set logscale y
set pointsize 0.5
set xr [1000.0:10000000.0]
set output "./figures/seq_b_po.ps"
set terminal postscript eps color

plot "./data/regular_seq_b.dat" using 1:($2/$1) title 'Regular Binary Queue' w linespoints pointtype 4 linecolor rgb "#008000", \
     "./data/lazy_seq_b.dat" using 1:($2/$1) title 'Lazy Binary Queue' w linespoints pointtype 9 linecolor rgb "#DC143C", \
     "./data/eager_seq_b.dat" using 1:($2/$1) title 'Eager Binary Queue' w linespoints pointtype 7 linecolor rgb "#8A2BE2", \
     "./data/binomial_seq_b.dat" using 1:($2/$1) title 'Boost Binomial Queue' w linespoints pointtype 6 linecolor rgb "#008B8B", \
     "./data/fibonacci_seq_b.dat" using 1:($2/$1) title 'Boost Fibonacci Heap' w linespoints pointtype 5 linecolor rgb "#DAA520", \
         
#pause -1 "cont";
