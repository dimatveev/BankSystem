#include "Bank.cpp"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <iostream>

int main() {
  int active_user_id = 0;
  try {
    curlpp::Cleanup myCleanup;

    // Создаем объект Easy
    curlpp::Easy myRequest;

    // Устанавливаем URL
    myRequest.setOpt<curlpp::options::Url>("https://example.com");

    // Выполняем запрос
    myRequest.perform();

    // Получаем ответ
    std::string response;
    myRequest.setOpt<curlpp::options::WriteFunction>([&response](char* ptr, size_t size, size_t nmemb) -> size_t {
      response.append(ptr, size * nmemb);
      return size * nmemb;
    });

    // обработка https запроса
    std::cout << "Response: " << response << std::endl;
    
    // отправка https обработаннного запроса назад
    //...
  }
  catch(const curlpp::LogicError& e)
  {
      std::cout << e.what() << std::endl;
  }
  catch(const curlpp::RuntimeError& e)
  {
      std::cout << e.what() << std::endl;
  }
  return 0;
}