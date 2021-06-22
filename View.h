//
// Created by sj on 2020/5/30.
//

#ifndef SIMPLEVIEWER_VIEW_H
#define SIMPLEVIEWER_VIEW_H

#include <iostream>
#include <vector>
#include "utils.h"
#include <algorithm>
#include "object.h"

typedef std::vector<std::vector<float>> imgFloat;
typedef std::vector<std::vector<int>> imgInt;
typedef std::vector<std::vector<utils::point2d>> imgCenter;

class View {
public:
    View();
    View(const std::vector<utils::data>& input);
    void Build(const std::vector<utils::data>& input);
    void Project(const utils::data& da, int& row, int& col);
    void Project(const utils::point2d& input, int& row, int& col);
    int Count(const int& row, const int& col) {return voxelPointNum_[row][col];}
    int GetProb(const int& row, const int& col) {return voxelProb_[row][col];}
    utils::point2d GetCenter(const int& row, const int& col){return voxelCenter_[row][col];};
    utils::point2d GetOffset(const int& row, const int& col){return voxelOffset_[row][col];};

    const size_t rows() const {return rows_;};
    const size_t cols() const {return cols_;};

private:
    size_t rows_;
    size_t cols_;
    float range_x_max_;
    float range_x_min_;
    float range_y_max_;
    float range_y_min_;
    float resolution_;
    imgInt voxelPointNum_;
    imgFloat voxelProb_;
    imgCenter voxelOffset_;
    imgCenter voxelCenter_;
    imgFloat voxel;

};


#endif //SIMPLEVIEWER_VIEW_H
