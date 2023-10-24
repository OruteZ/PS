#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
#include<stack>
#include<array>
#include<map>

#pragma region MACRO

#define LL long long
#define DEBUG false
#define PRINT_LINE std::cout << "--------------------" << '\n'
#define REPEAT(n) for(int _ = 0; _ < n; _++)

#pragma endregion

struct node {
public:
    std::string word;
    std::map<std::string, node> children;

    void set(const std::vector<std::string> &w, int index) {
        if(index == w.size()) return;

        auto output = children.find(w[index]);
        if(output == children.end()) {
            children[w[index]] = node{w[index]};

            output = children.find(w[index]);
        }

        output->second.set(w, index + 1);
    }

    void print(int depth) {
        if(depth >= 0) {
            REPEAT(depth) std::cout << "--";
            std::cout << word << '\n';
        }

        for(auto &child: children) {
            child.second.print(depth + 1);
        }
    }
};

struct Trie {
    node root {"__ROOT__"};

    Trie() {
        root.children.clear();
    }

    void set(const std::vector<std::string> &words) {
        root.set(words, 0);
    }

    void print() {
        root.print(-1);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    Trie trie;

    int t; std::cin >> t;

    while(t--) {
        int size; std::cin >> size;

        std::vector<std::string> words(size);
        for(auto &word : words) {
            std::cin >> word;
        }

        trie.set(words);
    }

    trie.print();


    return 0;
}