//
//  rectangle.cpp
//  OpenGLFramework
//
//  Created by Laszlo Korte on 15.08.14.
//  Copyright (c) 2014 Laszlo Korte. All rights reserved.
//

#include "./rectangle.h"

namespace lkogl {
    namespace ui {
        Rectangle::Rectangle()
        {
        }
        
        Rectangle::Rectangle(int width, int height)
        {
            min_ = {0,0};
            max_ = {width, height};
         }
        
        Rectangle::~Rectangle()
        {
        }
        
        const Rectangle::Position Rectangle::center() const
        {
            return (max_ + min_) / 2;
        }
        
        void Rectangle::setCenter(const Position& c)
        {
            Rectangle::Position size = (max_ - min_);
            
            max_ = c + size/2;
            min_ = c - size/2;
        }
        
        const Rectangle::Position Rectangle::topLeft() const
        {
            return min_;
        }
        
        const Rectangle::Position Rectangle::topRight() const
        {
            return {max_.x, min_.y};
        }
        
        const Rectangle::Position Rectangle::bottomLeft() const
        {
            return {min_.x, max_.y};
        }
        
        const Rectangle::Position Rectangle::bottomRight() const
        {
            return {max_.x, max_.y};
        }
        
        const Rectangle::ScalarType Rectangle::left() const
        {
            return min_.x;
        }
        
        const Rectangle::ScalarType Rectangle::right() const
        {
            return max_.x;
        }
        
        const Rectangle::ScalarType Rectangle::top() const
        {
            return min_.y;
        }
        
        const Rectangle::ScalarType Rectangle::bottom() const
        {
            return max_.y;
        }
        
        
        const Rectangle::ScalarType Rectangle::width() const
        {
            return max_.x - min_.x;
        }
        
        const Rectangle::ScalarType Rectangle::height() const
        {
            return max_.y - min_.y;
        }
        
        
        void Rectangle::setSize(const ScalarType& width, const ScalarType& height)
        {
            Position center = (max_ + min_) / 2;
            
            min_ = {center.x - width/2, center.y - height/2};
            max_ = {center.x + width/2, center.y + height/2};
        }
        
        void Rectangle::setTopLeft(const Position& p)
        {
            Position center = (max_ + min_) / 2;
            ScalarType oldWidth = width();
            ScalarType oldHeight = height();
            
            min_ = p;
            min_ = min_ + Position{oldWidth, oldHeight};
        }
        
        
        const Rectangle::Position Rectangle::size() const
        {
            return max_ - min_;
        }
        
        bool Rectangle::contains(const Position &p) const
        {
            return p.x >= min_.x && p.y >= min_.y
                && p.x <= max_.x && p.y <= max_.y;
        }
        
    }
}