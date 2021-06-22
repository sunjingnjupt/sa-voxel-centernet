#ifndef OBJECT_H_
#define OBJECT_H_

#include "QGLViewer/frame.h"
#include <memory>
class Object {
public:
    using Ptr = std::shared_ptr<Object>;
    explicit Object(){}
    void draw() const;
    qglviewer::Frame frame;
};

#endif // OBJECT_H_