using namespace cop4530;

//PUBLIC INTERFACE
template<typename K, typename V>
HashTable<K,V>::HashTable(size_t size)
{
  thesize = 0;
  unsigned long temp = prime_below(size);
  if(temp == 0)
    htable.reserve(default_capacity);
  else
    htable.resize(temp);
}
template<typename K, typename V>
HashTable<K,V>::~HashTable()
{
    clear();
}
template<typename K, typename V>
void HashTable<K,V>::clear()
{
    makeEmpty();
}
template<typename K, typename V>
void HashTable<K,V>::dump()
{
  size_t bucket = 0;
  for(const auto& entry : htable)
  {
    cout<<"v["<<bucket++<<"]: ";
    for(const auto& entryData : entry)
    {
        cout<<entryData.first<<' '<<entryData.second;
        if(entry.size() > 1 && entryData != entry.back())
          cout<<": ";
    }
    cout<<endl;
  }
}
template <typename K, typename V>
size_t HashTable<K,V>::size()
{
    return thesize;
}
template<typename K, typename V>
bool HashTable<K,V>::contains(const K & k)const
{
  auto& lists = htable[myhash(k)];
  for (auto& kv : lists) 
  {
    if (kv.first == k) 
      return true;  
  }
  return false;
}
template<typename K, typename V>
bool HashTable<K,V>::match(const pair<K, V> &kv)const
{
  auto & whichTable = htable[myhash(kv.first)];
  return find( begin(whichTable), end(whichTable), kv) != end(whichTable);
}
template <typename K, typename V>
bool HashTable<K,V>::insert(pair<K,V>& kv)
{
  
  auto & lists = htable[myhash(kv.first)];
  if(match(kv))
    return false;

  for(auto & pairs : lists)
  {
    if(pairs.first==kv.first)
    {
      pairs.second = move(kv.second);
      return true;
    }
  }
  lists.push_back(move(kv));
    
  if(++thesize > htable.size())
    rehash();
  return true;
  
}
template <typename K, typename V>
bool HashTable<K,V>::insert(pair<K,V>&& kv)
{
  return insert(kv);
}
template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) 
{
  ofstream file(filename);
  if (!file.is_open()) 
    return false;
  
  for (auto& list : htable) 
    for (auto& kv : list) 
      file << kv.first << " " << kv.second << endl;
  
  file.close();
  return true;
}
template<typename K, typename V>
bool HashTable<K,V>::remove(const K & k)
{
  auto& lists = htable[myhash(k)];
  if(!contains(k))
    return false;
  auto start = lists.begin();
  auto last = lists.end();
  while(start!=last)
  {
    if(start->first==k)
    {
      lists.erase(start);
      --thesize;
      break;
    }
    ++start;
  }
  return true;
}
template<typename K, typename V>
bool HashTable<K,V>::load(const char* filename)
{
  ifstream file(filename);
  if (!file.is_open()) 
    return false;
  
  clear();
  K key;
  V value;
  while (file >> key >> value) 
    insert(make_pair(key, value));
  
  file.close();
  return true;
}

//PRIVATE HELPER FUNCTIONS
template <typename K, typename V>
void HashTable<K,V>::makeEmpty()
{
    thesize = 0;
    for( auto & thisTable : htable )
        thisTable.clear( );
}
template <typename K, typename V>
void HashTable<K,V>::rehash()
{
  cout<<"Rehash function ran!!"<<endl;
  HTABLE oldTable = htable;

  htable.resize( prime_below( 2 * htable.size( ) ) );
  for( auto & thisTable : htable )
    thisTable.clear( );

  thesize = 0;
  for( auto & thisTable : oldTable )
    for( auto & x : thisTable )
      insert(std::move(x));
}
template<typename K, typename V>
size_t HashTable<K,V>::myhash(const K& k)const
{
  static hash<K> hf;
  return hf(k) % htable.size();
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K,V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

