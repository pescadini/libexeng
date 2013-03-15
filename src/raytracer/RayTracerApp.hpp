
#ifndef __RAYTRACER_RAYTRACERAPP_HPP__
#define __RAYTRACER_RAYTRACERAPP_HPP__

#include <vector>
#include <boost/scoped_ptr.hpp>

#include "Application.hpp"

namespace RayTracer
{
    class RayTracerApp : public Application
    {
    public:
        RayTracerApp();
        
        virtual ~RayTracerApp();
        
        virtual void initialize(const StringVector& cmdLine);

        virtual double getFrameTime() const;
        
        virtual void processInput();
        
        virtual ApplicationStatus::Enum getStatus();
        
        virtual void update(double seconds);
        
        virtual void present();
        
        virtual int getExitCode() const;
        
        virtual void terminate();
        
    private:
        struct Private;
        boost::scoped_ptr<Private> impl;
    };
}

#endif	//__RAYTRACER_RAYTRACERAPP_HPP__
