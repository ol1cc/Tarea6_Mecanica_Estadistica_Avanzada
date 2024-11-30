set terminal pngcairo size 800,600 font "Arial,16"
set output 'p2_velocity_500.png'

set xlabel "Time"
set ylabel "Velocity"
plot "p2_time_position_velocity_500.txt" using 1:2 with lines lw 2 title "v(t)"

unset terminal

set terminal pngcairo size 800,600 font "Arial,16"
set output 'p2_position_500.png'
set ylabel "Position"
plot "p2_time_position_velocity_500.txt" using 1:3 with lines lw 2 title "x(t)"