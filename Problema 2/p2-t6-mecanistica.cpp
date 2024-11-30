#include<fstream>
#include<iostream>
#include<sstream>
#include<random>
#include<vector>

double euler(double v, double dt, double f){
    double v_1 = v + dt * f;
    return v_1;
}

int main(){
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<double> noise(-1, 1);

    const double dt = 0.02;
    const int steps = 500;
    double v = 0;
    double x = 0;

    std::vector<double> time;
    std::vector<double> velocity;
    std::vector<double> position;

    double sum_f = 0;
    double sum_x = 0;
    double sum_v = 0;

    for(int i = 0; i <= steps; ++i){
        double t = i * dt;
        time.push_back(t);
        velocity.push_back(v);
        position.push_back(x);

        double f = noise(gen);
        std::cout << "Noise: " << f << std::endl;
        v += dt * f;
        x += dt * v;
    }

    std::ostringstream filename;
    filename << "p2_time_position_velocity_" << steps << ".txt";

    std::ofstream file(filename.str());
    if(file.is_open()){
        for(size_t i = 0; i < time.size(); ++i){
            file << time[i] << ", " << position[i] << ", " << velocity[i] << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file.";
        return 1;
    }
    return 0;
}