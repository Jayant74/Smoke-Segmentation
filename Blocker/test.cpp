#include <stdio.h>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <iterator>

// Struct to hold x,y coordinates of a point
struct point
{
    float x, y;
};

// Creates a floating def of infinity
static constexpr float inf = std::numeric_limits<float>::infinity();

// Create struct for axis-aligned-bounding-box
struct box
{
    point min{inf, inf};    //Instance of point with inf,inf as x,y coord.
    point max{-inf, -inf};  //Instance of point with -inf,-inf as x,y coord.

    // An overloaded compount assignment operator '|='
    // This allows box and point to be combined, in this case to extend the struct box 
    // as an argument of point p. 
    box & operator |= (point const & p)
    {
        min.x = std::min(min.x, p.x);   // Obv. min.x=inf > p.x, so it will return p.x
        min.y = std::min(min.y, p.y);
        max.x = std::max(max.x, p.x);
        max.y = std::max(max.y,p.y);
        return *this;   // returns a 'box' or 'point' object?
    }
};

// Template function that finds the lowest and highest x-values and y-values. No pair preservation.
template <typename Iterator>
box bbox(Iterator begin, Iterator end)
{
    box result;
    for (auto it = begin; it != end; ++it)  // begin/end are pointer types to be dereferenced
        result |= *it;   // *it references a point p 
    
    std::cout << "TEST BBOX: " << "(" << result.min.x << ", " << result.min.y << "), (" << result.max.x << ", " << result.max.y << ")" << std::endl;
    return result;  // the bounding box result is extended over points referenced by 'it'
}

std::vector<point> combinator(point const & p1, point const & p2)
{
    std::vector<point> vec(4);
    std::vector<float> X = {p1.x, p2.x};
    std::vector<float> Y = {p1.y, p2.y};
    for(int i=0; i<4; ++i)
    {
        if (i>=2) {
            vec[i] = {X[1],Y[i-2]};
        };

        if (i<2)
            vec[i] = {X[0],Y[i]};
    }
    return vec;
}

using node_id = std::uint32_t;
static constexpr node_id null = node_id(-1);

// IDs for the children of the node
struct node
{
    node_id children[2][2] {
        {null, null},
        {null, null}
    };
};

struct quadtree
{
    box bbox;
    node_id root;
    std::vector<node> nodes;
    
};

int main()
{

    // Test point
    point p1;
    point p2;
    point p3;
    point p4;

    p1.x = 7;
    p1.y = 4;

    p2.x = 6;
    p2.y = 5;

    p3.x = 5;
    p3.y = 7;

    p4.x = 2;
    p4.y = 3;

    std::vector<point> POI = {{p1, p2}};
    std::cout << "TEST POINT: \n" << "point: (" << p1.x << ", " << p1.y << ")\n\n";
    
    /*
    for (const point& p : node)
        std::cout << "TEST VECTOR OF POINTS: \n" << "( " << p.x << ", " << p.y << " )\n" << std::endl;
    */

    // Test box
    box example;
    example |= p1;
    std::cout << "TEST BOX: \n" << "x: " << example.min.x << " y: "  << example.min.y << std::endl; 

    // Test bbox
    bbox(POI.begin(), POI.end());

    // Create Combination (4 corners of bounding box)
    auto arr = combinator(p1, p3);

    /*
    for(int j=0; j<4; j++) {
        std::cout << "TEST COMBO: \n" << "(" << arr[j].x << ", "  << arr[j].y << ")\n" << std::endl; 
    }    
    */



    

    return 0; 
}