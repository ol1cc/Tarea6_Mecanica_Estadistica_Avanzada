#include<fstream>
#include<iostream>
#include<sstream>
#include<random>
#include<vector>

void update_averages(double value, std::vector<double>& averages, int index, int steps) {
    if(index + 1 >= averages.size()){
        std::cerr << "Error: Index out of bounds.";
        return;
    }
    averages[index] += value / steps;
    averages[index + 1] += value * value / steps;
}

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
    std::vector<double> f_noise;

    std::vector<double> averages(6, 0);

    for(int i = 0; i <= steps; ++i){
        double t = i * dt;
        double f = noise(gen);

        time.push_back(t);
        velocity.push_back(v);
        position.push_back(x);
        f_noise.push_back(f);

        v += dt * f;
        x += dt * v;

        update_averages(f, averages, 0, steps);
        update_averages(x, averages, 2, steps);
        update_averages(v, averages, 4, steps);
    }

    std::ostringstream txv;
    txv << "data/time_position_velocity_" << steps << ".txt";
    std::ofstream file(txv.str());
    if (file.is_open()) {
        for (size_t i = 0; i < time.size(); ++i) {
            file << time[i] << "\t" << position[i] << "\t" << velocity[i] << "\t" << f_noise[i] << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file.";
        return 1;
    }

    std::ostringstream avrgs;
    avrgs << "data/averages_" << steps << ".txt";
    std::ofstream averages_file(avrgs.str());
    if (averages_file.is_open()) {
        averages_file << "Average position: " << averages[2] << "\nAverage velocity: " << averages[4]
                      << "\nAverage noise: " << averages[0] << std::endl;
        averages_file << "==========" << std::endl;
        averages_file << "Average squared position: " << averages[3] << "\nAverage squared velocity: " << averages[5]
                      << "\nAverage squared noise: " << averages[1];
        averages_file.close();
    } else {
        std::cerr << "Unable to open file.";
        return 1;
    }
}