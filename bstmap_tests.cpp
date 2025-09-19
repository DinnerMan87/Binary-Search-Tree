#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

#include "bstmap.h"

using namespace std;
using namespace testing;

namespace {

class Random {
 private:
  static mt19937 rng;

 public:
  static void seed(int s) {
    Random::rng.seed(s);
  }

  /**
   * Generate a random integer in the range 0 (inclusive) to `max` (exclusive)
   */
  static int randInt(int max) {
    // Even though mt19937 is standardized, STL distributions aren't!
    // So, unfortunately, even though this is biased, we're forced to
    // do something like this. Technically uint32_fast_t isn't...
    // totally consistent across platforms? But within reason it works.
    return rng() % (max + 1);
  }
};

std::mt19937 Random::rng;

TEST(BSTMapCore, CoreTests) {
  BSTMap mapa = BSTMap<int,int>();
  EXPECT_THAT(mapa.empty(), Eq(true));
  EXPECT_THAT(mapa.size(), Eq(0));

  map<int,int> reference;
  for(int i = 0; i < 5; i++){
    mapa.insert(i,i);
    reference[i] = i;
    EXPECT_THAT(mapa.at(i), Eq(reference[i]))
    << "Map at key " << i << ": " << mapa.at(i);
  }
  EXPECT_THAT(mapa.empty(), Eq(false));
  EXPECT_THAT(mapa.size(), Eq(5));
  ASSERT_THROW(mapa.at(-1),out_of_range)
  << "Map at key -1 is out of range" << endl;

  EXPECT_THAT(mapa.contains(0), Eq(true))
  << "Map doesn't contain 0 when it should" << endl;
  EXPECT_THAT(mapa.contains(3), Eq(true))
  << "Contains function is running false for 3 when it should be true" << endl;
  EXPECT_THAT(mapa.contains(-1), Eq(false))
  << "Contains function is running true for -1 when it should be false" << endl;

  mapa.insert(0,-1);
  EXPECT_THAT(mapa.at(0), Eq(reference[0]))
  << "Map at key 0 is " << mapa.at(0);
  
  /*stringstream s;
  s << "```text" << endl << "0: 0" << endl << "1: 1" << endl << "2: 2" << endl << "3: 3" << endl << "4: 4" << endl << "```" << endl;
  EXPECT_THAT(mapa.to_string(),StrEq(""))
  << "Yours: " << mapa.to_string() << " vs " << "Correct: " << s << endl; */

  mapa.clear();
  EXPECT_THAT(mapa.empty(), Eq(true));
  EXPECT_THAT(mapa.size(), Eq(0));
  ASSERT_THROW(mapa.at(0),out_of_range)
  << "Map at key -1 is out of range" << endl;

  BSTMap mp1 = BSTMap<int,int>();
  mp1.insert(0,0);
  mp1.insert(1,1);
  mp1.insert(2,2);
  BSTMap mp2 = mp1;
  for(int i = 0; i < 3; i++){ 
    EXPECT_THAT(mp2.at(i), Eq(i))
    << "data at " << i << " is \"" << mp2.at(i) << "\"" << endl;
  }
  mp2.clear();
  int mpsize = mp1.size();
  EXPECT_THAT(mpsize, Eq(3))
  << "size=\"" << mpsize << "\"" << endl;
  int isEmpty = mp1.empty();
  EXPECT_THAT(isEmpty, Eq(false))
  << "isEmpty=\"" << isEmpty << "\"" << endl;
  mpsize = mp2.size();
  EXPECT_THAT(mpsize, Eq(0))
  << "size=\"" << mpsize << "\"" << endl;
  isEmpty = mp2.empty();
  EXPECT_THAT(isEmpty, Eq(true))
  << "isEmpty=\"" << isEmpty << "\"" << endl;

  BSTMap<int,int> mp3 = mp2;
  mpsize = mp3.size();
  EXPECT_THAT(mpsize, Eq(0))
  << "size=\"" << mpsize << "\"" << endl;
  isEmpty = mp3.empty();
  EXPECT_THAT(isEmpty, Eq(true))
  << "isEmpty=\"" << isEmpty << "\"" << endl;

  mp3.insert(0,0);
  mp3.insert(1,1);
  mp3.insert(2,2);
  mp3 = mp2;
  mpsize = mp3.size();
  EXPECT_THAT(mpsize, Eq(0))
  << "size=\"" << mpsize << "\"" << endl;
  isEmpty = mp3.empty();
  EXPECT_THAT(isEmpty, Eq(true))
  << "isEmpty=\"" << isEmpty << "\"" << endl;

  mp2 = mp1;
  for(int i = 0; i < 3; i++){ 
    EXPECT_THAT(mp2.at(i), Eq(i))
    << "data at " << i << " is \"" << mp2.at(i) << "\"" << endl;
  }
  isEmpty = mp2.empty();
  EXPECT_THAT(isEmpty, Eq(false))
  << "isEmpty=\"" << isEmpty << "\"" << endl;

  BSTMap<int,int>& mp1ref = mp1;
  mp1 = mp1ref;
  for(int i = 0; i < 3; i++){ 
    EXPECT_THAT(mp1.at(i), Eq(i))
    << "data at " << i << " is \"" << mp1.at(i) << "\"" << endl;
  }
  
}

TEST(BSTMapAug, AugTests) {
  BSTMap<int,int> map = BSTMap<int,int>();

  ASSERT_THROW(map.remove_min(),runtime_error)
  << "Map is empty" << endl;

  map.insert(3,3);
  map.insert(1,1);
  map.insert(0,0);
  map.insert(2,2);
  map.insert(5,5);
  map.insert(4,4);
  map.insert(6,6);

  EXPECT_THAT(map.remove_min() , Eq(Pair(0,0)))
  << "Remove_min gives out: " << map.remove_min();
  int mpsize = map.size();
  EXPECT_THAT(mpsize, Eq(6))
  << "size=\"" << mpsize << "\"" << endl;
 
  map.clear();

  map.insert(0,0);
  map.insert(1,1);
  EXPECT_THAT(map.remove_min() , Eq(Pair(0,0)))
  << "Remove_min gives out: " << map.remove_min();
  int mpsize = map.size();
  EXPECT_THAT(mpsize, Eq(1))
  << "size=\"" << mpsize << "\"" << endl;
  EXPECT_THAT(map.at(1), Eq(1))
  << "Map at key 1 is: " << map.at(1) << endl;

  map.clear();
  map.begin();
  int key;
  int value;
  EXPECT_THAT(map.next(key,value),Eq(false))
  << endl;
  
}

}  // namespace
