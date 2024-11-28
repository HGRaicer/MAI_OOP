#pragma once
#include <list>

class FixedBlockMemoryResource final: public std::pmr::memory_resource {
private:
    std::list<void*> allocated_blocks;
    char* memory_pool;
    size_t pool_size;
    size_t offset;

protected:
    /// \brief Allocate a block of memory of size \p bytes with an alignment of
    ///        \p alignment.
    ///
    /// \details This function allocates a block of memory of size \p bytes with an
    ///          alignment of \p alignment from the pre-allocated pool. If the
    ///          allocation request would exceed the available memory, a
    ///          `std::bad_alloc` is thrown.
    ///
    /// \param bytes The size of the memory block to allocate
    /// \param alignment The alignment of the memory block to allocate
    ///
    /// \returns A pointer to the allocated memory block
    void* do_allocate(size_t bytes, size_t alignment) override {
        if (offset + bytes > pool_size) {
            throw std::bad_alloc();
        }
        void* ptr = memory_pool + offset;
        offset += bytes;
        allocated_blocks.push_back(ptr);
        return ptr;
    }

    /// \brief Deallocate a block of memory of size \p bytes with an alignment of
    ///        \p alignment at address \p ptr.
    ///
    /// \details This function deallocates a block of memory of size \p bytes with an
    ///          alignment of \p alignment at address \p ptr. The memory must have been
    ///          allocated with `do_allocate`.
    ///
    /// \param ptr The address of the memory block to deallocate
    /// \param bytes The size of the memory block to deallocate
    /// \param alignment The alignment of the memory block to deallocate
    void do_deallocate(void* ptr, size_t bytes, size_t aligment) override {
        allocated_blocks.remove(ptr);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

public:
    explicit FixedBlockMemoryResource(size_t total_size) : pool_size(total_size), offset(0) {
        memory_pool = new char[pool_size];
    }

    ~FixedBlockMemoryResource() override{
        delete[] memory_pool;
    }
};
