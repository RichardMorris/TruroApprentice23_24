#include "weighted_graph.h"
using namespace std;
#include <catch2/catch_all.hpp>
#include <algorithm>    // std::fill
#include <vector>       // std::vector
#include <map>
#include <unordered_map> 

TEST_CASE("Build graph")
{
    wnode R("Redruth");
    wnode C("Camborne");
    wnode F("Falmouth");
    wnode T("Truro");
  wnode A("St Austell");
  graph g;

  g.add_node(&R);
  g.add_node(&C);
  g.add_node(&F);
  g.add_node(&T);
  g.add_node(&A);

  g.add_edge(&R,&C,5);
  g.add_edge(&R,&T,10);
  g.add_edge(&R,&A,40);
  g.add_edge(&T,&A,20);
  g.add_edge(&T,&F,8);
  
  int dist;
  dist = g.dijkstra(&C, &C);
  REQUIRE(0 == dist);
  dist = g.dijkstra(&R, &R);
  REQUIRE(0 == dist);
  dist = g.dijkstra(&T, &T);
  REQUIRE(0 == dist);
  dist = g.dijkstra(&F, &F);
  REQUIRE(0 == dist);
  dist = g.dijkstra(&A, &A);
  REQUIRE(0 == dist);

  dist = g.dijkstra(&C, &R);
  REQUIRE(5 == dist);
  dist = g.dijkstra(&C, &T);
  REQUIRE(15 == dist);
  dist = g.dijkstra(&C, &F);
  REQUIRE(23 == dist);
  dist = g.dijkstra(&C, &A);
  REQUIRE(35 == dist);


}

TEST_CASE("Collection times") {
    const int size = 10000; // Size of the vector
    const int lower_bound = 1; // Lower bound of the random numbers
    const int upper_bound = 100000; // Upper bound of the random numbers

    // Seed for the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate a vector of unique random numbers
    std::vector<int> randomNumbers;
    randomNumbers.reserve(size);

    std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);

    BENCHMARK("Build random vector") {
        while (randomNumbers.size() < size) {
            int randomNum = distribution(gen);
            if (std::find(randomNumbers.begin(), randomNumbers.end(), randomNum) == randomNumbers.end()) {
                randomNumbers.push_back(randomNum);
            }
        }
    };
}

class CustomObject {
public:
    int key1;
    int key2;

    CustomObject(int k1, int k2) : key1(k1), key2(k2) {}

    // Define hash function
    size_t hash() const {
        // You can use any suitable hash function here
        return std::hash<int>()(key1) ^ std::hash<int>()(key2);
    }

    // Define equality operator
    bool operator==(const CustomObject& other) const {
        return (key1 == other.key1) && (key2 == other.key2);
    }
};

struct KeyHash
{
    std::size_t operator()(const CustomObject& k) const
    {
        return k.hash();
    }
};
 
struct KeyEqual
{
    bool operator()(const CustomObject& lhs, const CustomObject& rhs) const
    {
        return lhs == rhs;
    }
};


template<> struct std::hash<CustomObject> {
    std::size_t operator()(CustomObject const& s) const noexcept {
        std::size_t h1 = std::hash<int>{}(s.key1);
        std::size_t h2 = std::hash<int>{}(s.key2);
        return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion) https://en.cppreference.com/w/Talk:cpp/utility/hash
    }
};

TEST_CASE("Hash table") {

    CustomObject cu(45,67);
    //std::unordered_map<CustomObject, std::string,KeyHash,KeyEqual> map2 = {};
    std::unordered_map<CustomObject,std::string> map2;

    map2[cu] = "foobar";
    REQUIRE(map2[cu] == "foobar");

    std::cout << "buckets " << map2.bucket_count() << " loadFactor " << map2.load_factor() << std::endl;


    const int size = 100; // Size of the vector
    const int lower_bound = 1; // Lower bound of the random numbers
    const int upper_bound = 100000; // Upper bound of the random numbers

    // Seed for the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate a vector of unique random numbers
    std::vector<int> randomNumbers;
    randomNumbers.reserve(size);

    std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);
    while (randomNumbers.size() < size) {
        int randomNum = distribution(gen);
        if (std::find(randomNumbers.begin(), randomNumbers.end(), randomNum) == randomNumbers.end()) {
            randomNumbers.push_back(randomNum);
        }
    }


    std::unordered_map<int, int> my_map;

    std::cout << "buckets " << my_map.bucket_count() << " loadFactor " << my_map.load_factor() << std::endl;

    int count=0;
    for(auto n : randomNumbers) {
        ++count;
        my_map[n] = n*n;
        std::cout << count << " buckets " << my_map.bucket_count() << " loadFactor " << my_map.load_factor() << std::endl;
    }


}


