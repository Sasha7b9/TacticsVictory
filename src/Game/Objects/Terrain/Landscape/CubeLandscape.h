#pragma once


#include "SideCube.h"
#include "CornerCube.h"
#include "EdgeCube.h"


class CubeLandscape
{
public:
    CubeLandscape();
    SharedPtr<SideCube> sides[4];
    SharedPtr<CornerCube> corners[4];
    SharedPtr<EdgeCube> edges[2];
    
private:
};

/*                     Corner_0              Corner_1
                          |                    |                                                      
                          |   Edge_0           |                                                      
                          |     |              |                                                      
                          |     |              |                                                      
                          |     |              |                                                      
                          /-----+--------------/
                        /       |            / |                           /|\ Y
                      /         |          /   |                            |
                    /                    /     |                            |    -/| Z
                  /                  / |       |                            |    /
                 |----------------| /  |       |                            |   /
                 |                |    |       |                            |  /
                 |                |    |       |                            | /         
                 |                |    |       |                            |/----------+
                 |                |    |      /                                          X
                 |                |    |    /
                 |       |        |    |   /
                 |       |        |    | /
                 |       |        |  / |/
                 |-------+--------|/
                         |
                         |
                         |
                       Side_3
*/                       
