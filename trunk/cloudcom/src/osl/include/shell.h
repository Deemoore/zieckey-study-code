#ifndef _QOSLIB_APPSHELL_H
#define _QOSLIB_APPSHELL_H

#if H_PROVIDE_APPSHELL

#include "osl/include/object.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"
#include "osl/include/function.h"

namespace osl
{

    class Tokener;
	class Log;

    //! Application shell system.
    //! \par It can serve as register of command processor.
    //! \note command with name "help" is reserved by the shell.
    //! \par  "move -ofi", "move --fix=value targetparameter", "mov -o --fix=434"
    class _EXPORT_OSLIB AppShell : public osl::Object
    {
        H_ALLOC_OBJECT( AppShell );
    public:

        //! Command object parsed from text.
        class _EXPORT_OSLIB Command
        {
        public:
            //! Param in command. "--fixed=434"---- name is "fixed", value is"434"
            struct Param
            {
                StringA  strName;
                StringA   strVal;
            };

            H_DEF_LIST( Param,  ParamList );
            H_DEF_VECTOR( StringA, TargetList );
        public:
            //! Gets command name.
            const StringA& getName() const
            {
                return m_strName;
            };

            //! Gets parameter.
            //! \return NULL if can not find parameter. The returned value can not be stored and use later.
            Param* getParam( const StringA& strParam );

            //! Gets targets of the command.
            const TargetList& getTargetList() const
            {
                return m_vTargets;
            }

            //! Gets targets of the command.
            const ParamList& getParamList() const
            {
                return m_vParams;
            }

            //! Query whether has target.
            //! \remark string is case sensitive.
            //! \return false if can not find target.
            bool hasTarget( const String& strTarget/*, bool bCaseSensitive = true*/ ) const ;

            //! Query whether has param.
            //! \remark string is case sensitive.
            //! \return false if can not find target.
            bool hasParam( const Param& param/*, bool bCaseSensitive = true*/ ) const ;

            void setCmdName( const StringA& strCmdName )
            {
                m_strName = strCmdName;
            }

            void addParam( const Param& param )
            {
                m_vParams.push_back( param );
            }

            void addTargetParam( const StringA& strParam )
            {
                m_vTargets.push_back( strParam );
            }

            //! dump the command to stdout.
            void dump( std::ostream& out );
        private:
            friend class AppShell;
            StringA             m_strName;   //! Name of the command.
            TargetList         m_vTargets;   //! Target list
            ParamList           m_vParams;   //! Parameter list
        private:

            //! Adjust escaped characters in the command and parameters.
            void adjustEscapedCharacters();

            H_ALLOCRAW_OPERATORS( AppShell_Command );
        }; //end of class Command

    public:

        //! Command function.
        typedef Function2<Command*, AppShell*>  CommandFunc;

        //! Command Item in command map
        struct CommandItem
        {
            StringA       strDesc;
            CommandFunc  funcCmd;
            H_ALLOCRAW_OPERATORS( AppShell_CommandItem );
        };

        H_DEF_HASHMAP( StringA, CommandItem*, CommandMap );

        typedef StringAList            CommandStringList;
        enum { MAX_CommandHistory = 20, };  //! max command history list.
    public:
        AppShell( void );
        ~AppShell( void );

        //! Process a command text.
        //! \remark Command consists of a command name, any parameter with or without value. e.g."move -front 433.2 -left 433.0"
        //! \par Application should call the method to parse command and dispatch command processor.
        void processCommand( const StringA& strText );

        //! Register command.
        //! \note command with name "help" is reserved by the shell.
        //! \return false if command with the same name has registered.
        bool registerCommand( const StringA& strCmdName, const CommandFunc& func, const StringA& strDesc );

        //! Unregister command with the name.
        void ungisterCommand( const StringA& strCmdName );

        //! Gets command item by command name.
        //! \return NULL if can not find any one.
        const CommandItem* getCommandItem( const StringA& strCmdName );


        //! Clear commands in the object.
        void clearCommands();

        //! Show all helps content.
        void showCommandDescriptions();

        //! Show one command description associate with the command name
        void showCommandDescription( const String& strCmdName );

        //! Gets command map registered.
        const CommandMap& getCommandMap()const;


        //! Sets standard output log.
        void setStdOut( Log* pLog );

        //! Gets standard out log.
        Log* getStdOut()const;


        //! Sets error output log.
        void setErrorOut( Log* pLog );

        //! Gets error out log. All error should be out put here.
        Log* getErrorOut()const;


        ////! Cache asynchronized command in queue.
        ////! \remark It is thread safe, and used where processCommand not proper.
        //void cacheAsyncCommandT( const StringA& strCmd );

        ////! Process
        //void processCachedCommandT();

        //! Gets history.
        const CommandStringList& getHistory()const;


        //! \brief Parse the command text and return command object.
        //! \param strCmdText
        //! \param cmd[out] The command will be stored here.
        //! \return bool return true if parse successfully, or return false.
        static bool parseCommand( const StringA& strCmdText, Command& cmd );
        static bool parseCommand( const char* szCmdText,     Command& cmd );

    private:

        CommandMap             m_mapCmd;   //! Command map.

        Log*                m_pStdOut;
        Log*              m_pErrorOut;

        CommandStringList    m_vHistory;


    private:
        //! \brief parse parameters like ' --host=192.168.0.43' and push the parameter Param to <code>cmd</code>
        //! \param token
        //! \param cmd[out] The command will be stored here.
        static void parseParam( Tokener &token, Command& cmd );

        //! \brief parse a value. It takes care of string quoted with single or double quoter.
        static StringA parseValue( Tokener &token );

        //! \brief parse the command name.
        //! \param token
        //! \param cmd[out] The command will be stored here.
        //! \return bool return true if parse successfully, or return false.
        static bool parseCommandName( Tokener &token, AppShell::Command &cmd );

        //! parse single char parameters, e.g. 'ps -aux' command has there single char parameters: a,u,x
        //! and push the parameters Param to <code>cmd</code>
        //! \param token
        //! \param cmd[out]
        static void parseSingleCharParam( Tokener& token, Command& pcmd );


        //! Execute the command. This will call the function binded to this command
        void processCommand( Command* pCmd  );


        void recordHistoryCommand( const StringA& strText );




        //! Show help information
        void processHelpCommand( const StringA &strText );

        //for test, we open this interface function
    private:
        //! Parse the command text and return command object.
        //! \note Returned object should be deleted by caller method.
        //Command* parseCommand( const StringA& strCmdText );

    };

    typedef RefPtr< AppShell > AppShellPtr;


    template<class T>
    T getShellParam( AppShell::Command* pCmd , const char* pParamName )
    {
        AppShell::Command::Param* pParam = pCmd->getParam( pParamName );

        if ( pParam && pParam->strVal.length() )
        {
            return osl::lexical_cast<T>( pParam->strVal );
        }
        else
        {
            throw std::exception();
        }
    }

    inline const AppShell::CommandMap& AppShell::getCommandMap() const
    {
        return m_mapCmd;
    }

    inline void AppShell::setStdOut( Log* pLog )
    {
        m_pStdOut = pLog;
    }

    inline Log* AppShell::getStdOut() const
    {
        return m_pStdOut;
    }

    inline void AppShell::setErrorOut( Log* pLog )
    {
        m_pErrorOut = pLog;
    }

    inline Log* AppShell::getErrorOut() const
    {
        return m_pErrorOut;
    }

    inline const AppShell::CommandStringList& AppShell::getHistory() const
    {
        return m_vHistory;
    }

    inline bool operator==( const AppShell::Command::Param& lhs, const AppShell::Command::Param& rhs )
    {
        return rhs.strName == lhs.strName && rhs.strVal == lhs.strVal;
    }
};

#endif // end of #if H_PROVIDE_APPSHELL



#endif// end of # 

