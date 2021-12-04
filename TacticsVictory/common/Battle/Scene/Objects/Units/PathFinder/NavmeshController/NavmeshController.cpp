
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

#include "Scene/Objects/Units/PathFinder/NavmeshController/NavmeshController.h"
#include <assert.h>


//  Version of the serialized controller data. New members 
//  means new versions.
#define CUR_VERSION 4


class NavpointController;
class WalkPath;


using namespace Pi;


//  NavmeshController is the core of the entire system. It should be attached 
//  to a group node, which should have Locator children of type "navi".
class NavmeshController : public Controller, public ListElement<NavmeshController>,
    public NavmeshInterface {

  public:

    struct NeighborInfo {
      NeighborInfo(long i, Marker *m) : ix_(i), mrk_(m) {}
      NeighborInfo() {}
      long ix_;
      Marker *mrk_;
    };

    //  Nothing is private inside the .cpp file -- you can only get 
    //  at the data through the abstract NavmeshInterface anyway!
    unsigned short version_;
    unsigned short meshCleanup_;
    float radius_;
    float verticalDistance_;
    float hJump_;
    float vJump_;
    float vFall_;
    ColorRGBA meshColor_;
    Array<Marker *> markers_;
    Array<long> neighborIndices_;
    Array<NeighborInfo> neighborArray_;
    long curEnumNode_;
		bool showingGeometry_;
		Renderable lines_;
		Point3D *lineVertices_;
		ColorRGBA *lineColors_;
		unsigned short *lineIndices_;

    NavmeshController();
    ~NavmeshController();

    //  Editor support
    Controller *Replicate() const;
    static bool ValidNode(const Node *node);
    virtual int GetSettingCount() const override;
    virtual Setting *GetSetting(int index) const override;
    void SetSetting(const Setting *setting);

    //  saving/loading
    unsigned long GetPackSize(unsigned long packFlags) const;
    virtual void Pack(Packer& data, PackFlag::E packFlags) const override;
    virtual void Unpack(Unpacker& data, uint unpackFlags) override;

    //  Node functions
    void Preprocess();
    void Move();

    //  Implementation functions
    void AddPotentialNeighbor(Point3D const &center, Node *node);
    void Rebuild();
    long GetMarkerCount() { return markers_.GetElementCount(); }
    bool ShowingGeometry() { return showingGeometry_; }
    void ShowGeometry();
    void HideGeometry();
    //  Geometry queries
    bool TooSteepGround(Point3D const &a, Point3D const &b);
    float GetPosHeight(Point3D const &pos);
    float CastRay(Point3D const &a, Point3D const &b);
    Marker *NavmeshController::FindClosestMarkerTo(Point3D const &begin, Point3D const &end, bool forward);
    //  A-star searching through the mesh
    bool AStarSearchIntoWalkPath(Marker *begin, Marker *end, WalkPath *wp);

    //  The Command handler. Doesn't really have to be a member.
    static void NavmeshCommand(char const *text);
    static List<NavmeshController> allNavMeshes_;

    //  Implementation of the NavmeshInterface protocol.
    virtual char const *Name() {
      return GetTargetNode()->GetNodeName();
    }
    virtual long CountNodes() {
      return markers_.GetElementCount();
    }
    virtual Point3D GetNodePosition(long index) {
      assert(index < CountNodes());
      return markers_[index]->GetWorldPosition();
    }
    virtual long CountNodeNeighbors(long index) {
      assert(index < CountNodes());
      return neighborIndices_[index+1] - neighborIndices_[index];
    }
    virtual long GetNodeNeighbor(long node, long index);

    //  The meat for any client of this controller is the NavmeshPathCreate()
    //  function, which does pathfinding.
    virtual NavmeshPath *NavmeshPathCreate(Point3D const &begin, Point3D const &end);
};

List<NavmeshController> NavmeshController::allNavMeshes_;


//  The NavpointController is used to just hang some data onto the 
//  navmesh markers (so I know which index they are in the markers list).
//  If those markers have other controllers when loading the file, I blow 
//  those controllers away. Tough luck! :-)
class NavpointController : public Controller {
  public:

    NavmeshController *navmesh_;
    long navmeshIndex_;

    NavpointController(NavmeshController *nmc, long ix)
        : Controller(kNavpointControllerType), navmesh_(nmc), navmeshIndex_(ix) {}
    ~NavpointController() {}

    //  Just dummy implementations, as this controller is only ever 
    //  instantiated when creating the navmesh; it shouldn't get saved 
    //  to the file. I have no factory for it, hence no saving or loading.

    Controller *Replicate() const { assert(0); return 0; }
    static bool ValidNode(const Node *node) { return false; }
    virtual int GetSettingCount() const override { return 0; }
    virtual Setting *GetSetting(int index) const override { return 0; }
    void SetSetting(const Setting *setting) {}

    unsigned long GetPackSize(unsigned long packFlags) const { return 0; }
    virtual void Pack(Packer& data, PackFlag::E packFlags) const override {}
    virtual void Unpack(Unpacker& data, uint unpackFlags) override {}

    void Preprocess() {}
    void Move() {}
};


//  NavRenderable is used to keep track of the Renderable, and the backing 
//  vertex data, all in one convenient object. It also keeps a list of all 
//  instances of itself, for convenient addition to the graphics manager.
struct NavRenderable : public Renderable {
  public:
    static Array<NavRenderable *> all_;

    //  After creating it, call AddVertex() some number of times, 
    //  followed by Commit(). Only after Commit() will the renderable 
    //  be ready to render.
    NavRenderable()
      : Renderable(PiTypeRender::E::LineStrip, PiStateRender::DepthTest)
    {
      all_.AddElement(this);
    }
    ~NavRenderable() {
      all_.RemoveElement(all_.FindElement(this));
    }

    Array<Point3D> vertices_;

    void AddVertex(Point3D const &p) {
      vertices_.AddElement(p);
    }
    void Commit() {
        SetVertexAttributeArray(PiArrayIndex::Position, 0, vertices_.GetElementCount());
    }
};

Array<NavRenderable *> NavRenderable::all_;



static Command navmeshCommand_("navmesh", &NavmeshController::NavmeshCommand);

bool GetPoint3D(char const *&ptr, Point3D *out) {
  String<100> str;
  while (*ptr && isspace(*ptr)) {
    ++ptr;
  }
  char const *base = ptr;
  while (*ptr && *ptr != ',') {
    ++ptr;
  }
  if (base - ptr >= 100) return false;
  str.Set(base, ptr-base);
  out->x = Text::StringToFloat(str);
  if (!*ptr) return false;
  base = ptr+1;
  ptr = base;
  while (*ptr && *ptr != ',') {
    ++ptr;
  }
  if (base - ptr >= 100) return false;
  str.Set(base, ptr-base);
  out->y = Text::StringToFloat(str);
  if (!*ptr) return false;
  base = ptr+1;
  ptr = base;
  while (*ptr == '-' || *ptr == 'e' || *ptr == 'E' || *ptr == '.' || (*ptr >= '0' && *ptr <= '9')) {
    ++ptr;
  }
  if (base - ptr >= 100) return false;
  str.Set(base, ptr-base);
  out->z = Text::StringToFloat(str);
  return true;
}


namespace {
  class RemoveAllNavs {
    public:
      ~RemoveAllNavs() {
        NavmeshController::allNavMeshes_.RemoveAll();
      }
  };
  static RemoveAllNavs ran;
}

//  Template on the navmesh type, as some of the functions are called from "const".
//  This function passes miscellaneous information about each member to the visitor, 
//  effectively binding data semantics to each member. In some other languages, this 
//  could be done with member annotations (such as C#), but not in plain C++.
template<typename Navmesh, typename Visitor> void NavmeshVisit(Navmesh &c, Visitor &v) {
  v(c.version_, 1, 1, CUR_VERSION, 0, 0);
  v(c.radius_, 1, 2.0f, 200.0f, 1.0f, "Radius", 'radi');
  v(c.verticalDistance_, 1, 0.125f, 10.0f, 0.125f, "Vertical", 'vert');
  v(c.hJump_, 1, 0.125f, 10.0f, 0.125f, "Walk Resolution", 'hjmp');
  v(c.vJump_, 1, 0.125f, 4.0f, 0.125f, "Maximum Rise", 'vjmp');
  v(c.vFall_, 3, 0.125f, 8.0f, 0.125f, "Maximum Fall", 'vfal');
  v(c.meshCleanup_, 2, 1, 3, "Complexity", 'clup');
  v(c.meshColor_, 4, "Mesh Color", 'mcol');
}

//  Use NavmeshSaveVisitor to save data to a packer.
//  This could be used for any controller, really.
class NavmeshSaveVisitor {
  public:
    NavmeshSaveVisitor(Packer& data, unsigned long packFlags)
      : packer_(data), flags_(packFlags)
    {
    }
    Packer &packer_;
    unsigned long flags_;
    void operator()(const unsigned short &s, unsigned short version, unsigned short min, unsigned short max, char const *name, unsigned long id) {
      packer_ << s;
    }
    void operator()(const float &f, unsigned short version, float min, float max, float step, char const *name, unsigned long id) {
      packer_ << f;
    }
    void operator()(const ColorRGBA &c, unsigned short version, char const *name, unsigned long id) {
      packer_ << c;
    }
};

//  Use NavmeshLoadVisitor to load data from an unpacker.
//  This could be used for any controller, really, except for the "version_" test
//  (which could be a passed-in parameter).
class NavmeshLoadVisitor {
  public:
    NavmeshLoadVisitor(NavmeshController &ctl, Unpacker& data, unsigned long packFlags)
      : ctl_(ctl), packer_(data), flags_(packFlags)
    {
    }
    NavmeshController &ctl_;
    Unpacker &packer_;
    unsigned long flags_;
    void operator()(unsigned short &s, unsigned short version, unsigned short min, unsigned short max, char const *name, unsigned long id) {
      if (ctl_.version_ >= version) {
        packer_ >> s;
      }
      if (s < min) s = min;
      if (s > max) s = max;
    }
    void operator()(float &f, unsigned short version, float min, float max, float step, char const *name, unsigned long id) {
      if (ctl_.version_ >= version) {
        packer_ >> f;
      }
      if (f < min) f = min;
      if (f > max) f = max;
    }
    void operator()(ColorRGBA &c, unsigned short version, char const *name, unsigned long id) {
      if (ctl_.version_ >= version) {
        packer_ >> c;
      }
    }
};

//  Use NavmeshSizeVisitor to calculate size needed to save.
//  This could be used for any controller, really.
class NavmeshSizeVisitor {
  public:
    NavmeshSizeVisitor()
      : size_(0)
    {
    }
    long size_;
    void operator()(const unsigned short &s, unsigned short version, unsigned short min, unsigned short max, char const *name, unsigned long id) {
      size_ += 2;
    }
    void operator()(const float &f, unsigned short version, float min, float max, float step, char const *name, unsigned long id) {
      size_ += 4;
    }
    void operator()(const ColorRGBA &c, unsigned short version, char const *name, unsigned long id) {
      size_ += sizeof(ColorRGBA);
    }
};

//  Use NavmeshControlMaker to create the appropriate control for each member.
//  Note that each member will be visited for only creating one specific control, 
//  but that's OK because visiting is really fast. You'd need thousands of controls 
//  to even be able to measure any n-squared effect.
//  This could be used for any controller, really.
class NavmeshControlMaker {
  public:
    NavmeshControlMaker(long toMake = -1)
      : cnt_(0)
      , toMake_(toMake)
      , set_(0)
    {
    }
    long cnt_;
    long toMake_;
    Setting *set_;
    void operator()(const unsigned short &s, unsigned short version, unsigned short min, unsigned short max, char const *name, unsigned long id) {
      if (!name) return;
      ++cnt_;
      if (cnt_-1 == toMake_) {
        set_ = new IntegerSetting(id, s, name, min, max, 1);
      }
    }
    void operator()(const float &f, unsigned short version, float min, float max, float step, char const *name, unsigned long id) {
      if (!name) return;
      ++cnt_;
      if (cnt_-1 == toMake_) {
        set_ = new FloatSetting(id, f, name, min, max, step);
      }
    }
    void operator()(const ColorRGBA &c, unsigned short version, char const *name, unsigned long id) {
      if (!name) return;
      ++cnt_;
      if (cnt_-1 == toMake_) {
        set_ = new ColorSetting(id, c, name, name);
      }
    }
};

//  Use NavmeshControlGetter to apply data from a control to the appropriate member.
//  Note that each member will be visited for only applying one specific control, 
//  but that's OK because visiting is really fast. You'd need thousands of controls 
//  to even be able to measure any n-squared effect.
//  This could be used for any controller, really.
class NavmeshControlGetter {
  public:
    NavmeshControlGetter(unsigned long toGet, const Setting *set)
      : toGet_(toGet)
      , set_(set)
    {
    }
    unsigned long toGet_;
    const Setting *set_;
    void operator()(unsigned short &s, unsigned short version, unsigned short min, unsigned short max, char const *name, unsigned long id) {
      if (!name) return;
      if (id == toGet_) {
        s = (unsigned short)static_cast<const IntegerSetting *>(set_)->GetIntegerValue();
        if (s < min) s = min;
        if (s > max) s = max;
      }
    }
    void operator()(float &f, unsigned short version, float min, float max, float step, char const *name, unsigned long id) {
      if (!name) return;
      if (id == toGet_) {
        f = static_cast<const FloatSetting *>(set_)->GetFloatValue();
        if (f < min) f = min;
        if (f > max) f = max;
      }
    }
    void operator()(ColorRGBA &c, unsigned short version, char const *name, unsigned long id) {
      if (!name) return;
      if (id == toGet_) {
        c = static_cast<const ColorSetting *>(set_)->GetColor();
      }
    }
};



//  Actual implementation
NavmeshController::NavmeshController()
  : Controller(kNavmeshControllerType)
  , radius_(10.0f)
  , verticalDistance_(4.0f)
  , hJump_(0.5f)
  , vJump_(0.5f)
  , vFall_(4.0f)
  , meshColor_(1, 1, 1, 1)
  , showingGeometry_(false)
  , lines_(kRenderIndexedLines, PiStateRender::DepthTest)
  , lineVertices_(0)
  , lineColors_(0)
  , lineIndices_(0)
  , version_(CUR_VERSION)
  , meshCleanup_(2)
{
  allNavMeshes_.Append(this);
	TheEngine->AddCommand(&navmeshCommand_);
}

NavmeshController::~NavmeshController() {
  delete[] lineVertices_;
  delete[] lineColors_;
  delete[] lineIndices_;
}

Controller *NavmeshController::Replicate() const {
  return new NavmeshController();
}

unsigned long NavmeshController::GetPackSize(unsigned long packFlags) const {
  NavmeshSizeVisitor nsv;
  //  Use the convenient visitor function
  NavmeshVisit(*this, nsv);
  return nsv.size_;
}

void NavmeshController::Pack(Packer& data, unsigned long packFlags) const {
  NavmeshSaveVisitor nsv(data, packFlags);
  //  Use the convenient visitor function
  NavmeshVisit(*this, nsv);
}

void NavmeshController::Unpack(Unpacker& data, unsigned long unpackFlags) {
  NavmeshLoadVisitor nlv(*this, data, unpackFlags);
  //  Use the convenient visitor function
  NavmeshVisit(*this, nlv);
  version_ = CUR_VERSION;
}

long NavmeshController::GetSettingCount() const {
  NavmeshControlMaker ncm(-1);
  //  Use the convenient visitor function
  NavmeshVisit(*this, ncm);
  return ncm.cnt_;
}

Setting *NavmeshController::GetSetting(long index) const {
  NavmeshControlMaker ncm(index);
  //  Use the convenient visitor function
  NavmeshVisit(*this, ncm);
  return ncm.set_;
}

void NavmeshController::SetSetting(const Setting *setting) {
  NavmeshControlGetter ncg(setting->GetSettingIdentifier(), setting);
  //  Use the convenient visitor function
  NavmeshVisit(*this, ncg);
}

void NavmeshController::Preprocess() {
  Controller::Preprocess();
  //  Preprocess is called when the controller first starts up after being 
  //  unpacked from file. Build the navigation mesh data. I do it at start-
  //  up instead of as a pre-process to avoid the possibility of a stale 
  //  connectivity mesh. If this takes too much time, it can be saved to 
  //  the file, and you'd have to "navmesh build" in the editor to regenerate 
  //  new data.
  Rebuild();
}

//  Build the connectivity data between locators.
void NavmeshController::Rebuild() {
  //  First, turn off any debug visualization. Remember whether it was on for later.
  bool doShow = false;
  if (showingGeometry_) {
    HideGeometry();
    doShow = true;
  }

  //  Reset all connectivity information.
  markers_.SetElementCount(0);
  neighborIndices_.SetElementCount(0);
  neighborArray_.SetElementCount(0);

  //  Walk all children, looking for "navi" locators.
  Node *node = GetTargetNode();
  long snc = node->GetSubnodeCount();
  for (Node *cld = node->GetFirstSubnode(); cld; cld = cld->Next()) {
    if (cld->GetNodeType() == kNodeMarker) {
      Marker *mrk = static_cast<Marker *>(cld);
      if (mrk->GetMarkerType() == kMarkerLocator) {
        //  this is a point to consider
        markers_.AddElement(mrk);
        //  Make sure this node has a NavpointController controller where I can 
        //  store information about the node. Anything "navi" is owned by me, not 
        //  the user!
        if (mrk->GetController() != 0 && mrk->GetController()->GetControllerType() != kNavpointControllerType) {
          delete mrk->GetController();
        }
        if (!mrk->GetController()) {
          mrk->SetController(new NavpointController(this, markers_.GetElementCount()-1));
        }
      }
      else {
        //  Let the user know -- this is probably a mistake
        String<200> str("Locator child of navmesh is not a 'navi' locator: ");
        ((str += mrk->GetNodeName()) += " at position ") += mrk->GetWorldPosition();
        Engine::Report(str, kReportNoSpace);
      }
    }
  }

  //  For each navpoint, iterate nodes within a sphere, and check them for my own navpoints.
  for (curEnumNode_ = 0; curEnumNode_ < markers_.GetElementCount(); ++curEnumNode_) {
    //  Any neighbors will start at this point in the neighborArray_, so 
    //  remember that (one entry per marker) in the neighborIndices_ array.
    neighborIndices_.AddElement(neighborArray_.GetElementCount());
    Point3D center = markers_[curEnumNode_]->GetWorldPosition();
    long neighborBase = neighborArray_.GetElementCount();
    //  Walk all known markers, finding potential neighbors within the 
    //  indicated radius.
    for (long i = 0; i < markers_.GetElementCount(); ++i) {
      //  Don't allow node as its own neighbor.
      if (i == curEnumNode_) continue;
      Marker *tMarker = markers_[i];
      Vector3D vec(tMarker->GetWorldPosition() - center);
      //  todo: could turn these divisions into reciprocal mults
      vec.x /= radius_;
      vec.y /= radius_;
      vec.z /= verticalDistance_;
      //  Test the spheroid here.
      //  Theory is that a vector within the spheroid will be 
      //  within the unit sphere after the division above.
      if (SquaredMag(vec) < 1) {
        AddPotentialNeighbor(center, tMarker);
      }
    }
    //  Now, I may have too many neighbors, depending on radius.
    //  Figure out which neighbors are "the best" in some sense. That sense being 
    //  that a node is removed if it is filtered out by planes facing the source 
    //  through other nodes, for at least two other nodes.
    long neighborTop = neighborArray_.GetElementCount();
    //  Note that this is order dependent. However, I believe it's 
    //  good enough.
    for (long i = neighborBase; i < neighborTop; ++i) {
      long numBlocking = 0;
      Vector3D iCenter = neighborArray_[i].mrk_->GetWorldPosition();
      for (long j = neighborBase; j < neighborTop; ++j) {
        if (i == j) continue;
        if (neighborArray_[j].mrk_ == 0) continue;
        //  construct plane from source to j
        Vector3D jCenter = neighborArray_[j].mrk_->GetWorldPosition();
        Vector3D normal = (center - jCenter).Normalize();
        //  check if plane culls out i
        if (iCenter * normal < jCenter * normal) {
          ++numBlocking;
          if (numBlocking == meshCleanup_) {
            neighborArray_[i].mrk_ = 0;
            break;
          }
        }
      }
      //  figure out whether there's some impassable step in the way
      if (neighborArray_[i].mrk_ && TooSteepGround(markers_[curEnumNode_]->GetWorldPosition(), 
          neighborArray_[i].mrk_->GetWorldPosition())) {
        neighborArray_[i].mrk_ = 0;
      }
    }
    //  Now, compact neighbor array to not contain null pointers
    for (long i = neighborBase; i < neighborTop;) {
      if (!neighborArray_[i].mrk_) {
        neighborArray_[i] = neighborArray_[neighborTop-1];
        --neighborTop;
      }
      else {
        ++i;
      }
    }
    neighborArray_.SetElementCount(neighborTop);
  }
  //  terminate the array
  neighborIndices_.AddElement(neighborArray_.GetElementCount());

  if (doShow) {
    ShowGeometry();
  }
}

void NavmeshController::Move() {
  //  do nothing here
}

bool NavmeshController::ValidNode(const Node *node) {
  // navmesh controller only goes on group nodes
  return node->GetNodeType() == kNodeGroup;
}

//  Cast a ray from point A to point B, and return the time of intersection 
//  as a parameter between 0 and 1. Return 1 if there is no intersection. 
//  todo: this should probably cast a thick ray, to make sure an entity can 
//  actually pass through the space.
float NavmeshController::CastRay(Point3D const &a, Point3D const &b) {
  CollisionData collData;
  memset(&collData, 0, sizeof(collData));
  GetTargetNode()->GetWorld()->DetectCollision(a, b, 0, 0, &collData);
  return collData.param;
}

//  When a node is within the defined spheroid of another (radius, vertical size), 
//  it gets passed here as a potential neighbor. Do some more testing to make sure 
//  that it's possible to walk from currently considered node to neighbor.
void NavmeshController::AddPotentialNeighbor(Point3D const &center, Node *node) {
  assert(node->GetNodeType() == kNodeMarker);
  //  Don't pay attention to nodes that I don't understand.
  if (node->GetController() != 0 && node->GetController()->GetControllerType() == kNavpointControllerType) {
    NavpointController *npc = static_cast<NavpointController *>(node->GetController());
    if (npc->navmesh_ == this && npc->navmeshIndex_ != curEnumNode_) {
      //  test whether the target is excluded or included, by looking at connector names
      Connector *conn = node->GetFirstConnector();
      bool forceLink = false;
      while (conn) {
        //  if it starts or ends with a minus, make the target node ineligible
        if (((conn->GetConnectorKey() >> 24) == '-')
            || ((conn->GetConnectorKey() & 0xff) == '-')) {
          if (conn->GetTarget() == markers_[curEnumNode_]) {
            return;
          }
        }
        //  if it starts or ends with a plus, make sure it's always linked up
        if (((conn->GetConnectorKey() >> 24) == '+')
            || ((conn->GetConnectorKey() & 0xff) == '+')) {
          if (conn->GetTarget() == markers_[curEnumNode_]) {
            forceLink = true;
          }
        }
        conn = conn->ListElement<Connector>::Next();
      }
      //  Run a raycast and perhaps add the node as a neighbor.
      //  Note that I run the tests twice, to add the reciprocal connection.
      //  That allows me to build the list of neighbors as a linear array, as 
      //  there are no inserts in the middle.
      float param = 0;
      if (!forceLink) {
        param = CastRay(center, node->GetWorldPosition());
      }
      if (forceLink || (param >= 1.0f)) {
        neighborArray_.AddElement(NeighborInfo(
            static_cast<NavpointController *>(node->GetController())->navmeshIndex_,
            static_cast<Marker *>(node)));
      }
      else {
        //  oops, can't get there from here!
      }
    }
  }
}

//  The user typed "navmesh something" into the console.
void NavmeshController::NavmeshCommand(char const *text) {
  String<kMaxCommandLength>	output;

  if (TheWorldMgr->GetWorld() == 0) {
    Engine::Report("No world is loaded.", kReportNoSpace | kReportError);
    return;
  }

  if (!allNavMeshes_.GetElementCount()) {
    Engine::Report("Could not find navmesh controller.", kReportNoSpace | kReportError);
    return;
  }

  //  if there is some text, check which command it is
  if (text && text[0]) {
    int matched = 0;
    if (!strncmp(text, "build", 5)) {
      //  call rebuild on matching navmeshes to re-do the connectivity
      text += 5;
      while (*text && isspace(*text)) ++text;
      for (NavmeshController *navmesh = allNavMeshes_.First(); navmesh; 
          navmesh = navmesh->ListElement<NavmeshController>::Next()) {
        if (navmesh->GetTargetNode() && strstr(navmesh->GetTargetNode()->GetNodeName(), text)) {
          navmesh->Rebuild();
          ++matched;
        }
      }
    }
    else if (!strncmp(text, "show", 4)) {
      //  call show on matching navmeshes to show the mesh geometry
      text += 4;
      while (*text && isspace(*text)) ++text;
      for (NavmeshController *navmesh = allNavMeshes_.First(); navmesh; 
          navmesh = navmesh->ListElement<NavmeshController>::Next()) {
        if (navmesh->GetTargetNode() && strstr(navmesh->GetTargetNode()->GetNodeName(), text)) {
          navmesh->ShowGeometry();
          ++matched;
        }
      }
    }
    else if (!strncmp(text, "hide", 4)) {
      //  call hide on matching navmeshes to stop drawing the mesh geometry
      text += 4;
      while (*text && isspace(*text)) ++text;
      for (NavmeshController *navmesh = allNavMeshes_.First(); navmesh; 
          navmesh = navmesh->ListElement<NavmeshController>::Next()) {
        if (navmesh->GetTargetNode() && strstr(navmesh->GetTargetNode()->GetNodeName(), text)) {
          navmesh->HideGeometry();
          ++matched;
        }
      }
    }
    else if (!strncmp(text, "path", 4)) {
      //  do various path finding operations
      text += 4;
      Point3D start, stop;
      NavmeshPath *wp = 0;
      while (*text && isspace(*text)) ++text;
      if (!strncmp(text, "clear", 5)) {
        //  navmesh path clear to remove all rendered paths
        for (long n = NavRenderable::all_.GetElementCount(); n > 0; --n) {
          delete NavRenderable::all_[n-1];
        }
      }
      else if (!GetPoint3D(text, &start) || !GetPoint3D(text, &stop)) {
        //  else navmesh path x,y,z x,y,z for start->end
        //  if not, then tell the user what to do
        goto usage;
      }
      else {
        while (*text && isspace(*text)) ++text;
        //  Do a pathfind on the first mesh that matches the given name
        //  (which may be empty, meaning first mesh).
        for (NavmeshController *navmesh = allNavMeshes_.First(); navmesh; 
            navmesh = navmesh->ListElement<NavmeshController>::Next()) {
          if (navmesh->GetTargetNode() && strstr(navmesh->GetTargetNode()->GetNodeName(), text)) {
            //  Actually do pathfinding.
            wp = navmesh->NavmeshPathCreate(start, stop);
            //  Tell the user if it didn't work.
            if (!wp) {
              ((((output = "No path found from ") += start) += " to ") += stop) += ".";
              Engine::Report(output, kReportError | kReportNoSpace);
            }
            else {
              //  Create a new renderable to hold the line list
              NavRenderable *nr = new NavRenderable();
              int n = 0;
              Point3D pos = start;
              nr->AddVertex(pos);
              Vector3D dir;
              //  Step through the returned path, extracting positions 
              //  as I go.
              while (wp->Move(pos, &dir)) {
                pos += dir * 0.125f;
                nr->AddVertex(pos);
              }
              //  Make sure the vertices render.
              nr->Commit();
              wp->Dispose();
            }
            ++matched;
            break;
          }
        }
      }
    }
    else {
usage:
      Engine::Report("Usage: navmesh [build|show|hide|path [matchname]]", kReportNoSpace | kReportError);
      Engine::Report("path takes 'clear' or '{begin} {end}' X,Y,Z triplets.", kReportNoSpace);
      matched = -1;
    }
    if (!matched) {
      ((output = "No navmesh matching '") += text ) += "' found.";
      Engine::Report(output, kReportNoSpace | kReportError);
    }
  }
  else {
    //  if just plain "navmesh," do a status report on each navmesh
    for (NavmeshController *navmesh = allNavMeshes_.First(); navmesh; 
        navmesh = navmesh->ListElement<NavmeshController>::Next()) {
      if (!navmesh->GetTargetNode()) {
        Engine::Report("Navmesh controller found with no target node.\n",
            kReportError | kReportNoSpace);
        continue;
      }
      output = navmesh->GetTargetNode()->GetNodeName();
      Engine::Report(output, kReportNoSpace | kReportHeading);
      output = "    Show Mesh: ";
      output += navmesh->ShowingGeometry() ? "ON" : "OFF";
      Engine::Report(output, kReportNoSpace);
      output = "    Number Nodes: ";
      output += navmesh->GetMarkerCount();
      Engine::Report(output, kReportNoSpace);
    }
  }
}

//  ShowGeometry builds a line list to represent the connectivity.
//  Lines start bright, and end up black at the destination. They 
//  also start above, and end up below the destination, to make it 
//  easy to tell directivity apart.
void NavmeshController::ShowGeometry() {
  //  Re-build the list if already showing.
  if (showingGeometry_) {
    HideGeometry();
  }
  showingGeometry_ = true;

  //  Set up the renderable with how many line vertices and indices I'll need.
  long nMarkers = markers_.GetElementCount();
  lines_.SetVertexCount(markers_.GetElementCount()*2);
  lineVertices_ = new Point3D[nMarkers*2];
  lineColors_ = new ColorRGBA[nMarkers*2];
	lines_.SetFaceCount(neighborArray_.GetElementCount());
  lineIndices_ = new unsigned short[2 * neighborArray_.GetElementCount()];

  //  Add one vertex per node. Well, two, to separate start and 
  //  end position/color.
  for (long v = 0; v < nMarkers; ++v) {
    lineVertices_[v] = markers_[v]->GetWorldPosition() + Vector3D(0, 0, 0.05f);
    lineVertices_[v+nMarkers] = lineVertices_[v] + Vector3D(0, 0, -0.1f);
    lineColors_[v] = meshColor_;
    lineColors_[v+nMarkers] = ColorRGBA(0, 0, 0, 1);
  }

  //  Add one line per neighbor per node.
  long cur = 0;
  for (long t = 1; t < neighborIndices_.GetElementCount(); ++t) {
    long num = neighborIndices_[t] - neighborIndices_[t-1];
    for (long n = 0; n < num; ++n) {
      assert(cur < 2 * neighborArray_.GetElementCount());
      lineIndices_[cur] = (unsigned short)(t-1);
      lineIndices_[cur+1] = (unsigned short)static_cast<NavpointController *>(
          neighborArray_[cur>>1].mrk_->GetController())->navmeshIndex_ + nMarkers;
      cur += 2;
    }
  }

  //  Tell the renderable what to render.
	lines_.SetAttributeArray(kArrayVertex, lineVertices_);
	lines_.SetAttributeArray(kArrayColor0, lineColors_);
	lines_.SetFaceArray(lineIndices_);
}

//  undo the damage from ShowGeometry().
void NavmeshController::HideGeometry() {
  if (showingGeometry_) {
    showingGeometry_ = false;
    delete[] lineVertices_;
    lineVertices_ = 0;
    delete[] lineColors_;
    lineColors_ = 0;
    delete[] lineIndices_;
    lineIndices_ = 0;
  }
}

//  Test whether it's possible to walk from point a to point b 
//  without falling off a cliff, or reaching an impassable stairstep.
//  This function uses parameters set in the controller edit panel quite 
//  heavily, and is the most tweakable part of the implementation.
bool NavmeshController::TooSteepGround(Point3D const &a, Point3D const &bPos)
{
  Point3D aPos(a);
  //  March along the ray with distance hJump_.
  Vector3D dir = bPos - aPos;
  int n = Magnitude(dir) / hJump_;
  dir.Normalize();
  float v = GetPosHeight(aPos);
  while (n > 0) {
    aPos += dir * hJump_;
    //  If any one distance in height is greater than vJump_, return TRUE
    float v2 = GetPosHeight(aPos);
    if (v2 < v - vJump_) {
      return true;
    }
    if (v2 > v + vFall_) {
      return true;
    }
    v = v2;
    --n;
  }
  return false;
}

//  Find the height above ground of a given point.
//  Don't find ground if it's further away than twice the allowable fall height, 
//  as an optimization (avoiding long ray casts).
float NavmeshController::GetPosHeight(Point3D const &pos) {
  CollisionData collData;
  memset(&collData, 0, sizeof(collData));
  //  There could be a cliff of more than 10 meters drop -- I'll assume that's 
  //  just a 10 meter drop, and make up the difference later.
  GetTargetNode()->GetWorld()->DetectCollision(pos, pos + Vector3D(0, 0, -2*vFall_), 
      0, 0, &collData);
  return collData.param * 2 * vFall_;
}

//  WalkPath is returned to clients to implement the NavmeshPath interface.
class WalkPath : public NavmeshPath {
  public:
    WalkPath(NavmeshController *c)
      : ctl_(c)
      , walkDirection_(0, 0, 0)
      , refPosHeight_(0) {
    }
    void Dispose() { delete this; }
    bool Move(Point3D const &p, Vector3D *oDir)
    {
      //  First, tell the user to walk in "some" direction, in case 
      //  I take an early out.
      *oDir = walkDirection_;
      if (!walkItems_.GetElementCount()) {
        //  This path is all done walking.
        return false;
      }
      //  Where am I walking to right now, and am I there?
      Point3D &targ = walkItems_[0];
      float h = ctl_->GetPosHeight(p);
      Point3D src(p.x, p.y, p.z-h+refPosHeight_);
      if (fabs(src.z - targ.z) < 0.5f) { // don't allow being above or below by a lot
        //  If I have walked past the target position, as measured by a 
        //  dot product, then I'm "there". This makes sure all points are 
        //  reached fully.
        if (src * walkDirection_ >= targ * walkDirection_) {
          if (SquaredMag(targ-src) < ctl_->hJump_ * ctl_->hJump_) {
            //  I am actually close enough. Great! Let's move to the next spot.
            walkItems_.RemoveElement(0);
            if (walkItems_.GetElementCount() == 0) {
              //  I'm there!
              return false;
            }
            refPosHeight_ = ctl_->GetPosHeight(walkItems_[0]);
          }
        }
      }
      //  Again, tell the user where to walk.
      walkDirection_ = (targ-src).Normalize();
      *oDir = walkDirection_;
      return true;
    }

    NavmeshController *ctl_;
    Array<Point3D> walkItems_;
    Vector3D walkDirection_;
    float refPosHeight_;
};

//  Return the index within a navmesh of a given locator node.
//  This function could probably be optimized out with better data layout.
static long MarkerIndex(Marker *m) {
  assert(m->GetMarkerType() == kMarkerLocator);
  assert(static_cast<LocatorMarker *>(m)->GetLocatorType() == kLocatorNavpointType);
  return static_cast<NavpointController *>(m->GetController())->navmeshIndex_;
}

//  Among all markers within reach of "begin," find the one closest to 
//  the "end" point. Within reach is defined as walkable from begin to 
//  the marker if forward is true, else walkable from marker to begin.
Marker *NavmeshController::FindClosestMarkerTo(Point3D const &begin, Point3D const &end, bool forward) {
  //  find node within radius that:
  //  1) is walkable to
  //  2) is closest towards target
  //  If no such node, try 2*radius. If still none, give up.
  Marker *mark = 0;
  for (int r = 1; r < 3; ++r) {
    float r2 = radius_ * radius_ * r * r;
    float d2 = 1e20f;
    for (long n = markers_.GetElementCount(), i = 0; i != n; ++i) {
      Point3D markerPos(markers_[i]->GetWorldPosition());
      float cr = SquaredMag(markerPos - begin);
      if (cr <= r2) {
        float cd = SquaredMag(markerPos - end);
        if (!mark || cd < d2) {
          //  test walkability, either to marker, or from marker, based on 'forward'
          if (!TooSteepGround(forward ? begin : markerPos, forward ? markerPos : begin)) {
            mark = markers_[i];
            d2 = cd;
          }
        }
      }
    }
    if (mark) {
      break;
    }
  }
  return mark;
}

bool NavmeshController::AStarSearchIntoWalkPath(Marker *begin, Marker *end, WalkPath *wp) {

  //  Define a potential path member, as a place to keep running 
  //  cost and the actual path taken. It also caches values that 
  //  would be slightly more expensive to look up. Ideally, the 
  //  list of Potentials should be the same as the list of markers 
  //  and the list of neighbors should point to these -- I'll get 
  //  around to that optimization once this function becomes the 
  //  bottleneck (which it might very well do for large levels).
  class Potential : public ListElement<Potential> {
    public:
      Potential(Marker *node, long ix)
        : marker_(node), pos_(node->GetWorldPosition()), ix_(ix), estCost_(0), costToReach_(0), from_(0), visited_(false)
      {
      }
      Marker *marker_;
      Point3D pos_;
      long ix_;
      float estCost_;
      float costToReach_;
      Potential *from_;
      bool visited_;
  };

  List<Potential> openList;
  Array<Potential *> nodeArray;

  //  Make sure our "Potential" array gets deleted when the function exits.
  class Del {
    public:
      Del(Array<Potential *> &pt) : pt_(pt) {}
      Array<Potential *> &pt_;
      ~Del() {
        long n = pt_.GetElementCount();
        for (long i = 0; i != n; ++i) {
          delete pt_[i];
        }
      }
  };
  Del del(nodeArray);

  //  set up needed data structures
  long nMarkers = markers_.GetElementCount();
  long nVisited = 1;
  nodeArray.SetElementCount(nMarkers);    //  todo: this array could be optimized as a retained member
  for (long i = 0; i < nMarkers; ++i) {
    nodeArray[i] = new Potential(markers_[i], i);
  }
  float currentCost = 0;
  Point3D endPos = end->GetWorldPosition();
  
  //  Initialize the search by seeding the open list with the start.
  //  For the current node, figure out where I can get to, at what estimated final cost.
  //  Insert into the priority queue (sorted on estimated final cost). The heuristic I 
  //  use is simple Euler distance (vector length), which is an admissible A-star 
  //  heuristic.
  Potential *p = nodeArray[MarkerIndex(begin)];
  p->costToReach_ = 0;
  p->estCost_ = Magnitude(endPos - p->pos_);
  p->from_ = 0;
  p->visited_ = true;
  openList.Append(p);

  while (openList.GetElementCount()) {
    openList.Remove(p = openList.First());
    //  If I find the end, I'm done! Note that if the actual cost of the 
    //  edges was significantly higher than the heuristic, I would actually 
    //  have to keep searching a little bit further (until the real cost of 
    //  the current node is smaller than the heuristic cost of the next node 
    //  in the open list) if I wanted the optimal solution for the last step, 
    //  but that's not a problem here. -- jwatte 2007-08-23
    if (p->marker_ == end) {
      break;
    }
    long base = neighborIndices_[p->ix_];
    long end = neighborIndices_[p->ix_ + 1];
    while (base < end) {
      Potential *n = nodeArray[MarkerIndex(neighborArray_[base].mrk_)];
      float ctr = Magnitude(n->pos_ - p->pos_) + p->costToReach_;
      if (!n->visited_ || ctr < n->costToReach_) {
        n->costToReach_ = ctr;
        n->estCost_ = ctr + Magnitude(endPos - n->pos_);
        n->from_ = p;
        //  insert n into openList based on cost (list is treated as a priority queue)
        Potential *c = openList.First();
        while (c && c->estCost_ <= n->estCost_) {
          c = c->Next();
        }
        //  InsertBefore(n, nullptr) will crash, unfortunately
        if (c) {
          openList.InsertBefore(n, c);
        }
        else {
          openList.Append(n);
        }
        n->visited_ = true;
      }
      ++base;
    }
    p = 0;
  }

  if (!p) {
    //  can't get there from here
    return false;
  }

  //  unwind the solution, which is currently stored in reverse order
  Potential *q = p;
  long cnt = 0;
  while (q) { //  count the number of items needed
    ++cnt;
    q = q->from_;
  }
  long base = wp->walkItems_.GetElementCount();
  wp->walkItems_.SetElementCount(base+cnt);
  q = p;
  while (cnt) { //  walk through again and fill the array
    --cnt;
    wp->walkItems_[base+cnt] = q->pos_;
    q = q->from_;
  }

  //  Whew! I'm done!
  return true;
}

NavmeshPath *NavmeshController::NavmeshPathCreate(Point3D const &begin, Point3D const &end) {
  String<200> output;
  WalkPath *wp = new WalkPath(this);

  //  test how far we have to go
  float mag2 = SquaredMag(end - begin);
  if (mag2 < 0.01f) {
    //  If I'm already at the destination, don't bother doing anything else
    return wp;
  }

  //  test if it might be faster to just walk from here to there
  if (mag2 <= radius_*radius_*4) {
    //  If I may be able to walk in a straight line, don't use the nav mesh
    if ((1.0f <= CastRay(begin, end)) && !TooSteepGround(begin, end)) {
      wp->walkItems_.AddElement(end);
    }
  }

  //  if I didn't find a solution, I need to use the nav mesh
  if (wp->walkItems_.GetElementCount() == 0) {

    //  Find my way onto the nav mesh from the source
    Marker *markBegin = FindClosestMarkerTo(begin, end, true);
    //  Find my way from the navmesh to the destination
    Marker *markEnd = FindClosestMarkerTo(end, begin, false);
    Point3D beginPos;

    if (!markBegin) {
      output = "No path beginning found in navmesh ";
      (((((output += Name()) += " from ") += begin) += " to ") += end) += ".";
      goto error;
    }

    if (!markEnd) {
      output = "No path end found in navmesh ";
      (((((output += Name()) += " from ") += begin) += " to ") += end) += ".";
      goto error;
    }

    //  Don't walk to beginning if it's close enough to the start already
    beginPos = markBegin->GetWorldPosition();
    if (SquaredMag(beginPos - begin) > 0.01f) {
      wp->walkItems_.AddElement(beginPos);
    }

    //  plan through the node network (A-star)
    if (!AStarSearchIntoWalkPath(markBegin, markEnd, wp)) {
      output = "You can't get there from here in navmesh ";
      (((((output += Name()) += " from ") += begin) += " to ") += end) += ".";
      goto error;
    }

    //  plan from the final network node to destination -- I know, if there 
    //  are no elements, that end is at least some bit away from start
    long ec = wp->walkItems_.GetElementCount();
    if (ec == 0 || SquaredMag(wp->walkItems_[ec-1] - end) > 0.01f) {
      wp->walkItems_.AddElement(end);
    }
  }

  //  now refine the solution so that no stupid back-and-forth happens in the 
  //  beginning or end
  while (wp->walkItems_.GetElementCount() > 1) {
    Point3D wp1(wp->walkItems_[1]);
    //  Don't search further than twice radius, to avoid 
    //  too many ray casts.
    if (SquaredMag(begin - wp1) > radius_*radius_*4) {
      break;
    }
    //  Chop nodes off the beginning if it's possible to walk from the start 
    //  to the second node in the list.
    if ((1.0f <= CastRay(begin, wp1)) && !TooSteepGround(begin, wp1)) {
      wp->walkItems_.RemoveElement(0);
    }
    else {
      break;
    }
  }
  long n;
  while ((n = wp->walkItems_.GetElementCount()) > 2) {
    Point3D wp3 = wp->walkItems_[n-3];
    //  Don't search further than twice radius, to avoid 
    //  too many ray casts.
    if (SquaredMag(wp3 - end) > radius_*radius_*4) {
      break;
    }
    //  Chop nodes off the end (last item) if it's possible to walk straight 
    //  from the third-to-last node, thus removing the second-to-last node.
    if ((1.0f <= CastRay(wp3, end)) && !TooSteepGround(wp3, end)) {
      wp->walkItems_.RemoveElement(n-2);
    }
    else {
      break;
    }
  }
  assert(wp->walkItems_.GetElementCount() > 0);
  assert(wp->walkItems_[n-1] == end);

  //  make it know where to go first -- I know I have at least one position in the list
  wp->walkDirection_ = (wp->walkItems_[0] - begin).Normalize();
  wp->refPosHeight_ = GetPosHeight(begin);

  return wp;

error:
  Engine::Report(output, kReportError);
  delete wp;
  return 0;
}

long NavmeshController::GetNodeNeighbor(long node, long index) {
  assert(index < CountNodeNeighbors(node));
  return static_cast<NavpointController *>(neighborArray_[neighborIndices_[node] + index].mrk_
      ->GetController())->navmeshIndex_;
}



//  Render any debug visualization I might have going on.
void MaybeRenderNavmeshes() {
  //  Need a renderlist to submit geometry.
  List<Renderable> renderList;

  //  For each navmesh controller, check whether it wants something rendered.
  //  I do not add it to the scene graph itself (I initially did this) because 
  //  C4 currently does poorly with things that are bigger than a single zone.
  for (NavmeshController *navmesh = NavmeshController::allNavMeshes_.First(); navmesh; 
      navmesh = navmesh->ListElement<NavmeshController>::Next()) {
    if (navmesh->showingGeometry_) {
      renderList.Append(&navmesh->lines_);
    }
  }

  //  Render any NavRenderables I have registered.
  for (long n = NavRenderable::all_.GetElementCount(), i = 0; i != n; ++i) {
    renderList.Append(NavRenderable::all_[i]);
  }

  //  Actually issue the geometry I've collected.
  TheGraphicsMgr->DrawRenderList(&renderList);

  //  The default for a list destructor is to delete all members. That's not what I want.
  renderList.RemoveAll();
}

//  Search through all navmeshes, returning the first one that matches 
//  the indicated name (as a substring).
NavmeshInterface *GetNavmeshController(char const *name) {
  for (NavmeshController *navmesh = NavmeshController::allNavMeshes_.First(); navmesh;
      navmesh = navmesh->ListElement<NavmeshController>::Next()) {
    if (!name || strstr(navmesh->Name(), name)) {
      return navmesh;
    }
  }
  return 0;
}

//  Make sure the World Editor can instantiate these controllers.
ControllerReg<NavmeshController> navmeshControllerReg(kNavmeshControllerType, "Navmesh");

