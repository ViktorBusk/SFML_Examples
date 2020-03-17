//#include "utils.hpp"
//
//using namespace std;
//
//int main()
//{
//	//Init random
//	srand(time(NULL));
//
//	float n;
//	std::cout << "N: ";
//	std::cin >> n;
//	std::cout << "" << std::endl;
//
//	float taylorP = 0;
//
//	for (float i = 1; i <= n; i++)
//	{
//		int nom = 1;
//		float denom = pow(i, 2);
//		taylorP += (nom / denom);
//	}
//	float PI = sqrt(6 * taylorP);
//
//	std::cout << PI << std::endl;
//
//	system("PAUSE");
//	return 0;
//}
