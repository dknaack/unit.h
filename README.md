# unit.h - Single header unit testing

`unit.h` is a single-header unit testing library. To create a new test simply
use the `TEST` macro:

```c
#include "unit.h"

TEST(example_test) {
    if (1 + 1 != 2)
        unit_test_fail("1 + 1 != 2");
}
```

In the `main` function you need to run all tests using the `unit_test_run_all`
function:

```c
int
main(void)
{
    return unit_tests_run();
}
```

This will run all unit tests registered with the `TEST` macro.
