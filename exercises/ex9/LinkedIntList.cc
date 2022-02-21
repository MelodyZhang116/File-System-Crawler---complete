#include "LinkedIntList.h"
using std::shared_ptr;
using std::weak_ptr;
namespace intlist333 {
LinkedIntList::LinkedIntList(){
    num_elements_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
}
void LinkedIntList::Push(const int payload) {
    Node* node = new Node();
    node->prev = nullptr;
    node->payload = payload;
    if (num_elements_ == 0) {
        node->next = nullptr;
        head_ = node; //
        tail_ = node; //
        //shared_ptr<Node> head_(node);
        //shared_ptr<Node> tail_(node);
    } else {
        //head_->prev = shared_ptr<Node>(node);
        head_->prev = node; //
        node->next = head_;
        head_ = node;
    }
    num_elements_++;
}
void LinkedIntList::Append(const int payload) {
    Node* node = new Node;
    //shared_ptr<Node> ptr;
    //node->next = ptr;
    node -> next = nullptr; //
    node->payload = payload;
    if (num_elements_ == 0) {
        //node->prev = ptr;
        node->prev = nullptr;
        head_ = node;
        tail_ = node;
        //shared_ptr<Node> head_(node);
        //shared_ptr<Node> tail_(node);
    } else {
        tail_->next = node;
        node->prev = tail_;
        tail_ = node;
    }
    num_elements_++;
}
bool LinkedIntList::Pop(int* const payload_ptr) {
    if (num_elements_ == 0) {
        return false;
    } else if (num_elements_ == 1){
        *payload_ptr = head_->payload;
        num_elements_--;
    } else {
        *payload_ptr = head_->payload;
        head_ = head_->next;
        num_elements_--;
    }
    return true;
}
bool LinkedIntList::Slice(int* const payload_ptr) {
    if (num_elements_ == 0) {
        return false;
    } else if (num_elements_ == 1){
        *payload_ptr = tail_->payload;
        num_elements_--;
    } else {
        *payload_ptr = tail_->payload;
        tail_ = tail_->prev;
        num_elements_--;
    }
    return true;
}
}   // namespace intlist333
