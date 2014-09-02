//
//  octree.h
//  OpenGLFramework
//
//  Created by Laszlo Korte on 02.09.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#ifndef __OpenGLFramework__octree__
#define __OpenGLFramework__octree__

#include <set>
#include <array>
#include <iostream>

#include "../elements/aabb3.h"
#include "../elements/relation.h"

using lkogl::math::elements::Aabb3;

namespace lkogl {
    namespace math {
        namespace graphs {
            template<typename T, typename E, const Aabb3<T>(E::*G)(void) const = &E::boundingBox>
            class Octree {
                static const int OCT = 8;
                static const int NODE_CAPACITY = 2;
                
                Aabb3<T> bounds_;
                
                int childCount_ = 0;
                std::array<std::unique_ptr<Octree<T, E, G>>, OCT> children_;
                std::vector<std::shared_ptr<E>> elements_;
                
            public:
                explicit Octree(Aabb3<T> bounds) : bounds_(bounds)
                {
                    if(bounds.volume() == 0) {
                        throw;
                    }
                }
                
                void insert(const std::shared_ptr<E> e)
                {
                    Aabb3<T> bounding = (&*e->*G)();
                    if(math::elements::intersects(bounding, bounds_)) {
                        if(elements_.size() < NODE_CAPACITY) {
                            elements_.push_back(e);
                        } else {
                            insertIntoChildren(e);
                        }
                    } else {
                        Octree<T, E, G>* thisAsNode(new Octree<T, E, G>(bounds_, std::move(children_), std::move(elements_)));
                        elements_ = std::vector<std::shared_ptr<E>>();
                        children_ = std::array<std::unique_ptr<Octree<T, E, G>>, OCT>();
                        
                        Vec3<int> dirInt = math::sign(bounding.center() - bounds_.center());
                        
                        Vec3<T> lowerOffset = math::Vec3<T>(dirInt.x <= 0?1:0, dirInt.y<=0?1:0, dirInt.z<=0?1:0);
                        Vec3<T> upperOffset = math::Vec3<T>(dirInt.x>0?1:0, dirInt.y>0?1:0, dirInt.z>0?1:0);
                        
                        Vec3<T> expansion = bounds_.max - bounds_.min;
                        
                         Aabb3<T> newBounds = Aabb3<T>(bounds_.min - lowerOffset*expansion, bounds_.max + upperOffset * expansion);
                        
                        bounds_ = newBounds;
                        
                        int index = 7-(dirInt.x + (dirInt.y<<1) + (dirInt.z<<2));
                        
                        children_[index].reset(thisAsNode);
                        
                        insert(e);
                    }
                }
                
                void remove(std::shared_ptr<E> e)
                {
                    Aabb3<T> bounding = (&*e->*G)();
                    if(math::elements::intersects(bounding, bounds_)) {
                        elements_.erase(std::find(elements_.begin(), elements_.end(), e));
                        
                        for(unsigned int i=0;i<OCT;i++) {
                            removeFromChild(e,i);
                        }
                    }
                }
                
                std::set<std::shared_ptr<E>> queryRange(Aabb3<T> range)
                {
                    std::set<std::shared_ptr<E>> result;
                    
                    return result;
                }
                
                bool empty() const
                {
                    return elements_.size() == 0 && childCount_ == 0;
                }
                
                ~Octree()
                {
                }
                
                
                
                void print() const
                {
                    print(0, "X");
                }
                
            private:
                Octree(Aabb3<T> b,
                       std::array<std::unique_ptr<Octree<T, E, G>>, OCT> c,
                       std::vector<std::shared_ptr<E>> el) :
                bounds_(b),
                children_(std::move(c)),
                elements_(std::move(el))
                {
                    
                }
                
                void insertIntoChildren(const std::shared_ptr<E> e)
                {
                    for(unsigned int i=0;i<OCT;i++) {
                        insertIntoChild(e, i);
                    }
                }
                
                void insertIntoChild(const std::shared_ptr<E> e, unsigned int i)
                {
                    Aabb3<T> bounding = (&*e->*G)();
                    
                    math::Vec3<T> childWidth = (bounds_.max - bounds_.min)/T(2);
                    math::Vec3<T> lowerOffset(i&1, (i>>1)&1,(i>>2)&1);
                    math::Vec3<T> upperOffset = math::Vec3<T>(1,1,1) - lowerOffset;
                    
                    Aabb3<T> childBounding(bounds_.min + childWidth*lowerOffset, bounds_.max - childWidth*upperOffset);
                    
                    if(math::elements::intersects(childBounding, bounding))
                    {
                        if(!children_[i]) {
                            children_[i].reset(new Octree<T, E, G>(childBounding));
                            childCount_++;
                        }
                        
                        children_[i]->insert(e);
                    }
                }
                
                void removeFromChild(const std::shared_ptr<E> e, unsigned int i)
                {
                    if(children_[i]) {
                        children_[i]->remove(e);
                        if(children_[i]->empty()) {
                            children_[i].reset();
                            childCount_--;
                        }
                    }
                }
                
                
                
                void print(int depth, const std::string& label) const
                {
                    for(int i = 0; i < depth; i++)
                    {
                        std::cout << "  ";
                    }
                    
                    std::cout << label << ":";
                    std::cout << "["<< bounds_.min.x << "," << bounds_.min.y << "," << bounds_.min.z <<"]-";
                    std::cout << "["<< bounds_.max.x << "," << bounds_.max.y << "," << bounds_.max.z <<"]";
                    for(auto e : elements_) {
                        std::cout << e << ", ";
                    }
                    std::cout  << std::endl;
                    
                    if(children_[0]) { children_[0]->print(depth+1, "LeftDownFlat"); }
                    if(children_[1]) { children_[1]->print(depth+1, "RightDownFlat"); }
                    if(children_[2]) { children_[2]->print(depth+1, "LeftUpFlat"); }
                    if(children_[3]) { children_[3]->print(depth+1, "RightUpFlat"); }
                    if(children_[4]) { children_[4]->print(depth+1, "LeftDownDeep"); }
                    if(children_[5]) { children_[5]->print(depth+1, "RightDownDeep"); }
                    if(children_[6]) { children_[6]->print(depth+1, "LeftUpDeep"); }
                    if(children_[7]) { children_[7]->print(depth+1, "RightUpDeep"); }
                    
                }
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__octree__) */
