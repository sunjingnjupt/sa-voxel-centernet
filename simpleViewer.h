#include <QGLViewer/qglviewer.h>
#include <fstream>
#include <iostream>
#include "utils.h"
#include "View.h"
#include <assert.h>
#include "object.h"

class Node{
public:
    Node* parent = nullptr;
    // been visted, 0 not visted, -1 has visted, 1 has visted condition 2, loop condition??
    int visted = 0;
    // true has find center node, false not find center node
    bool is_root_center = false;
    int rank = 0;  // center has hight rank, first rank is zeros
    int row = 0;
    int col = 0;
    int seg_id = -1;
};

class Segment
{
public:
    Segment() {};
    Segment(int input_seg_id):seg_id(input_seg_id) {}
    int seg_id = -1;
};

typedef std::vector<std::vector<Node>> imgNode;
typedef std::vector<std::vector<Node*>> imgNodePtr;
typedef std::vector<std::vector<bool>> imgBool;
class Viewer : public QGLViewer {
protected:
    virtual void draw();
    virtual void init();
    void find_all_node();
    void find_all_node2();
    void find_all_node_parent_record(Node* x, std::vector<Node*>& path);
    void draw2();
    void drawCircle(const float & radius, const int & numPoints) const;

public:
    std::vector<Object::Ptr> objects;

private:
    std::string binFileName_ = "../binFile/47.bin";
    // std::string binFileName_ = "./binFile/8.bin";
    std::vector<utils::data> offsets_;
    View view_;

// cluster center relative
private:
//    size_t rows_ = 512U;
//    size_t cols_ = 512U;
    size_t rows_ = 256U;
    size_t cols_ = 256U;
    imgNode nodes_ = imgNode(rows_, std::vector<Node>(cols_, Node()));
    imgInt gridVotes_ = imgInt(view_.rows(), std::vector<int>(view_.cols(), 0));
    std::vector<Segment> segments_;
    float confidence_min_threshold_ = 0.3f;
    float blocking_threshold_ = 0.3f;
    imgBool grid_sklip_;

private:
    void PrintOffsets();
};
