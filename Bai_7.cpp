#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "utils.h" // Include the header file for utility functions

using namespace std;
//Complexity
//Time: O(n)
//Space: 1
int naive_trap(vector<int> height) {
    int size = height.size();
    height.push_back(0); //dummy tail
    int left = 0;
    int right = 0;
    int amount_trap = 0;
    bool flag = 1;
    int i = 0;
    while (flag){
        flag = 0;
        i = 0;
        while (i < size - 1){
            if (height[i] > height[i + 1]){ //Nếu bắt đầu của 1 con dốc đi xuống
                left = i; //ping left = đẩu con dốc (đỉnh đầu tiên)
                int j = i;
                while (j < size){
                    if (height[j] >= height[j+1]) j++; //Nếu chưa đi xuống hết dốc thì tiếp tục đi xuống
                    else if (height[j] < height[j+1]){ //Nếu đi xuống hết dốc
                        while (j < size && height[j] <= height[j+1]) j++; //Đi lên đến khi gặp đỉnh kế tiếp
                        right = j; //ping right = đỉnh kế tiếp
                        int val = min(height[left], height[right]); //Tìm độ cao nhỏ nhất của 2 đỉnh == độ cao của đáy hố nước
                        if (val == height[left])
                            for(int k = left; k <= right && height[k] <= val; k++){
                                amount_trap += val - height[k]; //sum amlunt of trapped water
                                height[k] += val - height[k]; //fill the gap
                            }
                        else
                            for(int k = right; k >= left && height[k] <= val; k--){
                                amount_trap += val - height[k];
                                height[k] += val - height[k];
                            }
                        flag = 1;
                        break;
                    }
                }
                i = j; //nhảy tới đỉnh kế tiếp
            }else i++;
        }   
    }
    
    return amount_trap;
}

//complexity
//Time: O(n)
int two_pointer_trap(vector<int> height){
    int n = height.size();
    int lmax = height[0]; // Initialize the left maximum height to the first element of the height array
    int rmax = height[n-1]; // Initialize the right maximum height to the last element of the height array
    int lpos = 1; // Initialize the left position pointer to the second element of the height array
    int rpos = n-2; // Initialize the right position pointer to the second-to-last element of the height array
    int water = 0; // Initialize the total amount of trapped water to 0
    while(lpos <= rpos)
    {
        if(height[lpos] >= lmax) // If the height at the left position is greater than or equal to the left maximum height
        {
            lmax = height[lpos]; // Update the left maximum height
            lpos++; // Move the left position pointer to the right
        }
        else if(height[rpos] >= rmax) // If the height at the right position is greater than or equal to the right maximum height
        {
            rmax = height[rpos]; // Update the right maximum height
            rpos--; // Move the right position pointer to the left
        }
        else if(lmax <= rmax && height[lpos] < lmax) // If the left maximum height is less than or equal to the right maximum height and the height at the left position is less than the left maximum height
        {
            water += lmax - height[lpos]; // Calculate the amount of trapped water between the left maximum height and the height at the left position
            lpos++; // Move the left position pointer to the right
        }
        else
        {
            water += rmax - height[rpos]; // Calculate the amount of trapped water between the right maximum height and the height at the right position
            rpos--; // Move the right position pointer to the left
        }
    
    }
    return water; // Return the total amount of trapped water
}

int prefix_trap(vector<int> height){
    int n = height.size();
    vector<int> lmax(n, 0);
    vector<int> rmax(n, 0);
    lmax[0] = height[0];
    rmax[n-1] = height[n-1];
    for(int i = 1; i < n; i++){
        lmax[i] = max(lmax[i-1], height[i]);
    }
    for(int i = n-2; i >= 0; i--){
        rmax[i] = max(rmax[i+1], height[i]);
    }
    int water = 0;
    for(int i = 0; i < n; i++){
        water += min(lmax[i], rmax[i]) - height[i];
    }
    return water;
}

int main() {
    vector<int> height = {4, 2, 0, 3, 2, 5};
    
    // Test naive_trap function
    int trappedWaterNaive = naive_trap(height);
    cout << "Amount of trapped water (naive_trap): " << trappedWaterNaive << endl;
    
    // Test two_pointer_trap function
    int trappedWaterTwoPointer = two_pointer_trap(height);
    cout << "Amount of trapped water (two_pointer_trap): " << trappedWaterTwoPointer << endl;

    //Test prefix_trap function
    int trappedWaterPrefix = prefix_trap(height);
    cout << "Amount of trapped water (prefix_trap): " << trappedWaterPrefix << endl;
    
    return 0;
}