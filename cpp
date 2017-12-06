
//vector:
auto c = vector<int>{1,2,3,4,5};

c = vector<int>{begin(c), end(c)};
//c is initialized to the range from begin to end
//so c contains 1,2,3,4,5.

//using random access iterators
c= vector<int>{begin(c)+1, end(c)-1};
//c now contains 2,3,4

c= vector<int>(10, 123);
//c contains 10 elements each initialized to 123
for(auto e: c)
{
  ASSERT(e == 123);
}

//iterating:
for(auto e:c)
{
  cout << e << endl;
}
//OR
for(auto i = 0; i != c.size(); i++)
{
  cout << c[i] << endl;
}
//OR
for (auto i = begin(c); i != end(c); i++)
{
  cout << *i << endl;
}
//OR reverse order
for(auto i = rbeging(c); i != rend(c); i++)
{
  cout << *i << endl;
}

//emplace is used to construct element in place at location without move
//insert element in back
c.emplace_back(6);
//insert in front
c.emplace(begin(c), 0);

c.size() //return size
c.empty() //check if empty
c.clear() //removes all elements
reverse(begin(c), end(c)); //reverse the elements

list:
doubly linked list

auto c = list<int>{};
ASSERT(c.empty());

c= list<int>{1,2,3,4,5};
ASSERT(!c.empty());
ASSERT(c.size()==5);

c = list<int>{begin(c), end(c)};
c is initialized to the range from begin to end
so c contains 1,2,3,4,5.

//random access iterators cannot be used for linked list
c = list<int>{ begin(c)+1, end(c)-1}; //will not work
//biderectional iterators will work here
c = list<int>{ ++begin(c), --end(c)}; //will work
//c contains 2,3,4 , removes first and last element


//initializing a list using random access iterators of vector
auto v = vector<int>{1,2,3};
c= list<int>(begin(v)+1, end(c)-1};
//c contains 2
ASSERT(c.size() == 1);
ASSERT(c.front() ==2 );

//create a list with 10 elements initialized to zero
c = list<int>(10);
ASSERT(c.size() == 10);
for(auto e: c)
{
  ASSERT(e == 0);
}

//creating a list initialized with 123
c = list<int>(10, 123);
for(auto e: c)
{
  ASSERT(e == 123);
}

//remove odd numbers in a list
c.remove_if([] (int val)
{
  return val & 1;
});

//set, sorted array of keys
auto c = set<int> {};
//OR
auto c = set<int, less<int>> {}; //less<int> is the compare function

c = set<int>{1,2,5,4,3};

c.insert(0);

auto result = c.emplace(6); //returns an iterator pointing to the inserted OR existing element
// the iterator above consists of pair, first points to the element, second points to bool(element was inserted or not)
ASSERT(*result.first == 6); //element is 6
ASSERT(result.second); //element was inserted

result = c.emplace(6); //call emplace again
ASSERT(*result.first == 6); //element is 6
ASSERT(!result.second); //element was not inserted as it already exists

//removing elements
auto next = c.erase(begin(c));  //next should point to the next element after the removed one
ASSERT(*next == 1);

ASSERT(1 == c.erase(6)); //1 is the mumber of elements removed
ASSERT(0 == c.erase(123)); //no element was removed

auto i = c.find(3);
ASSERT(*i == 3); //found 3
ASSERT(end(c) == c.find(123)); //if not found it returns the end of sequence

//range
auto upper = c.upper_bound(3);// return iterator pointing to the first element greater than the key value 3
ASSERT(*upper == 4);

auto lower = c.lower_bound(3); //returns iterator to the element that is not less than key value
ASSERT(*lower == 3); //if 3 did not exist then it would be 4

auto range = c.equal_range(3); //return a pair of iterators
ASSERT(range.first == lower);
ASSERT(range.second == upper);

//partitioning the set
//first < 3
for(auto i = begin(c); i != lower; i++)
{
  cout << *i << endl;
}
//next > 3
for(auto i = upper; i != end(c); i ++)
{
  cout << *i << endl;
}

//map key-value pair sorted

auto c = map<int, double> {};
c = map<int, double> { {1,1.1}, {4,4.1}, {2,2.1}, {3, 3.1}, {5, 5.1}};

ASSERT(c[4] == 4.1);
c[6] = 6.1;

auto v = c[7]; //key 7 does not exist so is inserted with a default value
ASSERT(c[7] == 0.0);

auto result = c.insert(make_pair(8, 8.1));
ASSERT(result.second); //element was inserted

result = c.emplace(9, 9.1);

auto i = c.find(6);
ASSERT(i->first == 6); //key
ASSERT(i->second == 6.1); //value

c.erase(i); //erase element pointed to be iterator
c.erase(7); //erase using key

for( auto & v: c)
{
  cout << "key=" << v.first << " value=" << v.second << endl;
}

//multimap
auto c = multimap<int, double> { {1,1.1}, {2, 2.1}, {2, 2.2}, {3, 3.1}};

auto result = c.emplace(2,2.3);
ASSERT(result->first == 2);
ASSERT(result->second == 2.3);

for( auto & v: c)
{
  cout << "key=" << v.first << " value=" << v.second << endl;
}
