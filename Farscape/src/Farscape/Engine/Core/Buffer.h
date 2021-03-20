#pragma once
#include "Core.h"

namespace Farscape {

    /**
     * Implementation of a generic buffer
     *
     * We will need buffers everywhere. There is possibly a better way to do this but whatever.
     */
    struct Buffer
    {
        byte* Data;
        uint32_t Size;

        /**
         * Default ctor
         *
         * @return an instance of Buffer
         */
        Buffer()
            : Data(nullptr)
            , Size(0)
        { }


		/**
		 * Parametrized ctor
		 *
		 * @param Data A pointer to the beginning of the buffer.
		 * @param Size The size of the buffer to allocate.
		 * @return an instance of Buffer
		 */
		Buffer(byte* data, uint32_t size)
			: Data(data), Size(size)
		{
		}


		/**
		 * Performs a deep copy of Buffer
		 *
		 * @param data A pointer to the beginning of the buffer to copy.
		 * @param Size The size of the buffer to copy.
		 * @return an instance of Buffer
		 */
		static Buffer Copy(void* data, uint32_t size)
		{
			Buffer buffer;
			buffer.Allocate(size);
			memcpy(buffer.Data, data, size);
			return buffer;
		}


		/**
		 * Allocates memory for a new Buffer
		 *
		 * @param Size The size to allocate.
		 */
		void Allocate(uint32_t size)
		{
			delete[] Data;
			Data = nullptr;

			if (size == 0)
				return;

			Data = new byte[size];
			Size = size;
		}


		/**
		 * Initializes a buffer with zeros
		 *
		 */
		void ZeroInitialize()
		{
			if (Data)
				memset(Data, 0, Size);
		}


		/**
		 * Sets a pointer to a memory location equal to buffer + offset and returns it as a templated type
		 *
		 * @param offset How much to offset the start of buffer.
		 * @return a pointer of type T
		 */
		template<typename T>
		T& Read(uint32_t offset = 0)
		{
			return *(T*)(Data + offset);
		}


		/**
		 * Write to the Buffer.Data
		 *
		 * @param data A pointer to the beginning of the data to write to this buffer.
		 * @param size The size of the of data to write.
		 * @param offset How much to offset data
		 */
		void Write(void* data, uint32_t size, uint32_t offset = 0)
		{
			FS_CORE_ASSERT(offset + size <= Size, "Buffer overflow!");
			memcpy(Data + offset, data, size);
		}


		/**
		 * The bool cast tells us if the buffer (data) is null
		 *
		 * @return true if data is initialized false otherwise
		 */
		operator bool() const
		{
			return Data;
		}


		/**
		 * [] operator returns a requested element
		 *
		 * @param index Index of the element to fetch
		 * @return byte reference
		 */
		byte& operator[](int index)
		{
			return Data[index];
		}


		/**
		 * [] operator returns a requested element (const)
		 *
		 * @param index Index of the element to fetch
		 * @return byte 
		 */
		byte operator[](int index) const
		{
			return Data[index];
		}


		/**
		 * A nice casting helper for our buffer
		 *
		 * @param index Index of the element to fetch
		 * @return ponter to data cast to T pointer
		 */
		template<typename T>
		T* CastTo()
		{
			return (T*)Data;
		}


		/**
		 * Gets the size of the buffer
		 *
		 * @return size of the buffer
		 */
		inline uint32_t GetSize() const { return Size; }
    };

}
