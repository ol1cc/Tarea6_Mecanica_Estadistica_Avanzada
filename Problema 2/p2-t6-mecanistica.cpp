#include<fstream>
#include<iostream>
#include<sstream>
#include<random>
#include<vector>

int main(){
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<double> noise(-1, 1);

    const double dt = 0.02;
    int steps;
    std::cout << "Enter amount of steps: ";
    std::cin >> steps;
    double v = 0;
    double x = 0;

    std::vector<double> time;
    std::vector<double> velocity;
    std::vector<double> position;

    double avrg_f = 0;
    double avrg_x = 0;
    double avrg_v = 0;

    double avrg_f2 = 0;
    double avrg_x2 = 0;
    double avrg_v2 = 0;

    for(int i = 0; i <= steps; ++i){
        double t = i * dt;
        time.push_back(t);
        velocity.push_back(v);
        position.push_back(x);

        double f = noise(gen);
        v += dt * f;
        x += dt * v;

        avrg_f += f;
        avrg_x += x;
        avrg_v += v;

        avrg_f2 += f * f;
        avrg_x2 += x * x;
        avrg_v2 += v * v;        
    }

    avrg_f /= steps;
    avrg_x /= steps;
    avrg_v /= steps;

    avrg_f2 /= steps;
    avrg_x2 /= steps;
    avrg_v2 /= steps;

    std::ostringstream txv;
    txv << "data/time_position_velocity_" << steps << ".txt";

    std::ofstream file(txv.str());
    if(file.is_open()){
        for(size_t i = 0; i < time.size(); ++i){
            file << time[i] << ", " << position[i] << ", " << velocity[i] << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file.";
        return 1;
    }

    std::ostringstream avrgs;
    avrgs << "data/averages_" << steps << ".txt";
    std::ofstream averages(avrgs.str());
    if(averages.is_open()){
        averages << "Average position: " << avrg_x << "\nAverage velocity: " << avrg_v << "\nAverage noise: " << avrg_f << std::endl;
        averages << "==========" << std::endl;
        averages << "Average squared position: " << avrg_x2 << "\nAverage squared velocity: " << avrg_v2 << "\nAverage squared noise: " << avrg_f2;
        averages.close();
    } else {
        std::cerr << "Unable to open file.";
        return 1;
    }
    return 0;
}