#include<random>
#include<numbers>
#include<fstream>
#include<iostream>
#include <fftw3.h>

int main(){
    const double pi = std::numbers::pi;
    const double k = 4 * pi * pi;
    const double kappa = 1e-4;
    const double dt = 0.01;
    const double A = sqrt(3 * kappa);

    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<double> noise(-A, A);

    std::vector<double> time;
    std::vector<double> velocity;
    std::vector<double> position;

    double v = 0;
    double x = 0;
    
    int steps;
    std::cout << "Enter amount of steps: ";
    std::cin >> steps;

    if (steps <= 0) {
    std::cout << "El número de pasos debe ser mayor que cero." << std::endl;
    return 1;
    }

    for(int i = 0; i <= steps; ++i){
        double t = i * dt;
        time.push_back(t);
        position.push_back(x);

        double f = noise(gen);
        v += dt * (f - k * x - v);
        x += dt * v;
    }

    std::ofstream file_x("data/trayectory.txt");
    
    for(int i = 0; i <= 1000; ++i ) {
        file_x << time[i] << "\t" << position[i] << std::endl;
    }

    fftw_complex *out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (steps / 2 + 1));
    double *in = (double*)fftw_malloc(sizeof(double) * steps);

    for (int i = 0; i < steps; ++i) {
        in[i] = position[i];
    }

    fftw_plan plan = fftw_plan_dft_r2c_1d(steps, in, out, FFTW_ESTIMATE);
    fftw_execute(plan);
    std::ofstream output("data/power_spectral_density.txt");

    for (int i = 0; i <= steps / 2; ++i) {
        double real = out[i][0];
        double imag = out[i][1];
        double amplitude = real * real + imag * imag; // |X(f)|^2
        double psd = amplitude / steps;              // P(f) = |X(f)|^2 / N
        double freq = i / (dt * steps);              // f = k / (N * Δt)

        output << freq << "\t" << psd << "\n";
    }

    output.close();

    fftw_destroy_plan(plan);
    fftw_free(out);
    fftw_free(in);

    std::cout << "Power spectral density saved to 'power_spectral_density.txt'.\n";


    return 0;
}