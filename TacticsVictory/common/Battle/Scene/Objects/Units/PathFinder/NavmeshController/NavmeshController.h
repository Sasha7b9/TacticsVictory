/*

Copyright (c) 2007 Jon Watte

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#pragma once

//  These types are used by the controller. You really only need to 
//  pay attention to the kLocatorNavpointType, because each locator 
//  used by the navmesh should be "navi".
enum {
  kLocatorNavpointType    = 'navi',
  kNavmeshControllerType  = 'nav ',
  kNavpointControllerType = 'navp',
};


//  When navigating, the result of a pathfinding query is a NavmeshPath 
//  instance. Call Dispose() on it when you're done navigating.
class NavmeshPath {
  protected:
    virtual ~NavmeshPath() {}
  public:
    virtual void Dispose() = 0;

    //! Call Move() to update the navigation's sense of where you 
    //! are, and receive advice about what direction to move in.
    //! \return true if you are still on the navigation path, and 
    //! false if you have reached your destination (or the navigation 
    //! has given up). Call Dispose() when you're done with the path.
    virtual bool Move(Pi::Point3D const &pos, Pi::Vector3D *dir) = 0;
};


//  The main interface to navigation is the NavmeshInterface, which allows 
//  you to query a few things about each navmesh, as well as run a pathfinding 
//  query and return a plan (in the form of NavmeshPath).
class NavmeshInterface {
  protected:
    virtual ~NavmeshInterface() {}
  public:
    //  Return name of this navmesh (== name of group node)
    virtual char const *Name() = 0;
    //  Count the number of locators in this mesh.
    virtual long CountNodes() = 0;
    //  Find where each locator is.
    virtual Pi::Point3D GetNodePosition(long index) = 0;
    //  Count the number of neighbors of a given node.
    virtual long CountNodeNeighbors(long index) = 0;
    //  Get a specific neighbor node number for a given node.
    virtual long GetNodeNeighbor(long node, long index) = 0;

    //  Do actual pathfinding. This is the "meat" that you want to actually use.
    virtual NavmeshPath *NavmeshPathCreate(Pi::Point3D const &begin, Pi::Point3D const &end) = 0;
};

//  Call from your GameWorld::Render() function, after calling World::Render(), 
//  to make sure that navmesh show and navmesh path commands can output to the screen.
void MaybeRenderNavmeshes();
//  Find a given navmesh in the world, if defined. Thus, you can have multiple navmeshes 
//  with different names, and use them for different things.
NavmeshInterface *GetNavmeshController(char const *name);

//  These should be built-in to C4, I think!

template<size_t N> Pi::String<N> &operator+=(Pi::String<N> &left, Pi::Vector3D const &right)
{
  return (((((left += right.x) += ",") += right.y) += ",") += right.z);
}

template<size_t N> Pi::String<N> &operator+=(Pi::String<N> &left, Pi::Point3D const &right)
{
  return (((((left += right.x) += ",") += right.y) += ",") += right.z);
}

template<size_t N> Pi::String<N> &operator+=(Pi::String<N> &left, float const &right)
{
  return left += Pi::Text::FloatToString(right);
}
