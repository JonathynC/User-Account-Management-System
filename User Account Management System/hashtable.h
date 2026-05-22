#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<iostream>
#include<utility>
#include<vector>
#include<list>
#include<algorithm>
#include<functional>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;
namespace cop4530
{
    template<typename K, typename V>
    class HashTable
    {
        private:
        static const unsigned int max_prime = 1301081;
        static const unsigned int default_capacity = 11;
        size_t thesize;
        typedef typename::pair<K,V> pairs;
        typedef typename::list<pairs> lists;
        typedef typename::vector<lists> HTABLE;
        HTABLE htable;
        void makeEmpty();
        void rehash();
        size_t myhash(const K& k)const;
        unsigned long prime_below(unsigned long);
        void setPrimes(vector<unsigned long>&);


        public:
        explicit HashTable(size_t size = 101);
        ~HashTable();
        bool contains(const K & k)const;
        bool match(const pair<K, V> &kv)const;
        bool insert(pair<K,V>& kv);
        bool insert(pair<K,V>&& kv);
        bool remove(const K & k);
        bool load(const char *filename);
        void clear();
        void dump();
        size_t size();
        bool write_to_file(const char *filename);
        bool operator==(const K& otherKey) const;
        bool operator!=(const K& otherKey) const;

    };

    #include "hashtable.hpp"
}
#endif