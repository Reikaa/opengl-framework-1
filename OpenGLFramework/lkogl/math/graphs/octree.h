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
#include <vector>
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
                static const int NODE_CAPACITY = 1;
                
                Aabb3<T> bounds_;
                
                int childCount_ = 0;
                std::array<std::array<std::array<std::unique_ptr<Octree<T, E, G>>, 2>, 2>, 2> children_;
                std::vector<std::shared_ptr<E>> elements_;
                
            public:
                explicit Octree(Aabb3<T> bounds) : bounds_(bounds)
                {
                    if(bounds.volume() == 0) {
                        throw;
                    }
                    elements_.reserve(NODE_CAPACITY);
                }
                
                void insert(const std::shared_ptr<E> e)
                {
                    if(math::elements::intersects((&*e->*G)(), bounds_)) {
                        if(elements_.size() < NODE_CAPACITY) {
                            elements_.push_back(e);
                        } else {
                            insertIntoChildren(e);
                        }
                    }
                }
                
                void remove(std::shared_ptr<E> e)
                {
                    if(math::elements::intersects((&*e->*G)(), bounds_)) {
                        auto pos = std::find(elements_.begin(), elements_.end(), e);
                        if(pos != elements_.end()) {
                            elements_.erase(pos);
                        } else {
                            removeFromChildren(e);
                        }
                    }
                }
                
                template<typename Q>
                std::set<std::shared_ptr<E>> queryRange(const Q& range) const
                {
                    std::set<std::shared_ptr<E>> result;
                    queryRange(range, result);
                    
                    return result;
                }
                
                std::set<std::shared_ptr<E>> queryAll() const
                {
                    return queryRange(bounds_);
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
                
                std::vector<Aabb3<T>> boxes() const
                {
                    std::vector<Aabb3<T>> result;
                    
                    boxes(result);
                    
                    return result;
                }
                
            private:
                
                void insertIntoChildren(const std::shared_ptr<E> e)
                {
                    for(unsigned short x=0;x<2;x++) {
                        for(unsigned short y=0;y<2;y++) {
                            for(unsigned short z=0;z<2;z++) {
                                insertIntoChild(e, x, y, z);
                            }
                        }
                    }
                }
                
                void insertIntoChild(const std::shared_ptr<E> e, unsigned short x, unsigned short y, unsigned short z)
                {
                    
                    if(!children_[x][y][z]) {
                        
                        Vec3<T> halfWidth = bounds_.dimensions() / T(2);
                        Vec3<T> lowerOff = Vec3<T>(x,y,z);
                        Vec3<T> upperOff = 1.0f-lowerOff;
                        
                        
                        children_[x][y][z].reset(new Octree(Aabb3<T>(bounds_.min + lowerOff*halfWidth, bounds_.max - upperOff*halfWidth)));
                        childCount_++;
                    }
                    
                    children_[x][y][z]->insert(e);
                    
                    if(children_[x][y][z]->empty()) {
                        children_[x][y][z].reset();
                        childCount_--;
                    }
                }
                
                void removeFromChildren(const std::shared_ptr<E> e)
                {
                    for(unsigned short x=0;x<2;x++) {
                        for(unsigned short y=0;y<2;y++) {
                            for(unsigned short z=0;z<2;z++) {
                                removeFromChild(e, x, y, z);
                            }
                        }
                    }
                }
                
                void removeFromChild(const std::shared_ptr<E> e, unsigned short x, unsigned short y, unsigned short z)
                {
                    if(children_[x][y][z]) {
                        children_[x][y][z]->remove(e);
                        if(children_[x][y][z]->empty()) {
                            children_[x][y][z].reset();
                            childCount_--;
                        }
                    }
                }
                
                template<typename Q>
                void queryRange(const Q& range, std::set<std::shared_ptr<E>>& result) const
                {
                    if(math::elements::relationship(range, bounds_) != elements::VolumeRelation::OUTSIDE) {
                        for(auto e : elements_) {
                            if(math::elements::relationship(range, (&*e->*G)()) != elements::VolumeRelation::OUTSIDE) {
                                result.insert(e);
                            }
                        }
                    }
                    queryRangeChildren(range, result);
                }
                
                template<typename Q>
                void queryRangeChildren(const Q& range, std::set<std::shared_ptr<E>>& result) const
                {
                    for(unsigned short x=0;x<2;x++) {
                        for(unsigned short y=0;y<2;y++) {
                            for(unsigned short z=0;z<2;z++) {
                                if(children_[x][y][z]) {
                                    children_[x][y][z]->queryRange(range, result);
                                }
                            }
                        }
                    }
                }
                
                void print(int depth, const std::string& label) const
                {
                    for(int i=0;i<depth;i++) {
                        std::cout << "  ";
                    }
                    std::cout << label;
                    std::cout << "(";
                    std::cout << elements_.size();
                    std::cout << "/";
                    std::cout << childCount_;
                    std::cout << ")";
                    
                    if(empty()) {
                        std::cout << "EMPTY";
                    }
                    
                    std::cout << std::endl;

                    int test = 0;
                    
                    for(unsigned short x=0;x<2;x++) {
                        for(unsigned short y=0;y<2;y++) {
                            for(unsigned short z=0;z<2;z++) {
                                auto l = std::string(x>0?"right":"left") + (y>0?"top":"bottom") + (z>0?"deep":"shallow");
                                if(children_[x][y][z]) {
                                    children_[x][y][z]->print(depth+1, l);
                                    test++;
                                }
                            }
                        }
                    }
                    
                    
                }
                
                void boxes(std::vector<Aabb3<T>>& result) const
                {
                    result.push_back(bounds_);

                    for(unsigned short x=0;x<2;x++) {
                        for(unsigned short y=0;y<2;y++) {
                            for(unsigned short z=0;z<2;z++) {
                                if(children_[x][y][z]) {
                                    children_[x][y][z]->boxes(result);
                                }
                            }
                        }
                    }
                }
            };
        }
    }
}

#endif /* defined(__OpenGLFramework__octree__) */
