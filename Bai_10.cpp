#include <iostream>
#include <vector>
#include <algorithm>

int largestSquareArea(std::vector<std::vector<int>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
    int maxArea = 0;

    // Initialize first row and first column
    for (int i = 0; i < m; i++) {
        dp[i][0] = matrix[i][0];
        maxArea = std::max(maxArea, dp[i][0]);
    }
    for (int j = 0; j < n; j++) {
        dp[0][j] = matrix[0][j];
        maxArea = std::max(maxArea, dp[0][j]);
    }

    // Calculate dp values
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 1) {
                dp[i][j] = std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                maxArea = std::max(maxArea, dp[i][j]);
            }
        }
    }

    return maxArea * maxArea;
}

int main() {
    int m, n;
    std::cin >> m >> n;
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));

    // Read input matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }

    int result = largestSquareArea(matrix);
    std::cout << result << std::endl;

    return 0;
}
