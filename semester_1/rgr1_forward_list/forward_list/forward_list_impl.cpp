#include "forward_list_impl.h"

ForwardList::ForwardList() : head_(nullptr), size_(0) {}

ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr), size_(0) {
    if (rhs.head_ == nullptr) return;

    head_ = new Node(rhs.head_->value_);
    Node* currentNew = head_;
    Node* currentOld = rhs.head_->next_;

    while (currentOld != nullptr) {
        currentNew->next_ = new Node(currentOld->value_);
        currentNew = currentNew->next_;
        currentOld = currentOld->next_;
    }
    size_ = rhs.size_;
}

ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr), size_(0) {
    for (size_t i = 0; i < count; ++i) {
        PushFront(value);
    }
}

ForwardList::ForwardList(std::initializer_list<int32_t> init) : head_(nullptr), size_(0) {
    for (auto it = std::rbegin(init); it != std::rend(init); ++it) {
        PushFront(*it);
    }
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this != &rhs) {
        Clear();
        Node* current_rhs = rhs.head_;
        Node* last_added = nullptr;
        while (current_rhs != nullptr) {
            Node* newNode = new Node(current_rhs->value_);
            if (head_ == nullptr) {
                head_ = newNode;
            } else {
                last_added->next_ = newNode;
            }
            last_added = newNode;
            current_rhs = current_rhs->next_;
            ++size_;
        }
    }
    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

void ForwardList::PushFront(int32_t value) {
    Node* newNode = new Node(value);
    newNode->next_ = head_;
    head_ = newNode;
    ++size_;
}

void ForwardList::PopFront() {
    if (head_ != nullptr) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
        --size_;
    }
}

void ForwardList::Remove(int32_t value) {
    Node* current = head_;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->value_ == value) {
            Node* to_delete = current;
            if (prev == nullptr) { 
                head_ = current->next_;
                current = head_;
            } else {
                prev->next_ = current->next_;
                current = prev->next_;
            }
            delete to_delete;
            --size_;
        } else {
            prev = current;
            current = current->next_;
        }
    }
}

void ForwardList::Clear() {
    while (head_ != nullptr) {
        PopFront();
    }
}

bool ForwardList::FindByValue(int32_t value) {
    Node* current = head_;
    while (current != nullptr) {
        if (current->value_ == value)
            return true;
        current = current->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = head_;
    while (current != nullptr) {
        out << current->value_ << (current->next_ ? " " : "");
        current = current->next_;
    }
}

int32_t ForwardList::Front() const {
    if (head_ != nullptr)
        return head_->value_;
    return -1;  
}

size_t ForwardList::Size() const {
    return size_;
}

