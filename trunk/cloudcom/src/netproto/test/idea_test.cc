#include "netproto/include/test_common.h"
#include "netproto/include/idea.h"

//openssl
#if H_NPP_PROVIDE_RSA
#ifdef H_WINDOWS_API
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"libeay32.lib")
#	else
#		pragma comment(lib,"libeay32.lib")
#	endif
#endif
#endif //

//openssl
#if H_NPP_PROVIDE_IDEA_ENCRYPT && !H_NPP_PROVIDE_RSA
#ifdef H_WINDOWS_API
#	ifdef H_DEBUG_MODE
#		pragma comment(lib,"idea.lib")
#	else
#		pragma comment(lib,"idea.lib")
#	endif
#endif
#endif // end of #if ( H_PROVIDE_NET_CA_ENCRYPT )


namespace
{
    void test_encrypt_decrypt( const unsigned char* s )
    {
        {
            std::string strideakey = "abcdefghabcdefgh";
            IDEA_KEY_SCHEDULE ekey;
            IDEA_KEY_SCHEDULE dkey;
            idea_set_encrypt_key( (const unsigned char*)strideakey.c_str(), &ekey );
            idea_set_decrypt_key( &ekey, &dkey );
            npp::IDEA::mem_data_t endata;
            npp::IDEA::mem_data_t dedata;

            endata.data = (u_char*)malloc( 1024 );
            dedata.data = (u_char*)malloc( 1024 );

            size_t len = strlen( ( const char* )s );

            npp::IDEA::encrypt( s, len, &ekey, &endata );

            {
                ::IDEA_KEY_SCHEDULE keyIdeaEncrypt;
                ::idea_set_encrypt_key( ( npp::u8* )strideakey.c_str(), &keyIdeaEncrypt );
                npp::MemoryDataStream encrypted;
                npp::IDEA::encrypt( s, len, keyIdeaEncrypt, encrypted );
                if ( endata.data_len > 0 )
                {
                    H_TEST_ASSERT( 0 == strncmp( (const char*)endata.data, ( const char* )encrypted.getCache(), endata.data_len ) );
                }
                H_TEST_ASSERT( endata.data_len == H_ALIGN( len, 8 ) );
                H_TEST_ASSERT( endata.data_len == encrypted.getSize() );
            }


            {
                npp::MemoryDataStream decrypted;
                npp::IDEA::decrypt( endata.data, endata.data_len, dkey, decrypted );
                npp::IDEA::decrypt( endata.data, endata.data_len, &dkey, &dedata );
                H_TEST_ASSERT( dedata.data_len == H_ALIGN(len, 8) );
                H_TEST_ASSERT( decrypted.getSize() == dedata.data_len );
                if ( dedata.data_len > 0 ) 
                {
                    H_TEST_ASSERT( 0 == strncmp( ( const char* )s, ( const char* )decrypted.getCache(), len ) );
                }
            }

            {
                npp::IDEA idea;
                idea.initialize(strideakey);

                size_t encrypted_data_len = npp::IDEA::getEncryptDataLen(npp::IDEA::PaddingZero, len);
                char* buf = new char[encrypted_data_len];
                H_TEST_ASSERT(idea.encrypt(s, len, npp::IDEA::PaddingZero, buf, encrypted_data_len));
                H_TEST_ASSERT(encrypted_data_len == endata.data_len);
                H_TEST_ASSERT(0 == memcmp(endata.data, buf, encrypted_data_len));
                H_TEST_ASSERT(encrypted_data_len == H_ALIGN(len, 8));

                size_t decrypted_data_len = encrypted_data_len;
                char* debuf = new char[decrypted_data_len];
                H_TEST_ASSERT(idea.decrypt(buf, encrypted_data_len, npp::IDEA::PaddingZero, debuf, decrypted_data_len));
                H_TEST_ASSERT(0 == memcmp(s, debuf, len));
                H_TEST_ASSERT(decrypted_data_len == H_ALIGN(len, 8));
                H_TEST_ASSERT(decrypted_data_len == encrypted_data_len);
            }

            {
                npp::IDEA idea;
                idea.initialize(strideakey);

                size_t encrypted_data_len = npp::IDEA::getEncryptDataLen(npp::IDEA::PaddingPKCS7, len);
                char* buf = new char[encrypted_data_len];
                H_TEST_ASSERT(idea.encrypt(s, len, npp::IDEA::PaddingPKCS7, buf, encrypted_data_len));

                size_t decrypted_data_len = encrypted_data_len;
                char* debuf = new char[decrypted_data_len];
                H_TEST_ASSERT(idea.decrypt(buf, encrypted_data_len, npp::IDEA::PaddingPKCS7, debuf, decrypted_data_len));
                H_TEST_ASSERT(0 == memcmp(s, debuf, len));
                H_TEST_ASSERT(len == decrypted_data_len);
            }

            free( endata.data );
            free( dedata.data );
        }
    }

    void test_1()
    {
        {
            std::string strideakey = "abcdefghabcdefgh";
            const unsigned char* s = ( const unsigned char* )"abcdefg";
            unsigned int len = strlen( ( const char* )s );
            npp::MemoryDataStream ds;
            npp::IDEA::encrypt( s, len, strideakey, ds );
            {
                ::IDEA_KEY_SCHEDULE keyIdeaEncrypt;
                ::idea_set_encrypt_key( ( npp::u8* )strideakey.c_str(), &keyIdeaEncrypt );
                npp::MemoryDataStream encrypted;
                npp::IDEA::encrypt( s, len, keyIdeaEncrypt, encrypted );
                H_TEST_ASSERT( 0 == strncmp( ( const char* )ds.getCache(), ( const char* )encrypted.getCache(), ds.getSize() ) );
            }
            H_TEST_ASSERT( ds.getSize() == H_ALIGN( len, 8 ) );
            {
                npp::MemoryDataStream decrypted;
                npp::IDEA::decrypt( ( npp::u8* )ds.getCache(), ds.getSize(), strideakey, decrypted );
                H_TEST_ASSERT( 0 == strncmp( ( const char* )s, ( const char* )decrypted.getCache(), len ) );
            }

            {
                npp::MemoryDataStream decrypted;
                ::IDEA_KEY_SCHEDULE keyIdeaEncrypt;
                ::IDEA_KEY_SCHEDULE keyIdeaDecrypt;
                ::idea_set_encrypt_key( ( npp::u8* )strideakey.c_str(), &keyIdeaEncrypt );
                ::idea_set_decrypt_key( &keyIdeaEncrypt, &keyIdeaDecrypt );
                npp::IDEA::decrypt( ( npp::u8* )ds.getCache(), ds.getSize(), keyIdeaDecrypt, decrypted );
                H_TEST_ASSERT( 0 == strncmp( ( const char* )s, ( const char* )decrypted.getCache(), len ) );
            }


            s = ( const unsigned char* )"0123456789";
            len = strlen( ( const char* )s );
            ds.reset();
            npp::IDEA::encrypt( s, len, strideakey, ds );
            H_TEST_ASSERT( ds.getSize() == H_ALIGN( len, 8 ) );


            s = ( const unsigned char* )"abcdefg1234567893366521455513231213321321";
            len = strlen( ( const char* )s );
            ds.reset();
            npp::IDEA::encrypt( s, len, strideakey, ds );
            H_TEST_ASSERT( ds.getSize() == H_ALIGN( len, 8 ) );
        }


        {

            const unsigned char* s = NULL;
            s = ( const unsigned char* )"abcdefg";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"uiasiudfuiasdiufaiusdfiuasdifuasiudfiuasdfiuasdiufaisudfiuasdfhasdfahsdfhasdfhasdkfjsadkjfasdfasdhf  ;';';      46123124124576543234568543214567890!@#$%^&*(''-0-09 09 8 8 89 7 7 6 56 5";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"uiassdfasdfasdfasd5f4asd   ```~~``1122234~!@#$%^&*()_+[}{{}[[][]/'';;'\\\\\\;;lkkjhgfdfghjkl5f4a6sd4fas6dfas3df1as3d2f1as6df84as6df7/*//*//**//*/***---+++/iudfuiasdiufaiusdfiuasdifuasiudfiuasdfiuasdiufaisudfiuasdfhasdfahsdfhasdfhasdkfjsadkjfasdfasdhf  ;';';      46123124124576543234568543214567890!@#$%^&*(''-0-09 09 8 8 89 7 7 6 56 5";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"abcdefg1234567893366521455513231213321321";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1234";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123456";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1234567";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345678";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123456789";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345678901";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123456789012";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1234567890123";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345678901234";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"123456789012345";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"1234567890123456";
            test_encrypt_decrypt(s);
            s = ( const unsigned char* )"12345678901234567";
            test_encrypt_decrypt(s);
        }


    }

    void test_2()
    {
        std::string strideakey = "abcdefghabcdefgh";
        const unsigned char* s = ( const unsigned char* )"abcdefg";
        unsigned int len = strlen( ( const char* )s );
        npp::MemoryDataStream ds;
        npp::IDEA idea;
        H_TEST_ASSERT(idea.initialize(strideakey));
        H_TEST_ASSERT(idea.encrypt( s, len, ds ));
        H_TEST_ASSERT( ds.getSize() == H_ALIGN( len, 8 ) );
        npp::MemoryDataStream decrypted;
        H_TEST_ASSERT(idea.decrypt( ( npp::u8* )ds.data(), ds.size(), decrypted ));
        H_TEST_ASSERT( 0 == strncmp( ( const char* )s, ( const char* )decrypted.data(), len ) );
    }

    void test_getEncryptDataLen()
    {
        for (size_t i = 1; i <= 8; ++i)
        {
            H_TEST_ASSERT(npp::IDEA::getEncryptDataLen(npp::IDEA::PaddingZero, i) == 8);
        }

        for (size_t i = 0; i <= 7; ++i)
        {
            H_TEST_ASSERT(npp::IDEA::getEncryptDataLen(npp::IDEA::PaddingPKCS7, i) == 8);
        }


        for (size_t i = 8; i <= 15; ++i)
        {
            H_TEST_ASSERT(npp::IDEA::getEncryptDataLen(npp::IDEA::PaddingPKCS7, i) == 16);
        }

        H_TEST_ASSERT(npp::IDEA::getEncryptDataLen(npp::IDEA::PaddingPKCS7, 0) == 8);
        H_TEST_ASSERT(npp::IDEA::getEncryptDataLen(npp::IDEA::PaddingPKCS7, 8) == 16);
    }
}

TEST_UNIT(idea_test_1)
{
    test_getEncryptDataLen();
    test_1();
    test_2();
}
