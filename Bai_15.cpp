#include <iostream>
#include <cmath>
#include <iomanip>

const double pi = 3.14159;

//Time complexity: O(1)
double calculateUnionArea(int x1, int y1, int x2, int y2, int radius) {
    double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    double circle_area = pi * radius * radius;
    double union_area = 0;
    
    if (distance >= 2 * radius) {
        union_area = 2 * circle_area;
    } 
    else if (x1 == x2 && y1 == y2){
        union_area = circle_area;
    }    
    else {
        double angle = acos(distance / (2 * radius)) * 2;
        double triangle_area = 0.5 * radius * radius * sin(angle);
        double sector_area = radius * angle;
        double intersection_area = (sector_area - triangle_area) *2;
        union_area = 2 * circle_area - intersection_area;
    }
    return  union_area;
}

int main() {
    int x1, y1, x2, y2, radius;
    std::cout << "Enter the coordinates of the first circle's center (x1 y1): ";
    std::cin >> x1 >> y1;
    std::cout << "Enter the coordinates of the second circle's center (x2 y2): ";
    std::cin >> x2 >> y2;
    std::cout << "Enter the radius of the circles: ";
    std::cin >> radius;
    
    double union_area = calculateUnionArea(x1, y1, x2, y2, radius);
    std::cout << "The area of the union of the two circles is: " << std::setprecision(3) << std::fixed << union_area << std::endl;
    
    return 0;
}
