#ifndef _FINGER_B_TREE_BI_PTR_H
#define _FINGER_B_TREE_BI_PTR_H

#include <cstdint>
#include <memory>
#include <utility>
#include <type_traits>

namespace finger_b_tree {

template <typename A, typename B>
class BiPtr {
 public:
  BiPtr() : BiPtr(nullptr) {}
  BiPtr(BiPtr&& other) : BiPtr() { std::swap(ptr_, other.ptr_); }
  BiPtr& operator(BiPtr&& other) {
    std::swap(ptr_, other.ptr_);
  }
  BiPtr(const BiPtr&) = delete;
  BiPtr& operator(const BiPtr&) = delete;

  BiPtr(nullptr_t) : ptr_(reinterpret_cast<uintptr_t>(nullptr)) {}
  BiPtr(std::unique_ptr<A> ptr) : ptr_(reinterpret_cast<void*>(ptr.release())) {}
  BiPtr(std::unique_ptr<B> ptr) : ptr_(reinterpret_cast<void*>(ptr.release()) | 1) {}

  ~BiPtr() { Delete(); }

  A* AsLeft() {
    if ((ptr_ & 1) == 0) {
      return reinterpret_cast<A*>(ptr_);
    } else {
      return nullptr;
    }
  }

  B* AsRight() {
    if (ptr_ & 1) {
      return reinterpret_cast<B*>(ptr_ & (~1));
    } else {
      return nullptr;
    }
  }

 private:
  void Delete() {
    if (ptr_ & 1) {
      delete reinterpret_cast<B*>(ptr_ & (~1));
    } else {
      delete reinterpret_cast<A*>(ptr_);
    }
    ptr_ = reinterpret_cast<uintptr_t>(nullptr);
  }

  uintptr_t ptr_;
};

}  // namespace finger_b_tree

#endif  // _FINGER_B_TREE_BI_PTR_H
