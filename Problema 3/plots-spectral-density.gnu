set terminal pngcairo size 800,600 enhanced font 'Arial,12'

k = 4 * pi ** 2
kappa = 1e-4

I(x) = kappa/((2 * pi) * ((k - x * x) ** 2 + x ** 2))

set xlabel "ω"
set ylabel "Power Spectral Density (10⁻⁷)"
set xrange [0:20]

set output "plots/average_spectral_density_1.png"
plot"data/power_spectral_density.txt" using ($1*2*pi):($2*1e7) with l lw 2 title "Numeric (N = 1)", I(x)*1e7 with l lw 2 title "Analytic"

set output "plots/average_spectral_density_10.png"
plot "data/average_power_spectral_density_10.txt" using ($1*2*pi):($2*1e7) with l lw 2 title "Numeric (N = 10)", I(x)*1e7 with l lw 2 title "Analytic"

set output "plots/average_spectral_density_100.png"
plot "data/average_power_spectral_density_100.txt" using ($1*2*pi):($2*1e7) with l lw 2 title "Numeric (N = 100)", I(x)*1e7 with l lw 2 title "Analytic"

unset output