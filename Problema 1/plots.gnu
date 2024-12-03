reset

set terminal pngcairo size 800,600 font "Arial,16"

plot_files = "time_position_velocity_500.txt time_position_velocity_50000.txt"
output_files = "position_500.png velocity_500.png noise_500.png position_50000.png velocity_50000.png noise_50000.png"
y_labels = "\"Position x(t)\" \"Velocity v(t)\" \"Noise f(t)\" \"Position x(t)\" \"Velocity v(t)\" \"Noise f(t)\""
column_numbers = "2 3 4 2 3 4"
set xlabel "time t"
unset key

do for [i=0:5] {
    file_index = int(i / 3) + 1  # Calculate which file to use (1 or 2)
    column_index = i % 3 + 1    # Cycle through columns for each file
    set output sprintf("plots/%s", word(output_files, i+1))
    set ylabel word(y_labels, i+1)
    plot sprintf("data/%s", word(plot_files, file_index)) using 1:int(word(column_numbers, column_index)) with lines lw 2
    unset output
}