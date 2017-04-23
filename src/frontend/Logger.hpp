#pragma once

#include <cstdarg>
#include <string>

#include "incaudio.h"
#include "incgraphics.h"

char *strdup(const char *s);

class Logger {
  std::string filename;
  FILE *file;
  Logger(const char *filename);
  ~Logger();
  void Write(const char *fmt, va_list args);
  void WriteFmt(const char *prefix, const char *fmt, va_list args);
  static Logger *instance;
public:
  static void Setup(const char *filename);
  static void Say(const char *fmt, ...);
  static void Info(const char *fmt, ...);
  static void Warning(const char *fmt, ...);
  static void Error(const char *fmt, ...);
  static void MirrorLog(FILE *redir);
  static void Close();
};
