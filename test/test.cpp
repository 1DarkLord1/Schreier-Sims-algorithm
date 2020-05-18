#include "schreier_test.h"
#include "autotest.h"

int main() {
	schreier_test tst;
	tst.run_all_tests();
	Test::show_final_result();
	return 0;
}
