///**
// * @file ResourceManager.hpp
// * @brief Defines the ResourceManager class.
// */
//
///*
// * Copyright (c) 2013 Felipe Apablaza.
// *
// * The license and distribution terms for this file may be
// * found in the file LICENSE in this distribution.
// */
//
//#ifndef __EXENG_RESOURCEMANAGER_HPP__
//#define __EXENG_RESOURCEMANAGER_HPP__
//
//#include <list>
//#include <xe/Resource.hpp>
//#include <xe/ResourceLoader.hpp>
//
//namespace xe {
//    /**
//     * @brief Resource manager class.
//	 *
//	 * This abstract class hold the logic for a basic management of resources 
//	 * (simply boils down to the lifetime management of those resources)
//     */
//    class EXENGAPI ResourceManager {
//    public:
//		ResourceManager();
//		virtual ~ResourceManager() = 0;
//
//		virtual Resource* get(const std::string &uri);
//		virtual const Resource* get(const std::string &uri) const;
//
//	protected:
//		virtual void addLoader(ResourceLoader *loader);
//		virtual void removeLoader(ResourceLoader *loader);
//
//		std::list<ResourceLoader*>& getLoaders();
//
//		void put(const std::string &uri, ResourcePtr resource);
//
//	protected:
//		struct Impl;
//		Impl *impl = nullptr;
//    };
//}
//
//#endif //__EXENG_RESOURCEFACTORY_HPP__