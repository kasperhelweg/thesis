set logscale x
#set logscale y
set pointsize 0.5
set xr [1000.0:10000000.0]
set output "./figures/lazy_list_vec_push_po.ps"
set terminal postscript eps color

plot "./data/lazy_vec_push.dat" using 1:($2/$1) title 'Lazy Binary Queue - Vector' w linespoints pointtype 8 linecolor rgb "#808000", \
     "./data/lazy_push.dat" using 1:($2/$1) title 'Lazy Binary Queue - List' w linespoints pointtype 9 linecolor rgb "#DC143C", \

#pause -1 "cont";
