#include <stdio.h>

#include <sys/time.h>
#include <assert.h>

#include <iomanip>
#include <iostream>
using namespace std;


#define _EXPORT_OSLIB

// Copy from leveldb http://code.google.com/p/leveldb/source/browse/trunk/util/random.h
// A very simple random number generator.  Not especially good at
// generating truly random bits, but good enough for our needs in this
// package.
class _EXPORT_OSLIB Random 
{
private:
    uint32_t seed_;
public:
    explicit Random(uint32_t s) : seed_(s & 0x7fffffffu) { }
    uint32_t next() {
        static const uint32_t M = 2147483647L;   // 2^31-1
        static const uint64_t A = 16807;  // bits 14, 8, 7, 5, 2, 1, 0
        // We are computing
        //       seed_ = (seed_ * A) % M,    where M = 2^31-1
        //
        // seed_ must not be zero or M, or else all subsequent computed values
        // will be zero or M respectively.  For all other values, seed_ will end
        // up cycling through every number in [1,M-1]
        uint64_t product = seed_ * A;

        // Compute (product % M) using the fact that ((x << 31) % M) == x.
        seed_ = static_cast<uint32_t>((product >> 31) + (product & M));
        // The first reduction may overflow by 1 bit, so we may need to
        // repeat.  mod == M is not possible; using > allows the faster
        // sign-bit-based test.
        if (seed_ > M) {
            seed_ -= M;
        }
        return seed_;
    }

    // Returns a uniformly distributed value in the range [0..n-1]
    // REQUIRES: n > 0
    uint32_t uniform(int n) { assert( n > 0 ); return next() % n; }

    // Randomly returns true ~"1/n" of the time, and false otherwise.
    // REQUIRES: n > 0
    bool onein(int n) { assert(n > 0 ); return (next() % n) == 0; }

    // Skewed: pick "base" uniformly from range [0,max_log] and then
    // return "base" random bits.  The effect is to pick a number in the
    // range [0,2^max_log-1] with exponential bias towards smaller numbers.
    uint32_t skewed(int max_log) 
    {
        return uniform(1 << uniform(max_log + 1));
    }
};//end of class Random

void test1_random()
{
    //#pragma message "Compiling " __FILE__ "todo "
    struct timeval tv;
    gettimeofday( &tv, NULL );
    char timebuf[256] = {};
    strftime( timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", localtime(&(tv.tv_sec)));
    std::cout << "tv1.tv_sec=" << tv.tv_sec << std::endl
        << "tv1.tv_usec=" << tv.tv_usec << std::endl
        << timebuf << std::endl;

    {
        const int sz = 100;
        char a[sz] = {};
        Random rnd( sz );
        for ( int i = 0; i < sz; ++i )
        {
            int index = rnd.next() % sz;
            std::cout << index << " " ;
            a[index] = 1;
        }

        for ( int i = 0; i < sz; ++i )
        {
        }
    }
}

void test2_snprintf()
{
    const char* s = "abcdefghijklmnopqrstuvwxyz";

    const size_t LEN = 6;
    char* tmp = (char*)malloc( sizeof(char) * LEN );
    int n = snprintf( tmp, LEN, "%s", s );

    printf( "snprintf ret=%d strlen(tmp)=%lu |%s|", n, strlen(tmp), tmp );

    free(tmp);
}



int main()
{
    //test1_random();
    test2_snprintf();
    return 0;
}
