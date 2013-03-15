

#include "GraphicsDriverBase.hpp"

#include <cassert>

namespace exeng
{
    namespace graphics
    {
        GraphicsDriverBase::GraphicsDriverBase()
        {
            this->model.identity();
            this->view.identity();
            this->projection.identity();
            this->modelView.identity();
            
            this->viewPort.set(0.0f);
            
            this->fullScreen = false;
            
            this->vertexBuffer = NULL;
            this->indexBuffer = NULL;
        }
        
        
        GraphicsDriverBase::~GraphicsDriverBase()
        {
        }
        
        
        DisplayMode GraphicsDriverBase::getDisplayMode() const
        {
            return this->displayMode;
        }
        
        
        exeng::math::Matrix4f GraphicsDriverBase::getTransform(Transform::Type transform)
        {
            assert( transform == Transform::World || 
                    transform == Transform::View || 
                    transform == Transform::Projection);
            
            switch (transform)
            {
                case Transform::World:      return this->model;
                case Transform::View:       return this->view;
                case Transform::Projection: return this->projection;
            }

			return math::Matrix4f();
        }
        
        
        bool GraphicsDriverBase::getFullScreenStatus() const
        {
            return this->fullScreen;
        }
        
        
        Material GraphicsDriverBase::getMaterial() const
        {
            return this->material;
        }
        
        
        math::Rectf GraphicsDriverBase::getViewport() const
        {
            return this->viewPort;
        }
    }
}