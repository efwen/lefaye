#pragma once

#include <cstdint>
#include <utility> //std::pair

#ifdef LF_WIN32
  #include <windows.h>
#endif

namespace lf::os {
  enum class FileOpenMode {
    kRead = 0,
    kWrite
  };

  enum class FileSeekMode {
    kBegin = 0,
    kCurrent,
    kEnd
  };

  class File {
  public:

    File();
    virtual ~File();

    bool open(const char* filename, FileOpenMode mode);
    void close();

    std::pair<bool, size_t> read(void* data, size_t size);
    std::pair<bool, size_t> write(const void* data, size_t size) const;
    std::pair<bool, size_t> tell() const;
    std::pair<bool, size_t> seek(int32_t seekAmount, FileSeekMode mode) const;
    void flush() const;

    bool isOpen() const;
    bool atEOF() const;

  protected:
#ifdef LF_WIN32
    HANDLE file_handle;
#endif
    bool at_eof;
  };

  inline bool File::isOpen() const {
    return file_handle != INVALID_HANDLE_VALUE;
  }

  inline bool File::atEOF() const {
    return at_eof;
  }
}
