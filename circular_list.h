#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace my {

template <typename T>
class circular_list {
private:
    struct node {
        T value;
        node* next;
        node* prev;

        template <typename... Args>
        explicit node(Args&&... args) 
            : value(std::forward<Args>(args)...), next(nullptr), prev(nullptr) {}
    };

    node* head_;
    size_t size_;

public:
    
    circular_list() noexcept : head_(nullptr), size_(0) {}
    
    circular_list(std::initializer_list<T> init) : circular_list() {
        for (const auto& item : init) {
            push_back(item);
        }
    }

    template <typename InputIt>
    circular_list(InputIt first, InputIt last) : circular_list() {
        insert(end(), first, last);
    }

	circular_list(const circular_list& other) : head_(nullptr), size_(0) {
		for (const auto& item : other) {
		    push_back(item);
		}
	}

	circular_list(circular_list&& other) noexcept 
		: head_(other.head_), size_(other.size_) {
		other.head_ = nullptr;
		other.size_ = 0;
	}

	circular_list& operator=(circular_list other) noexcept {
		swap(other);
		return *this;
	}

	~circular_list() noexcept {
		clear();
	}
    
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    class iterator;
    class const_iterator;
    
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    

	void clear() noexcept {
		while (!empty()) {
		    pop_front();
		}
	}
	
    iterator begin() noexcept { return iterator(head_, this); }
    const_iterator begin() const noexcept { return const_iterator(head_, this); }
    const_iterator cbegin() const noexcept { return begin(); }

    iterator end() noexcept { return iterator(nullptr, this); }
    const_iterator end() const noexcept { return const_iterator(nullptr, this); }
    const_iterator cend() const noexcept { return end(); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }

    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crend() const noexcept { return rend(); }

    reference front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head_->value;
    }

    const_reference front() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head_->value;
    }

    reference back() {
        if (empty()) throw std::out_of_range("List is empty");
        return head_->prev->value;
    }

    const_reference back() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head_->prev->value;
    }

    bool empty() const noexcept { return size_ == 0; }
    size_t size() const noexcept { return size_; }
    size_t max_size() const noexcept { return std::numeric_limits<size_t>::max(); }


    iterator insert(const_iterator pos, const T& value) {
        return emplace(pos, value);
    }

    iterator insert(const_iterator pos, T&& value) {
        return emplace(pos, std::move(value));
    }

    template <typename InputIt>
    void insert(const_iterator pos, InputIt first, InputIt last) {
        for (; first != last; ++first) {
            pos = insert(pos, *first);
            ++pos;
        }
    }

    iterator erase(const_iterator pos) {
    	if (empty()) {
			throw std::out_of_range("List is empty");
		}
		if (!pos.node_) {
			throw std::out_of_range("Invalid iterator (null)");
		}
        if (empty() || !pos.node_) {
            throw std::out_of_range("Invalid iterator");
        }
        
        node* to_delete = pos.node_;
        node* next_node = to_delete->next;
        
        if (size_ == 1) {
            head_ = nullptr;
        } else {
            to_delete->prev->next = to_delete->next;
            to_delete->next->prev = to_delete->prev;
            
            if (to_delete == head_) {
                head_ = next_node;
            }
        }
        
        delete to_delete;
        --size_;
        return iterator(next_node, this);
    }

    void push_front(const T& value) {
        emplace_front(value);
    }

    void push_front(T&& value) {
        emplace_front(std::move(value));
    }

    void push_back(const T& value) {
        emplace_back(value);
    }

    void push_back(T&& value) {
        emplace_back(std::move(value));
    }

    void pop_front() {
        if (empty()) throw std::out_of_range("List is empty");
        erase(begin());
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("List is empty");
        erase(--end());
    }

    template <typename... Args>
    reference emplace_front(Args&&... args) {
        node* new_node = new node(std::forward<Args>(args)...);
        
        if (empty()) {
            new_node->next = new_node;
            new_node->prev = new_node;
            head_ = new_node;
        } else {
            new_node->next = head_;
            new_node->prev = head_->prev;
            head_->prev->next = new_node;
            head_->prev = new_node;
            head_ = new_node;
        }
        
        ++size_;
        return new_node->value;
    }

    template <typename... Args>
    reference emplace_back(Args&&... args) {
        node* new_node = new node(std::forward<Args>(args)...);
        
        if (empty()) {
            new_node->next = new_node;
            new_node->prev = new_node;
            head_ = new_node;
        } else {
            new_node->next = head_;
            new_node->prev = head_->prev;
            head_->prev->next = new_node;
            head_->prev = new_node;
        }
        
        ++size_;
        return new_node->value;
    }

    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        node* new_node = new node(std::forward<Args>(args)...);
        
        if (empty()) {
            new_node->next = new_node;
            new_node->prev = new_node;
            head_ = new_node;
        } else {
            node* p = pos.node_ ? pos.node_ : head_;
            new_node->next = p;
            new_node->prev = p->prev;
            p->prev->next = new_node;
            p->prev = new_node;
            
            if (p == head_ && pos == begin()) {
                head_ = new_node;
            }
        }
        
        ++size_;
        return iterator(new_node, this);
    }

    void resize(size_type count) {
        resize(count, T());
    }

    void resize(size_type count, const T& value) {
        while (size_ > count) {
            pop_back();
        }
        while (size_ < count) {
            push_back(value);
        }
    }

    void swap(circular_list& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(size_, other.size_);
    }

    void remove(const T& value) {
        remove_if([&value](const T& v) { return v == value; });
    }

    template <typename UnaryPredicate>
    void remove_if(UnaryPredicate p) {
        for (auto it = begin(); it != end();) {
            if (p(*it)) {
                it = erase(it);
            } else {
                ++it;
            }
        }
    }

    void reverse() noexcept {
        if (size_ < 2) return;
        
        node* current = head_;
        do {
            std::swap(current->next, current->prev);
            current = current->prev;
        } while (current != head_);
        
        head_ = head_->next;
    }

    void unique() {
        unique(std::equal_to<T>());
    }

    template <typename BinaryPredicate>
    void unique(BinaryPredicate p) {
        if (size_ < 2) return;
        
        auto it = begin();
        auto next = it;
        ++next;
        
        while (next != end()) {
            if (p(*it, *next)) {
                next = erase(next);
            } else {
                it = next;
                ++next;
            }
        }
    }

    void sort() {
        sort(std::less<T>());
    }

    template <typename Compare>
    void sort(Compare comp) {
        if (size_ < 2) return;
        
        std::vector<T> elements;
        elements.reserve(size_);
        
        for (const auto& item : *this) {
            elements.push_back(item);
        }
        
        std::sort(elements.begin(), elements.end(), comp);
        
        clear();
        for (const auto& item : elements) {
            push_back(item);
        }
    }
};

template <typename T>
class circular_list<T>::iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator() : node_(nullptr), list_(nullptr) {}
    iterator(node* n, const circular_list* l) : node_(n), list_(l) {}

	reference operator*() const { 
		if (!node_) throw std::out_of_range("Iterator not dereferenceable");
		return node_->value; 
	}
    
    pointer operator->() const { return &node_->value; }

	iterator& operator++() {
		if (!node_) throw std::out_of_range("Iterator not dereferenceable");
		node_ = node_->next;
		if (node_ == list_->head_) { 
		    node_ = nullptr;
		}
		return *this;
	}

    iterator operator++(int) {
        iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    iterator& operator--() {
        if (!node_) {
            if (!list_ || !list_->head_) throw std::out_of_range("Iterator not decrementable");
            node_ = list_->head_->prev;
        } else {
            node_ = node_->prev;
        }
        return *this;
    }

    iterator operator--(int) {
        iterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const iterator& other) const { 
        return node_ == other.node_; 
    }
    
	bool operator!=(const iterator& other) const { 
		return node_ != other.node_; 
	}

    operator const_iterator() const {
        return const_iterator(node_, list_);
    }

private:
    node* node_;
    const circular_list* list_;
    friend class circular_list;
};

template <typename T>
class circular_list<T>::const_iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    const_iterator() : node_(nullptr), list_(nullptr) {}
    const_iterator(node* n, const circular_list* l) : node_(n), list_(l) {}
    const_iterator(iterator it) : node_(it.node_), list_(it.list_) {}

reference operator*() const { 
    if (!node_) throw std::out_of_range("Iterator not dereferenceable");
    return node_->value; 
}
    
    pointer operator->() const { return &node_->value; }

	const_iterator& operator++() {
		if (!node_) throw std::out_of_range("Iterator not dereferenceable");
		node_ = node_->next;
		if (node_ == list_->head_) {
		    node_ = nullptr;
		}
		return *this;
	}

    const_iterator operator++(int) {
        const_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    const_iterator& operator--() {
        if (!node_) {
            if (!list_ || !list_->head_) throw std::out_of_range("Iterator not decrementable");
            node_ = list_->head_->prev;
        } else {
            node_ = node_->prev;
        }
        return *this;
    }

    const_iterator operator--(int) {
        const_iterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const const_iterator& other) const { 
        return node_ == other.node_; 
    }
    
    bool operator!=(const const_iterator& other) const { 
        return !(*this == other); 
    }

private:
    node* node_;
    const circular_list* list_;
    friend class circular_list;
};

} 

#endif 
