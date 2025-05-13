/*
* 0 -- pop
* 1 -- push
* 2 -- mod
*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include "timer.h"
#include <avl_tree.h>

int arr[100] = { 287, 110, 299, 967, 51, 151, 693, 729, 483, 79,
	93, 542, 298, 716, 49, 212, 773, 237, 327, 199,
	535, 783, 219, 735, 494, 431, 374, 641, 223, 45,
	733, 623, 382, 818, 883, 709, 60, 1, 660, 911,
	629, 908, 895, 447, 845, 114, 13, 201, 979, 884,
	660, 979, 629, 508, 219, 254, 803, 486, 891, 919,
	352, 667, 619, 644, 59, 481, 319, 513, 289, 98,
	800, 804, 605, 942, 126, 15, 911, 738, 391, 833,
	878, 353, 892, 235, 414, 204, 705, 769, 739, 716,
	62, 648, 953, 547, 756, 692, 622, 113, 849, 276
};

int main() {
	while (1) {
		avl<int, 100> ol([](const int& a, const int& b) -> bool {
			return a < b;
			});
		ScopedTimer timer("100 pushes");
		__pragma(loop(count(100)))
			for (size_t i = 0; i < 100; i++) {
				ol << arr[i];
			}
	}

	/*const char* testcase_dir = "testcases";
	for (const auto& testcase_file : std::filesystem::directory_iterator(testcase_dir)) {
		std::ifstream testcase(testcase_file.path());
		uint32_t op_cnt;
		int op_type;
		float op_value;
		if (testcase.is_open()) {
			std::cout << "testing using" << testcase_file.path() << '\n';
			testcase >> op_cnt;
			for (int i = 0; i < op_cnt; i++) {
				testcase >> op_type;
				switch (op_type) {

				}
			}
		}
	}*/

	return 0;
}