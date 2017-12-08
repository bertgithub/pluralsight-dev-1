
Big O:
O(1) // always execute at the same time regardless of input size
O(N) //algorithm whose performance is propotional to the size of input data set. e.g iterating using a for loop
O(N**2) // n-squared an alogrithm whose performance is propotional to the square of the input data set, e.g nested for loop algos
O(N**3  N**4...) //deeper nesting
O(2**N) //algo whose growth doubles with each extra input data e.g. fibonacci numbers
O(log N) // binary search, split the data and search

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
for(auto i = rbegin(c); i != rend(c); i++)
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

// inserting using generate_n algorithm
int i = 0;
vector<int> v = {};
std::generate_n(back_inserter(v), 5, [&](){ return i++; });
IS SAME AS
for(i =0; i < 5; i++) { v.push_back(i); }

// counting how many times value 3 appears  the vector
int mycount = std::count(begin(v), end(v), 3);

// erasing an item in an iterator
for(auto it = begin(v); it != end(v); it++)
{
   if(*it == 3)
      v.erase(it); //deleting the item invalidates the iterator, it cannot do a it++ to continue on
}
// erasing using remove_if
auto endv2 = std::remove_if(begin(v), end(v), [](int n){ return n == 3; });
//endv2 now points to an iterator at the end of the modified vector after removing all the elements with 3
v.erase(endv2, end(v)); //will erase the excess elements
//e.g v orig has 0,1,2,3,4,0,1,2,3,4
// after remove_if v has 0,1,2,4,0,1,2,4,3,4 last 2 elems are left over from the orig vector
//v.erase now erases these excess elements and the result will be 0,1,2,4,0,1,2,4
OR
v.erase(std::remove_if(begin(v), end(v), [](int n) { return n == 3; }), end(v));


move semantics:
//moving is much faster than copying
//move constructor:
Resource(Resource&& r) : name(move(r.name)) {}
//move assignment operator
Resource& operator=(Resource&& r)
{
  if(this != &r){name = move(r.name); r.name.clear();}
  return *this;
}

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


string:
auto s = string { "This is a string"};
s = string(s, 4, 3); //"is "
ASSERT(s == "is ");

auto pos = s.find('s');
auto sstr = s.substr(pos);
ASSERT(sstr == "s is a string");

auto trim(string const &s) ->string
{
  auto front = find_if_not(begin(s), end(s), isspace);
  auto back = find_if_not(rbegin(s), rend(s), isspace);
  //back returns reverse iterator
  //back.base() return the 
  
  return string{ front, back.base() };
}


  //regex:
  auto s = string { "call 877-808-2321 to reach me" };
  auto r = regex { R"((\d{3})-(\d{3})-(\d{3}))"};
  
  auto m = smatch{};
  ASSERT(m.empty()); //empty match results
  //call search
  ASSERT(regex_search(s, m, r)); //regex_search returns true/false if match exists
  OR
  ASSERT(!m.empty());
  
for( auto &sub : m)
{
  cout << sub.length() << &*sub.first << endl;
}
//will return 877-808-2321 first
//then 877
//then 808
//then 2321

auto output = m.format(R"($`<a href="link..."> $1 $2 $3</a?$`)");

lambda:
using namespace std;
vector<int> v{1,2,3,4,5};
vector<int> doubleV(v.size());
int factor = 2;
transform(begin(v), end(v), begin(doubleV),
  [=](int i){ i * factor; }
); //end transform

functor:
A functor is pretty much just a class which defines the operator().

struct add_x
{
  add_x(int x): x(x) {}
  int operator()(int y) { return x+y; }
private:
  int x;
};

add_x add42(42); // struct is init to 42
int i = add42(8); //call to add 8
ASSERT(i == 50);

memory management:
Forcing a class to be allocated on heap:
class Person2
{
 //constructor, copy const and destructor are private
 Person2(){};
 Person2(const Person2& _){}
 ~Person2() {}
 
 int ref_count;
public:
  //use static factory method to allocate on heap
  static Person2 * create()
  {
   auto *p = new Person2;
   return p;
  }
  void add_ref() { ref_count++; }
  void release()
  {
    if(--ref_count == 0)
      delete this;
  }
};

rvalue reference:
int meaningOfLife() { return 42;}
void move_rvalue()
{
  int a =0;
  int &&y = meaningOfLife();
  
  Address book[100];
  book[55] = Address("Paris"); //two copies exists here
  book[55] = move(Address("Paris")); //only one copy exist
  
  auto swap = [] (int&a, int&b)
  {
    int tmp{a};
    a= b;
    b = tmp;
  };
  
  int x= 2, z = 5;
  swap (x, z);
  
  auto betterSwap = [] (int&a, int& b)
  {
    int tmp(move(a));
    a = move(b);
    b = move(tmp);
    //there are no multiple allocations here
  }
  
}

unique_ptr:

unique_ptr<Address> create_address(string const& city)
{
  return unique_ptr<Address>(new Address(city));
  OR
  return make_unique<Address>(city);
}


void test()
{
   auto a = create_address("Paris");
   //a gets destroyed automatically
   
   auto v(a); //does not work, no operator() for unique
   auto v = a; //does not work, no copy for unique
   
   auto v = move(a); //a gives up ownership of a
   if(a)
   {
     //will not come here as a no longer owns the ptr
   }
   
   Address *ptr = v.get();  //get the pointer
   
   Address *ptr = v.release();// release it ownership to ptr
   Address *p;
   ptr.reset(); //delete the owned object
   OR
   ptr.reset(p); //releases its ownership to p
   
}

auto GetHen() -> unique_ptr<Hen>
{
  return make_unique<Hen>(2,3.9f);
}
void test()
{
   auto hen = GetHen(); //a unique pointer is created
} // the hen object is destroyed.

auto UpdateHen(unique_ptr<Hen>(hen) -> unique_ptr<Hen)
{
  hen->eggs += 1.4;
  return hen;
}

void test()
{
   auto hen = GetHen(); //a unique pointer is created
   
   hen = UpdateHen(hen); // will not compile, no copy is allowed.
   hen = Updatehen(move(hen)); //ok
} // the hen object is destroyed.

unique_ptr_deleter:
  std::cout << "Custom deleter demo\n";
  std::ofstream("demo.txt") << 'x'; // prepare the file to read
  {
      std::unique_ptr<std::FILE, decltype(&std::fclose)> fp(std::fopen("demo.txt", "r"),
                                                            &std::fclose);
      if(fp) // fopen could have failed; in which case fp holds a null pointer
        std::cout << (char)std::fgetc(fp.get()) << '\n';
  } // fclose() called here, but only if FILE* is not a null pointer
    // (that is, if fopen succeeded)
 
  std::cout << "Custom lambda-expression deleter demo\n";
  {
    std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr)
        {
            std::cout << "destroying from a custom deleter...\n";
            delete ptr;
        });  // p owns D
    p->bar();
  } // the lambda above is called and D is destroyed
 

shared_ptr:

auto sp = shared_ptr<int> {};
ASSERT(!sp); //it is not a valid pointer
ASSERT(sp.use_count() == 0);
sp = make_shared<int>(123);
ASSERT(sp); //it is a valid pointer now
ASSERT(sp.use_count() == 1);
ASSERT(sp.unique()); //owned by one only.

auto sp2 = sp;
ASSERT(sp.use_count() == 2);
ASSERT(!sp.unique()); //NOT owned by one only.
ASSERT(sp2.use_count() == 2);
ASSERT(!sp2.unique()); //NOT owned by one only.

int copy = *sp;
int *ref = *sp;
int *ptr = sp.get();
ASSERT(sp.get() == sp2.get());
OR
ASSERT(sp == sp2);

shared_ptr  points to control block(contains: strong ref count, weak ref count, deleter)
shared_ptr also points to the object

weak_ptr:
are great for breaking loops in data structures.
they are used to refer to objects but only access it if the object exists,
without preventing the object from being deleted.

it always starts with a shared pointer.
auto sp = make_shared<int>(123);
auto wp = weak_ptr<int>{sp}; //init with a shared pointer

ASSERT(!wp.expired()); //there is an outstanding shared pointer so it has not expired.
ASSERT(wp.use_count() == 1); //NOTE this is the strong ref count of the shared pointer

The above two methods are no guarantee that you have access to the shared pointer before you get a hold of it.

if(auto locked = wp.lock())
{
  //lock method returns a new shared pointer with a strong reference count to the managed object
  you can use the shared object here
}

sp = nullptr; //reset the original shared pointer
ASSERT(wp.expired()); //the weak pointer is now expired
ASSERT(wp.use_count() == 0); 

if(auto locked = wp.lock())
{
  //lock method returns an empty ptr so will not come here
  you cannot use the shared object here
}
else
{
  wp.reset(); //frees the control block, this is necessary
}

class Person3
{
public:
  shared_ptr<Address> address;
  
  Person3(string const& city)
  {
     address = make_shared<Address>(city);
  }
  ~Person3()
  {
      //no need to destroy address, it is a smart pointer.
  }
}

void test()
{
   shared_ptr<Address> a;
   {
      Person3 p("Paris");
      a = p.address; //ref count is increased
   } //p is destroyed, a ref_count is decremented  
} //a is destroyed here

variadic template:

template<typename T, typename ...U>
auto sum(T y, U ...u) ->decltype(t + sum(u...))
{
   return t + sum(u...);
}
// what if there is only one arg? the above would not work.
need to declare for one arg
template<typename T>
T sum(T t) { return t; }

void variadic()
{
   cout << sum(1,2,3,4) << endl;
}

...u is called a parameter pack
a parameter pack can be expanded OR counted.

A variadic class template
template<class ... types> struct Tuple {};
e.g:
Tuple<> t0; //no args
Tuple<int> t1; //1 arg
Tuple<int, float> t2; //2 args

A variadic function template
template<class ... types> void f(Types ... args);
f(); //no args
f(1); //1 arg
f(2,1.0); //2 args

template<typename Stream, typename... cols>
class Printer
{
  public:
    void output_line(const Columns&... cols);
};

void output_line(const Columns&... cols)
{
  write_line(validate(columns)...); //the compiler expands the parameter pack here and apsses each to validate function
}
//will get expanded to
void output_line(const int& col1, const double& col2, const string& col3)
{
  write_line(validate(col1), validate(col2), validate(col3));
}

//working recursively with parameter packs
template<typename value, typename ...values>
void write_line(const value& val, const values&... values) const
{
  write_column(val, _sep);
  write_line(values...);
}

//for last  value
template<typename value>
void write_line(const value& val) const 
{
  write_column(val, "\n");
}

//Another example of traversing template parameter types
template<typename... types>  //allow zero parameters
struct TupleSize;

template<typename Head, typename... types>  //traverse types
struct TupleSize<head, Tail...>
{
  static const size_t value = sizeof(Head) + TupleSize<Tail...>::value;
};

template<> struct TupleSize<>  //end recursion
{
  static const size_t value = 0;
};

Tuple<>::value; //0
Tuple<int, double, char>::value; //13 on a 32 bit platform

metaprogramming:
factorial

template<int n> struct Factorial
{
  enum {value = n * Factorial<n-1>::value};
};

//now define the specific for factorial 0
templatee <> struct Factorial<0>
{
   enum { value = 1 };
};

void metaprogramming()
{
  int x = Factorial<4>::value; //x=24 this value is already available prior to run time
  int y = Factorial<0>::value;
}
