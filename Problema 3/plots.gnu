set terminal pngcairo size 800,600 font "Arial,16"

plot_files = "power_spectral_density.txt trayectory.txt"
output_files = "power_spectral_density.png trayectory.png"
x_labels = "Frequency (Hz) Time (s)"
y_labels = "\"Power Spectral Density\" x(t)"
column_numbers = "2 2"
titles = "I(ω) x(t)"

do for [i=0:1] {
    set output sprintf("plots/%s", word(output_files, i+1))
    set xlabel word(x_labels, i+1)
    set ylabel word(y_labels, i+1)
    plot sprintf("data/%s", word(plot_files, i+1)) using 1:int(word(column_numbers, i+1)) with lines lw 2 title word(titles, i+1)
    unset output
}