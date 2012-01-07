#include "osl/include/QOSLibPrerequisits.h"

#ifdef H_OS_MACOSX
#include "OSXClipboard.h"
#include <sys/types.h>
#include <sys/sysctl.h>

namespace osl
{

    class _EXPORT_OSLIB OS::OSImpl
    {
    public:

        //! returns the current operation system version as string.
        const wchar_t* getOperationSystemVersion() const
        {


        }

        //! copies text to the clipboard
        void copyToClipboard( const c8* text ) const
        {
            OSXCopyToClipboard( text );

        }

        //! gets text from the clipboard
        //! \return Returns 0 if no string is in there.
        c8* getTextFromClipboard() const
        {
            return ( OSXCopyFromClipboard() );

        }

        //! gets the processor speed in megahertz
        //! \param MHz: The integer variable to store the speed in.
        //! \return Returns true if successful, false if not
        bool getProcessorSpeedMHz( u32* MHz ) const
        {
            struct clockinfo CpuClock;
            size_t Size = sizeof( clockinfo );

            if ( !sysctlbyname( "kern.clockrate", &CpuClock, &Size, NULL, 0 ) )
            {
                return false;
            }
            else if ( MHz )
            {
                *MHz = CpuClock.hz;
            }

            return true;

        }

        //! gets the total and available system RAM
        //! \param Total: will contain the total system memory
        //! \param Avail: will contain the available memory
        //! \return Returns true if successful, false if not
        bool getSystemMemory( u32* Total, u32* Avail ) const
        {
            H_ASSERT( false && "Not implemented" );

        }

        //! Sleep for a while.It will sleep the calling thread.
        //! \param nMilliseconds Milliseconds to sleep.
        void sleep( u32 nMilliseconds )
        {
            usleep( nMilliseconds * 1000 );
        }

    private:
    };

};//namespace

#endif // #if defined(H_OS_WINDOWS)
