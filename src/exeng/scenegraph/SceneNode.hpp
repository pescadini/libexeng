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


#ifndef __EXENG_SCENE_SCENENODE_HPP__
#define __EXENG_SCENE_SCENENODE_HPP__

#include <vector>

#include <exeng/Object.hpp>
#include <exeng/math/TMatrix.hpp>

namespace exeng { namespace scenegraph {
    class EXENGAPI SceneNode;
    class EXENGAPI SceneNodeData;

    typedef std::vector<SceneNode*> SceneNodes;
    typedef SceneNodes::iterator SceneNodesIterator;

    /**
     * @brief Node of the Scene Graph.
     * 
     * Represent any existing entity on a 3D-World
     * 
     * @TODO: Clean the interface.
     */
    class EXENGAPI SceneNode : public Object {
    public:
        SceneNode();
        explicit SceneNode(const std::string& name);
        
        SceneNode(const std::string &name, SceneNode *parent);
        
        virtual ~SceneNode();

        virtual std::string toString() const;
        
        exeng::math::Matrix4f getTransform() const;
        
        void setTransform(const exeng::math::Matrix4f& transform);
        
        std::string getName() const;
        
        void setName(const std::string &name);
        
        int getChildCount() const;
        
        SceneNode* getChild(int index) const;
        
        SceneNode* getChild(const std::string& name) const;
        
        SceneNode* getChild(const std::string& name);
        
        bool existChild(const std::string& name) const;
        
        bool hasParent() const;

        SceneNode* getParent() const;
        
        void setParent(SceneNode* parent);

        SceneNode* findNode(const std::string &name) const;
        
        SceneNode* addChild(SceneNode *childPtr);
        
        SceneNode* removeChild(const std::string& name);

        SceneNode* removeChild(SceneNode* childRef);

        SceneNode* addChild(const std::string& name);
        
        void orphan();
        
        void setData(SceneNodeData* data);

        SceneNodeData* getData() const;
        
        const SceneNodes& getChilds() const;
        
    private:
        struct Private;
        Private *impl;
    };
}}

#endif
