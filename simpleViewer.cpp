#include "simpleViewer.h"

using namespace std;
// Draws a spiral

void Viewer::draw2() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    qglColor(Qt::black);
    glPushMatrix();
    fprintf(stderr, "[INFO] show ing.....\n");
    utils::data* tmpData = offsets_.data();
    // draw origin points
    glPointSize(2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    tmpData = offsets_.data();
    for (int idx = 0; idx < offsets_.size(); ++idx) {
        float cls = tmpData->cls;
        glVertex3f(tmpData->x, tmpData->y, tmpData->z);
        tmpData += 1;
    }
    glEnd();
    glPopMatrix();

    glPointSize(1.0f);
    float x, y, z;
    glBegin(GL_LINES);
    tmpData = offsets_.data();
    glColor3f(0.835f, 0.031f, 0.043f); // 浅红色
    for (int idx = 0; idx < offsets_.size(); ++idx) {
        x = tmpData->x - tmpData->reg[0];
        y = tmpData->y - tmpData->reg[1];
        z = tmpData->z - tmpData->reg[2];
        float cls = tmpData->cls;
        if (cls > 0.3f) {
            glVertex3f(tmpData->x, tmpData->y, tmpData->z);
            glVertex3f(x, y, z);
        }
        tmpData += 1;
    }
    glEnd();

    // draw center points
    glPointSize(1.2f);
    glColor3f(0.0f, 1.0f, 0.0f); //
    glBegin(GL_POINTS);
    tmpData = offsets_.data();
    for (int idx = 0; idx < offsets_.size(); ++idx) {
        x = tmpData->x - tmpData->reg[0];
        y = tmpData->y - tmpData->reg[1];
        z = tmpData->z - tmpData->reg[2];
        float cls = tmpData->cls;
        if (cls > 0.3f) {
            glVertex3f(x, y, z);
        }
        tmpData += 1;
    }
    glEnd();
    // draw origin points
    glPointSize(3.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    tmpData = offsets_.data();
    for (int idx = 0; idx < offsets_.size(); ++idx) {
        float cls = tmpData->cls;
        if (cls > 0.3f) {
            glVertex3f(tmpData->x, tmpData->y, tmpData->z);
        }
        tmpData += 1;
    }
    glEnd();
    glPopMatrix();
    glFlush();
}

void Viewer::draw() {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    qglColor(Qt::black);
    glPushMatrix();
    fprintf(stderr, "[INFO] show ing.....\n");
    // show voxel point with prob_
    // draw origin points
    glPointSize(3.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    utils::data* tmpData = offsets_.data();
    for (int idx = 0; idx < offsets_.size(); ++idx) {
        float cls = tmpData->cls;
//        if (cls > 0.3f) {
            glVertex3f(tmpData->x, tmpData->y, 0.0);
//        }
        tmpData += 1;
    }
    glEnd();

    glPointSize(2.5f);
    glBegin(GL_POINTS);
    for (int row = 0; row < view_.rows(); ++row) {
        for (int col = 0; col < view_.cols(); ++col) {
            // int numVoxelPts = view_.Count(row, col);
            float prob = view_.GetProb(row, col);
            // if (numVoxelPts > 0) {
            if (prob > confidence_min_threshold_) {
                const float& prob = view_.GetProb(row, col);
                // glColor3f(prob, prob, prob);
                glColor3f(1.0f, 1.0f, 1.0f);
                utils::point2d center2d = view_.GetCenter(row, col);
                glVertex3f(center2d.x, center2d.y, 0.0f);
            }
        }
    }
    glEnd();
    // draw node
//    glBegin(GL_LINES);
//    for (int row = 0; row < rows_; ++row) {
//        for (int col = 0; col < cols_; ++col) {
//            Node* node = &nodes_[row][col];
////            if (view_.Count(node->row, node->col) == 0 ||
////                view_.GetProb(node->row, node->col) < confidence_min_threshold_) {
////                continue;
////            }
//            // Node* root_node = utils::FindRootNode(node);
//            Node* root_node = node->parent;
//            utils::point2d nodePt = view_.GetCenter(node->row, node->col);
//            utils::point2d rootNodePt = view_.GetCenter(root_node->row, root_node->col);
//            glColor3f(1.0f, 0.0f, 0.0f);
//            glVertex3f(nodePt.x, nodePt.y, 0.0f);
//            glColor3f(0.0f, 1.0f, 0.0f);
//            glVertex3f(rootNodePt.x, rootNodePt.y, 0.0f);
////            printf("[%d][%d] (%f, %f) ==> (%f, %f)\n",
////               node->row, node->col, nodePt.x, nodePt.y, rootNodePt.x, rootNodePt.y);
//        }
//    }
//    glEnd();

    // draw offset
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int row = 0; row < view_.rows(); ++row)
    {
        for (int col = 0; col < view_.cols(); ++col) {
            int numVoxelPts = view_.Count(row, col);
            if (numVoxelPts > 0) {
                const float& prob = view_.GetProb(row, col);
                if (prob > confidence_min_threshold_) {
                    utils::point2d center2d = view_.GetCenter(row, col);
                    glVertex3f(center2d.x, center2d.y, 0.0f);
                    utils::point2d offset2d = view_.GetOffset(row, col);
                    glVertex3f(offset2d.x, offset2d.y, 0.0f);
                }
            }
        }
    }
    glEnd();
    glPopMatrix();
    //  draw Segment center
    glPointSize(1.2f);
    glColor3f(0.0f, 1.0f, 0.0f);
    int count = 0;
    for (int row = 0; row < rows_; ++row){
        for (int col = 0; col < cols_; ++col) {
            Node* node = &nodes_[row][col];
            if (gridVotes_[node->row][node->col]) {
                glPushMatrix();
                utils::point2d seg_center = view_.GetCenter(row, col);
                glTranslatef(seg_center.x, seg_center.y, 0.0f);
                drawCircle(0.08, 12);
                glPopMatrix();
                ++count;
            }
        }
    }
    std::cout << "count: " << count << std::endl;
    // end of draw Segment
    glFlush();
}

void Viewer::drawCircle(const float & radius, const int & numPoints) const
{
    // glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
//    glBegin(GL_LINE_STRIP);
    // solid circle
     glBegin(GL_TRIANGLE_FAN);
    for (size_t idx = 0; idx < numPoints; ++idx)
    {
        glVertex3f(radius * cos(2 * M_PI / numPoints * idx), radius * sin(2 * M_PI / numPoints * idx), 0.0f);
    }
    glVertex3f(radius * cos(0), radius * sin(0), 0);
    glEnd();
}

void Viewer::init() {
    // Restore previous viewer state.
    glClear(GL_COLOR_BUFFER_BIT);
    setBackgroundColor(QColor(1, 0, 1));
    offsets_ = utils::ReadKittiBinByPath(binFileName_);
    // PrintOffsets();
    // 下面俩行， 一定要加， 不要会有阴影显示
    setSceneRadius(50);
    camera()->showEntireScene();
    objects.clear();
    view_.Build(offsets_);
    // restoreStateFromFile();
    find_all_node();
    find_all_node2();
}

void Viewer::find_all_node2()
{
    imgBool grid_skips(view_.rows(), std::vector<bool>(view_.cols(), true));
    // init whole nodes
    for (int row = 0; row < view_.rows(); ++row) {
        for (int col = 0; col < view_.cols(); ++col) {
            nodes_[row][col].parent = &nodes_[row][col];
            nodes_[row][col].row = row;
            nodes_[row][col].col = col;
        }
    }
    for (int row = 0; row < view_.rows(); ++row) {
        for (int col = 0; col < view_.cols(); ++col) {
            grid_skips[row][col] = view_.Count(row, col) == 0 ||
                                   view_.GetProb(row, col) < confidence_min_threshold_;
            // get offset position float
            utils::point2d center_estimate = view_.GetOffset(row, col);
            int center_row;
            int center_col;
            if (grid_skips[row][col]) {
                continue;
            }
            view_.Project(center_estimate, center_row, center_col);
            // let current node parent to be the offset parent
            nodes_[row][col].parent = &nodes_[center_row][center_col];

//            printf("node[%d][%d] ===> nodes_[%d][%d]\n",
//                   nodes_[row][col].row, nodes_[row][col].col,
//                   nodes_[center_row][center_col].row,
//                   nodes_[center_row][center_col].col);
        }
    }
    for (int row = 0; row < view_.rows(); ++row) {
        for (int col = 0; col < view_.cols(); ++col) {
            if (!grid_skips[row][col]) {
                auto root_node = nodes_[row][col].parent;
                ++gridVotes_[root_node->row][root_node->col];
            }
        }
    }
}

void Viewer::find_all_node()
{

}

void Viewer::find_all_node_parent_record(Node* x, std::vector<Node*>& path)
{

}

void Viewer::PrintOffsets()
{
    for (int idx = 0; idx < offsets_.size(); ++idx) {
        fprintf(stderr, "%f %f %f %f %f %f %f %f\n", offsets_[idx].batchIdx, offsets_[idx].x,
            offsets_[idx].y, offsets_[idx].z, offsets_[idx].cls, offsets_[idx].reg);
    }
    fprintf(stderr, "[INFO] data shape is [%d, %d]\n", offsets_.size(), 8);
}

