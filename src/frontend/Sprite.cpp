#include "Sprite.hpp"
#include "Debug.hpp"
#include "ColorBuffer.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "Shape.hpp"

template <typename T> std::vector <Sprite<T> > Sprite<T>::storage;

template <typename T>
Sprite<T>::Sprite(T &data):
  data(data)
{}

template <typename T>
Sprite<T>::~Sprite()
{}

template <typename T>
Sprite<T>::operator T&() {
  return data;
}

template <typename T>
void Sprite<T>::Clear() {
  data.Clear();
}

template <>
void Sprite<Shape *>::Clear() {
  data->Clear();
  delete data;
}

template <typename T>
T &Sprite<T>::Access(size_t i) {
  return storage[i];
}

template <typename T>
T &Sprite<T>::operator[](size_t i) {
  return storage[i];
}

template <typename T>
size_t Sprite<T>::Add(T &data) {
  storage.push_back(Sprite<T>(data));
  return storage.size() - 1;
}

template <typename T>
void Sprite<T>::Pop(){
  storage.back().Clear();
  storage.pop_back();
}

template <typename T>
void Sprite<T>::Cleanup() {
  while(!storage.empty())
    Pop();
}

template class Sprite<Font>;
template class Sprite<gl::Texture>;
template class Sprite<gl::ColorBuffer>;
template class Sprite<Shape *>;
