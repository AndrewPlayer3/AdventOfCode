#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<int> run(vector<int> mem) {
    for(int i = 0; i < mem.size();) {
        int OP = (mem[i] % 100) / 1;
        int A  = ((mem[i] % 1000) - OP) / 100;
        int B  = ((mem[i] % 10000) - A)  / 1000;
        int C  = ((mem[i] % 100000) - B)  / 10000; // Should always be ZERO
        int a_param; int b_param;
        if(i+1 < mem.size()) {
            if(A == 0) a_param = mem[i+1];
            else a_param = i+1;
        }
        if(i+2 < mem.size()) {
            if(B == 0) b_param = mem[i+2];
            else b_param = i+2;
        }        
        switch(OP) {
            case 1:
                mem[mem[i+3]] = mem[a_param] + mem[b_param];
                i+=4; break;
            case 2:
                mem[mem[i+3]] = mem[a_param] * mem[b_param];
                i+=4;  break;
            case 3:
                int input;
                cout << "Enter an int: ";
                cin >> input;
                mem[mem[i+1]] = input;
                i+=2; break;
            case 4:
                if(A == 0) cout << mem[mem[i+1]] << endl;  
                else       cout << mem[    i+1 ] << endl;
                i+=2; break;
            case 5:
                if(mem[a_param] != 0) i = mem[b_param]; 
                else i+=3; break;
            case 6:
                if(mem[a_param] == 0) i = mem[b_param]; 
                else i+=3; break;
            case 7:
                if(mem[a_param] < mem[b_param]) mem[mem[i+3]] = 1; 
                else mem[mem[i+3]] = 0;
                i+=4; break;
            case 8:
                if(mem[a_param] == mem[b_param]) mem[mem[i+3]] = 1; 
                else mem[mem[i+3]] = 0;
                i+=4; break;
            case 99:
                return mem; break;
            default:
                i++; break;
        }
    }
    return {0};
}

int to_int(string s) {
    istringstream is(s);
    int number;
    if(is >> number) return number;
    else cout << "Something went wrong..." << endl;
    exit(1);
}

int main() {
    ifstream file("input.txt");
    string line = "";
    vector<int> mem;
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
    vector<int> done = run(mem);
    return 0;
}