#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int run(vector<long long>& mem) {
    long long base = 0;
    for(int i = 0; i < mem.size();) {
        int OP = (mem[i] % 100) / 1;
        int A  = ((mem[i] % 1000) - OP) / 100;
        int B  = ((mem[i] % 10000) - A)  / 1000;
        int C  = ((mem[i] % 100000) - B)  / 10000; // Should always be ZERO
        long long a_param; long long b_param; long long c_param;
        long long input = 0;
        if(i+1 < mem.size()) {
            if(A == 0) a_param = mem[i+1];
            else if(A == 1) a_param = i+1;
            else if(A == 2 && (mem[i+1]+base)<mem.size()) a_param = mem[i+1] + base;
        }
        if(i+2 < mem.size()) {
            if(B == 0) b_param = mem[i+2];
            else if(B == 1) b_param = i+2;
            else if(B == 2 && (mem[i+2]+base)<mem.size()) b_param = mem[i+2] + base;
        }
        if(i+3 < mem.size()) {
            if(C == 0) c_param = mem[i+3];
            else if(C == 1) c_param = i+3;
            else if(C == 2) c_param = mem[i+3] + base;
        }        
        switch(OP) {
            case 1:
                mem[c_param] = mem[a_param] + mem[b_param];
                i+=4; break;
            case 2:
                mem[c_param] = mem[a_param] * mem[b_param];
                i+=4;  break;
            case 3:
                cout << "Enter an integer: ";
                cin >> input;
                mem[a_param] = input;
                i+=2; 
                break;
            case 4:
                cout << mem[a_param] << endl;
                i+=2;
                break;
            case 5:
                if(mem[a_param] != 0) i = mem[b_param]; 
                else i+=3; break;
            case 6:
                if(mem[a_param] == 0) i = mem[b_param]; 
                else i+=3; break;
            case 7:
                if(mem[a_param] < mem[b_param]) mem[c_param] = 1; 
                else mem[c_param] = 0;
                i+=4; break;
            case 8:
                if(mem[a_param] == mem[b_param]) mem[c_param] = 1; 
                else mem[c_param] = 0;
                i+=4; break;
            case 9:
                base += mem[a_param];
                i+=2; break;
            case 99:
                return mem[0]; break;
            default:
                i++; break;
        }
    }
    return {0};
}

long long to_int(string s) {
    istringstream is(s);
    long long number;
    if(is >> number) return number;
    else cout << "Something went wrong..." << endl;
    exit(1);
}

int main() {
    ifstream file("input.txt");
    string line = "";
    vector<long long> mem;
    while(getline(file, line)) {
        int pos = 0;
        string temp = "";
        while(pos != line.size()) {
            if(isdigit(line[pos]) || line[pos] == '-') {
                temp += line[pos];
            }
            if(line[pos] == ',' || pos == line.size() - 1) {
                mem.push_back(to_int(temp));
                temp = "";
                pos;
            }
            ++pos;
        }
    }
    mem.resize(mem.size() + 1000);
    run(mem);
    return 0;
}