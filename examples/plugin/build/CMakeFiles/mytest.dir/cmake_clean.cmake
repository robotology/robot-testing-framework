FILE(REMOVE_RECURSE
  "CMakeFiles/mytest.dir/MyTest.cpp.o"
  "libmytest.pdb"
  "libmytest.so"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/mytest.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
