#pragma once

#include <vector>

template <typename T> class Data;

template <typename T>
class Sprite {
  T data;
public:
  Sprite(T &data);
  ~Sprite();
  operator T&();
  void Clear();
  T &operator [](size_t i);
  static T &Access(size_t i);
  static std::vector <Sprite <T> > storage;
  static size_t Add(T &data);
  static void Pop();
  static void Cleanup();
};
