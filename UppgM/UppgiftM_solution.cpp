#include <vector>
#include <stdexcept>

template <typename T>
class Stack{
public:
  Stack();
  void push(T value);
  T top() const;
  T pop();
  bool empty() const;
  int size() const;
private:
  std::vector<T> data;
};

template <typename T>
Stack<T>::Stack(){}

template <typename T>
void Stack<T>::push(T value){
  data.push_back(value);
}

template <typename T>
T Stack<T>::top() const{
  if (empty())
    throw std::out_of_range("Tom stack!");
  return data.back();
}

template <typename T>
T Stack<T>::pop(){
  if (empty())
    throw std::out_of_range("Tom stack!");
  T val = data.back();
  data.pop_back();
  return val;
}

template <typename T>
bool Stack<T>::empty() const {
  return data.empty();
}

template <typename T>
int Stack<T>::size() const {
  return data.size();
}
