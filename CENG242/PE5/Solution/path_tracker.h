#ifndef PATH_VECTORS_H
#define PATH_VECTORS_H

#include <iostream>

/* DO NOT EDIT HEADER FILE*/

class PathTracker
{
public:
    int final_x;
    int final_y;
    float displacement;
    float distance;

    /**
     * Empty constructor
     * 
     * Initialize all attributes as 0
     */
    PathTracker();

    /**
     * Constructor
     * 
     * Given existing_path array contains x,y couples representing vectors
     * to add end-to-end.
     * [1, 2, 3, 4, 5, 6] -> 3 vectors: [1, 2], [3, 4], [5, 6]
     * Add them end-to end: [1, 2] + [3, 4] + [5, 6] -> [9, 12]
     * Note: Update displacement and distance at each addition.
     * 
     * @param existing_path List of vectors to add end-to-end
     * @param number_of_vectors The number of vectors (not the size of the array)
    */
    PathTracker(int *existing_path, int number_of_vectors);

    /**
     * sum and equal operator
     * Adds new vector to the end of the path.
     * 
     * Note: All properties of the object will be updated.
     * final_x and final_y coordinates, displacement and distance
     * values will be updated. 
     * 
     * @param rhs Integer array with length of 2, containing x, y components of the vector to be added.
     * @return this PathTracker after adding new vector to the end.
     */
    PathTracker &operator+=(const int *new_vector);

    /**
     * Equality comparison overload
     * 
     * This operator checks only displacements.
     * 
     * @param rhs The PathTracker to compare
     * @return returns true if both displacements are same false otherwise
     */
    bool operator==(const PathTracker &rhs) const;

    /**
     * Comparison overload
     * 
     * This operator checks only displacements.
     * 
     * @param rhs The PathTracker to compare
     * @return returns true if the displacement of original PathTracker is longer, false otherwise
     */
    bool operator>(const PathTracker &rhs) const;

    /**
     * Comparison overload
     * 
     * This operator checks only displacements.
     * 
     * @param rhs The PathTracker to compare
     * @return returns true if the displacement of original PathTracker is shorter, false otherwise
     */
    bool operator<(const PathTracker &rhs) const;

    /**
     * Equality comparison overload
     * 
     * This operator checks only distance of the PathTracker
     * 
     * @param distance floating-point to compare
     * @return returns true if the distance value of PathTracker and comp value are equal, false otherwise
     */
    bool operator==(float comp) const;

    /**
     * Calculates and returns the displacement value of the path. 
     * Displacement: Distance between final position and the first position (origin)
     * 
     * @return value of the displacement
     */
    float calculate_displacement();

    /**
     * Calculates and sets the distance value of the path.
     * Distance: Total length of the path.
     * 
     * @param x x-component of the newly added vector
     * @param y y-component of the newly added vector
     */
    void calculate_distance(int x, int y);

    /**
     * It is a helper function which calculates Euclidean distance between two
     * points on the vector space.
     * 
     * @param x1 x-component of the first point
     * @param y1 y-component of the first point
     * @param x2 x-component of the second point
     * @param y2 y-component of the second point
     * @return Euclidean distance value
     */
    float calculate_l2(int x1, int y1, int x2, int y2);

    /**
     * Prints the summary of the PathTracker as:
     * Final position: [x,y] Displacement: #disp# Distance: #dist#
     * Do not forget the newline char at the end.
     */
    void summary();
};

#endif //PATH_VECTORS_H
