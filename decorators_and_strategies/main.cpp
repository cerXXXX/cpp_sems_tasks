#include <functional>
#include <iostream>


class Calculator {
    std::function<double(double, double)> strategy_;

public:
    explicit Calculator(std::function<double(double, double)> s)
        : strategy_(std::move(s)) {}
    double execute(double a, double b) const {
        return strategy_(a, b);
    }
};


std::function<double(double, double)> logging(
    const std::function<double(double, double)>& f, const std::string& name) {
    return [f, name](double a, double b) {
        double res = f(a, b);
        std::cout << name << "(" << a << ", " << b << ") = " << res << "\n";
        return res;
    };
}


double add(double a, double b) {
    return a + b;
}


double mul(double a, double b) {
    return a * b;
}


int main() {
    Calculator calculator_add(logging(add, "add"));
    Calculator calculator_mul(logging(mul, "mul"));

    calculator_add.execute(2, 3);
    calculator_mul.execute(8, 19);
}
