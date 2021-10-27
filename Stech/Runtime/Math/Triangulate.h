//
// Created by fer on 10/2/2021.
// Ported from https://www.flipcode.com/archives/Efficient_Polygon_Triangulation.shtml
//

#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include <vector>
#include "raylib.h"

class Triangulate {
public:

    // triangulate a contour/polygon, places results in STL vector
    // as series of triangles.
    static bool Process(const std::vector<Vector2> &contour,
                        std::vector<Vector2> &result);

    // compute area of a contour/polygon
    static float Area(const std::vector<Vector2> &contour);

    // decide if point Px/Py is inside triangle defined by
    // (Ax,Ay) (Bx,By) (Cx,Cy)
    static bool InsideTriangle(float Ax, float Ay,
                               float Bx, float By,
                               float Cx, float Cy,
                               float Px, float Py);
private:
    static bool Snip(const std::vector<Vector2> &contour,int u,int v,int w,int n,std::vector<int> &V);

};


#endif
