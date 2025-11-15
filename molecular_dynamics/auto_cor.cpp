#include <vector>

double mean(std::vector<double> x) {
    double sum = 0;
    for (int i = 0; i < x.size(); ++i) {
        sum += x[i];
    }
    return sum / x.size();
}

/*
double integrate(std::vector<double> x, std::) {


}
*/
std::vector<double> autocor(std::vector<double> x) {
    double m = mean(x);

    std::vector<double> autocorrelation(x.size()/2);

}