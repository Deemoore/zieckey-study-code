#include "libtest/include/QLibTestPrerequisits.h"
// #include "osl/include/QFileUtil.h"
// 
// #include "libtest/include/QTestObject.h"
// using namespace osl;
// 
// namespace
// {
//     class TEditHistory : public LibTest::ITestObject
//     {
// 
//         void testAll();
// 
//         const char* getCommand();
//         const char* getDesc();
//         void invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell );
// 
// 
//         void test_1();
//         void test_2();
//     };
// 
//     const char* TEditHistory::getCommand()
//     {
//         return "test_edithistory";
//     }
// 
//     const char* TEditHistory::getDesc()
//     {
//         return "test_edithistory";
//     }
// 
//     void TEditHistory::testAll()
//     {
//         test_1();
//         test_2();
//     }
// 
//     void TEditHistory::invoke( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
//     {
//         testAll();
//     }
// 
//     namespace
//     {
//         class PrintCmd : public osl::EHCmd
//         {
//         public:
//             PrintCmd( const char* name )
//                 : m_strCmdName(name)
//             {
//                 m_bCanUndo = true;
//                 m_bCanRedo = true;
//             }
// 
//             virtual void redo(){ std::cout << m_strCmdName.c_str() << ":redo" << std::endl; }
//             virtual void undo(){ std::cout << m_strCmdName.c_str() << ":undo" << std::endl; }
//             virtual bool canUndo(){ return m_bCanUndo; };
//             virtual bool canRedo(){ return m_bCanRedo; };
// 
// 
//             virtual const char* getCmdName() const { return m_strCmdName.c_str(); };
// 
// 
//             void setCanUndo(bool val) { m_bCanUndo = val; }
//             void setCanRedo(bool val) { m_bCanRedo = val; }
//         private:
//             osl::StringA m_strCmdName;
// 
//             bool m_bCanUndo;
//             bool m_bCanRedo;
//         };
// 
//         typedef osl::RefPtr<PrintCmd> PrintCmdPtr;
//     }
// 
//     void TEditHistory::test_1()
//     {
//         s_pEditHistory_OSLib->clear();
// 
// 
//         s_pEditHistory_OSLib->addHistory( H_NEW PrintCmd( "A" ) );
//         s_pEditHistory_OSLib->addHistory( H_NEW PrintCmd( "B" ) );
//         s_pEditHistory_OSLib->addHistory( H_NEW PrintCmd( "C" ) );
//         s_pEditHistory_OSLib->addHistory( H_NEW PrintCmd( "D" ) );
// 
//         //test1
// #ifdef H_DEBUG_MODE
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printUndoList( oss );
//             H_ASSERT( oss.str() == "ABCD" );
//         }
// 
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printRedoList( oss );
//             H_ASSERT( oss.str() == "" );
//         }
// #endif
// 
//         s_pEditHistory_OSLib->undo();
//         s_pEditHistory_OSLib->undo();
// #ifdef H_DEBUG_MODE
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printUndoList( oss );
//             H_ASSERT( oss.str() == "AB" );
//         }
// 
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printRedoList( oss );
//             H_ASSERT( oss.str() == "DC" );
//         }
// #endif
// 
// 
// 
//         s_pEditHistory_OSLib->redo();
// #ifdef H_DEBUG_MODE
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printUndoList( oss );
//             H_ASSERT( oss.str() == "ABC" );
//         }
// 
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printRedoList( oss );
//             H_ASSERT( oss.str() == "D" );
//         }
// #endif
// 
// 
//         s_pEditHistory_OSLib->addHistory( H_NEW PrintCmd("E") );
//         s_pEditHistory_OSLib->addHistory( H_NEW PrintCmd("F") );
//         s_pEditHistory_OSLib->addHistory( H_NEW PrintCmd("G") );
//         s_pEditHistory_OSLib->redo();//no redo cmd here
//         s_pEditHistory_OSLib->undo();
//         s_pEditHistory_OSLib->undo();
// #ifdef H_DEBUG_MODE
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printUndoList( oss );
//             H_ASSERT( oss.str() == "ABCE" );
//         }
// 
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printRedoList( oss );
//             H_ASSERT( oss.str() == "GF" );
//         }
// #endif
// 
//     }
// 
//     void TEditHistory::test_2()
//     {
//         s_pEditHistory_OSLib->clear();
//         s_pEditHistory_OSLib->setMaxCommand( 3 ); // set the max Command we record in the history
// 
//         PrintCmdPtr pCmd_A = H_NEW PrintCmd( "A" );
//         PrintCmdPtr pCmd_B = H_NEW PrintCmd( "B" );
//         PrintCmdPtr pCmd_C = H_NEW PrintCmd( "C" );
//         PrintCmdPtr pCmd_D = H_NEW PrintCmd( "D" );
//         PrintCmdPtr pCmd_E = H_NEW PrintCmd( "E" );
//         PrintCmdPtr pCmd_F = H_NEW PrintCmd( "F" );
// 
// 
//         s_pEditHistory_OSLib->addHistory( pCmd_A );
//         s_pEditHistory_OSLib->addHistory( pCmd_B );
//         s_pEditHistory_OSLib->addHistory( pCmd_C );
//         s_pEditHistory_OSLib->addHistory( pCmd_D );
// 
//         //test1
// #ifdef H_DEBUG_MODE
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printUndoList( oss );
//             H_ASSERT( oss.str() == "BCD" );
//         }
// 
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printRedoList( oss );
//             H_ASSERT( oss.str() == "" );
//         }
// 
//         H_ASSERT( s_pEditHistory_OSLib->getCurCmd() == pCmd_D );
// #endif
//         pCmd_C->setCanUndo( false );
// 
//         s_pEditHistory_OSLib->undo();
//         s_pEditHistory_OSLib->undo();
// #ifdef H_DEBUG_MODE
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printUndoList( oss );
//             H_ASSERT( oss.str() == "" );
//         }
// 
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printRedoList( oss );
//             H_ASSERT( oss.str() == "D" );
//         }
// 
//         H_ASSERT( s_pEditHistory_OSLib->getCurCmd() == NULL );
// #endif
// 
// 
// 
//         s_pEditHistory_OSLib->redo();
//         s_pEditHistory_OSLib->addHistory( pCmd_E );
//         s_pEditHistory_OSLib->addHistory( pCmd_F );
//         s_pEditHistory_OSLib->undo();
//         s_pEditHistory_OSLib->undo();
//         s_pEditHistory_OSLib->undo();
// #ifdef H_DEBUG_MODE
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printUndoList( oss );
//             H_ASSERT( oss.str() == "" );
//         }
// 
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printRedoList( oss );
//             H_ASSERT( oss.str() == "FED" );
//         }
// 
// 
//         H_ASSERT( s_pEditHistory_OSLib->getCurCmd() == NULL );
// #endif
// 
//         pCmd_E->setCanRedo( false );
//         s_pEditHistory_OSLib->redo();
//         s_pEditHistory_OSLib->redo();
// 
// #ifdef H_DEBUG_MODE
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printUndoList( oss );
//             H_ASSERT( oss.str() == "D" );
//         }
// 
//         {
//             osl::OStringStreamA oss;
//             s_pEditHistory_OSLib->printRedoList( oss );
//             H_ASSERT( oss.str() == "" );
//         }
// 
// 
//         H_ASSERT( s_pEditHistory_OSLib->getCurCmd() == pCmd_D );
// #endif
// 
// 
// 
// 
// 
// 
// 
//         s_pEditHistory_OSLib->setMaxCommand( 100 ); // set the max Command we record in the history
//     }
// 
// }
// 
// 
// 
// 
// 
// CREATE_FUNCTION( TEditHistory );
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
