
#ifndef __EXENG_STATIC_BUFFER_HPP__
#define __EXENG_STATIC_BUFFER_HPP__

#include <xe/Buffer.hpp>

namespace xe {

	/**
	 * @brief Wrapper over a raw C buffer.
	 */
	class EXENGAPI StaticBuffer : public Buffer {
	public:
		StaticBuffer(void* data, const int dataSize);

		virtual int getHandle() const override;

		virtual int getSize() const override;
		
		virtual const void* getPointer() const override;

	private:
		void* data = nullptr;
		int dataSize = 0;
	};

	typedef std::unique_ptr<StaticBuffer> StaticBufferPtr;
}

#endif	// __EXENG_STATIC_BUFFER_HPP__