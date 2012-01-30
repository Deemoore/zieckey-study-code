/****************************** Module Header ********************************\
    Name: no_copy.h
 Created: 2012/01/08 8:1:2012 1:40
  Author: weizili

 Purpose: 
\*****************************************************************************/
#ifndef OSLIB_NO_COPY_H_
#define OSLIB_NO_COPY_H_

namespace osl
{
    //! The derived class from NoCopy has no ability 
	//! to copy construct and assign construct
	class NoCopy
	{
	protected:
		NoCopy() {};
	private:
		NoCopy( const NoCopy& );
		NoCopy&operator=( const NoCopy& );
	};
}


#endif // OSLIB_NO_COPY_H_
