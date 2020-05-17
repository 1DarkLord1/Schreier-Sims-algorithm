#include "shraer_test.h"
#include "autotest.h"

int main() {
	shraer_test tst;
	tst.run_all_tests();
	Test::show_final_result();
	return 0;
}
