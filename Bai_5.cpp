#include <iostream>
#include <string>
#include <vector>

// Do phuc tap: O(n + m) (KMP)

// Function to compute the Longest Proper Prefix which is also Suffix (LPS) array
// std::vector<int> computeLPS(const std::string& pattern) {
//     int len = pattern.length();
//     std::vector<int> lps(len, 0); // Initialize LPS array with 0
//     int i = 1;
//     int j = 0;

//     while (i < len) {
//         if (pattern[i] == pattern[j]) { // If characters match
//             lps[i] = j + 1; // Update LPS value for current index
//             i++;
//             j++;
//         } else {
//             if (j != 0) { // If j is not at the beginning of the pattern
//                 j = lps[j - 1]; // Move j to the previous LPS value
//             } else {
//                 lps[i] = 0; // No LPS value found, set it to 0
//                 i++;
//             }
//         }
//     }

//     return lps; // Return the LPS array
// }

// // Function to find positions of all occurrences of pattern B in string A
// std::vector<int> findSubstringPositions(const std::string& A, const std::string& B) {
//     std::vector<int> positions; // Vector to store the positions
//     int lenA = A.length();
//     int lenB = B.length();

//     std::vector<int> lps = computeLPS(B); // Compute LPS array for pattern B

//     int i = 0;
//     int j = 0;

//     while (i < lenA) {
//         if (A[i] == B[j]) { // If characters match
//             i++;
//             j++;
//         }

//         if (j == lenB) { // If pattern B is found
//             positions.push_back(i - j + 1); // Add the starting position to the vector
//             j = lps[j - 1]; // Move j to the previous LPS value
//         } else if (i < lenA && A[i] != B[j]) { // If characters don't match
//             if (j != 0) { // If j is not at the beginning of the pattern
//                 j = lps[j - 1]; // Move j to the previous LPS value
//             } else {
//                 i++; // Move to the next character in string A
//             }
//         }
//     }

//     return positions; // Return the vector of positions
// }

// int main() {
//     std::string A, B;
//     std::getline(std::cin, A); // Read string A from input
//     std::getline(std::cin, B); // Read string B from input

//     std::vector<int> positions = findSubstringPositions(A, B); // Find positions of pattern B in string A

//     for (int i = 0; i < positions.size(); i++) {
//         std::cout << positions[i]; // Print each position
//         if (i < positions.size() - 1) {
//             std::cout << " "; // Print space between positions
//         }
//     }

//     return 0;
// }

//     // BEGIN: ed8c6549bwf9
//     // Time complexity: O(n + m), where n is the length of string A and m is the length of string B.
//     // The hash values of both strings are calculated in O(n + m) time.
//     // Sliding the window through string A takes O(n) time.
//     // Overall, the time complexity is dominated by the calculation of hash values, which is O(n + m).

//     // Space complexity: O(1)
//     // The algorithm uses a constant amount of extra space to store the hash values, power, and occurrences vector.
//     // Therefore, the space complexity is O(1).
//     // END: ed8c6549bwf9

// cach khac: dung hashing

using namespace std;

const int BASE = 311;
const int MOD = 1e9 + 7;

vector<int> findOccurrences(const string& A, const string& B) {
    int lenA = A.length();
    int lenB = B.length();

    // Calculate the hash value of B
    int hashB = 0;
    for (int i = 0; i < lenB; i++) {
        hashB = (hashB * BASE + (B[i] - 'a')) % MOD;
    }

    // Calculate the hash value of the first lenB characters of A
    int hashA = 0;
    for (int i = 0; i < lenB; i++) {
        hashA = (hashA * BASE + (A[i] - 'a')) % MOD;
    }

    vector<int> occurrences;

    // Check if B appears at position 0
    if (hashA == hashB) {
        occurrences.push_back(0);
    }

    // Calculate the power of BASE^lenB
    int power = 1;
    for (int i = 0; i < lenB - 1; i++) {
        power = (power * BASE) % MOD;
    }

    // Slide the window of length lenB through A
    for (int i = lenB; i < lenA; i++) {
        // Update the hash value of the window
        hashA = (hashA - (power * (A[i - lenB] - 'a')) % MOD + MOD) % MOD;
        hashA = (hashA * BASE + (A[i] - 'a')) % MOD;

        // Check if B appears at position i - lenB + 1
        if (hashA == hashB) {
            occurrences.push_back(i - lenB + 1);
        }
    }

    return occurrences;
}

int main() {
    string A, B;
    getline(cin, A);
    getline(cin, B);

    vector<int> occurrences = findOccurrences(A, B);

    for (int i = 0; i < occurrences.size(); i++) {
        cout << occurrences[i] + 1 << " ";
    }

    return 0;
}


// bien the: 