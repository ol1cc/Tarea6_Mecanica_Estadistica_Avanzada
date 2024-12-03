#include<random>
#include<numbers>
#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
#include<fftw3.h>

int main() {
    const double pi = std::numbers::pi;
    const double k = 4 * pi * pi;
    const double kappa = 1e-4;
    const double dt = 0.01;
    const double A = sqrt(3 * kappa / dt);

    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<double> noise(-A, A);

    int steps = 50000;
    int runs;
    std::cout << "Enter the number of runs: ";
    std::cin >> runs;

    if (runs <= 0) {
        std::cerr << "The number of runs must be greater than zero.";
        return 1;
    }

    std::vector<double> avg_psd(steps / 2 + 1, 0.0);

    for (int r = 0; r < runs; ++r) {
        std::vector<double> time;
        std::vector<double> position;

        double v = 0;
        double x = 0;

        for (int i = 0; i <= steps; ++i) {
            double t = i * dt;
            time.push_back(t);
            position.push_back(x);

            double f = noise(gen);
            v += dt * (f - k * x - v);
            x += dt * v;
        }

        fftw_complex *out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (steps / 2 + 1));
        double *in = (double*)fftw_malloc(sizeof(double) * steps);

        for (int i = 0; i < steps; ++i) {
            in[i] = position[i];
        }

        fftw_plan plan = fftw_plan_dft_r2c_1d(steps, in, out, FFTW_ESTIMATE);
        fftw_execute(plan);

        for (int i = 0; i <= steps / 2; ++i) {
            double real = out[i][0] * dt;
            double imag = out[i][1] * dt;
            double amplitude = real * real + imag * imag; // |X(f)|^2
            double psd = amplitude / (2 * pi * steps * dt); // P(f) = |X(f)|^2 / (2 π N Δt)
            avg_psd[i] += psd;
        }

        fftw_destroy_plan(plan);
        fftw_free(out);
        fftw_free(in);

        std::cout << "Run " << (r + 1) << "/" << runs << " completed.\n";
    }

    for (double &psd : avg_psd) {
        psd /= runs;
    }

    std::ostringstream avrgs;
    avrgs << "data/average_power_spectral_density_" << runs << ".txt";

    std::ofstream output(avrgs.str());
    for (int i = 0; i <= steps / 2; ++i) {
        double freq = i / (dt * steps); // f = k / (N * Δt)
        output << freq << "\t" << avg_psd[i] << "\n";
    }

    output.close();
    std::cout << "Averaged power spectral density saved to " << avrgs.str() << std::endl;

    return 0;
}