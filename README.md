# unit.h - Single header unit testing

`unit.h` is a single-header unit testing library. To create a new test simply
use the `TEST` macro:

```c
#include "unit.h"

TEST(example_test) {
    assert(1 + 1 == 3);
}
```

In the `main` function you need to run all tests using the `unit_test_run_all`
function:

```c
int
main(void)
{
    return unit_test_run_all();
}
```

This will run all unit tests registered with the `TEST` macro.
