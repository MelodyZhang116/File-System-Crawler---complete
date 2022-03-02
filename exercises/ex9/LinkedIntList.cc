#include "LinkedIntList.h"
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
namespace intlist333 {

void LinkedIntList::Push(const int payload) {
    //shared_ptr<Node> node(new Node(payload)); 
    auto node = make_shared<Node>();
    node->payload = payload;
    // node->prev = nullptr;
    node->payload = payload;
    if (num_elements_ == 0) {
        // node->next = nullptr;
        // head_ = node; //
        // tail_ = node; //
        // shared_ptr<Node> head_(node);
        // shared_ptr<Node> tail_(node);
        // tail_->payload = payload;
        start = node;
    } else {
        head_->prev = node;
        //head_->prev = node; //
        node->next = shared_ptr<Node>(head_);
        head_ = shared_ptr<Node>(node);
    }
    end = nd;
    num_elements_++;
}
void LinkedIntList::Append(const int payload) {
    Node* node = new Node;
    //shared_ptr<Node> ptr;
    //node->next = ptr;
    // node -> next = nullptr; //
    node->payload = payload;
    if (num_elements_ == 0) {
        //node->prev = ptr;
        // node->prev = nullptr;
        //head_ = node;
        // tail_ = node;
        shared_ptr<Node> head_(node);
        shared_ptr<Node> tail_(node);
    } else {
        tail_->next = shared_ptr<Node>(node);
        node->prev = tail_;
        tail_ = shared_ptr<Node>(node);
    }
    num_elements_++;
}
bool LinkedIntList::Pop(int* const payload_ptr) {
    if (num_elements_ == 0) {
        return false;
    } else if (num_elements_ == 1){
        *payload_ptr = head_->payload;
        shared_ptr<Node> ptr;
        head_ = ptr;
        tail_ = ptr;
        num_elements_--;
    } else {
        *payload_ptr = head_->payload;
        head_->next->prev = nullptr;
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
        head_ = nullptr;
        tail_ = nullptr;
        num_elements_--;
    } else {
        *payload_ptr = tail_->payload;
        tail_->prev->next = nullptr;
        tail_ = tail_->prev;
        num_elements_--;
    }
    return true;
}
}   // namespace intlist333