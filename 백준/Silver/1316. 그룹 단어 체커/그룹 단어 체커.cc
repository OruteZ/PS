#include<iostream>

bool is_group_word(std::string word) {
    bool checker[27];
    for(int i = 0; i < 27; i++) checker[i] = false;

    char before = '\n';

    for(auto c : word) {
        int index = (int)(c - 'a');

        if(checker[index] == true && before != c) return false;

        checker[index] = true; 
        before = c;
    }

    return true;
}

int main() {
    int t_case;
    std::cin >> t_case;

    std::string word;
    int answer = 0;
    while(t_case--) {
        std::cin >> word;

        if(is_group_word(word)) {
            answer++;
        }
    }

    std::cout << answer << std::endl;
}