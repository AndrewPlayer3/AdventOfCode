#ifndef _PATHS_HPP_
#define _PATHS_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace chrono;

class Point {
public:
    int x, y;
    Point()
        : x(0), y(0) {}
    Point(int x, int y)
        : x(x), y(y) {}
    int distance_from(Point p) {return abs(p.x-x) + abs(p.y-y);}
};
enum Orientation {UP_DOWN,LEFT_RIGHT};
enum Direction {UP,DOWN,LEFT,RIGHT};
class Line {
public:
    Point A;
    Point B;
    Orientation O;
    Direction D;
    Line()
        : A(Point(0, 0)), B(Point(0, 0)) {}
    Line(Point A, Point B)
        : A(A), B(B) {
            set_direction();
            set_orientation();
        }
    void set_orientation() {
        if(A.x < B.x) {
            O = LEFT_RIGHT;
        } else if(B.x < A.x) {
            Point temp = B; B = A; A = temp; O = LEFT_RIGHT;
        } else if(A.y > B.y) {
            O = UP_DOWN;
        } else {
            Point temp = A; A = B; B = temp; O = UP_DOWN;
        }
    }
    void set_direction() {
        if(A.y == B.y) {
            if(A.x < B.x) D = RIGHT;
            else D = LEFT;
        } else {
            if(A.y > B.y) D = DOWN;
            else D = UP;
        }
    }
    int get_length() { return (abs(B.x - A.x) + abs(B.y - A.y)); }
    Point get_significant() {
        if(O == UP_DOWN) {
            if(A.y > B.y) return A;
            else return B;
        } else {
            if(A.x < B.x) return A;
            else return B;
        }
    }
    bool intersects(Line L) {
        if(O == L.O) return false;
        switch(O) {
            case LEFT_RIGHT:
                if((A.x <= L.A.x && B.x >= L.B.x)
                && (A.y <= L.A.y && B.y >= L.B.y)) return true;
                break;
            case UP_DOWN:
                if((A.x >= L.A.x && B.x <= L.B.x)
                && (A.y >= L.A.y && B.y <= L.B.y)) return true;
                break;
            default:
                cout << "Orientation not set..." << endl;
                return false;
        }
        return false;
    }
    Point get_intersection(Line L) {
        if(O == UP_DOWN) {
            int x = A.x; int y = L.A.y;
            return Point(x, y);
        } else {
            int x = L.A.x; int y = A.y;
            return Point(x, y);
        }
    }
};

class Path {
public:
    vector<Line> lines;
    vector<int> steps;
    Path()
        : lines() {}
    Path(vector<Line> lines)
        : lines(lines) {init_steps();}
    void init_steps() {
        int accum = 0;
        for(Line l : lines) {
            accum+=l.get_length();
            steps.push_back(accum);
        }
    }
    size_t size() {return lines.size();}
    Line& operator[](int i) {return lines[i];}
};

#endif