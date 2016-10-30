#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H

#include "boundingBox.hpp"
#include "vec3.hpp"

namespace glRender {

class AABB : public BoundingBox
{
public:
    AABB(const Vec3 & center, float halfSide);
    const Vec3 & center() const;
    float halfSide() const;
    const Vec3 & min();
    const Vec3 & max();

    void setCenter(const Vec3 & center);
    void setHalfSide(float halfSide);

    virtual bool intersects(Ray * ray) const;

private:
    void _updateMinMax();

private:
    Vec3 m_center;
    float m_halfSide;
    Vec3 m_min;
    Vec3 m_max;
};

}

#endif // AXISALIGNEDBOUNDINGBOX_H