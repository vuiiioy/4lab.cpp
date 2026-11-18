#include <charconv>
#include <clocale>
#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <system_error>

#include "money.h"

bool ReadInt(const std::string& prompt, int* value) {
  while (true) {
    std::cout << prompt;
    std::string line{};
    if (!std::getline(std::cin, line)) {
      return false;
    }

    int parsed_value{0};
    const char* const begin{line.data()};
    const char* const end{begin + line.size()};
    const std::from_chars_result result{
        std::from_chars(begin, end, parsed_value)};
    if (result.ec == std::errc() && result.ptr == end) {
      *value = parsed_value;
      return true;
    }
    std::cout << "Ошибка: введите одно целое число.\n";
  }
}

bool ReadIntRange(const std::string& prompt, int min_value, int max_value,
                  int* value) {
  while (true) {
    int parsed_value{0};
    if (!ReadInt(prompt, &parsed_value)) {
      return false;
    }
    if (parsed_value >= min_value && parsed_value <= max_value) {
      *value = parsed_value;
      return true;
    }
    std::cout << "Ошибка: введите число от " << min_value << " до " << max_value
              << ".\n";
  }
}

bool ReadUnsignedInt(const std::string& prompt, unsigned int* value) {
  while (true) {
    std::cout << prompt;
    std::string line{};
    if (!std::getline(std::cin, line)) {
      return false;
    }

    unsigned int parsed_value{0};
    const char* const begin{line.data()};
    const char* const end{begin + line.size()};
    const std::from_chars_result result{
        std::from_chars(begin, end, parsed_value)};
    if (result.ec == std::errc() && result.ptr == end) {
      *value = parsed_value;
      return true;
    }
    std::cout << "Ошибка: введите целое число от 0 до "
              << std::numeric_limits<unsigned int>::max() << ".\n";
  }
}

bool CreateMoney(Money* money, bool* was_created) {
  *was_created = false;
  std::cout << "\nСоздание объекта Money\n"
               "1. Конструктор без параметров\n"
               "2. Конструктор с рублями\n"
               "3. Конструктор с рублями и копейками\n"
               "0. Назад\n";
  int constructor{0};
  if (!ReadIntRange("Выберите конструктор (0-3): ", 0, 3, &constructor)) {
    return false;
  }
  if (constructor == 0) {
    return true;
  }

  unsigned int rubles{0};
  std::int16_t kopeks{0};
  if (constructor == 2 || constructor == 3) {
    if (!ReadUnsignedInt(
            "Введите количество рублей (от 0 до " +
                std::to_string(std::numeric_limits<unsigned int>::max()) +
                "): ",
            &rubles)) {
      return false;
    }
  }
  if (constructor == 3) {
    unsigned int entered_kopeks{0};
    while (true) {
      if (!ReadUnsignedInt("Введите количество копеек (от 0 до 99): ",
                           &entered_kopeks)) {
        return false;
      }
      if (entered_kopeks <= 99) {
        kopeks = static_cast<std::int16_t>(entered_kopeks);
        break;
      }
      std::cout << "Ошибка: количество копеек должно быть от 0 до 99.\n";
    }
  }

  try {
    if (constructor == 1) {
      *money = Money();
    } else if (constructor == 2) {
      *money = Money(rubles);
    } else {
      *money = Money(rubles, kopeks);
    }
  } catch (const std::invalid_argument& error) {
    std::cout << "Не удалось создать объект: " << error.what() << '\n';
    return true;
  }

  std::cout << "Объект создан: " << *money << '\n'
            << "Свойство rubles: " << money->rubles() << '\n'
            << "Свойство kopeks: " << money->kopeks() << '\n';
  *was_created = true;
  return true;
}

bool RunAddKopeks(const Money& money) {
  unsigned int amount{0};
  if (!ReadUnsignedInt(
          "Сколько копеек добавить (от 0 до " +
              std::to_string(std::numeric_limits<unsigned int>::max()) + "): ",
          &amount)) {
    return false;
  }
  try {
    const Money result{money.AddKopeks(amount)};
    std::cout << "Результат добавления: " << result << '\n';
  } catch (const std::overflow_error& error) {
    std::cout << "Ошибка: " << error.what() << '\n';
  }
  return true;
}

bool RunUnaryOperation(Money* money) {
  std::cout << "\nУнарные операции\n"
               "1. Префиксный ++ (добавить копейку)\n"
               "2. Постфиксный ++ (добавить копейку)\n"
               "3. Префиксный -- (вычесть копейку)\n"
               "4. Постфиксный -- (вычесть копейку)\n"
               "0. Назад\n";
  int operation{0};
  if (!ReadIntRange("Выберите операцию (0-4): ", 0, 4, &operation)) {
    return false;
  }
  if (operation == 0) {
    return true;
  }

  try {
    if (operation == 1) {
      ++(*money);
      std::cout << "После префиксного ++: " << *money << '\n';
    } else if (operation == 2) {
      const Money previous{(*money)++};
      std::cout << "Значение до постфиксного ++: " << previous << '\n'
                << "Значение после операции: " << *money << '\n';
    } else if (operation == 3) {
      --(*money);
      std::cout << "После префиксного --: " << *money << '\n';
    } else {
      const Money previous{(*money)--};
      std::cout << "Значение до постфиксного --: " << previous << '\n'
                << "Значение после операции: " << *money << '\n';
    }
  } catch (const std::underflow_error& error) {
    std::cout << "Ошибка: " << error.what() << '\n';
  } catch (const std::overflow_error& error) {
    std::cout << "Ошибка: " << error.what() << '\n';
  }
  return true;
}

void PrintConversions(const Money& money) {
  std::cout << "Явное преобразование в unsigned int (рубли): "
            << static_cast<unsigned int>(money) << '\n'
            << "Неявное преобразование в double (доля рубля без целых рублей): "
            << static_cast<double>(money) << '\n';
}

bool RunBinaryOperation(const Money& money, bool addition) {
  unsigned int amount{0};
  const std::string operation{addition ? "+" : "-"};
  if (!ReadUnsignedInt(
          "Введите количество копеек для операции " + operation + " (от 0 до " +
              std::to_string(std::numeric_limits<unsigned int>::max()) + "): ",
          &amount)) {
    return false;
  }
  try {
    const Money result{addition ? money + amount : money - amount};
    std::cout << "Результат: " << result << '\n';
  } catch (const std::underflow_error& error) {
    std::cout << "Ошибка: " << error.what() << '\n';
  } catch (const std::overflow_error& error) {
    std::cout << "Ошибка: " << error.what() << '\n';
  }
  return true;
}

int main() {
  std::setlocale(LC_ALL, "Russian");
  Money money{};
  bool money_created{false};

  while (true) {
    std::cout << "\nЛабораторная работа №4. Перегрузка операторов\n"
                 "Вариант 2. Класс Money\n"
                 "1. Задание 1: создать объект / выбрать конструктор\n"
                 "2. Задание 1: добавить копейки (AddKopeks)\n"
                 "3. Задание 2: унарные ++ и --\n"
                 "4. Задание 2: преобразование типов\n"
                 "5. Задание 2: сложить копейки (Money + unsigned int)\n"
                 "6. Задание 2: вычесть копейки (Money - unsigned int)\n"
                 "0. Выход\n";
    int choice{0};
    if (!ReadIntRange("Выберите пункт меню (0-6): ", 0, 6, &choice)) {
      std::cout << "\nВвод завершен. До свидания!\n";
      return 0;
    }
    if (choice == 0) {
      std::cout << "До свидания!\n";
      return 0;
    }
    if (choice == 1) {
      bool was_created{false};
      if (!CreateMoney(&money, &was_created)) {
        std::cout << "\nВвод завершен. До свидания!\n";
        return 0;
      }
      money_created = money_created || was_created;
      continue;
    }
    if (!money_created) {
      std::cout << "Сначала создайте объект Money (пункт меню 1).\n";
      continue;
    }

    if (choice == 2) {
      if (!RunAddKopeks(money)) {
        std::cout << "\nВвод завершен. До свидания!\n";
        return 0;
      }
    } else if (choice == 3) {
      if (!RunUnaryOperation(&money)) {
        std::cout << "\nВвод завершен. До свидания!\n";
        return 0;
      }
    } else if (choice == 4) {
      PrintConversions(money);
    } else if (choice == 5 || choice == 6) {
      if (!RunBinaryOperation(money, choice == 5)) {
        std::cout << "\nВвод завершен. До свидания!\n";
        return 0;
      }
    }
  }
}
