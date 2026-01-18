#include "DynamicString.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cstring>
#include <string>

using std::cout;
using std::endl;
using std::out_of_range;
using std::strcmp;
using std::ostringstream;
using std::stoi;

template <typename T>
void test(int testNum, int& correct, T actual, T expected){

   if(actual == expected){
      correct++;
      cout << "Passed Test " << testNum << endl;
   }
   else{
      cout << "***Failed Test " << testNum << "***" << endl;
      cout << "Actual: " << actual << " Expected: " << expected << endl;
   }
}

void testString(int testNum, int& correct, const char* actual, const char* expected){

   if(actual && expected && strcmp(actual, expected) == 0){
      correct++;
      cout << "Passed Test " << testNum << endl;
   }
   else{
      cout << "***Failed Test " << testNum << "***" << endl;
      if(actual && expected){
         cout << "Actual: " << actual << " Expected: " << expected << endl;
      }
   }
}

int accessor_tests(){

   int testNum  = 1;
   int correct = 0;

   /*Basic initialization and accessor checks*/
   /*Checks len, capacity, c_str, char_at, []*/
   cout << "--------Accessor Tests--------" << endl;
   /*Simple string*/
   DynamicString s2("abc");
   test(testNum++, correct, s2.len(), 3);  // 1
   test(testNum++, correct, s2.char_at(0), 'a'); // 2
   test(testNum++, correct, s2[2], 'c'); // 3
   testString(testNum++, correct, s2.c_str(), "abc"); // 4

   /*Empty String*/
   DynamicString s1;
   test(testNum++, correct, s1.len(), 0); // 5
   testString(testNum++, correct, s1.c_str(), ""); // 6

   /*Long string*/
   DynamicString s3("1234567890qwertyuiopasdfghjklzxcvbnm");
   test(testNum++, correct, s3.len(), 36); // 7
   test(testNum++, correct, s3.char_at(7), '8'); // 8

   /*Symbols*/
   DynamicString s4("abc ;2420* Rocks!ABC");
   test(testNum++, correct, s4.len(), 20); // 9
   test(testNum++, correct, s4.char_at(3), ' '); // 10
   testString(testNum++, correct, s4.c_str(), "abc ;2420* Rocks!ABC"); // 11

   /*Really long string*/
   DynamicString s5("1234567890qwertyuiopasdfghjklzxcvbnmMNBVCXZLKJHGFDSAPOIUYTREabc");
   test(testNum++, correct, s5.len(), 63); // 12
   test(testNum++, correct, s5.char_at(10), 'q'); // 13
   test(testNum++, correct, s5[61], 'b'); // 14
   testString(testNum++, correct, s5.c_str(), "1234567890qwertyuiopasdfghjklzxcvbnmMNBVCXZLKJHGFDSAPOIUYTREabc"); // 15

   return testNum-1 == correct;

}

int output_operator_tests(){

   int testNum  = 1;
   int correct = 0;

   cout << "--------Output Operator Tests--------" << endl;
   DynamicString s1;
   DynamicString s2("abc"); 
   DynamicString s3("1234567890qwertyuiopasdfghjklzxcvbnm");
   DynamicString s4("abc ;2420* Rocks!ABC");
   DynamicString s5("1234567890qwertyuiopasdfghjklzxcvbnmMNBVCXZLKJHGFDSAPOIUYTREabc");
   ostringstream output;
   output << s2;
   testString(testNum++, correct, output.str().c_str(), "abc"); // 1
   output.str("");
   output.clear();
   output << s3;
   testString(testNum++, correct, output.str().c_str(), "1234567890qwertyuiopasdfghjklzxcvbnm"); // 2
   output.str("");
   output.clear();
   output << s4;
   testString(testNum++, correct, output.str().c_str(), "abc ;2420* Rocks!ABC"); // 3
   output.str("");
   output.clear();
   output << s1;
   testString(testNum++, correct, output.str().c_str(), ""); // 4
   output.str("");
   output.clear();
   output << s2 << s3;
   testString(testNum++, correct, output.str().c_str(), "abc1234567890qwertyuiopasdfghjklzxcvbnm"); // 5
   output.str("");
   output.clear();

   return testNum-1 == correct;
}

int comparison_tests(){

   int testNum  = 1;
   int correct = 0;

   DynamicString s1;
   DynamicString s2("abc");
   DynamicString s3("1234567890qwertyuiopasdfghjklzxcvbnm");
   DynamicString s4("abc ;2420* Rocks!ABC");
   DynamicString s5("1234567890qwertyuiopasdfghjklzxcvbnmMNBVCXZLKJHGFDSAPOIUYTREabc");
   cout << "--------Comparison Tests, Prefix--------" << endl;
   /*Prefix*/
   test(testNum++, correct, s4.startsWith(s2), true); // 1
   test(testNum++, correct, s2.startsWith(s4), false); // 2
   test(testNum++, correct, s2.startsWith("ac"), false); // 3
   test(testNum++, correct, s2.startsWith(s2), true); // 4
   /*More Prefix tests*/
   test(testNum++, correct, s5.startsWith(s3), true); // 5
   test(testNum++, correct, s3.startsWith(s5), false); // 6
   test(testNum++, correct, s5.startsWith(s5), true); // 7
   test(testNum++, correct, s3.startsWith("1234"), true); // 8
   test(testNum++, correct, s3.startsWith("4321"), false); // 9
   test(testNum++, correct, s3.startsWith("ABC"), false); // 10
   /*Prefix with empty string*/
   test(testNum++, correct, s1.startsWith(s2), false); // 11
   test(testNum++, correct, s2.startsWith(s1), true); // 12

   /*Suffix*/
   cout << "--------Comparison Tests, Suffix--------" << endl;
   test(testNum++, correct, s5.endsWith(s2), true); // 13
   test(testNum++, correct, s2.endsWith(s5), false); // 14
   test(testNum++, correct, s2.endsWith(s2), true); // 15
   test(testNum++, correct, s2.endsWith("dbc"), false); // 16
   test(testNum++, correct, s2.endsWith("aabc"), false); // 17
   test(testNum++, correct, s3.endsWith("zxcvbnm"), true); // 18
   test(testNum++, correct, s4.endsWith("ABC"), true); // 19
   test(testNum++, correct, s4.endsWith("BBC"), false); // 20
   /*Suffix with empty string*/
   test(testNum++, correct, s1.endsWith(s2), false); // 21
   test(testNum++, correct, s2.endsWith(s1), true); // 22


   /*Comparisions*/
   cout << "--------Comparison Tests, Compare--------" << endl;
   test(testNum++, correct, s2.compare(s2)==0, true); // 23
   test(testNum++, correct, s2.compare("abc")==0, true); // 24
   test(testNum++, correct, s2.compare("bad")<0, true); // 25
   test(testNum++, correct, s2.compare("funny")<0, true); // 26
   test(testNum++, correct, s2.compare("ab")>0, true); // 27
   test(testNum++, correct, s2.compare("bc")<0, true); // 28
   test(testNum++, correct, s3.compare("1234567890qwertyuiopasdfghjklzxcvbnmabc")<0, true); // 29
   test(testNum++, correct, s3.compare("1234567890qwertyuiopasdfghjklzxcvbnm")==0, true); // 30
   test(testNum++, correct, s3.compare("1234567890aqwertyuiopasdfghjkl")>0, true); // 31
   test(testNum++, correct, s3.compare("1234567890abcdefghijkqwertyuiopasdfghjkl")>0, true); // 32
   test(testNum++, correct, s4.compare("ABC ;2420* Rocks!ABC")>0, true); // 33

   test(testNum++, correct, s1.compare(s2)<0, true); // 34
   test(testNum++, correct, s2.compare(s1)>0, true); // 35

   cout << "--------Comparison Tests, Find--------" << endl;
   test(testNum++, correct, s2.find('a'), 0); // 36
   test(testNum++, correct, s2.find('b'), 1); // 37
   test(testNum++, correct, s2.find('c'), 2); // 38
   test(testNum++, correct, s2.find('d'), -1); // 39
   test(testNum++, correct, s5.find('a'), 20); // 40
   test(testNum++, correct, s5.find('d'), 22); // 41
   test(testNum++, correct, s5.find('a', 21), 60); // 42
   test(testNum++, correct, s5.find('d', 23), -1); // 43

   return testNum-1 == correct;
}

int modification_tests(){

   int testNum  = 1;
   int correct = 0;

   DynamicString s1;
   DynamicString s2("abc");
   DynamicString s3("1234567890qwertyuiopasdfghjklzxcvbnm");
   DynamicString s4("abc ;2420* Rocks!ABC");
   DynamicString s5("1234567890qwertyuiopasdfghjklzxcvbnmMNBVCXZLKJHGFDSAPOIUYTREabc");
   cout << "--------Modification Tests, ToUppder--------" << endl;
   /*ToUpper*/
   s1.toUpper();
   test(testNum++, correct, s1.len(), 0); // 1
   testString(testNum++, correct, s1.c_str(), ""); // 2

   s2.toUpper();
   test(testNum++, correct, s2.len(), 3); // 3
   testString(testNum++, correct, s2.c_str(), "ABC"); // 4

   s4.toUpper();
   testString(testNum++, correct, s4.c_str(), "ABC ;2420* ROCKS!ABC"); // 5

   s5.toUpper();
   testString(testNum++, correct, s5.c_str(), "1234567890QWERTYUIOPASDFGHJKLZXCVBNMMNBVCXZLKJHGFDSAPOIUYTREABC"); // 6

   /*ToLower*/
   cout << "--------Modification Tests, ToLower--------" << endl;
   s1.toLower();
   test(testNum++, correct, s1.len(), 0); // 7
   testString(testNum++, correct, s1.c_str(), ""); // 8 

   s4.toLower();
   testString(testNum++, correct, s4.c_str(), "abc ;2420* rocks!abc"); // 9

   s5.toLower();
   testString(testNum++, correct, s5.c_str(), "1234567890qwertyuiopasdfghjklzxcvbnmmnbvcxzlkjhgfdsapoiuytreabc"); // 10

   cout << "--------Modification Tests, Replace--------" << endl;
   s2.replace('B', 'c');
   testString(testNum++, correct, s2.c_str(), "AcC"); // 11
   s2.replace('A', 'a');
   testString(testNum++, correct, s2.c_str(), "acC"); // 12
   s2.replace('C', 'c');
   testString(testNum++, correct, s2.c_str(), "acc"); // 13
   s2.replace('c', 'b');
   testString(testNum++, correct, s2.c_str(), "abb"); // 14
   s2.replace('a', 'b');
   testString(testNum++, correct, s2.c_str(), "bbb"); // 15
   s2.replace('b', 'd');
   testString(testNum++, correct, s2.c_str(), "ddd"); // 16

   /* Assignment */
   cout << "--------Modification Tests, Assignment--------" << endl;
   s2[0] = 'b';
   test(testNum++, correct, s2[0], 'b'); // 17
   s3[3] = 'a';
   test(testNum++, correct, s3.char_at(3), 'a'); // 18
   s4[1] = 'q';
   test(testNum++, correct, s4.char_at(1), 'q'); // 19
   s2[0] = 'a';
   s2[1] = 'b';
   s2[2] = 'c';
   testString(testNum++, correct, s2.c_str(), "abc"); // 20

   return testNum-1 == correct;
}

int deep_copy_tests(){

   int testNum  = 1;
   int correct = 0;

   DynamicString s1;
   DynamicString s2("abc");
   DynamicString s3("1234567890qwertyuiopasdfghjklzxcvbnm");
   DynamicString s4("abc ;2420* Rocks!ABC");
   DynamicString s5("1234567890qwertyuiopasdfghjklzxcvbnmMNBVCXZLKJHGFDSAPOIUYTREabc");
   /* Deep Copy */
   cout << "--------Deep Copy Tests, Copy Constructor--------" << endl;
   DynamicString s6(s2); //Copy Constructor
   test(testNum++, correct, s6.char_at(2), 'c'); // 1
   //Make sure it was a deep copy
   s6[2] = 'e';
   test(testNum++, correct, s6.char_at(2), 'e'); // 2
   test(testNum++, correct, s2.char_at(2), 'c'); // 3

   cout << "--------Deep Copy Tests, Assignment Operator--------" << endl;
   s6 = s3; // Assignment operator
   test(testNum++, correct, s6.char_at(3), '4'); // 4
   //Make sure it was a deep copy
   s6[3] = 'f';
   test(testNum++, correct, s6.char_at(3), 'f'); // 5
   test(testNum++, correct, s3.char_at(3), '4'); // 6

   return testNum-1 == correct;
}

int bounds_checking_tests(){

   int testNum  = 1;
   int correct = 0;

   DynamicString s1;
   DynamicString s2("abc");
   DynamicString s3("1234567890qwertyuiopasdfghjklzxcvbnm");
   DynamicString s4("abc ;2420* Rocks!ABC");
   DynamicString s5("1234567890qwertyuiopasdfghjklzxcvbnmMNBVCXZLKJHGFDSAPOIUYTREabc");
   cout << "---------Additional Tests, Bounds Checking----------" << endl;
   try{
      s1.char_at(1);//out_of_range
      test(testNum++, correct, 0, 1); // 1
   }
   catch(out_of_range){
      test(testNum++, correct, 0, 0); // 1
   }
   try{
      s2.char_at(-1);//out_of_range
      test(testNum++, correct, 0, 1); // 2
   }
   catch(out_of_range){
      test(testNum++, correct, 0, 0); // 2
   }
   try{
      s1[1];//out_of_range
      test(testNum++, correct, 0, 1); // 3
   }
   catch(out_of_range){
      test(testNum++, correct, 0, 0); // 3
   }
   try{
      s3[-2];//out_of_range
      test(testNum++, correct, 0, 1); // 4
   }
   catch(out_of_range){
      test(testNum++, correct, 0, 0); // 4
   }
   try{
      s2[4];//out_of_range
      test(testNum++, correct, 0, 1); // 5
   }
   catch(out_of_range){
      test(testNum++, correct, 0, 0); // 5
   }
   try{
      s2[6];//out_of_range
      test(testNum++, correct, 0, 1); // 6
   }
   catch(out_of_range){
      test(testNum++, correct, 0, 0); // 6
   }

   cout << "---------Additional Tests, Find indexBounds----------" << endl;

   test(testNum++, correct, s1.find('a'), -1); // 7
   test(testNum++, correct, s2.find('a', 3), -1); // 8
   test(testNum++, correct, s2.find('a', 5), -1); // 9
   test(testNum++, correct, s2.find('a', -1), 0); // 10

   return testNum-1 == correct;
}

int main(int argc, char** argv){

   int test = 0;
   int count = 0;

   if(argc > 1){
      test = stoi(argv[1]);
   }
   switch(test){
      case 0:
         if (accessor_tests()) count++;
         if (output_operator_tests()) count++;
         if (comparison_tests()) count++;
         if (modification_tests()) count++;
         if (deep_copy_tests()) count++;
         if (bounds_checking_tests()) count++;
         cout << "Passed " << count << " out of 6 tests";
         return count != 6;
      case 1:
         return !accessor_tests();
      case 2:
         return !output_operator_tests();
      case 3:
         return !comparison_tests();
      case 4:
         return !modification_tests();
      case 5:
         return !deep_copy_tests();
      case 6:
         return !bounds_checking_tests();
   }

}
