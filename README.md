cstp是一个C++模板库，其功能有两个：  
1、于编译期实现字符串拼接。  
2、于编译期实现整型转字符串。  

examples:

字符串拼接
```cpp
#include "cstring.h"

constexpr char str1[] = "abc";
constexpr char str2[] = "def";

//cstr1.size() is 3
//cstr1.data() is {'a', 'b', 'c'}
constexpr auto cstr1 = cstp::to_cstr(str1);

//cstr2.size() is 6
//cstr2.data() is {'a', 'b', 'c', 'd', 'e', 'f'}
constexpr auto cstr2 = cstr1 + str2;

//cstr3.size() is 4
//cstr3.data() is {'a', 'b', 'c', '1', '2', '\0'}
//cout << cstr3.data(); print "abc12"
constexpr auto cstr3 = cstp::cstring<3>('a', 'b', 'c') + 
                       cstp::to_cstr("12") +
                       cstp::cstring<1>('\0');

```


整型转字符串

```cpp
#include "cint.h"

constexpr int num1 = 100;
constexpr int num2 = -123;

//cstr1.size() is 3
//cstr1.data() is {'1', '0', '0'}
constexpr auto cstr1 = cstp::csint<num1>().cstr();

//cstr2.size() is 4
//cstr2.data() is {'-', '1', '2', '3'}
constexpr auto cstr2 = cstp::csint<num2>().cstr();

//cstr3.size() is 3
//cstr3.data() is {'9', '9', '9'}
constexpr auto cstr3 = cstp::cuint<999ULL>().cstr();
```

cstp::csint能够支持的范围等同于int64_t所能表示的范围[-2^63, 2^63-1]，  
cstp::cuint能够支持的范围等同于uint64_t所能表示的范围[0, 2^64]。