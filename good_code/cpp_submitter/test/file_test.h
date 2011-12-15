#include <file_handler.h>
#include <string>
#include <cppunit/extensions/HelperMacros.h>
 
class FileTest :public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(FileTest);
    CPPUNIT_TEST(testSingleDirectory);
    CPPUNIT_TEST(testMultipleDirectory);
    CPPUNIT_TEST(testSingleDirectoryDeletePos);
    CPPUNIT_TEST(testSingleDirectoryMultipleSmallFile);
    CPPUNIT_TEST_SUITE_END();
  public:
    void setUp();
    void tearDown();
    void testSingleDirectory();
    void testMultipleDirectory();
    void testSingleDirectoryDeletePos();
    void testSingleDirectoryMultipleSmallFile();
  protected:
    static const std::string test_command[8];
};
