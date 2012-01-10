#include "osl/include/inner_pre.h"

#if H_PROVIDE_APPSHELL


#include <iomanip>
#include <iostream>
#include <fstream>
#include "osl/include/shell.h"
#include "osl/include/tokener.h"
#include "osl/include/string_ext.h"
#include "osl/include/string_util.h"

namespace osl
{

    typedef std::pair<u32, u32> SubStringA; // first is start of string, second is last over pos which is not included in the string.

    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////
    AppShell::Command::Param* AppShell::Command::getParam( const StringA& strParam )
    {
        ParamList::iterator it( m_vParams.begin() ), ite( m_vParams.end() );

        for ( ; it != ite; ++it )
        {
            if ( it->strName == strParam )
            {
                return &( *it );
            }
        }

        return NULL;
    }
    //----------------------------------------------
    bool AppShell::Command::hasTarget( const String& strTarget/*, bool bCaseSensitive = true*/ ) const
    {
        return osl::is_contain( m_vTargets , strTarget );
    }

    //-------------------------------------------------------------------
    bool AppShell::Command::hasParam( const Command::Param& param/*, bool bCaseSensitive = true*/ ) const
    {
        return osl::is_contain( m_vParams, param );
    }

    //----------------------------------------------
    void AppShell::Command::dump( std::ostream& out )
    {
        // name
        out << m_strName;
        // parameters
        {
            ParamList::iterator it( m_vParams.begin() ), ite( m_vParams.end() );

            for ( ; it != ite; ++it )
            {
                if ( it->strVal.size() )
                {
                    out << " --" << it->strName << "=" << it->strVal;
                }
                else
                {
                    if ( it->strName.size() == 1 )
                    {
                        out << " -" << it->strName;
                    }
                    else
                    {
                        out << " --" << it->strName;
                    }
                }
            }
        }
        // targets.
        {
            TargetList::iterator it( m_vTargets.begin() ), ite( m_vTargets.end() );

            for ( ; it != ite; ++it )
            {
                out << " " << *it;
            }
        }
    }
    //----------------------------------------------
    void AppShell::Command::adjustEscapedCharacters()
    {
    }

    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////
// 	void countClass( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
// 	{
// 		// "countClass CActor (class name) " 
// 
// 		if( pCmd->getTargetList().size() == 0 )
// 		{
// 			if( pShell->getStdOut() )
// 			{
// 				pShell->getStdOut()->logMessage( "no class name prescribed.  \"countClass CActor\" " );
// 			}
// 			return;
// 		}
// 
// 		osl::u32 nNumInsts = osl::MemAlloc::getNumInstancesByClassName( pCmd->getTargetList()[0].c_str() );
// 
// 		osl::OStringStreamA strTip;
// 
// 		strTip << nNumInsts << " -- "<< pCmd->getTargetList()[0];
// 
// 		if( pShell->getStdOut() )
// 		{
// 			pShell->getStdOut()->logMessage( strTip.str() );
// 		}
// 		else
// 		{
// 			std::cout << strTip.str().c_str();
// 		}
// 	}
// 
// 	//------------------------------------------------------
// 	void findMemObject( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
// 	{
// 		//findMemObject,	                             "findMemObject --class=(class name) --size=(class size, 0 is slow) --index=0 --rd=0(reference depth) " 
// 
// 		osl::StringA strClass = "Object";
// 		osl::u32   nClassSize = 0;
// 		osl::u32       nIndex = 0;
// 		osl::s32     nRefDepth = 0;
// 		// strClass
// 		{
// 			osl::AppShell::Command::Param* pParam = pCmd->getParam("class");
// 			if( pParam )
// 			{
// 				strClass = pParam->strVal;
// 			}
// 		}
// 
// 		// nClassSize
// 		{
// 			osl::AppShell::Command::Param* pParam = pCmd->getParam("size");
// 			if( pParam )
// 			{
// 				nClassSize = atoi( pParam->strVal.c_str() );
// 			}
// 		}
// 
// 		// nIndex
// 		{
// 			osl::AppShell::Command::Param* pParam = pCmd->getParam("index");
// 			if( pParam )
// 			{
// 				nIndex = atoi( pParam->strVal.c_str() );
// 			}
// 		}
// 
// 		// nRefDepth
// 		{
// 			osl::AppShell::Command::Param* pParam = pCmd->getParam("rd");
// 			if( pParam )
// 			{
// 				nRefDepth = atoi( pParam->strVal.c_str() );
// 			}
// 		}
// 
// 		osl::OStringStreamA strTip;
// 
// 		//
// 		void* pObject = osl::MemAlloc::findObjectByClassName( strClass.c_str(), nClassSize, nIndex );
// 
// 		while( pObject && --nRefDepth >= 0 )
// 		{
// 			strTip << "The " << ( nRefDepth + 1) << "'th reference holder:" << std::endl;
// 			{
// 				osl::MemAlloc::ObjectNode** pNodes = NULL;
// 
// 				//
// 				osl::MemAlloc::findObjectReferences( pNodes, (osl::PointerInt)pObject );
// 
// 				if( pNodes )
// 				{
// 					osl::MemAlloc::ObjectNode** pReferences = pNodes;
// 
// 					while( *pReferences )
// 					{
// 						strTip << "node size: " << (*pReferences)->nNodeSize
// 							<< "  offset:" << (*pReferences)->nOffset
// 							<< "  ==addr:0x" << std::setbase(16) << (osl::u64)(*pReferences)->pObject << "==";
// 
// 
// 						if( (*pReferences)->szClass )
// 						{
// 							strTip  << "  class:"  << (*pReferences)->szClass;
// 						}
// 
// 						if( (*pReferences)->szFile )
// 						{
// 							strTip  << "  file:"  << (*pReferences)->szFile;
// 						}
// 
// 						if( (*pReferences)->nLine )
// 						{
// 							strTip << "  line:" << (*pReferences)->nLine;
// 						}
// 
// 						strTip << std::endl;
// 
// 						++pReferences;
// 					}//while( *pReferences )
// 
// 					// enter new depth.
// 					pObject = *pNodes;
// 
// 					//
// 					osl::MemAlloc::freeObjectReferenceList( pNodes );
// 
// 				}//if( pNodes )
// 				else
// 				{
// 					strTip << "find nothing";
// 				}
// 			}
// 		}//while( pObject && --nRefDepth >= 0 )
// 
// #ifdef H_OS_WINDOWS
// 		strTip << "You can set break in HWorldShellCommands.h" << std::endl
// 			<< "object addr:0x" << std::setbase(16) << (osl::u64)pObject;
// #endif
// 
// 		if( pShell->getStdOut() )
// 		{
// 			pShell->getStdOut()->logMessage( strTip.str() );
// 		}
// 		else
// 		{
// 			std::cout << strTip.str().c_str();
// 		}
// 	}
// 
// 	//------------------------------------------------------
// 	void findMemRef( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
// 	{
// 		//"findMemRef --val=(value to find. integer, ignored if class used ) --class=(class name)  --size=(class size, 0 is slow.) --index=(i\'th element default is 0)" 
// 
// 		osl::PointerInt   val = 2048;
// 
// 		osl::StringA strClass;
// 		osl::u32   nClassSize = 0;
// 		osl::u32       nIndex = 0;
// 
// 		// strClass
// 		{
// 			osl::AppShell::Command::Param* pParam = pCmd->getParam("class");
// 			if( pParam )
// 			{
// 				strClass = pParam->strVal;
// 			}
// 		}
// 
// 		// nClassSize
// 		{
// 			osl::AppShell::Command::Param* pParam = pCmd->getParam("size");
// 			if( pParam )
// 			{
// 				nClassSize = atoi( pParam->strVal.c_str() );
// 			}
// 		}
// 
// 		// nIndex
// 		{
// 			osl::AppShell::Command::Param* pParam = pCmd->getParam("index");
// 			if( pParam )
// 			{
// 				nIndex = atoi( pParam->strVal.c_str() );
// 			}
// 		}
// 
// 		// val
// 		{
// 			osl::AppShell::Command::Param* pParam = pCmd->getParam("val");
// 			if( pParam )
// 			{
// 				val = atoi( pParam->strVal.c_str() );
// 			}
// 		}
// 
// 
// 		osl::OStringStreamA strTip;
// 		strTip << "findMemRef=======" << std::endl;
// 
// 		osl::MemAlloc::ObjectNode** pNodes = NULL;
// 
// 		if( strClass.length() )
// 		{
// 			osl::MemAlloc::findObjectReferences( pNodes, strClass.c_str(), nClassSize, nIndex );
// 		}else if( val != 0 )
// 		{
// 			//
// 			osl::MemAlloc::findObjectReferences( pNodes, val );
// 		}
// 
// 		if( pNodes )
// 		{
// 			osl::MemAlloc::ObjectNode** pReferences = pNodes;
// 
// 			while( *pReferences )
// 			{
// 				strTip << "node size: " << (*pReferences)->nNodeSize
// 					<< "  offset:" << (*pReferences)->nOffset
// 					<< "  ==addr:0x" << std::setbase(16) << (osl::u64)(*pReferences)->pObject << "==";
// 
// 
// 				if( (*pReferences)->szClass )
// 				{
// 					strTip  << "  class:"  << (*pReferences)->szClass;
// 				}
// 
// 				if( (*pReferences)->szFile )
// 				{
// 					strTip  << "  file:"  << (*pReferences)->szFile;
// 				}
// 
// 				if( (*pReferences)->nLine )
// 				{
// 					strTip << "  line:" << (*pReferences)->nLine;
// 				}
// 
// 				strTip << std::endl;
// 
// 				++pReferences;
// 			}
// 		}
// 
// 		if( pShell->getStdOut() )
// 		{
// 			pShell->getStdOut()->logMessage( strTip.str() );
// 		}
// 		else
// 		{
// 			std::cout << strTip.str().c_str();
// 		}
// 
// 		osl::MemAlloc::freeObjectReferenceList( pNodes );
// 	}

	//////////////////////////////////////////////////////////////////////////
	//                    Stat Memory
	//////////////////////////////////////////////////////////////////////////
	//
	void statMem( osl::AppShell::Command* pCmd, osl::AppShell* pShell )
	{
		// "statMem (Statistics all memory infos.) --min=123 --max=545 "
		bool bDetail = false;
		if( pCmd->hasTarget( "d" ) )
		{
			bDetail = true;
		}

		if( pCmd->hasTarget("usage") )
		{
// 			osl::OStringStreamA strTip;
// 
// 			osl::MemAlloc::dumpStats( strTip, 1024 * 1024 * 10, 0xffffffff, bDetail );	
// 
// 			if( pShell->getStdOut() )
// 			{
// 				pShell->getStdOut()->logMessage( strTip.str() );
// 			}

		}
		else
		{

			osl::u32 nMin = 0;
			osl::u32 nMax = 0xffffffff;

			// min size
			{
				osl::AppShell::Command::Param* pParam = pCmd->getParam("min");
				if( pParam )
				{
					nMin = atoi( pParam->strVal.c_str() );
				}
			}

			// max size
			{
				osl::AppShell::Command::Param* pParam = pCmd->getParam("max");
				if( pParam )
				{
					nMax = atoi( pParam->strVal.c_str() );
				}
			}


			std::fstream strTip( "memstat.txt", std::ios_base::out );


			// gets memory stat string. It may be very long, so patenice
// 			if( nMin > 0 || nMax < 1024 * 1024 * 50  )
// 			{
// 				osl::MemAlloc::dumpStats( strTip, nMin, nMax, bDetail  );	
// 
// 			}else{
// 
// 				osl::MemAlloc::dumpStats( strTip, bDetail );	
// 			}

			strTip.close();

			if( pShell->getStdOut() )
			{
				//pShell->getStdOut()->logMessage( "log has been added to memstat.txt, please see it." );
			}
			else
			{
				std::cout <<  "log has been added to memstat.txt, please see it." ;
			}

#ifdef H_OS_WINDOWS
			::ShellExecuteA( NULL, "edit", "memstat.txt", NULL, NULL, SW_SHOWNORMAL );
#endif
		}

	}

    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////
    
    //----------------------------------------------
    AppShell::AppShell( void )
    {
		m_pStdOut = NULL;
		m_pErrorOut = NULL;

		// add basic commands
// 		registerCommand( "countClass",    AppShell::CommandFunc( &countClass),   "countClass CActor (class name) " );
// 		registerCommand( "statMem",       AppShell::CommandFunc( &statMem),      "statMem (Statistics all memory infos.) --min=123 --max=545 " );
// 		registerCommand( "findMemObject", AppShell::CommandFunc( &findMemObject),   "findMemObject --class=(class name) --size=(class size, 0 is slow) --index=0 --rd=0(reference depth) "  );
// 		registerCommand( "findMemRef",    AppShell::CommandFunc( &findMemRef),      "findMemRef --val=(value to find. integer, ignored if class used ) --class=(class name)  --size=(class size, 0 is slow.) --index=(i\'th element default is 0)"  );
    }
    //----------------------------------------------
    AppShell::~AppShell( void )
    {
        clearCommands();
    }
    //----------------------------------------------
    bool AppShell::registerCommand( const StringA& strCmdName, const AppShell::CommandFunc& func, const StringA& strDesc )
    {
        StringA strCmdNameLC = strCmdName;
        StringUtil::toLowerCase( strCmdNameLC );
        CommandMap::iterator itCmd = m_mapCmd.find( strCmdNameLC );

        if ( itCmd != m_mapCmd.end() || strCmdName == "help" )
        {
            return false;
        }

        // add one command.
        CommandItem*& pCmd = m_mapCmd[strCmdNameLC];
        pCmd = H_NEW CommandItem;
        pCmd->strDesc = strDesc;
        pCmd->funcCmd = func;
        return true;
    }
    //----------------------------------------------
    void AppShell::ungisterCommand( const StringA& strCmdName )
    {
        StringA strCmdNameLC = strCmdName;
        StringUtil::toLowerCase( strCmdNameLC );
        CommandMap::iterator itCmd = m_mapCmd.find( strCmdNameLC );

        if ( itCmd != m_mapCmd.end() )
        {
            delete itCmd->second;
            m_mapCmd.erase( itCmd );
        }
    }
    //----------------------------------------------
    const AppShell::CommandItem* AppShell::getCommandItem( const StringA& strCmdName )
    {
        StringA strCmdNameLC = strCmdName;
        StringUtil::toLowerCase( strCmdNameLC );
        CommandMap::iterator itCmd = m_mapCmd.find( strCmdNameLC );

        if ( itCmd != m_mapCmd.end() )
        {
            return itCmd->second;
        }

        return NULL;
    }
    //----------------------------------------------
    void AppShell::clearCommands()
    {
        std::for_each( m_mapCmd.begin() , m_mapCmd.end() , DeletePairedPointer() );
        m_mapCmd.clear();
    }
    //----------------------------------------------
    void AppShell::showCommandDescriptions()
    {
        osl::OStringStreamA strTip;
        strTip << "#-----------------------------------------" << std::endl;
        strTip << "Help:" << std::endl;
        CommandMap::iterator it( m_mapCmd.begin() ), ite( m_mapCmd.end() );

        for ( ; it != ite; ++it )
        {
            strTip << it->first.c_str() << std::endl
                   << "   " << it->second->strDesc.c_str();
            strTip << std::endl;
        }

        strTip <<  "->";

        if ( m_pStdOut )
        {
            ////m_pStdOut->logMessage( strTip.str() );
        }
        else
        {
            std::cout << strTip.str();
        }
    }
    //----------------------------------------------
    void AppShell::showCommandDescription( const String& strCmdName )
    {
        osl::StringA strCmdNameLC = strCmdName;
        StringUtil::toLowerCase( strCmdNameLC );
        CommandMap::iterator it( m_mapCmd.find( strCmdNameLC ) );
        osl::OStringStreamA strTip;

        if ( it != m_mapCmd.end() )
        {
            strTip << it->first.c_str() << std::endl
                   << "   " << it->second->strDesc.c_str();
            strTip << std::endl;
        }
        else
        {
            return showCommandDescriptions();
        }

        strTip <<  "->";

        if ( m_pStdOut )
        {
            //m_pStdOut->logMessage( strTip.str() );
        }
        else
        {
            std::cout << strTip.str();
        }
    }
    //----------------------------------------------
    //! \param pStartBuf [in.out] Start buffer position.
    //! \return false if arrived end of string.
    bool skipSpaces( const char*& pStartBuf, const char* pEndBuf )
    {
        /// Skip leading sapce.
        while ( pStartBuf < pEndBuf )
        {
            if ( *pStartBuf == ' ' )
            {
                ++pStartBuf;
                continue;
            }

            break;
        }

        return pStartBuf == pEndBuf ? false : true;
    }
    //----------------------------------------------
    bool isParamChar( char nChar )
    {
        if ( ( nChar >= '0' && nChar <= '9' ) ||
                ( nChar >= 'a' && nChar <= 'z' ) ||
                ( nChar >= 'A' && nChar <= 'Z' ) ||
                nChar == '_' ||
                nChar == '-'
           )
        {
            return true;
        }

        return false;
    }
    bool isParamName( const char* pStartBuf, const char* pEndBuf )
    {
        /// check name.
        while ( pStartBuf < pEndBuf )
        {
            if ( !isParamChar( *pStartBuf ) )
            {
                return false;
            }

            ++pStartBuf;
        }

        return true;
    }
    //----------------------------------------------
    bool isNameChar( char nChar )
    {
        if ( ( nChar >= '0' && nChar <= '9' ) ||
                ( nChar >= 'a' && nChar <= 'z' ) ||
                ( nChar >= 'A' && nChar <= 'Z' ) ||
                nChar == '_' ||
                nChar == '.' ||
                nChar == '-' )
        {
            return true;
        }

        return false;
    }
    bool isCommandName( const char* pStartBuf, const char* pEndBuf )
    {
        /// check name.
        while ( pStartBuf < pEndBuf )
        {
            if ( !isNameChar( *pStartBuf ) )
            {
                return false;
            }

            ++pStartBuf;
        }

        return true;
    }
    //! \return NULL if can not find any char. Convert char will be considered.
    const char* findChar( const char* pStartBuf, const char* pEndBuf, char nChar )
    {
        const char* pCurBuf = pStartBuf;

        while ( pCurBuf < pEndBuf )
        {
            if ( *pCurBuf == nChar )
            {
                u32 nCountBackSlack = 0;
                const char* pTmpBuf = pCurBuf - 1;

                // count number of '\'      '\\a' '\\\a' '...\\\\...\a' '\a'
                while ( pTmpBuf >= pStartBuf )
                {
                    if ( *pTmpBuf-- == '\\' )
                    {
                        ++nCountBackSlack;
                        continue;
                    }

                    break;;
                }

                if ( nCountBackSlack % 2 == 1 )
                {
                    ++pCurBuf;
                    continue;
                }

                return pCurBuf;
            }

            ++pCurBuf;
        }

        return NULL;
    }
    //! \return NULL if can not find any char. Convert char will be considered.
    const char* findCharWithPostSpace( const char* pStartBuf, const char* pEndBuf, char nChar )
    {
        const char* pCurBuf = findChar( pStartBuf, pEndBuf, nChar );

        if ( pCurBuf )
        {
            if ( pCurBuf < pEndBuf )
            {
                if ( pCurBuf[1] != ' ' && pCurBuf + 1 != pEndBuf )
                {
                    return NULL;
                }
            }

            return pCurBuf;
        }

        return NULL;
    }

    ////----------------------------------------------
    //bool isNameChar( char nChar )
    //{
    //	if( ( nChar >= '0' && nChar <= '9' ) ||
    //		( nChar >= 'a' && nChar <= 'z' ) ||
    //		( nChar >= 'A' && nChar <= 'Z' ) ||
    //		nChar == '_' ||
    //		nChar == '.' ||
    //		nChar == '-')
    //	{
    //		return true;
    //	}

    //	return false;
    //}


    //----------------------------------------------
    //! \param szText Original
    //! \param strName[out] Name of command.
    //! \return of charachter range eated.
    //u32 parseCommandName( const char* szText )
    //{
    //    const char* pCurBuf = szText;
    //    const char* pEndBuf = pCurBuf + strlen( szText );
    //    const char* pLastCh = strchr( pCurBuf, ' ' );

    //    if ( pLastCh == NULL )
    //    {
    //        pLastCh = pEndBuf;
    //    }

    //    /// check name.
    //    if ( isCommandName( pCurBuf, pLastCh ) )
    //    {
    //        return u32( pLastCh - szText );
    //    }

    //    return 0;
    //}
    ////----------------------------------------------
    ////! \return eated number of character.
    //u32 parseValue( const char* pStartBuf, const char* pEndBuf, SubStringA& strVal )
    //{
    //    const char* pCurBuf = pStartBuf;

    //    /// Skip leading sapce.
    //    if ( !skipSpaces( pCurBuf, pEndBuf ) )
    //    {
    //        return 0;
    //    }

    //    if ( *pCurBuf != '\'' && *pCurBuf != '"' )
    //    {
    //        // find space.
    //        const char* pSpacePos = findChar( pCurBuf, pEndBuf, ' ' );

    //        if ( !pSpacePos )
    //        {
    //            pSpacePos = pEndBuf;
    //        }

    //        strVal.first  = pCurBuf - pStartBuf;
    //        strVal.second = pSpacePos - pStartBuf;
    //        return pSpacePos - pStartBuf;
    //    }

    //    const char* pSQuotaPos = findChar( pCurBuf, pEndBuf, '\'' );

    //    const char* pDQuotaPos = findChar( pCurBuf, pEndBuf, '"' );

    //    if ( pSQuotaPos && ( !pDQuotaPos || pSQuotaPos < pDQuotaPos ) )
    //    {
    //        const char* pNextSQuotaPos = findCharWithPostSpace( pSQuotaPos + 1, pEndBuf, '\'' );

    //        if ( !pNextSQuotaPos )
    //        {
    //            return 0;
    //        }

    //        strVal.first  = pCurBuf + 1 - pStartBuf;
    //        strVal.second = pNextSQuotaPos - pStartBuf;
    //        return pNextSQuotaPos + 1 - pStartBuf;
    //    }
    //    else if ( pDQuotaPos && ( !pSQuotaPos || pDQuotaPos < pSQuotaPos ) )
    //    {
    //        const char* pNextDQuotaPos = findCharWithPostSpace( pDQuotaPos  + 1, pEndBuf, '"' );

    //        if ( !pNextDQuotaPos )
    //        {
    //            return 0;
    //        }

    //        strVal.first  = pCurBuf + 1 - pStartBuf;
    //        strVal.second = pNextDQuotaPos - pStartBuf;
    //        return pNextDQuotaPos + 1 - pStartBuf;
    //    }
    //    else
    //    {
    //        // find space.
    //        const char* pSpacePos = findChar( pCurBuf, pEndBuf, ' ' );

    //        if ( !pSpacePos )
    //        {
    //            pSpacePos = pEndBuf;
    //        }

    //        strVal.first  = pCurBuf - pStartBuf;
    //        strVal.second = pSpacePos - pStartBuf;
    //        return pSpacePos - pStartBuf;
    //    }
    //}
    ////----------------------------------------------
    //u32 parseParamWithValue( const char* pStartBuf, const char* pEndBuf, SubStringA& strParam, SubStringA& strVal )
    //{
    //    const char* pCurBuf = pStartBuf;

    //    /// Skip leading sapce.
    //    if ( !skipSpaces( pCurBuf, pEndBuf ) )
    //    {
    //        return 0;
    //    }

    //    strParam.first = strParam.second = 0;
    //    strVal.first = strVal.second = 0;
    //    // parse name and value.
    //    //while( pCurBuf < pEndBuf )
    //    {
    //        const char* pLastNameCh = NULL;
    //        const char* pSpaceCh  = findChar( pCurBuf, pEndBuf, ' ' );
    //        const char* pAssignCh = findChar( pCurBuf, pEndBuf, '=' );

    //        if ( !pSpaceCh )
    //        {
    //            pSpaceCh = pEndBuf;
    //        }

    //        pLastNameCh = ( pSpaceCh < pAssignCh || !pAssignCh ) ? pSpaceCh : pAssignCh;

    //        if ( pLastNameCh <= pCurBuf )
    //        {
    //            return 0;
    //        }

    //        // 1. parameter name
    //        {
    //            strParam.first  = pCurBuf - pStartBuf;
    //            strParam.second = pLastNameCh - pStartBuf;

    //            if ( !isParamName( pCurBuf, pCurBuf + strParam.second ) )
    //            {
    //                return 0;
    //            }

    //            pCurBuf = pLastNameCh;
    //        }
    //        // 2. value
    //        {
    //            // find start of value.
    //            while ( pCurBuf < pEndBuf )
    //            {
    //                if ( *pCurBuf != ' ' &&
    //                        *pCurBuf != '=' )
    //                {
    //                    break;
    //                }

    //                ++pCurBuf;
    //            }

    //            // parse value
    //            SubStringA val;
    //            u32 nNumEated = parseValue( pCurBuf, pEndBuf, val );

    //            if ( nNumEated != 0 )
    //            {
    //                strVal.first  = pCurBuf - pStartBuf + val.first;
    //                strVal.second = strVal.first + ( val.second - val.first );
    //                // process quota
    //                pCurBuf += nNumEated;
    //            }
    //        }// parse value.
    //    }// parse name and value.
    //    return int( pCurBuf - pStartBuf );
    //}
    ////----------------------------------------------
    //u32 parseParamWithoutValue( const char* pStartBuf, const char* pEndBuf, HList<SubStringA>& vParams )
    //{
    //    const char* pCurBuf = pStartBuf;

    //    /// Skip leading sapce.
    //    if ( !skipSpaces( pCurBuf, pEndBuf ) )
    //    {
    //        return 0;
    //    }

    //    const char* pLastCh = strchr( pCurBuf, ' ' );

    //    if ( pLastCh == NULL )
    //    {
    //        pLastCh = pEndBuf;
    //    }

    //    while ( pCurBuf < pLastCh )
    //    {
    //        if ( !isParamChar( *pCurBuf ) )
    //        {
    //            return 0;
    //        }

    //        // add one parameter.
    //        {
    //            SubStringA str;
    //            str.first  = pCurBuf - pStartBuf;
    //            str.second = str.first + 1;
    //            vParams.push_back( str );
    //        }
    //        ++pCurBuf;
    //    }

    //    return int( pCurBuf - pStartBuf );
    //}
    ////----------------------------------------------
    //SubStringA parseTarget( const char* pStartBuf, const char* pEndBuf )
    //{
    //	const char* pCurBuf = pStartBuf;

    //	/// Skip leading space.
    //	if( !skipSpaces( pCurBuf, pEndBuf ) )
    //	{
    //		return 0;
    //	}

    //	return parseValue( pCurBuf, pEndBuf );
    //}


    //-------------------------------------------------------------------
    void AppShell::parseSingleCharParam( Tokener& token, AppShell::Command& cmd )
    {
        //parse parameter name
        token.skipSpaces();
        StringA s = token.nextString();
        Command::Param param;

        for ( u32 i = 0; i < s.length(); ++i )
        {
            param.strName.resize( 1 );
            param.strName[0] = s[i];
            param.strVal  = "";
            cmd.m_vParams.push_back( param );
        }
    }

    //-------------------------------------------------------------------
    bool AppShell::parseCommand( const StringA& strCmdText, AppShell::Command& cmd )
    {
        return parseCommand( strCmdText.c_str(), cmd );
    }

    //-------------------------------------------------------------------
    bool AppShell::parseCommand( const char* szCmdText,     Command& cmd )
    {
        Tokener token( szCmdText );
        /// parse command name.
        bool bParseOK = parseCommandName( token, cmd );

        if ( !bParseOK )
        {
            return false;
        }

        /// parse parameter.
        char c = token.nextClean();

        do
        {
            switch ( c )
            {
                    //parameter, name and value
                case '-':
                    if ( token.next() == '-' ) // e.g. --ParamName=value
                    {
                        parseParam( token, cmd );
                    }
                    else//e.g.  the command 'ps -aux' has 3 parameter: a,u,x
                    {
                        token.back();
                        parseSingleCharParam( token, cmd );
                    }
                    break;
                case 0:
                    break;
                default:
                    //parameter, only target name.
                    token.back();
                    cmd.m_vTargets.push_back( parseValue( token ) );
            }
            c = token.nextClean();
        }
        while ( c );

        return true;
    }

    //----------------------------------------------
    void AppShell::processCommand( const StringA& strText )
    {
        StringA strTrimedText = strText;
        StringUtil::trim( strTrimedText );

        if ( !strTrimedText.empty() )
        {
            Command cmd;
            bool bParseSuccess = parseCommand( strTrimedText, cmd );

            if ( bParseSuccess )
            {
                recordHistoryCommand( strText );
                processCommand( &cmd );
            }
            else if ( strTrimedText[0] == '?' )
            {
                processHelpCommand( strTrimedText );
            }
            else
            {
                if ( m_pStdOut )
                {
                    //m_pStdOut->logMessage( "Invalid command text!!" );
                }
                else
                {
                    std::cout << "Invalid command text!!";
                }
            }
        }

        if ( m_pStdOut )
        {
            //m_pStdOut->logMessage( "->" );
        }
        else
        {
            std::cout << std::endl << "->";
        }
    }

    void AppShell::parseParam( Tokener &token, AppShell::Command& cmd )
    {
        //parse parameter name
        token.skipSpaces();
        Command::Param param;
        param.strName = token.nextString( '=' );
        StringUtil::trim( param.strName, false, true );

        if ( param.strName.size() == 0 ) //不太标准参数，例如：configure --help
        {
            // 两个短杠 ‘--’，却没有等于号‘=’
            param.strName = parseValue( token );
        }
        else
        {
            //标准参数，例如: configure --prefix=/usr/local
            //parse parameter value
            param.strVal = parseValue( token );
        }

        cmd.m_vParams.push_back( param );
    }

    void AppShell::processCommand( Command* pCmd )
    {
        const CommandItem* pCmdItem = getCommandItem( pCmd->getName() );

        if ( pCmdItem )
        {
            if ( pCmdItem->funcCmd.getFunctionBase() )
            {
                pCmdItem->funcCmd( pCmd, this );
            }
        }
        else if ( pCmd->getName() == "help" || pCmd->getName() == "?" )
        {
            if ( pCmd->getTargetList().size() )
            {
                showCommandDescription( pCmd->getTargetList()[0] );
            }
            else
            {
                showCommandDescriptions();
            }
        }
        else
        {
            OStringStreamA strTip;
            strTip << "Unknown command:";
            pCmd->dump( strTip );

            if ( m_pStdOut )
            {
                //m_pStdOut->logMessage( strTip.str() );
            }
            else
            {
                std::cout << strTip.str();
            }
        }
    }

    void AppShell::recordHistoryCommand( const StringA& strText )
    {
        // put to history.
        m_vHistory.push_front( strText );

        if ( m_vHistory.size() > MAX_CommandHistory )
        {
            m_vHistory.pop_back();
        }
    }

    void AppShell::processHelpCommand( const StringA &strText )
    {
        StringA strCmdName;

        if ( strText.size() > 1 )
        {
            Tokener token( strText.c_str(), strText.size() );
            assert( token.next() == '?' );
            strCmdName = token.nextString();
        }

        showCommandDescription( strCmdName );
//         String strCmdName;
//
//         if ( strText.size() > 1 )
//         {
//             const StringA::value_type* pStartBuf = &strText[1];
//             const StringA::value_type* pEndBuf = &strText[0] + strText.size();
//
//             SubStringA strVal;
//
//             if ( parseValue( pStartBuf, pEndBuf, strVal ) )
//             {
//                 strCmdName.assign( pStartBuf + strVal.first, pStartBuf + strVal.second );
//             }
//         }
//
//         showCommandDescription( strCmdName );
    }

    //-------------------------------------------------------------------
    StringA AppShell::parseValue( Tokener &token  )
    {
        token.skipSpaces();
        char testc = token.next();
        StringA val;

        if ( testc == '"' || testc == '\'' )
        {
            val = token.nextString( testc );
            //StringUtil::trim( val );
        }
        else
        {
            token.back();
            val = token.nextString();
            StringUtil::trim( val, true, false );
        }

        return val;
    }

    //-------------------------------------------------------------------
    bool AppShell::parseCommandName( Tokener &token, AppShell::Command &cmd )
    {
        token.skipSpaces();
        char testc = token.next();

        if ( testc != '?' )
        {
            token.back();
            StringA strCmdName = token.nextString();
            StringUtil::trim( strCmdName );

            if ( strCmdName.length() )
            {
                cmd.m_strName = strCmdName;
            }
            else
            {
                return false;
            }
        }
        else
        {
            cmd.m_strName = "?";
            token.skipSpaces();
            StringA target = token.nextString();

            if ( target.length() )
            {
                cmd.addTargetParam( target );
            }
            else
            {
                return false;
            }
        }

        return true;
    }



};


#endif // end of #if H_PROVIDE_APPSHELL


