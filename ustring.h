#ifndef USTRING_H_INCLUDED
#define USTRING_H_INCLUDED

#include <iostream>
#include <fstream>

namespace nustr {
    const size_t NPOS = -1;

    class ustring {
    private:
        static const size_t MIN_NUM_POWER_OF_TWO = 2;
        static const size_t NUM_BIT_IN_BYTE = 8; // depends on version
        static const size_t MIN_CAP_TO_RESERVE = 8;
        static const size_t K_HASH = 1; 
        // it doesn't work in some cases if (k-1) % HASH_MOD != 0
        static const size_t HASH_MOD = 1000'000'007;
    public:
        using value_type = char;
        using size_type  = size_t;
        using reference  = value_type&;
        using const_reference = const value_type&;
        using value_pointer   = char*;
        using const_value_pointer = const char*;

    private:
        value_pointer arr = nullptr;
        size_type sz  = 0;
        size_type cap = 0;

    public:
        explicit ustring(size_type n);
        ustring(size_type n, value_type ch);
        ustring(const ustring& other, size_type pos = 0);
        ustring(const ustring& other, size_type pos, size_type count);
        ustring(std::initializer_list<value_type> list);
        ustring(const_value_pointer str);
        ustring(const_value_pointer str, size_type count);
        ustring(const_value_pointer str, size_type pos, size_type count);

        reference       at(size_type index);
        const_reference at(size_type index) const;
        reference front();
        reference back ();
        const_reference front() const;
        const_reference back () const;

        size_type size()     const;
        size_type lenght()   const;
        size_type capacity() const;
        bool empty()         const;
        void reserve(size_type new_cap);
        void resize (size_type count  );
        void shrink_to_fit();

        void clear();
        void push_back(value_type ch);
        void pop_back();
        ustring& insert(size_type pos, value_type ch);
        ustring& insert(size_type pos, value_type ch, size_type count);
        ustring& erase (size_type ind, size_type count);
        ustring& append(size_type count, value_type ch);
        ustring& append(const ustring&      str);
        ustring& append(const_value_pointer str);
        ustring& replace(size_type pos, size_type count, const ustring&      str);
        ustring& replace(size_type pos, size_type count, const_value_pointer str);

        size_type find(const ustring& substr, size_type pos = 0) const;
        size_type find(const_value_pointer s, size_type pos = 0) const;

        bool starts_with(value_type ch)         const;
        bool ends_with  (value_type ch)         const;
        bool starts_with(const_value_pointer s) const;
        bool ends_with  (const_value_pointer s) const;
        int  compare    (const_value_pointer s) const;
        int  compare    (const ustring& str)    const;
        int  compare    (const_value_pointer s, size_type count, size_type pos = 0) const;
        int  compare    (const ustring& str,    size_type count, size_type pos = 0) const;

        void getline(std::istream& fin);
        void getword(std::istream& fin);

        bool operator==(const ustring& other )      const;
        bool operator==(const_value_pointer s)      const;
        const_reference operator[](size_type index) const;
        reference       operator[](size_type index);
        ustring& operator= (const ustring& other);
        ustring& operator+=(const ustring& other);
        ustring& operator= (const_value_pointer s);
        ustring& operator+=(const_value_pointer s);

        void print(std::ostream& fout) const;
        void print(std::ostream& fout, size_type count) const;

        std::weak_ordering operator<=>(const ustring& other) const = default;

    private:
        void swap(ustring& other);
        size_type c_str_len(const_value_pointer str) const;
        size_type next_num_power_of_two(size_type x) const;
        std::pair<size_type, size_type> hash(const_value_pointer begin, const_value_pointer end) const;
        void rehash(size_type& hash, value_type lv, value_type nv, size_type k_hash_pow_len) const;

    public:
        ~ustring();
    };
}

nustr::ustring operator+(const nustr::ustring& a, const nustr::ustring& b);

std::ostream& operator<<(std::ostream& out, const nustr::ustring& str);
std::istream& operator>>(std::istream& in ,       nustr::ustring& str);

#endif // USTRING_H_INCLUDED