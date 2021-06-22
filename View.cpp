//
// Created by sj on 2020/5/30.
//

#include "View.h"

View::View()
{
    // rows_ = 512U;
    // cols_ = 512U;
    rows_ = 256U;
    cols_ = 256U;
    resolution_ = rows_ / 80.0F;
    range_x_max_ = 80.0f;
    range_x_min_ = 0.0f;
    range_y_min_ = -40.0f;
    range_y_max_ = 40.0f;
    voxelPointNum_ = imgInt(rows_, std::vector<int>(cols_, 0));
    voxelProb_ = imgFloat(rows_, std::vector<float>(cols_, 0.0f));
    voxelOffset_ = imgCenter(rows_, std::vector<utils::point2d>
            (cols_, utils::point2d(0.0f, 0.0f)));
    voxelCenter_ = imgCenter(rows_, std::vector<utils::point2d>
            (cols_, utils::point2d(0.0f, 0.0f)));
}

void View::Build(const std::vector<utils::data>& input) {
    for(size_t dataIdx = 0; dataIdx < input.size(); ++dataIdx)
    {
        const utils::data& da = input[dataIdx];
        int row;
        int col;
        Project(da, row, col);
        size_t debug = 1U;
        ++voxelPointNum_[row][col];
        if (voxelProb_[row][col] < da.cls) {
            voxelProb_[row][col] = da.cls;
            voxelOffset_[row][col] = utils::point2d((da.x - da.reg[0]), (da.y - da.reg[1]));
        }
    }
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col)
        {
            voxelCenter_[row][col] = utils::point2d((range_x_max_ - static_cast<float>(row) / resolution_ - 0.5f / resolution_),
                                                    (range_y_max_ - static_cast<float>(col) / resolution_ - 0.5f / resolution_));
        }
    }
    std::cout << "View::build finished..." << std::endl;
}

void View::Project(const utils::data& da, int& row, int& col)
{
    row = floor((-da.x + range_x_max_) * resolution_);
    col = floor((-da.y + range_y_max_) * resolution_);
}

void View::Project(const utils::point2d& input, int& row, int& col)
{
    printf("input ==> [%f, %f]\n", input.x, input.y);
    row = floor((-input.x + range_x_max_) * resolution_);
    col = floor((-input.y + range_y_max_) * resolution_);
    row = std::min(row, int(rows_ - 1));
    col = std::min(col, int(cols_ - 1));
    printf("input ==> [%d, %d]\n", row, col);
}