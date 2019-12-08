#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int count_elem(vector<int> layer, int elem) {
    int count = 0;
    for(int i : layer) if(i == elem) count++;
    return count;
}

int to_int(char c) {
    string s = ""; s += c;
    istringstream is(s);
    int number;
    is >> number; return number;
}

int main() {
    ifstream file("input.txt");
    string line = "";
    vector<vector<int>> layer_vector;
    pair<int, int> check = {150, 150};
    while(getline(file, line)) {
        int count = 0;
        vector<int> layer(25*6);
        for(char c : line) {
            if(count < (25*6)) { layer[count] = to_int(c); count++; } 
            if(count >= (25*6)) {
                layer_vector.push_back(layer);
                int zeros = count_elem(layer, 0);
                if(zeros < check.first) {
                    check.first = zeros;
                    check.second = count_elem(layer, 1) * count_elem(layer, 2);
                }
                count = 0;
            }
        }
    }
    std::cout << "Count: " << check.second << endl;
    vector<string> str_image(25*6);
    int i = 0;
    for(vector<int> layer : layer_vector) {
        for(int color : layer) {
            if(color != 2 && str_image[i] != "*" && str_image[i] != " " 
            && str_image[i] != "*\n" && str_image[i] != " \n") {
                if(color == 1) str_image[i] = "*";
                else if(color == 0) str_image[i] = " ";
                if(i % 25 == 24) str_image[i] += '\n';
            }
            i++;
        }
        i = 0;
    }
    for(string s : str_image) cout << s;
    return 0;
}