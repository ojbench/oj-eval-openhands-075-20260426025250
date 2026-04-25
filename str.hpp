#include <algorithm>
#include <cstring>
#include <vector>

class str
{
private:
    char *data;
    size_t length;

    void allocate_and_copy(const char *s, size_t len) {
        length = len;
        if (length > 0) {
            data = new char[length + 1];
            std::memcpy(data, s, length);
            data[length] = '\0';
        } else {
            data = nullptr;
        }
    }

public:
    str() : data(nullptr), length(0) {}

    str(const char &c) {
        length = 1;
        data = new char[2];
        data[0] = c;
        data[1] = '\0';
    }

    str(const char *&& s_) {
        if (s_ == nullptr) {
            data = nullptr;
            length = 0;
        } else {
            allocate_and_copy(s_, std::strlen(s_));
        }
    }

    str &operator=(const char *&& s_) {
        if (data != nullptr) {
            delete[] data;
        }
        if (s_ == nullptr) {
            data = nullptr;
            length = 0;
        } else {
            allocate_and_copy(s_, std::strlen(s_));
        }
        return *this;
    }

    str(const str &other) {
        allocate_and_copy(other.data, other.length);
    }

    str &operator=(const str &other) {
        if (this != &other) {
            if (data != nullptr) {
                delete[] data;
            }
            allocate_and_copy(other.data, other.length);
        }
        return *this;
    }

    char &operator[](size_t pos) {
        return data[pos];
    }

    size_t len() const {
        return length;
    }

    str join(const std::vector<str> &strs) const {
        if (strs.empty()) {
            return str();
        }
        
        size_t total_len = 0;
        for (size_t i = 0; i < strs.size(); ++i) {
            total_len += strs[i].length;
            if (i < strs.size() - 1) {
                total_len += length;
            }
        }
        
        str result;
        result.length = total_len;
        if (total_len > 0) {
            result.data = new char[total_len + 1];
            size_t pos = 0;
            for (size_t i = 0; i < strs.size(); ++i) {
                if (strs[i].length > 0) {
                    std::memcpy(result.data + pos, strs[i].data, strs[i].length);
                    pos += strs[i].length;
                }
                if (i < strs.size() - 1 && length > 0) {
                    std::memcpy(result.data + pos, data, length);
                    pos += length;
                }
            }
            result.data[total_len] = '\0';
        } else {
            result.data = nullptr;
        }
        
        return result;
    }

    str slice(size_t l, size_t r) const {
        if (l >= length || l >= r) {
            return str();
        }
        size_t end = (r > length) ? length : r;
        size_t slice_len = end - l;
        
        str result;
        result.allocate_and_copy(data + l, slice_len);
        return result;
    }

    ~str() {
        if (data != nullptr) {
            delete[] data;
        }
    }
};
