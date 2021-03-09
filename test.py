import os
import subprocess

test_out_dir = "build/lefaye/tests"
build_script_name = "build.bat"

def print_horiz_rule():
  print("----------------------------")

def print_test_suite_header(test_name):
  print("\n")
  print_horiz_rule()
  print("Running " + test_name + "...")
  print_horiz_rule()

def run_all_tests():
  test_list = filter(lambda x: x.endswith(".exe"), os.listdir(test_out_dir))
  test_failures = []

  for test in test_list:
    print_test_suite_header(test)
    result = subprocess.call(test_out_dir + "/" + test)
    if(result != 0):
      test_failures.append(test[:-4])
  
  return test_failures

def main():
  build_result = subprocess.call(build_script_name)
  if(build_result != 0):
    print("Build failed, cannot test!")
    os._exit(1)
  
  failures = run_all_tests()

  print_horiz_rule()
  if(len(failures) == 0):
    print("All tests passed!")
    print_horiz_rule()
  else:
    print("Some test suites failed!")
    print("Failed:")
    for fail in failures:
      print(" *  " + fail)
    print_horiz_rule()

if __name__ == '__main__':
  main()