#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
   // hash function entry point (i.e. this is h(k))
HASH_INDEX_T operator()(const std::string& k) const
{
    // Initialize array with zeros
    unsigned long long w[5] = {0};
    
    int len = k.length();
    int pos = len - 1; // Start from the rightmost character
    int group = 4; // Start from the rightmost group (w[4])
    
    while (pos >= 0 && group >= 0) {
        unsigned long long value = 0;
        unsigned long long power = 1;
        
        // Process up to 6 characters in this group
        for (int i = 0; i < 6 && pos >= 0; i++) {
            char c = k[pos--];
            value += letterDigitToNumber(c) * power;
            power *= 36;
        }
        
        w[group--] = value;
    }
    
    // Compute the final hash using the formula
    unsigned long long result = 0;
    for (int i = 0; i < 5; i++) {
        result += rValues[i] * w[i];
    }
    
    return result;
}

// A likely helper function is to convert a-z,0-9 to an integral value 0-35
HASH_INDEX_T letterDigitToNumber(char letter) const
{
    if (isalpha(letter)) {
        // Convert to lowercase and get value (a=0, b=1, etc.)
        return tolower(letter) - 'a';
    } else if (isdigit(letter)) {
        // Map '0' to 26, '1' to 27, etc.
        return letter - '0' + 26;
    }
    // For any other character (which shouldn't happen based on the constraints)
    return 0;
}


    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
