#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#include <queue>
#include <tuple>
#include <string>
#include "utils.h" // Include the header file for utility functions

using namespace std;

//Naive function for the problem
//Sinh ra toàn bộ các số chỉ gồm 0 và 1 rồi kiểm tra dư.
//Do m không quá 9 chữ số => m chỉ có thể có tối đa 2^9 = 512 số
// Vì vậy phát sinh ra hết 512 số này rồi kiểm tra dư vẫn chấp nhận được
//Complexity
//Time: O(n*2^n) với n là số chữ số của m

int naive_findM(int n){
    for(int mask = 1; mask < (1<<9); mask++){
        vector<bool>a;
        for(int i = 0; i < 9; i++){
            a.push_back((mask >> i) & 1);
        }
        reverse(a.begin(), a.end());
        // cout << "\na: ";
        // for(int i = 0; i < a.size(); i++){
        //     cout << a[i] << " ";
        // }
        int decimal = 0;
        for(int i = 0; i < a.size(); i++){
            decimal = decimal * 10 + a[i];
        }
        // cout << decimal << endl;
        if (decimal % n == 0){
            return decimal;
        }
    }
    return -1;
}

//GRaph bfs function for the problem
//Sinh ra các số chỉ gồm 0 và 1 rồi kiểm tra dư. Nếu dư == 0 thì trả về kết quả
//Node đầu tiên là 1, sau đó sinh ra node 11 và 10 rồi tiếp tục.
//Complexity
//Time: O(min(2^n, 2^k)) với n là số số dư có thể có của số chia n tức là (n-1), vì mỗi lần duyệt ta sẽ sinh ra 2 số mới, nên số lần duyệt là 2^n. 
//Tuy nhiên do chúng ta giới hạn lại chiều dài tối đa của m là k chữ số, nên số lần duyệt là 2^k 
std::string better_findM(int n) {
    std::unordered_map<int, std::pair<int, int>> parents;
    std::queue<std::tuple<int, int, int>> q;
    q.push({1 % n, 1, -1});
    int count = 0;

    while (!q.empty()) {
        // if (count >9) return "-1";
        
        auto [residue, digit, parent] = q.front();
        q.pop();
        // cout << residue << " " << digit << " " << parent << endl;
        
        count ++;
        if (parent.find(residue) != parents.end(s)) {
            continue;
        }

        if (residue == 0) {
            cout << "count: " << count << endl;
            std::vector<int> answer;
            while (true) {
                answer.push_back(digit);
                if (parent == -1) {
                    std::reverse(answer.begin(), answer.end());
                    std::string result;
                    for (int num : answer) {
                        result += std::to_string(num);
                    }
                    return result;
                }
                std::tie(digit, parent) = parents[parent];
            }
        }

        parents[residue] = {digit, parent};

        for (int nextDigit : {0, 1}) {
            q.push({(residue * 10 + nextDigit) % n, nextDigit, residue});
        }
        
    }

    return "";
}
int main() {
    int n; // Sample input
    cin >> n;
    int result = naive_findM(n);
    cout << "The smallest number divisible by " << n << " is: " << result << endl;
    cout << "The smallest number divisible by " << n << " is: " << better_findM(n) << endl;
    return 0;
}
