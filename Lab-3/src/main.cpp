#include "number.h"
#include "utilities.h"
#include <ctime>

int main () {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    const size_t vector_size = 500 + std::rand() % 501;

    std::vector<Number> v1 = step1(vector_size);
    std::vector<Number> v2 = step2(v1);

    auto l1_pair = step3(v1);
    auto  l2_pair = step4(v2);

    step5({v1, l1_pair.second},
          {v2, l2_pair.second});


    step6(l1_pair.first);
    step7(l1_pair.first);

    step8(v1, v2);
    auto l3 = step9(l1_pair.first, l2_pair.first);
    auto l3_ver3 = step10(l1_pair.first, l2_pair.first);

    return 0;
}

