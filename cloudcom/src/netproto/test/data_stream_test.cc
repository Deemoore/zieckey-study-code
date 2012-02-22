
#include "netproto/include/test_common.h"
#include "netproto/include/data_stream.h"

#include <iostream>

using namespace npp;

namespace
{
    void serialize_1()
    {
        char c = 'a';
        short t = 111;
        int   d = 221;
        long  l = 333;
        float f = 666.66;
        double ff = 7777.777;

        MemoryDataStream ds;
        ds << c << t << d << l << f << ff;
        H_TEST_ASSERT(!ds.isWriteBad());
        H_TEST_ASSERT(ds.size() == sizeof(c) + sizeof(t) + sizeof(d) + sizeof(l) + sizeof(f) + sizeof(ff));

        char c1 = 0;
        short t1 = 0;
        int   d1 = 0;
        long  l1 = 0;
        float f1 = 0.0;
        double ff1 = 0.0;
        ds >> c1 >> t1 >> d1 >> l1 >> f1 >> ff1;
        H_TEST_ASSERT(c == c1);
        H_TEST_ASSERT(t == t1);
        H_TEST_ASSERT(d == d1);
        H_TEST_ASSERT(l == l1);
        H_TEST_ASSERT(f == f1);
        H_TEST_ASSERT(ff == ff1);
        H_TEST_ASSERT(!ds.isReadBad());
        H_TEST_ASSERT(ds.getReadableSize() == 0);
    }


    void serialize_2()
    {
        std::string a = "aaaaaaaaaaaaaaaaaaaaaaa";
        std::string b = "bbbbbbbbbbbbbbbbbbbb";
        int   d = 221;
        long  l = 333;

        MemoryDataStream ds;
        ds << d << a << l << b;
        H_TEST_ASSERT(!ds.isWriteBad());

        int   d1 = 0;
        long  l1 = 0;
        std::string a1;
        std::string b1;
        ds >> d1 >> a1 >> l1 >> b1;
        H_TEST_ASSERT(d == d1);
        H_TEST_ASSERT(l == l1);
        H_TEST_ASSERT(a == a1);
        H_TEST_ASSERT(b == b1);
        H_TEST_ASSERT(!ds.isReadBad());
        H_TEST_ASSERT(ds.getReadableSize() == 0);
    }

    void serialize_vector_3()
    {  
        typedef std::vector<int> intvector;
        intvector iv;
        for (int i = 0; i < 100; ++i)
        {
            iv.push_back(i);
        }

        std::string a = "aaaaaaaaaaaaaaaaaaaaaaa";
        std::string b = "bbbbbbbbbbbbbbbbbbbb";
        int   d = 221;
        long  l = 333;

        MemoryDataStream ds;
        ds << d << a << l << b << iv;
        H_TEST_ASSERT(!ds.isWriteBad());

        int   d1 = 0;
        long  l1 = 0;
        std::string a1;
        std::string b1;
        intvector iv1;
        ds >> d1 >> a1 >> l1 >> b1 >> iv1;
        H_TEST_ASSERT(d == d1);
        H_TEST_ASSERT(l == l1);
        H_TEST_ASSERT(a == a1);
        H_TEST_ASSERT(b == b1);
        H_TEST_ASSERT(!ds.isReadBad());
        H_TEST_ASSERT(ds.getReadableSize() == 0);

        H_TEST_ASSERT(iv.size() == iv1.size());
        intvector::iterator it(iv.begin());
        intvector::iterator ite(iv.end());
        intvector::iterator it1(iv1.begin());
        intvector::iterator ite1(iv1.end());
        for (; it != ite; ++it, ++it1)
        {
            H_TEST_ASSERT((*it) == (*it1));
        }
    }

    void serialize_list_4()
    {  
        typedef std::list<int> intlist;
        intlist iv;
        for (int i = 0; i < 100; ++i)
        {
            iv.push_back(i);
        }

        std::string a = "aaaaaaaaaaaaaaaaaaaaaaa";
        std::string b = "bbbbbbbbbbbbbbbbbbbb";
        int   d = 221;
        long  l = 333;

        MemoryDataStream ds;
        ds << d << a << l << b << iv;
        H_TEST_ASSERT(!ds.isWriteBad());

        int   d1 = 0;
        long  l1 = 0;
        std::string a1;
        std::string b1;
        intlist iv1;
        ds >> d1 >> a1 >> l1 >> b1 >> iv1;
        H_TEST_ASSERT(d == d1);
        H_TEST_ASSERT(l == l1);
        H_TEST_ASSERT(a == a1);
        H_TEST_ASSERT(b == b1);
        H_TEST_ASSERT(!ds.isReadBad());
        H_TEST_ASSERT(ds.getReadableSize() == 0);

        H_TEST_ASSERT(iv.size() == iv1.size());
        intlist::iterator it(iv.begin());
        intlist::iterator ite(iv.end());
        intlist::iterator it1(iv1.begin());
        intlist::iterator ite1(iv1.end());
        for (; it != ite; ++it, ++it1)
        {
            H_TEST_ASSERT((*it) == (*it1));
        }
    }

    void serialize_set_5()
    {  
        typedef std::set<int> intset;
        intset iv;
        for (int i = 0; i < 100; ++i)
        {
            iv.insert(i);
        }

        std::string a = "aaaaaaaaaaaaaaaaaaaaaaa";
        std::string b = "bbbbbbbbbbbbbbbbbbbb";
        int   d = 221;
        long  l = 333;

        MemoryDataStream ds;
        ds << d << a << l << b << iv;
        H_TEST_ASSERT(!ds.isWriteBad());

        int   d1 = 0;
        long  l1 = 0;
        std::string a1;
        std::string b1;
        intset iv1;
        ds >> d1 >> a1 >> l1 >> b1 >> iv1;
        H_TEST_ASSERT(d == d1);
        H_TEST_ASSERT(l == l1);
        H_TEST_ASSERT(a == a1);
        H_TEST_ASSERT(b == b1);
        H_TEST_ASSERT(!ds.isReadBad());
        H_TEST_ASSERT(ds.getReadableSize() == 0);

        H_TEST_ASSERT(iv.size() == iv1.size());
        intset::iterator it(iv.begin());
        intset::iterator ite(iv.end());
        intset::iterator it1(iv1.begin());
        intset::iterator ite1(iv1.end());
        for (; it != ite; ++it, ++it1)
        {
            H_TEST_ASSERT((*it) == (*it1));
        }
    }


    void serialize_map_6()
    {  
        typedef std::set<int> intset;
        typedef std::map<int, double> intdoublemap;
        intset iv;
        intdoublemap idm;
        for (int i = 0; i < 100; ++i)
        {
            iv.insert(i);
            idm[i] = i;
        }

        std::string a = "aaaaaaaaaaaaaaaaaaaaaaa";
        std::string b = "bbbbbbbbbbbbbbbbbbbb";
        int   d = 221;
        long  l = 333;

        MemoryDataStream ds;
        ds << d << a << l << b << iv << idm;
        H_TEST_ASSERT(!ds.isWriteBad());

        int   d1 = 0;
        long  l1 = 0;
        std::string a1;
        std::string b1;
        intset iv1;
        intdoublemap idm1;
        ds >> d1 >> a1 >> l1 >> b1 >> iv1 >> idm1;
        H_TEST_ASSERT(d == d1);
        H_TEST_ASSERT(l == l1);
        H_TEST_ASSERT(a == a1);
        H_TEST_ASSERT(b == b1);
        H_TEST_ASSERT(!ds.isReadBad());
        H_TEST_ASSERT(ds.getReadableSize() == 0);

        H_TEST_ASSERT(iv.size() == iv1.size());
        H_TEST_ASSERT(idm.size() == idm1.size());
        {
            intset::iterator it(iv.begin());
            intset::iterator ite(iv.end());
            intset::iterator it1(iv1.begin());
            intset::iterator ite1(iv1.end());
            for (; it != ite; ++it, ++it1)
            {
                H_TEST_ASSERT((*it) == (*it1));
            }
        }

        {
            intdoublemap::iterator it(idm.begin());
            intdoublemap::iterator ite(idm.end());
            intdoublemap::iterator it1(idm1.begin());
            intdoublemap::iterator ite1(idm1.end());
            for (; it != ite; ++it, ++it1)
            {
                H_TEST_ASSERT((it->first) == (it1->first));
                H_TEST_ASSERT((it->second) == (it1->second));
            }
        }
    }
}

TEST_UNIT(memory_data_stream_test_serialize_1)
{
    serialize_1();
    serialize_2();
    serialize_vector_3();
    serialize_list_4();
    serialize_set_5();
    serialize_map_6();
}
