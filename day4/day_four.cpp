#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

bool has_adjacent(string n) {
    for(int i = 0; i < n.size(); i++) {
        if(i < n.size() - 1
        && n[i] == n[i+1]) 
            return true;
    }
    return false;
}

bool has_adjacent_part_two(string n) {
    for(int i = 0; i < n.size(); i++) {
        if(i < n.size() - 1 && n[i] == n[i+1] && n[i+1] != n[i+2]) {
            if((i == 0) || (i > 0 && n[i] != n[i-1])) return true;
        }
    }
    return false;
}

bool is_increasing(string n) {
    for(int i = 0; i < n.size(); i++) {
        if(i < n.size() - 1
        && n[i] > n[i+1]) 
            return false;
    }
    return true;
}

int count_possible(int begin, int end) {
    int count = 0;
    for(int i = begin; i < end; i++) {
        string i_as_string = to_string(i);
        if(has_adjacent_part_two(i_as_string)
        && is_increasing(i_as_string)) count++;
    }
    return count;
}

int main() {
    int begin = 236491;
    int end = 713787;
    int possible_passwords = count_possible(begin, end);
    cout << possible_passwords << endl;
    return 0;
}