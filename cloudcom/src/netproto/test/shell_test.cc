
#include "osl/include/test_common.h"

#include "osl/include/shell.h"
namespace
{

    void test1()
    {
        const char* cmd = "cmd";
        osl::AppShell shell;
        osl::AppShell::Command command;
        shell.parseCommand(cmd, command);

        H_TEST_ASSERT(command.getName() == "cmd");
    }


    void test2()
    {
        const char* cmd = "cmd ";
        osl::AppShell shell;
        osl::AppShell::Command command;
        shell.parseCommand(cmd, command);

        H_TEST_ASSERT(command.getName() == "cmd");
    }

    void test3()
    {
        const char* cmd = " cmd ";
        osl::AppShell shell;
        osl::AppShell::Command command;
        shell.parseCommand(cmd, command);

        H_TEST_ASSERT(command.getName() == "cmd");
    }


    void test4()
    {
        const char* cmd = " cmd";
        osl::AppShell shell;
        osl::AppShell::Command command;
        shell.parseCommand(cmd, command);

        H_TEST_ASSERT(command.getName() == "cmd");
    }
}



TEST_UNIT(appshell_test)
{
    test1();
    test2();
    test3();
    test4();
}



TEST_UNIT(appshell_test_2)
{
    const char* cmd = "cmd -aux d";
    osl::AppShell shell;
    osl::AppShell::Command command;
    shell.parseCommand(cmd, command);

    H_TEST_ASSERT(command.getName() == "cmd");
    H_TEST_ASSERT(command.getParam("a")->name() == "a");
    H_TEST_ASSERT(command.getParam("a")->value() == "");
    H_TEST_ASSERT(command.getParam("u")->name() == "u");
    H_TEST_ASSERT(command.getParam("u")->value() == "");
    H_TEST_ASSERT(command.getParam("x")->name() == "x");
    H_TEST_ASSERT(command.getParam("x")->value() == "");

    H_TEST_ASSERT(command.hasTarget("d"));
}


TEST_UNIT(appshell_test_3)
{
    const char* cmd = "cmd -b -c 1 d";
    osl::AppShell shell;
    osl::AppShell::Command command;
    shell.parseCommand(cmd, command);

    H_TEST_ASSERT(command.getName() == "cmd");

    H_TEST_ASSERT(command.getParam("b")->name() == "b");
    H_TEST_ASSERT(command.getParam("b")->value() == "");

    H_TEST_ASSERT(command.getParam("c")->name() == "c");
    H_TEST_ASSERT(command.getParam("c")->value() == "1");

    H_TEST_ASSERT(command.hasTarget("d"));
}



TEST_UNIT(appshell_test_4)
{
    const char* cmd = "cmd d";
    osl::AppShell shell;
    osl::AppShell::Command command;
    shell.parseCommand(cmd, command);

    H_TEST_ASSERT(command.getName() == "cmd");

    H_TEST_ASSERT(command.hasTarget("d"));
}


TEST_UNIT(appshell_test_5)
{
    const char* cmd = "cmd  d ";
    osl::AppShell shell;
    osl::AppShell::Command command;
    shell.parseCommand(cmd, command);

    H_TEST_ASSERT(command.getName() == "cmd");

    H_TEST_ASSERT(command.hasTarget("d"));
}


TEST_UNIT(appshell_test_6)
{
    const char* cmd = "cmd d --help ";
    osl::AppShell shell;

    {

        osl::AppShell::Command command;
        shell.parseCommand(cmd, command);

        H_TEST_ASSERT(command.getName() == "cmd");

        H_TEST_ASSERT(command.getParam("help")->name() == "help");
        H_TEST_ASSERT(command.getParam("help")->value() == "");

        H_TEST_ASSERT(command.hasTarget("d"));
    }

    {
        cmd = "cmd --help d";
        osl::AppShell::Command command;
        shell.parseCommand(cmd, command);

        H_TEST_ASSERT(command.getName() == "cmd");

        H_TEST_ASSERT(command.getParam("help")->name() == "help");
        H_TEST_ASSERT(command.getParam("help")->value() == "");

        H_TEST_ASSERT(command.hasTarget("d"));
    }

    {
        cmd = "cmd --help d ";
        osl::AppShell::Command command;
        shell.parseCommand(cmd, command);

        H_TEST_ASSERT(command.getName() == "cmd");

        H_TEST_ASSERT(command.getParam("help")->name() == "help");
        H_TEST_ASSERT(command.getParam("help")->value() == "");

        H_TEST_ASSERT(command.hasTarget("d"));
    }
}



TEST_UNIT(appshell_test_7)
{
    {
        const char* cmd = "cmd --aa=AA";
        osl::AppShell shell;
        osl::AppShell::Command command;
        shell.parseCommand(cmd, command);

        H_TEST_ASSERT(command.getName() == "cmd");

        H_TEST_ASSERT(command.getParam("aa")->name() == "aa");
        H_TEST_ASSERT(command.getParam("aa")->value() == "AA");
    }

    {
        const char* cmd = "cmd --aa=AA ";
        osl::AppShell shell;
        osl::AppShell::Command command;
        shell.parseCommand(cmd, command);

        H_TEST_ASSERT(command.getName() == "cmd");

        H_TEST_ASSERT(command.getParam("aa")->name() == "aa");
        H_TEST_ASSERT(command.getParam("aa")->value() == "AA");
    }
}



TEST_UNIT(appshell_test_8)
{
    const char* cmd = "cmd --aa=AA --bb=BB ";
    osl::AppShell shell;
    osl::AppShell::Command command;
    shell.parseCommand(cmd, command);

    H_TEST_ASSERT(command.getName() == "cmd");

    H_TEST_ASSERT(command.getParam("aa")->name() == "aa");
    H_TEST_ASSERT(command.getParam("aa")->value() == "AA");

    H_TEST_ASSERT(command.getParam("bb")->name() == "bb");
    H_TEST_ASSERT(command.getParam("bb")->value() == "BB");
}



TEST_UNIT(appshell_test_9)
{
    const char* cmd = "cmd d --help --aa=AA --bb=BB ";
    osl::AppShell shell;
    osl::AppShell::Command command;
    shell.parseCommand(cmd, command);

    H_TEST_ASSERT(command.getName() == "cmd");

    H_TEST_ASSERT(command.getParam("help")->name() == "help");
    H_TEST_ASSERT(command.getParam("help")->value() == "");

    H_TEST_ASSERT(command.getParam("aa")->name() == "aa");
    H_TEST_ASSERT(command.getParam("aa")->value() == "AA");

    H_TEST_ASSERT(command.getParam("bb")->name() == "bb");
    H_TEST_ASSERT(command.getParam("bb")->value() == "BB");


    H_TEST_ASSERT(command.hasTarget("d"));
}


TEST_UNIT(appshell_test_10)
{
    const char* cmd = "cmd d --help --aa=AA --bb=BB -aux";
    osl::AppShell shell;
    osl::AppShell::Command command;
    shell.parseCommand(cmd, command);

    H_TEST_ASSERT(command.getName() == "cmd");

    H_TEST_ASSERT(command.getParam("help")->name() == "help");
    H_TEST_ASSERT(command.getParam("help")->value() == "");

    H_TEST_ASSERT(command.getParam("aa")->name() == "aa");
    H_TEST_ASSERT(command.getParam("aa")->value() == "AA");

    H_TEST_ASSERT(command.getParam("bb")->name() == "bb");
    H_TEST_ASSERT(command.getParam("bb")->value() == "BB");

    H_TEST_ASSERT(command.getParam("a")->name() == "a");
    H_TEST_ASSERT(command.getParam("a")->value() == "");
    H_TEST_ASSERT(command.getParam("u")->name() == "u");
    H_TEST_ASSERT(command.getParam("u")->value() == "");
    H_TEST_ASSERT(command.getParam("x")->name() == "x");
    H_TEST_ASSERT(command.getParam("x")->value() == "");

    H_TEST_ASSERT(command.hasTarget("d"));
}


