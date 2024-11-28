#include <she_test.h>

#include <list>

TEST(validation, list_test) {
  std::list<int> list;

  list.emplace_front(1);
  auto e_1 = list.begin();

  list.emplace_front(2);
  auto e_2 = list.begin();

  list.emplace_front(3);
  auto e_3 = list.begin();

  list.emplace_front(4);
  auto e_4 = list.begin();

  list.emplace_front(5);
  auto e_5 = list.begin();

  list.erase(e_3);

  for (auto it = list.begin(); it != list.end(); ++it) {
    if (*it == 5) {
      it = list.erase(it);
    }
    std::cout << *it << std::endl;
  }

  for (const auto e : list) {
    std::cout << e << std::endl;
  }
}