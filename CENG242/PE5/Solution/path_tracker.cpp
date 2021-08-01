#include <iostream>
#include <math.h>
#include "path_tracker.h"

/* DO NOT EDIT HEADER FILE*/

/**
 * Empty constructor
 * 
 * Initialize all attributes as 0
 */
PathTracker::PathTracker()
{
    final_x=final_y=0;
    displacement=0;
    distance=0;
}

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
PathTracker::PathTracker(int *existing_path, int number_of_vectors)
{
    final_x=final_y=0;
    distance=0;
    for(int i=0;i<number_of_vectors;i++){
        distance+=sqrt(existing_path[2*i]*existing_path[2*i]+existing_path[2*i+1]*existing_path[2*i+1]);
        final_x+=existing_path[2*i];
        final_y+=existing_path[2*i+1];
    }
    displacement=sqrt(final_x*final_x+final_y*final_y);
}

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
PathTracker &PathTracker::operator+=(const int *new_vector)
{
    final_x+=new_vector[0];
    final_y+=new_vector[1];
    distance+=sqrt(new_vector[0]*new_vector[0]+new_vector[1]*new_vector[1]);
    displacement=sqrt(final_x*final_x+final_y*final_y);
    return *this;
}

/**
 * Equality comparison overload
 * 
 * This operator checks only displacements.
 * 
 * @param rhs The PathTracker to compare
 * @return returns true if both displacements are same false otherwise
 */
bool PathTracker::operator==(const PathTracker &rhs) const
{
    return displacement==rhs.displacement;
}

/**
 * Comparison overload
 * 
 * This operator checks only displacements.
 * 
 * @param rhs The PathTracker to compare
 * @return returns true if the displacement of original PathTracker is longer, false otherwise
 */
bool PathTracker::operator>(const PathTracker &rhs) const
{
    return displacement>rhs.displacement;
}

/**
 * Comparison overload
 * 
 * This operator checks only displacements.
 * 
 * @param rhs The PathTracker to compare
 * @return returns true if the displacement of original PathTracker is shorter, false otherwise
 */
bool PathTracker::operator<(const PathTracker &rhs) const
{
    return displacement<rhs.displacement;
}

/**
 * Equality comparison overload
 * 
 * This operator checks only distance of the PathTracker
 * 
 * @param distance floating-point to compare
 * @return returns true if the distance value of PathTracker and comp value are equal, false otherwise
 */
bool PathTracker::operator==(const float comp) const
{
    return comp==distance;
}

/**
 * Calculates and returns the displacement value of the path. 
 * Displacement: Distance between final position and the first position (origin)
 * 
 * @return value of the displacement
 */
float PathTracker::calculate_displacement()
{
    return sqrt(final_x*final_x+final_y*final_y);
}

/**
 * Calculates and sets the distance value of the path.
 * Distance: Total length of the path.
 * 
 * @param x x-component of the newly added vector
 * @param y y-component of the newly added vector
 */
void PathTracker::calculate_distance(int x, int y)
{
    distance+=sqrt(x*x+y*y);
}

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
float PathTracker::calculate_l2(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

/**
 * Prints the summary of the PathTracker as:
 * Final position: [x,y] Displacement: #disp# Distance: #dist#
 * Do not forget the newline char at the end.
 */
void PathTracker::summary()
{
    /* do NOT remove this line */
    std::cout.precision(5);
    
    /* WRITE YOUR CODE HERE */
    std::cout<<"Final Position: ["<<final_x<<","<<final_y<<"] Displacement: "<<displacement<<" Distance: "<<distance<<std::endl;
}