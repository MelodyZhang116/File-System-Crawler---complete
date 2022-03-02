#ifndef LINKEDINTLIST_H_
#define LINKEDINTLIST_H_

#include <memory>
#include "IntList.h"
using std::shared_ptr;
using std::weak_ptr;
namespace intlist333 {

// LinkedIntList is an implementation of
// the IntList abstract class. Implemented using
// a doubly linked list
class LinkedIntList: public IntList{
 public:
  // constructor
  LinkedIntList() : num_elements_(0), head_(nullptr), tail_(nullptr){ };
  // Destructor should be kept default
  // since smart pointers should clean
  // everything up for us
  virtual ~LinkedIntList() = default;

  //LinkedIntList(const LinkedIntList& copyme) = delete;
  //virtual LinkedIntList& operator=(const LinkedIntList& rhs) = delete;


  virtual int num_elements() const { return num_elements_; }
  virtual void Push(const int payload) ;
  virtual void Append(const int payload) ;
  virtual bool Pop(int* const payload_ptr) ;
  virtual bool Slice(int* const payload_ptr) ;

 private:
  int num_elements_;
  // Note that these should be modified
  // to use smart pointers at some point
  struct Node {
    int payload;
    Node* next;
    Node* prev;
    //shared_ptr<Node> next;
    //weak_ptr<Node> prev;
  };
  Node* head_;
  Node* tail_;
};

}  // namespace intlist333

#endif  // LINKEDINTLIST_H_
