---

This report was generated for **lmshen2** using **5712e5c0bc2b1de80663dc3b545dad3270e3b344** (latest commit as of **October 26th 2020, 1:35 am**)

---




## Score: 0/55 (0.00%)


### ✓ - [0/0] - Output from `make`

- **Points**: 0 / 0


```
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c cs225/HSLAPixel.cpp -o .objs/cs225/HSLAPixel.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c cs225/PNG.cpp -o .objs/cs225/PNG.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c cs225/lodepng/lodepng.cpp -o .objs/cs225/lodepng/lodepng.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c tests/tests.cpp -o .objs/tests/tests.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c cs225/catch/catchmain.cpp -o .objs/cs225/catch/catchmain.o
clang++ .objs/cs225/HSLAPixel.o .objs/cs225/PNG.o .objs/cs225/lodepng/lodepng.o .objs/tests/tests.o .objs/cs225/catch/catchmain.o  -std=c++1y -stdlib=libc++ -lc++abi -o test

```


### ✗ - [0/5] - test_insertion_idx_emp

- **Points**: 0 / 5


```
Original: 0 == insertion_idx(v, 0)
Expanded: 0 == 5
```


### ✗ - [0/5] - test_insertion_idx_small

- **Points**: 0 / 5


```
Original: 0 == insertion_idx(data, -1)
Expanded: 0 == 5
```


### ✗ - [0/5] - test_btree3_small

- **Points**: 0 / 5


```
Original: key_val.second == ret
Expanded: 5 == 0
```


### ✗ - [0/5] - test_btree3_large_seq

- **Points**: 0 / 5


```
Original: key_val.second == ret
Expanded: 1 == 0
```


### ✗ - [0/5] - test_btree3_large_rand

- **Points**: 0 / 5


```
Original: key_val.second == ret
Expanded: 1326571764 (0x4f11e0f4) == 0
```


### ✗ - [0/5] - test_btree64_large_seq

- **Points**: 0 / 5


```
Original: key_val.second == ret
Expanded: 1 == 0
```


### ✗ - [0/5] - test_btree64_large_rand

- **Points**: 0 / 5


```
Original: key_val.second == ret
Expanded: 1326571764 (0x4f11e0f4) == 0
```


### ✗ - [0/5] - test_btree128_med_rand

- **Points**: 0 / 5


```
Original: key_val.second == ret
Expanded: 1326571764 (0x4f11e0f4) == 0
```


### ✗ - [0/5] - test_btree256_med_rand

- **Points**: 0 / 5


```
Original: key_val.second == ret
Expanded: 782206782 (0x2e9f873e) == 0
```


### ✗ - [0/5] - test_btree12_double

- **Points**: 0 / 5


```
Original: key_val.second == ret
Expanded: 3.4f == 0.0f
```


### ✗ - [0/5] - test_btree12_strings

- **Points**: 0 / 5


```
Original: key_val.second == ret
Expanded: "skye" == ""
```


---