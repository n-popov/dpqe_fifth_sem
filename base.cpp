// Параллельное программирование

// Процесс -- аналог задачи для компьтера. Процесс состоит из:
// 1. Машинных инструкций -- .exe файл для Windows
// 2. Места, выделенного для него в памяти.
// ! Один исполнитель может работать над
// одним процессом в один момент времени
// ! Переключение контекста (context switch) всегда имеет место --
// это переключение исполнителя (процессора) с одной задачи (процесса)
// на другую.

// Поток -- аналог процесса, но делит память с другими потоками.
// Всегда один или более потоков относятся к какому-либо процессу.
// Одно ядро процессора часто может исполнять более, чем один поток
// одновременно (обычно два потока).

#include <iostream>
#include <thread> // потоки
#include <utility>

void print_word(const std::string& word) {
    std::cout << "The word is " << word << '!' << std::endl;
}

void print_word_and_return_word(const std::string& word, std::string& result) {
    result = word;
    std::cout << "The word is " << word << '!' << std::endl;
}

std::string return_word(const std::string& word) {
    std::cout << "The word is " << word << '!' << std::endl;
    return word;
}

//int main() {
//    std::thread first_thread(print_word, "FIRST");
//    std::thread second_thread(print_word, "SECOND");
//    // Нельзя получить возвращаемое значение функции!
//    print_word("MAIN");
//    // Если родительский поток завершает исполнение раньше, чем дочерние,
//    // то дочерние умирают (тут же завершаются, обычно некорректно)
//    // ==> их нужно подождать!
//    first_thread.join();
//    second_thread.join();
//    // Мы видим, что каждый раз результат разный.
//    // (Это очень плохо -- поведение не определено).
//    // Дело в том, что происходит конкуренция за
//    // общий ресурс -- глобальный объект std::cout.
//}

//
//int main() {
//    std::string word = "WORD";
//    std::string result;
//    // Передача ссылок в поток
//    std::thread other_thread(print_word_and_return_word,
//                             std::cref(word), std::ref(result));
//    other_thread.join();
//    std::cout << "Returned word is " << result << std::endl;
//
//}

// В C++ есть и второй способ организации параллелизма
// std::future -- фьючерсы (контракты на поставку ресурса к такому-то сроку)
// В C++ -- контракт на выполнение функции.
// Здесь можно в любой момент потребовать результат.

#include <future>

int main() {
    // std::async может работать в двух вариантах:
    // параллельном (запускает выполнение сразу же и независимо)
    // -- std::launch::async
    // и отложенном (запускает выполнение только тогда,
    // когда попросят результат)
    // -- std::launch::deferred
    auto first_future = std::async(std::launch::deferred, return_word, "FIRST");
    auto second_future = std::async(std::launch::deferred, return_word, "SECOND");
    std::cout << "We are in main!" << std::endl;
    std::cout << "The second result is " << second_future.get() << std::endl;
    std::cout << "The first result is " << first_future.get() << std::endl;

}

//class WordHolder {
//public:
//    explicit WordHolder(std::string word) : word(std::move(word)) {}
//
//    void print_word() const {
//        std::cout << "My word is " << word << '!' << std::endl;
//    }
//
//    void set_word(const std::string &word) {
//        WordHolder::word = word;
//    }
//
//private:
//    std::string word;
//};
//
//int main() {
//    WordHolder holder("DPQE");
//    holder.print_word();
//    std::thread method_thread(&WordHolder::set_word, std::ref(holder), "SEPMP");
//    method_thread.join();
//    holder.print_word();
//}