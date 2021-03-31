#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

    void LinkedDequeue::Enqueue(Element e) {
        auto *node = new DoublyNode(e, nullptr, back_);

        if (size_ == 0) {
            front_ = node;
        } else {
            back_->previous = node;
        }
        back_ = node;
        size_++;
    }

    void LinkedDequeue::EnqueueFront(Element e) {

        auto *node = new DoublyNode(e, nullptr, front_);

        if (size_ == 0) {
            front_ = node;
            back_ = node;
        } else {
            front_->next = node;
            front_ = node;
        }
        size_++;
    }

    void LinkedDequeue::Dequeue() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }
        if (size_ == 1) {
            delete front_;
            front_ = nullptr;
            back_ = nullptr;
        } else {
            auto *node = front_->previous;
            delete front_;
            front_ = node;
            node->next = nullptr;
        }
        size_--;
    }

    void LinkedDequeue::DequeueBack() {
        if (size_ == 0) {
            throw std::logic_error("cannot not dequeue from empty queue");
        }
        if (size_ == 1) {
            delete front_;
            front_ = nullptr;
            back_ = nullptr;
        } else {
            auto *node = back_->next;
            delete back_;
            back_ = node;
            node->previous = nullptr;
        }
        size_--;

    }

    void LinkedDequeue::Clear() {
        for (DoublyNode *current_node = front_; current_node != nullptr;) {
            auto delete_node = current_node;
            current_node = current_node->previous;
            delete delete_node;
        }
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
    }

// === РЕАЛИЗОВАНО ===

    LinkedDequeue::~LinkedDequeue() {
        Clear();
    }

    std::optional<Element> LinkedDequeue::front() const {
        return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
    }

    std::optional<Element> LinkedDequeue::back() const {
        return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
    }

    bool LinkedDequeue::IsEmpty() const {
        return size_ == 0;
    }

    int LinkedDequeue::size() const {
        return size_;
    }

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

    std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
        os << "size: " << queue.size_ << '\n';
        for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
            if (current_node == queue.front_) os << "[FRONT] ";
            if (current_node == queue.back_) os << "[BACK] ";
            os << enum2str(current_node->data) << '\n';
        }
        return os;
    }

}  // namespace itis
