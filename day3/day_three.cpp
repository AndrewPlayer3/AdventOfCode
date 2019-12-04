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
    int distance_from(Point p) {
        return abs(p.x-x) + abs(p.y-y);
    }
    void print_point() {
        cout << "[" << x << ", " << y << "]";
    }
};

enum Orientation {
    UP_DOWN,
    LEFT_RIGHT
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Line {
public:
    Point A;
    Point B;
    Orientation O;
    Direction D;
    Line()
        : A(Point(0, 0)), B(Point(0, 0)) {}
    Line(Point A, Point B)
        : A(A), B(B) {}
    void set_orientation() {
        if(A.x < B.x) {
            O = LEFT_RIGHT;
        } else if(B.x < A.x) {
            Point temp = B;
            B = A;
            A = temp;
            O = LEFT_RIGHT;
        } else if(A.y > B.y) {
            O = UP_DOWN;
        } else {
            Point temp = A;
            A = B;
            B = temp;
            O = UP_DOWN;
        }
    }
    void set_direction() {
        if(A.y == B.y) {
            if(A.x < B.x) {
                D = RIGHT;
            } else {
                D = LEFT;
            }
        } else {
            if(A.y > B.y) {
                D = DOWN;
            } else {
                D = UP;
            }
        }
    }
    int get_length() {
        return (abs(B.x - A.x) + abs(B.y - A.y));
    }
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
                && (A.y <= L.A.y && B.y >= L.B.y)) {
                    return true;
                }
                break;
            case UP_DOWN:
                if((A.x >= L.A.x && B.x <= L.B.x)
                && (A.y >= L.A.y && B.y <= L.B.y)) {
                    return true;
                }
                break;
            default:
                cout << "Orientation not set..." << endl;
                return false;
        }
        return false;
    }
    Point get_intersection(Line L) {
        if(O == L.O); // do something;
        if(O == UP_DOWN) {
            int x = A.x;
            int y = L.A.y;
            return Point(x, y);
        } else {
            int x = L.A.x;
            int y = A.y;
            return Point(x, y);
        }
    }
    void print_line() {
        A.print_point();
        cout << " -> ";
        B.print_point();
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
    size_t size() {
        return lines.size();
    }
    Line& operator[](int i) {
        return lines[i];
    }
};

int get_distance(Point p) {
    return abs(p.x - 0) + (p.y - 0);
}

int get_min_distance(vector<Point> points) {
    int min = get_distance(points[1]);
    for(Point p : points) {
        int distance = get_distance(p);
        if(distance > 0 && distance < min) min = distance;
    }
    return min;
}

vector<Point> get_intersections(vector<Line> v1, vector<Line> v2) {
    vector<Point> intersections;
    for(int i = 0; i < v1.size(); i++) {
        for(int j = 0; j < v2.size(); j++) {
            if(v2[j].intersects(v1[i])) {
                Point intersection = v2[j].get_intersection(v1[i]);
                intersections.push_back(intersection);
            }
            if(v1[i].intersects(v2[j])) {
                Point intersection = v1[i].get_intersection(v2[j]);
                intersections.push_back(intersection);
            }
        }
    }
    return intersections;
}

vector<int> get_intersection_steps(Path p, Path q) {
    vector<Point> intersections;
    vector<int> step_vector;
    for(int i = 0; i < p.size(); i++) {
        for(int j = 0; j < q.size(); j++) {
            if(p[i].intersects(q[j])) {
                Point intersection = p[i].get_intersection(q[j]);
                int q_steps, p_steps;
                if(i == 0) p_steps = 0;
                else p_steps = p.steps[i-1];
                if(j == 0) q_steps = 0;
                else q_steps = q.steps[j-1];
                int q_offset, p_offset;
                switch(q[j].D) {
                    case RIGHT:
                        q_offset = intersection.x - q[j].A.x;
                        break;
                    case LEFT:
                        q_offset = q[j].B.x - intersection.x;
                        break;
                    case UP:
                        q_offset = intersection.y - q[j].B.y;
                        break;
                    case DOWN:
                        q_offset = q[j].A.y - intersection.y;
                        break;
                }
                switch(p[i].D) {
                    case RIGHT:
                        p_offset = intersection.x - p[i].A.x;
                        break;
                    case LEFT:
                        p_offset = p[i].B.x - intersection.x;
                        break;
                    case UP:
                        p_offset = intersection.y - p[i].B.y;
                        break;
                    case DOWN:
                        p_offset = p[i].A.y - intersection.y;
                        break;
                }
                int total_steps = q_steps + p_steps + q_offset + p_offset;
                intersections.push_back(intersection);
                step_vector.push_back(total_steps);
            }
        }
    }
    return step_vector;
}

int get_min_steps(vector<int> steps) {
    int min = steps[1];
    for(int i = 0; i < steps.size(); i++) {
        int step_count = steps[i];
        if(step_count > 0 && step_count < min) min = step_count;
    }
    return min;
}

vector<Line> get_lines(vector<pair<char, int>> wire1) {
    vector<Line> lines;
    int x, y = 0;
    int new_x, new_y = 0;
    Point p, q;
    Line  l;
    for(int i = 0; i < wire1.size(); i++) {
        switch(wire1[i].first) {
            case 'R':
                new_x = x + wire1[i].second;
                q.x = new_x; q.y = y;
                p.x = x; p.y = y;
                l.A = p; l.B = q;
                l.set_direction();
                l.set_orientation();
                lines.push_back(l);
                x = new_x;
                break;
            case 'L':
                new_x = x - wire1[i].second;
                q.x = new_x; q.y = y;
                p.x = x; p.y = y;
                l.A = p; l.B = q;
                l.set_direction();
                l.set_orientation();
                lines.push_back(l);
                x = new_x;
                break;
            case 'U':
                new_y = y + wire1[i].second;
                p.x = x; p.y = new_y;
                q.x = x; q.y = y;
                l.A = q; l.B = p;
                l.set_direction();
                l.set_orientation();
                lines.push_back(l);
                y = new_y;
                break;
            case 'D':
                new_y = y - wire1[i].second;
                p.x = x; p.y = new_y;
                q.x = x; q.y = y;
                l.A = q; l.B = p;
                l.set_direction();
                l.set_orientation();
                lines.push_back(l);
                y = new_y;
                break;
        }
    }
    return lines;
}

int to_int(string s) {
    int number;
    istringstream is(s);
    if(is >> number) return number;
    else cout << "Something went wrong" << endl;
    exit(1);
}

int main() {

    ifstream file("input.txt");
    string line = "";
    auto start = high_resolution_clock::now(); 
    vector<vector<pair<char, int>>> wires;
    vector<pair<char, int>> wire1;
    vector<pair<char, int>> wire2;
    wires.push_back(wire1);
    wires.push_back(wire2);
    int i = 0;
    cout << endl;
    while(getline(file, line)) {
        int pos = 0;
        char direction = ' ';
        string distance = "";
        while(pos != line.size() + 1) {
            if(isalpha(line[pos])) {
                direction = line[pos];
            } else if(isdigit(line[pos])) {
                distance += line[pos];
            } else if(pos == line.size() || line[pos] == ',') {
                wires[i].push_back(pair<char, int>(direction, to_int(distance)));
                direction = ' ';
                distance = "";
            }
            pos++;
        }
        i++;
    }
    vector<Line> wire1_lines = get_lines(wires[0]);
    vector<Line> wire2_lines = get_lines(wires[1]);
    Path P1(wire1_lines);
    Path P2(wire2_lines);
    vector<Point> intersections = get_intersections(wire1_lines, wire2_lines);
    vector<int> inter_steps = get_intersection_steps(P1, P2);
    int min_distance = get_min_distance(intersections);
    int min_steps = get_min_steps(inter_steps);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 
    cout << "Minimum Distance: " << min_distance << endl;
    cout << "Minimum Steps: " << min_steps << endl;
    cout << "Time: " << duration.count() << endl;
    cout << endl;
    return 0;
}