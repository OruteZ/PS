#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <climits>

#define DEBUG true

using namespace std;

struct point {
    int x;
    int y;
    int number;

    bool operator<(const point& other) const {
        return y < other.y;
    }

    bool operator==(const point& other) const {
        return
            x == other.x and
            y == other.y and
            number == other.number;
    }

    bool operator!=(const point& other) const {
        return
            x != other.x or
            y != other.y or
            number != other.number;
    }
} ;

bool comp(const point& l, const point& r) {
    return l.y >= r.y;
}

point NullPoint() {
    return point {-1, -1, -1};
}

//======= Tree Method ========
void insert(map<int, pair<point, point>>& tree, point value, point at) {
    if(value.x < at.x) {
        if(tree[at.number].first == NullPoint()) {
            tree[at.number].first = value;
            tree[value.number] = make_pair(NullPoint(), NullPoint());
            return;
        }
        
        insert(tree, value, tree[at.number].first);
    }
    
    else {
        if(tree[at.number].second == NullPoint()) {
            tree[at.number].second = value;
            tree[value.number] = make_pair(NullPoint(), NullPoint());
            return;
        }
        
        insert(tree, value, tree[at.number].second);
    }
}

void preorder(map<int, pair<point, point>>& tree, point at, vector<int>& ret) {
    point& l_child = tree[at.number].first;
    point& r_child = tree[at.number].second;


    ret.push_back(at.number);
    if(l_child != NullPoint()) preorder(tree, l_child, ret);
    if(r_child != NullPoint()) preorder(tree, r_child, ret);
}

void afterorder(map<int, pair<point, point>>& tree, point at, vector<int>& ret) {
    point& l_child = tree[at.number].first;
    point& r_child = tree[at.number].second;


    if(l_child != NullPoint()) afterorder(tree, l_child, ret);
    if(r_child != NullPoint()) afterorder(tree, r_child, ret);
    ret.push_back(at.number);
}

void inorder(map<int, pair<point, point>>& tree, point at, vector<int>& ret) {
    point& l_child = tree[at.number].first;
    point& r_child = tree[at.number].second;


    if(l_child != NullPoint()) inorder(tree, l_child, ret);
    ret.push_back(at.number);
    if(r_child != NullPoint()) inorder(tree, r_child, ret);
}

//======= Fin =======


vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer(2);

    vector<point> points(nodeinfo.size());
    for(int i = 0; i < points.size(); i++) {
        points[i].x = nodeinfo[i][0];
        points[i].y = nodeinfo[i][1];
        points[i].number = i + 1;
    }

    sort(points.begin(), points.end(), comp);

    map<int, pair<point, point>> tree;
    //push root
    tree[points[0].number] = make_pair(NullPoint(), NullPoint());

    for(int i = 1; i < points.size(); i++) {
        insert(tree, points[i], points[0]);
    }

     preorder(tree, points[0], answer[0]);
     afterorder(tree, points[0], answer[1]);
    


    return answer;
}