#include "../../unit.h"
#include "../factorial.h"

TEST(valid_test)
{
    if (factorial(6) != 720)
        unit_test_fail("Invalid factorial");
}

TEST(invalid_test)
{
    if (factorial(7) != 120)
        unit_test_fail("Invalid factorial for 5.");
}
