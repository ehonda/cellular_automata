#pragma once

#include "gmpxx.h"

#include "gtest/gtest.h"

namespace cellular_automata_test {

inline void EXPECT_EQ_MPZ(mpz_class a, mpz_class b) {
	EXPECT_TRUE(a == b) << "Comparison of two mpz_classes failed:\na\t=\t" << a.get_str() << "\nb\t=\t" << b.get_str();
}

}
