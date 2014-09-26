/**
 * @file GraphicsDriverBase.hpp
 * @brief Defines the GraphicsDriverBase abstract class.
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
#define __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__

#include <exeng/graphics/GraphicsDriver.hpp>

#include <list>
#include <boost/shared_ptr.hpp>

namespace exeng { namespace graphics {
    /**
     * @brief Base common functionality for easing the process 
     * of implementing graphics drivers
     */
    class GraphicsDriverBase : public GraphicsDriver {
    public:
        GraphicsDriverBase();
        virtual ~GraphicsDriverBase();
        virtual exeng::Matrix4f getTransform(Transform::Enum transform) override;
        virtual exeng::Rectf getViewport() const override;
        virtual const exeng::graphics::Material* getMaterial() const override;
        virtual std::unique_ptr<Buffer> createVertexBuffer(const std::int32_t size, const void* data) override;
        virtual std::unique_ptr<Buffer> createIndexBuffer(const std::int32_t size, const void* data) override;
        virtual void setTransformName(Transform::Enum transform, const std::string &name) override;
        virtual std::string getTransformName(Transform::Enum transform) const  override;
        
    protected:
        const Material *material = nullptr;
        Rectf viewport;
        Matrix4f transforms[3];
        std::string transformNames[3];
    };
}}

#include "GraphicsDriverBase.inl"

#endif  // __EXENG_GRAPHICS_GRAPHICSDRIVERBASE_HPP__
