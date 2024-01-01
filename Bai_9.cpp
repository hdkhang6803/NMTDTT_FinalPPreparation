#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "utils.h" // Include the header file for utility functions

//Dynamic programming solution
//Time complexity: O(m*n)
bool DP_isMatch(string s, string p) {
    int m = s.length();
    int n = p.length();

    // Create a 2D table to store the results of subproblems
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false)); //dp[i][j] kiểm tra i chữ đầu của s có match j chữ đầu của p (có rỗng ở đầu)

    // Empty pattern can match with empty string
    dp[0][0] = true;

    // Deals with patterns like a* or a*b* or a*b*c*
    for (int j = 1; j <= n; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2]; //Tính luôn trường hợp kí tự dp[0][j-1] bị xóa đi do ảnh hưởng của * ở dp[0][j]
        }
    }

    // Fill the table in bottom-up manner
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; //Nếu 2 kí tự khớp nhau hoặc có dấu '.' thì kết quả phụ thuộc vào lần so khớp trước đó
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2];  //Tính luôn trường hợp kí tự dp[0][j-1] bị xóa đi do ảnh hưởng của * ở dp[0][j]
                if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) { //Nếu ký tự trước đó là '.' hoặc khớp với ký tự hiện tại của s
                    dp[i][j] = dp[i][j] || dp[i - 1][j];  //Kết quả phụ thuộc vào 2 trường hợp: 
                                                          //1. Ký tự trước đó bị xóa đi (dp[i][j-2])
                                                          //2. Ký tự trước đó không bị xóa đi và phụ thuộc vào kết quả so khớp i-1 ký tự đầu của s (dp[i-1][j])
                }
            } else {
                dp[i][j] = false;
            }
        }
    }

    // Return the result
    return dp[m][n];
}

// //Two pointers approach
// bool TwoPointer_isMatch(string s, string p) {
//     int m = s.length();
//     int n = p.length();

//     int i = 0, j = 0;
//     int pidx = -1, sidx = -1;

//     while (i < m) {
//         if (j < n && (p[j] == s[i] || p[j] == '.')) {
//             ++i;
//             ++j;
//         } else if (j < n && p[j] == '*') {
//             bool match_skip_prev_pj = p[j-2] == s[i];
//             if (match_skip_prev_pj){
//                 sidx = i;
//                 pidx = j;
//                 i++; j++;
//             }else{
//                 if (p[j-1] == '.' || p[j-1] == s[i]){
//                     pidx = j - 1;
//                     sidx = i;
//                     i++;
//                 }else{
//                     j += 2;
//                 }
//             }
//         } else if (pidx == -1) {
//             return false;
//         } else {
//             j = pidx + 1;
//             i = sidx + 1;
//             sidx = i;
//         }
//     }

//     for (int k = j; k < n; k++) {
//         if (p[k] != '*') {
//             return false;
//         }
//     }

//     return true;
// }

int main(){
    string s = "aab";
    string p = "c*a*b";

    cout << DP_isMatch(s, p) << endl;
    // cout << TwoPointer_isMatch(s, p) << endl;
    return 0;
}
