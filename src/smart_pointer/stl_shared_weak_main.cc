#include <iostream>
#include <memory>
#include <string>

struct Person {
  std::string first_name;
  std::string last_name;
  int age;

  Person() { std::cout << "Person constructor" << std::endl; }
  ~Person() { std::cout << "Person destructor" << std::endl; }
  std::string FullName() { return first_name + ' ' + last_name; }
};

std::weak_ptr<Person> MakeWeakPerson() {
  // Construct a std::shared_ptr
  std::shared_ptr<Person> myPerson(new Person());

  myPerson->first_name = "Ari";
  myPerson->last_name = "Saif";

  std::weak_ptr<Person> weakPerson(myPerson);

  if (auto temp_shared_person =
          weakPerson
              .lock()) {  // Has to be copied into a shared_ptr before usage
    std::cout << "temp_shared_person->FullName(): "
              << temp_shared_person->FullName() << std::endl;
  } else {
    std::cout << "temp_shared_person is expired" << std::endl;
  }

  // Return a std::weak_ptr to the Person
  return weakPerson;
}

int main() {
  // Weak pointer going out of scope before shared pointer
  {
    std::shared_ptr<Person> p_shared1(new Person());

    // Can call functions just like a regular pointer!
    p_shared1->first_name = "Ari";
    p_shared1->last_name = "Saif";

    std::cout << "p_shared1->FullName(): " << p_shared1->FullName()
              << std::endl;

    std::cout << "p_shared1.use_count(): " << p_shared1.use_count()
              << std::endl;
    std::shared_ptr<Person> p_shared2 = p_shared1;

    p_shared2->first_name = "ari";

    std::cout << "p_shared2.use_count(): " << p_shared2.use_count()
              << std::endl;

    std::cout << "p_shared1->FullName(): " << p_shared1->FullName()
              << std::endl;

    {
      std::weak_ptr<Person> weakPerson(p_shared1);

      // Has to be copied into a shared_ptr before usage
      if (auto temp_shared_person = weakPerson.lock()) {
        std::cout << "temp_shared_person->FullName(): "
                  << temp_shared_person->FullName() << std::endl;
        std::cout << "temp_shared_person.use_count(): "
                  << temp_shared_person.use_count() << std::endl;
      } else {
        std::cout << "temp_shared_person is expired" << std::endl;
      }
    }

    std::cout << "p_shared1->FullName(): " << p_shared1->FullName()
              << std::endl;
    std::cout << "p_shared2.use_count(): " << p_shared2.use_count()
              << std::endl;
  }

  std::cout << "------------------------------------------" << std::endl;
  // Shared pointer going out of scope before weak pointer
  {
    std::weak_ptr<Person> weakPerson(MakeWeakPerson());

    // Has to be copied into a shared_ptr before usage
    if (auto temp_shared_person = weakPerson.lock()) {
      std::cout << "temp_shared_person->FullName(): "
                << temp_shared_person->FullName() << std::endl;
    } else {
      std::cout << "temp_shared_person is expired" << std::endl;
    }
  }
  return 0;
}
