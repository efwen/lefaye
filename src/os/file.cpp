#include "lf/os/file.hpp"
#include "lf/log.hpp"

#include <cstdint>

#include <windows.h>

namespace lf::os {

  File::File() :
    file_handle(INVALID_HANDLE_VALUE),
    at_eof(false)
    {}

  File::~File() {
    if(isOpen()) {
      close();
    }
  }

  bool File::open(const char* filename,
      FileOpenMode mode) {
    log::info("opening file \"{}\"", filename);

    file_handle = CreateFile(filename,
        (mode == FileOpenMode::kRead) ? GENERIC_READ : GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if(file_handle == INVALID_HANDLE_VALUE) {
      log::error("Failed to open file! GetLastError() = {}", GetLastError());
      return false;
    }

    return true;
  }

  void File::close() {
    CloseHandle(file_handle);
    file_handle = INVALID_HANDLE_VALUE;
  }

  std::pair<bool, size_t> File::read(void* data, size_t bytes) {
      DWORD bytesRead = 0;

      BOOL success = ReadFile(file_handle, data, bytes, &bytesRead, NULL);
      if(!success) {
        log::error("Failed to read file! GetLastError() = {}", GetLastError());
        return {false, 0};
      }

      if(bytesRead == 0) {
        at_eof = true;
      }

      return {true, bytesRead};
  }

  std::pair<bool, size_t> File::write(const void* data, size_t bytes) const {
    DWORD bytesWritten = 0;

    BOOL success = WriteFile(file_handle, data, bytes, &bytesWritten, NULL);
    if(!success) {
      log::error("Failed to write to file! GetLastError() = {}", GetLastError());
      return {false, 0};
    }

    return {true, bytesWritten};
  }

  void File::flush() const {
    BOOL success = FlushFileBuffers(file_handle);
    if(!success) {
      log::error("Failed to flush file buffer! GetLastError() = {}", GetLastError());
    }
  }

  std::pair<bool, size_t> File::tell() const {
    return seek(0, FileSeekMode::kCurrent);
  }

  std::pair<bool, size_t> File::seek(int32_t seekAmount, FileSeekMode mode) const { //possible add'l direction param
    DWORD position = SetFilePointer(file_handle, seekAmount, NULL, static_cast<uint32_t>(mode));
    if(position == INVALID_SET_FILE_POINTER) {
      log::error("Failed to seek! GetLastError() = {}", GetLastError());
      return {false, position};
    }

    return {true, position};
  }

  std::pair<bool, size_t> File::size() const {
    if(!isOpen()) {
      log::error("Failed to get file size; file not open.");
      return {false, 0};
    }

    return seek(0, FileSeekMode::kEnd);
  }
}
