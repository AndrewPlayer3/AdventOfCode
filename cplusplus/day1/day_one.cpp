#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

int accumulate(int& total, int& current) {
    int i = current / 3;
    int j = i - 2;
    if(j <= 0) return total;
    total += j;
    return accumulate(total, j);
}

int sum(std::vector<int> data) {
    int total = 0;
    for(int i : data) {
        int temp_total = 0;
        total += accumulate(temp_total, i);
    }
    return total;
}
 
int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    std::string line = "";
    std::vector<int> data;
    while(std::getline(file, line)) {
        int i;
        std::istringstream input(line);
        if(input >> i) {
            data.push_back(i);
        }
    }
    int s = sum(data);
    std::cout << s << std::endl;
    return 0;
}
