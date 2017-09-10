#ifndef TN_BUFFER_H
#define TN_BUFFER_H

#include <stdlib.h>
#include <string.h>

namespace TinyNet
{
    struct Buffer
    {
        void* data = nullptr;
        size_t bytes = 0;

        Buffer() = default;
        Buffer(int bytes)
        {
            data = malloc(bytes);
            this->bytes = bytes;
        }

        Buffer(const Buffer& rhs)
        {
            data = malloc(rhs.bytes);
            this->bytes = rhs.bytes;
            memcpy(data, rhs.data, bytes);
        }

        Buffer(Buffer&& rhs)
        {
            data = malloc(rhs.bytes);
            this->bytes = rhs.bytes;
            memcpy(data, rhs.data, bytes);
        }

        Buffer& operator=(const Buffer& rhs)
        {
            if(data)
                free(data);

            data = malloc(rhs.bytes);
            this->bytes = rhs.bytes;
            memcpy(data, rhs.data, bytes);
            return *this;
        }

        Buffer& operator=(Buffer&& rhs)
        {
            if(data)
                free(data);

            data = malloc(rhs.bytes);
            this->bytes = rhs.bytes;
            memcpy(data, rhs.data, bytes);
            return *this;
        }

        ~Buffer()
        {
            if(data)
                free(data);
        }

        bool resize(size_t bytes)
        {
            if(data)
                free(data);

            data = malloc(bytes);
            if(data == nullptr)
            {
                this->bytes = 0;
                return false;
            }
            this->bytes = bytes;
            return true;
        }
    };
}

#endif
