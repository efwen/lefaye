#include <gtest/gtest.h>
#include <lf/os/file.hpp>

#include <cstdio>
#include <windows.h>

using namespace lf::os;


class FileTest : public ::testing::Test {
  protected:
    void SetUp() override {
      fopen_s(&readFile, readFileName, "w");
      fprintf(readFile, "%s", testStr);
      fclose(readFile);

      fopen_s(&writeFile, writeFileName, "w");
      fclose(writeFile);
    }

    void TearDown() override {
      f.close();
      remove(readFileName);
      remove(writeFileName);
    }

    File f;
    FILE* readFile;
    const char* readFileName = "read_file.txt";
    const char* writeFileName = "write_file.txt";
    FILE* writeFile;
    const char* testStr = "The quick brown fox jumps over the lazy dog";
};

TEST_F(FileTest, Open) {
  bool result = f.open("dne.txt", FileOpenMode::kRead);
  ASSERT_EQ(result, false);

  result = f.open(readFileName, FileOpenMode::kRead);
  ASSERT_EQ(result, true);
}

//In kRead mode, read works, but write doesn't
TEST_F(FileTest, OpenModeRead) {
  char buf[16];
  f.open(readFileName, FileOpenMode::kRead);

  auto readResult = f.read(buf, 16);
  EXPECT_EQ(readResult.first, true);
  EXPECT_NE(readResult.second, 0);

  auto writeResult = f.write(buf, 16);
  EXPECT_EQ(writeResult.first, false);
  EXPECT_EQ(writeResult.second, 0);

  f.close();
}

//In kWrite mode, write works, but read doesn't
TEST_F(FileTest, OpenModeWrite) {
  char buf[16];
  f.open(writeFileName, FileOpenMode::kWrite);

  auto readResult = f.read(buf, 16);
  EXPECT_EQ(readResult.first, false);
  EXPECT_EQ(readResult.second, 0);

  auto writeResult = f.write(buf, 16);
  EXPECT_EQ(writeResult.first, true);
  EXPECT_NE(writeResult.second, 0);

  f.close();
}

TEST_F(FileTest, IsOpen) {
  ASSERT_EQ(f.isOpen(), false);
  f.open(readFileName, FileOpenMode::kRead);
  ASSERT_EQ(f.isOpen(), true);
  f.close();
  ASSERT_EQ(f.isOpen(), false);
}

TEST_F(FileTest, ReadHappyPath) {
  char buf[strlen(testStr)+1];

  f.open(readFileName, FileOpenMode::kRead);

  auto result = f.read(buf, sizeof(buf));

  //null-terminate return string
  buf[strlen(testStr)] = '\0';

  ASSERT_EQ(result.first, true);
  ASSERT_EQ(result.second, strlen(testStr));
  ASSERT_STREQ(buf, testStr);
}

//Test write puts the correct bytes to the file
//by writing to a file, reading it back, and
//comparing the result
TEST_F(FileTest, Write) {
  char buf[strlen(testStr) + 1];
  f.open(writeFileName, FileOpenMode::kWrite);

  auto result = f.write(testStr, strlen(testStr));
  ASSERT_EQ(result.first, true);
  f.close();

  f.open(writeFileName, FileOpenMode::kRead); //kRead intentional
  result = f.read(buf, sizeof(buf));
  ASSERT_EQ(result.first, true);

  buf[strlen(testStr)] = '\0';

  ASSERT_STREQ(buf, testStr);
}

TEST_F(FileTest, Tell) {
  f.open(readFileName, FileOpenMode::kRead);

  auto result = f.tell();
  EXPECT_EQ(result.first, true);
  EXPECT_EQ(result.second, 0) << "Files just opened should start at position 0";
}


TEST_F(FileTest, Seek) {
  f.open(readFileName, FileOpenMode::kRead);

  //should start at position 0
  size_t startPos = f.tell().second;
  EXPECT_EQ(startPos, 0);

  //moving left from the beginning should fail
  auto result = f.seek(-1, FileSeekMode::kBegin);
  EXPECT_EQ(result.first, false);
  EXPECT_EQ(result.second, INVALID_SET_FILE_POINTER);

  //Moving left from the end more than the file size should
  //fail
  result = f.seek(-10000, FileSeekMode::kEnd);
  EXPECT_EQ(result.first, false);
  EXPECT_EQ(result.second, INVALID_SET_FILE_POINTER);

  //moving left and right within the bounds of the file
  //from the middle should succeed
  result = f.seek(10, FileSeekMode::kBegin);
  EXPECT_EQ(result.first, true);
  EXPECT_EQ(result.second, 10);

  result = f.seek(5, FileSeekMode::kCurrent);
  EXPECT_EQ(result.first, true);
  EXPECT_EQ(result.second, 15);

  result = f.seek(-5, FileSeekMode::kCurrent);
  EXPECT_EQ(result.first, true);
  EXPECT_EQ(result.second, 10);
}

TEST_F(FileTest, AtEOF) {
  f.open(readFileName, FileOpenMode::kRead);
  ASSERT_EQ(f.atEOF(), false);
  char buf[256];
  f.read(buf, 256);
  ASSERT_EQ(f.atEOF(), false);
  f.read(buf, 10);
  ASSERT_EQ(f.atEOF(), true);
}
