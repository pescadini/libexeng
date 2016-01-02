/**
 * @file 
 * @brief 
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_SCENEGRAPH_LIGHT_HPP__
#define __EXENG_SCENEGRAPH_LIGHT_HPP__

#include <xe/Vector.hpp>
#include <xe/Enum.hpp>
#include <xe/sg/SceneNodeData.hpp>
#include <xe/sg/IRenderable.hpp>

namespace xe { namespace sg {
    /**
     * @brief Available instanciable light types.
     */
    struct LightType : public Enum {
        enum Enum {
            Directional,
            Point,
            Spot
        };
    };

    class EXENGAPI Light : public IRenderable {
        friend class Scene;

    public:
        Light();
        virtual ~Light();

        /**
         * @brief 
         */
        LightType::Enum getLightType() const;
            
        /**
         * @brief 
         */
        void setLightType(LightType::Enum lightType);
            
        /**
         * @brief 
         */
        void setPosition(const xe::Vector3f& pos);
            
        /**
         * @brief 
         */
        xe::Vector3f getPosition() const;
            
        /**
         * @brief 
         */
        void setTarget(const xe::Vector3f& target);
            
        /**
         * @brief 
         */
        xe::Vector3f getTarget() const;
            
        /**
         * @brief 
         */
        void setRange(float range);
            
        /**
         * @brief 
         */
        float getRange() const;

		virtual void renderWith(IRenderer *renderer);

    private:
        struct Private;
        Private *impl;
    };
}}

#endif // __EXENG_SCENEGRAPH_LIGHT_HPP__
