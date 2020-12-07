---

This report was generated for **lmshen2** using **706bb891bfc841183d28f84cccd9519086bf9fd2** (latest commit as of **December 7th 2020, 6:00 am**)

---




## Score: 0/10 (0.00%)


### ✓ - [0/0] - Output from `make`

- **Points**: 0 / 0


```
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c graph.cpp -o .objs/graph.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c NetworkFlow.cpp -o .objs/NetworkFlow.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c cs225/HSLAPixel.cpp -o .objs/cs225/HSLAPixel.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c cs225/PNG.cpp -o .objs/cs225/PNG.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c cs225/lodepng/lodepng.cpp -o .objs/cs225/lodepng/lodepng.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c tests/unit_tests.cpp -o .objs/tests/unit_tests.o
clang++  -std=c++1y -stdlib=libc++ -O0 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -MMD -MP -g -c cs225/catch/catchmain.cpp -o .objs/cs225/catch/catchmain.o
clang++ .objs/graph.o .objs/NetworkFlow.o .objs/cs225/HSLAPixel.o .objs/cs225/PNG.o .objs/cs225/lodepng/lodepng.o .objs/tests/unit_tests.o .objs/cs225/catch/catchmain.o  -std=c++1y -stdlib=libc++ -lc++abi -o test

```


### ✗ - [0/1] - Graph a - 4 -> b  has flow of 4.

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 4
Expanded: 0 == 4
```


### ✗ - [0/1] - Testing flow through two pipes - secret test

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 4
Expanded: 0 == 4
```


### ✗ - [0/1] - Graph a - 10 -> b  has flow of 10.

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 10
Expanded: 0 == 10
```


### ✗ - [0/1] - Testing flow through two pipes

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 8
Expanded: 0 == 8
```


### ✗ - [0/1] - Testing simple backflow - secret

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 37
Expanded: 11948384 (0xb65160) == 37
```


### ✗ - [0/1] - Testing simple backflow

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 20
Expanded: 13326488 (0xcb5898) == 20
```


### ✗ - [0/1] - Testing full pipe usage - secret

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 20
Expanded: 15866528 (0xf21aa0) == 20
```


### ✗ - [0/1] - Testing full pipe usage

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 10
Expanded: 14891680 (0xe33aa0) == 10
```


### ✗ - [0/1] - Testing 3 x 3 plumbing - secret

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 50
Expanded: 40479616 (0x269ab80) == 50
```


### ✗ - [0/1] - Testing 3 x 3 plumbing

- **Points**: 0 / 1


```
Original: n.getMaxFlow() == 8
Expanded: 30825344 (0x1d65b80) == 8
```


---