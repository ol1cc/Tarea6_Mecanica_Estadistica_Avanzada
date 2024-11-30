set terminal pngcairo size 800,600 font "Arial,16"

plot_files = "time_position_velocity_500.txt time_position_velocity_50000.txt"
output_files = "velocity_500.png position_500.png velocity_50000.png position_50000.png"
y_labels = "Velocity Position Velocity Position"
column_numbers = "2 3 2 3"
titles = "v(t) x(t) v(t) x(t)"

do for [i=0:3] {
    set output sprintf("plots/%s", word(output_files, i+1))
    set ylabel word(y_labels, i+1)
    plot sprintf("data/%s", word(plot_files, (i/2) + 1)) using 1:int(word(column_numbers, i+1)) with lines lw 2 title word(titles, i+1)
    unset output
}