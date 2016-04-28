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

#pragma once

#ifndef __EXENG_DATATYPE_HPP__
#define __EXENG_DATATYPE_HPP__

#include <xe/Config.hpp>
#include <xe/Enum.hpp>
#include <iostream>
#include <cstdint>

namespace xe {
    
    /**
     * @brief Basic data type enumeration.
     */
    struct DataType : public Enum {
        enum Kind { Int, Float };
        
        enum Enum {
            Unknown,
            UInt8, UInt16, UInt32,
            Int8, Int16, Int32,
            Float16, Float32 
        }; 
        
		static bool isSigned(DataType::Enum dt)  {
			switch (dt) {
				case DataType::UInt8:
				case DataType::UInt16:
				case DataType::UInt32:
					return false;

				default:
					return true;
			}
		}

		static DataType::Kind getKind(DataType::Enum dataType)  {
			switch (dataType) {
				case DataType::Float16: 
				case DataType::Float32: 
					return DataType::Float;

				default:
					return DataType::Int;
			}
		}

		static int getSize(DataType::Enum dataType)  {
			switch (dataType) {
				case DataType::UInt8:
				case DataType::Int8:
					return 1;

				case DataType::UInt16:
				case DataType::Int16:
				case DataType::Float16:
					return 2;

				case DataType::UInt32:
				case DataType::Int32:
				case DataType::Float32:
					return 4;

				default:
					return 0;
			}
		}
        
        template<typename BasicType>
        static bool isEqual(DataType::Enum dataType);
    };

}

#endif
