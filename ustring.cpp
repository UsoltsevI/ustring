#include <iostream>
#include <cstring>
#include <exception>
#include "ustring.h"

using namespace nustr;

ustring::ustring(size_type n): arr(new value_type[n + 1]), sz(n), cap(n + 1) {
    arr[n] = '\0';
}

ustring::ustring(size_type n, value_type ch): ustring(n) {
    std::fill(arr, arr + sz, ch);
}

ustring::ustring(const ustring& other, size_type pos)
        : ustring(other.sz - pos) {
    memcpy(arr, &other.arr[pos], other.sz - pos);
}

ustring::ustring(const ustring& other, size_type pos, size_type count)
        : ustring(count) {
    memcpy(arr, &other.arr[pos], sz);
}

ustring::ustring(std::initializer_list<value_type> list)
        : arr(new value_type[list.size() + 1])
        , sz (list.size())
        , cap(list.size() + 1) {
    std::copy(list.begin(), list.end(), arr);
    arr[sz] = '\0';
}

ustring::ustring(const_value_pointer s)
        : ustring(c_str_len(s)) {
    for (size_type i = 0; i <= sz; i++) {
        arr[i] = s[i];
    }
}

ustring::ustring(const_value_pointer str, size_type count)
        : ustring(count) {
    for (size_type i = 0; i < sz; i++) {
        arr[i] = str[i];
    }
}

ustring::ustring(const_value_pointer str, size_type pos, size_type count)
        : ustring(count) {
    memcpy(arr, &str[pos], count);
}

ustring::size_type ustring::c_str_len(const_value_pointer s) const {
    size_type len = 0;

    while (s[len] != '\0') {
        len++;
    }
    
    return len;
}

ustring::reference ustring::at(size_type index) {
    return arr[index];
}

ustring::const_reference ustring::at(size_type index) const {
    return arr[index];
}

ustring::reference ustring::front() {
    return arr[0];
}

ustring::const_reference ustring::front() const {
    return arr[0];
}

ustring::reference ustring::back() {
    return arr[sz - 1];
}

ustring::const_reference ustring::back() const {
    return arr[sz - 1];
}

bool ustring::empty() const {
    return (sz > 0 ? true : false);
}

ustring::size_type ustring::size() const {
    return sz;
}

ustring::size_type ustring::lenght() const {
    return sz;
}

ustring::size_type ustring::capacity() const {
    return cap;
}

void ustring::reserve(size_type new_cap) {
    if (new_cap > sz) {
        value_type *new_arr = new value_type[new_cap];
        memcpy(new_arr, arr, sz);
        delete[] arr;
        arr = new_arr;
        cap = new_cap;
        arr[sz] = '\0';
    }
}

void ustring::shrink_to_fit() {
    if (cap > sz + 1) {
        value_type *new_arr = new value_type[sz + 1];
        memcpy(new_arr, arr, sz);
        delete[] arr;
        arr = new_arr;
        cap = sz + 1;
        arr[sz] = '\0';
    }
}

void ustring::clear() {
    delete[] arr;
    sz  = 0;
    cap = 0;
}

ustring& ustring::insert(size_type pos, value_type ch) {
    if (pos >= sz) {
        sz = pos + 1;
        reserve(sz + 1);
    }

    arr[pos] = ch;

    return *this;
}

ustring& ustring::insert(size_type pos, value_type ch, size_type count) {
    if (pos + count >= sz) {
        sz = pos + count;
        reserve(sz + 1);
    }

    for (size_type i = pos; i < pos + count; i++) {
        arr[i] = ch; 
    }

    return *this;
}

ustring& ustring::erase(size_type ind, size_type count) {
    if (ind + count >= sz) {
        sz = ind + count;
        reserve(sz + 1);
    }

    memmove(arr + ind, arr + ind + count, sz - (ind + count));

    return *this;
}

void ustring::push_back(value_type ch) {
    if (cap == 0) {
        this->reserve(MIN_CAP_TO_RESERVE);
    }

    if (sz >= cap - 1) {
        this->reserve(cap * 2);
    }

    arr[sz] = ch;
    sz += 1;
    arr[sz] = '\0';
}

void ustring::pop_back() {
    if (sz == 0) {
        return;
    }

    arr[--sz] = '\0';
}

ustring& ustring::append(size_type count, value_type ch) {
    if (sz + count >= cap) {
        this->reserve(cap + count + 1);
    }

    for (size_type i = sz; i < sz + count; i++) {
        arr[i] = ch;
    }

    sz += count;
    arr[sz] = '\0';
    
    return *this;
}

ustring& ustring::append(const ustring& str) {
    if (sz + str.sz >= cap) {
        reserve(sz + str.sz + 1);
    }

    memcpy(arr + sz, str.arr, str.sz);

    sz += str.sz;
    arr[sz] = '\0';

    return *this;
}

ustring& ustring::append(const_value_pointer str) {
    size_type len = c_str_len(str);

    if (sz + len >= cap) {
        reserve(sz + len + 1);
    }

    memcpy(arr + sz, str, len);

    sz += len;
    arr[sz] = '\0';

    return *this;
}

ustring& ustring::replace(size_type pos, size_type count, const ustring& str) {
    if (pos + count >= sz) {
        sz = pos + count;
        reserve(sz + 1);
    }

    for (size_type i = 0; i < count; i++) {
        arr[pos + i] = str.arr[i];
    }

    return *this;
}

ustring& ustring::replace(size_type pos, size_type count, const_value_pointer str) {
    size_type len = c_str_len(str);

    if (pos + count >= sz) {
        sz = pos + count;
        reserve(sz + 1);
    }

    for (size_type i = 0; i < count; i++) {
        arr[pos + i] = str[i];
    }

    return *this;
}

void ustring::resize(size_type count) {
    value_type* new_arr = new value_type[count];

    memcpy(new_arr, arr, std::min(count, sz)); 

    delete[] arr;
    arr = new_arr;
    sz  = count;
    cap = sz + 1;
    arr[sz] = '\0';
}

ustring::size_type ustring::find(const ustring& substr, size_type pos) const {
    if (substr.sz + pos > sz) {
        return NPOS;
    }

    size_type curhash, subhash, k_hash_pow_len;

    std::pair<size_type, size_type> rethash = hash(substr.arr, &substr.arr[substr.sz]);
    subhash = rethash.first;

    rethash = hash(&arr[pos], &arr[pos + substr.sz]);
    curhash = rethash.first;
    k_hash_pow_len = rethash.second;

    for (size_type i = pos; i <= sz - substr.sz; i++) {
        if (subhash == curhash) {
            if (!compare(substr, substr.sz, i)) {
                return i;
            }
        }

        rehash(curhash, arr[i], arr[i + substr.sz], k_hash_pow_len);
    }

    return NPOS;
}

ustring::size_type ustring::find(const_value_pointer s, size_type pos) const {
    size_type len = c_str_len(s);

    if (len + pos > sz) {
        return NPOS;
    }

    size_type curhash, subhash, k_hash_pow_len;

    std::pair<size_type, size_type> rethash = hash(s, s + len);
    subhash = rethash.first;

    rethash = hash(&arr[pos], &arr[pos + len]);
    curhash = rethash.first;
    k_hash_pow_len = rethash.second;

    for (size_type i = pos; i <= sz - len; i++) {
        if (subhash == curhash) {
            if (!compare(s, len, i)) {
                return i;
            }
        }

        rehash(curhash, arr[i], arr[i + len], k_hash_pow_len);
    }

    return NPOS;
}

void ustring::rehash(size_type& hash, value_type lv, 
        value_type nv, size_type k_hash_pow_len) const {
    hash -= lv;
    hash /= K_HASH;
    hash += nv * k_hash_pow_len;
}

std::pair<ustring::size_type, ustring::size_type> 
ustring::hash(const_value_pointer begin, const_value_pointer end) const {
    size_type hash = 0;
    size_type k    = 1;
    size_type k_hash_pow_len = k;

    while (begin < end) {
        hash = (hash + *begin * k) % HASH_MOD;
        k_hash_pow_len = k;
        k = (k * K_HASH);
        begin++;
    }

    return {hash, k_hash_pow_len};
}

int ustring::compare(const ustring& str) const {
    for (size_type i = 0; i <= sz && i <= str.sz; i++) {
        if (arr[i] != str.arr[i]) {
            return arr[i] - str.arr[i];
        }
    }

    return 0;
}

int ustring::compare(const_value_pointer s) const {
    for (size_type i = 0; i <= sz; i++) {
        if (arr[i] != s[i]) {
            return arr[i] - s[i];
        }
    }

    return 0;
}

int ustring::compare (const_value_pointer s, size_type count, size_type pos) const {
    for (size_type i = 0; i < count; i++) {
        if (arr[pos + i] != s[i]) {
            return arr[pos + i] - s[i];
        }
    }

    return 0;
}

int ustring::compare (const ustring& str, size_type count, size_type pos) const {
    for (size_type i = 0; i < count; i++) {
        if (arr[pos + i] != str.arr[i]) {
            return arr[pos + i] - str.arr[i];
        }
    }

    return 0;
}

bool ustring::starts_with(value_type ch) const {
    if (sz > 0 && arr[0] == ch) {
        return true;
    }

    return false;
}

bool ustring::starts_with(const_value_pointer s) const {
    size_type len = c_str_len(s);

    if (len <= sz) {
        for (size_type i = 0; i < len; i++) {
            if (arr[i] != s[i]) {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool ustring::ends_with(value_type ch) const {
    if (cap > 0 && arr[sz] == ch) {
        return true;
    }

    return false;
}

bool ustring::ends_with(const_value_pointer s) const {
    size_type len = c_str_len(s);

    if (len < sz) {
        for (size_type i = len; i + 1 > 0; i--) {
            if (arr[sz - i] != s[len - i]) {
                return false;
            }
        }

        return true;
    }

    return false;
}

void ustring::getline(std::fstream& fin) {
    size_type i = 0;
    value_type rd = 0;

    fin >> rd;

    if (rd != '\n' && cap == 0) {
        reserve(MIN_CAP_TO_RESERVE);
    }

    while (rd != '\n' && rd != EOF) {
        if (i >= cap) {
            reserve(cap * 2);
        }

        arr[i++] = rd;
        fin >> rd;
    }

    sz = i;
    arr[sz] = '\0';
}

bool ustring::operator==(const ustring& other) const {
    if (!compare(other)) {
        return true;
    }

    return false;
}

bool ustring::operator==(const_value_pointer s) const {
    if (!compare(s)) {
        return true;
    }

    return false;
}

ustring::const_reference ustring::operator[](size_type index) const {
    return arr[index];
}

ustring::reference ustring::operator[](size_type index) {
    return arr[index];
}

ustring& ustring::operator=(const ustring& other) {
    ustring copy = other;
    swap(copy);
    return *this;
}

ustring& ustring::operator=(const_value_pointer s) {
    size_type len = c_str_len(s);

    delete[] arr;

    sz  = len;
    cap = len + 1;
    arr = new value_type[cap];

    memcpy(arr, s, sz);
    arr[sz] = '\0';

    return *this;
}

ustring& ustring::operator+=(const ustring& other) {
    append(other);
    return *this;
}

ustring& ustring::operator+=(const_value_pointer s) {
    append(s);
    return *this;
}

void ustring::print(std::ostream& fout) const {
    for (size_type i = 0; i < sz; i++) {
        fout << arr[i];
    }
}

void ustring::print(std::ostream& fout, size_type count) const {
    for (size_type i = 0; i < count; i++) {
        fout << arr[i];
    }
}

void ustring::swap(ustring& other) {
    std::swap(arr, other.arr);
    std::swap(sz , other.sz );
    std::swap(cap, other.cap);
}

ustring::size_type ustring::next_num_power_of_two(size_type x) const {
    if (x == 0) {
        return MIN_NUM_POWER_OF_TWO;
    }

    size_type res = 0;
    size_type pos = sizeof(size_type) * NUM_BIT_IN_BYTE;

    while (((x >> pos) & 1u) == 0)
        pos--;

    res = res | (1u << (pos + 1));

    return res;
}

ustring::~ustring() {
    delete[] arr;
}
