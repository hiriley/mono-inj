#include "injector.hxx"

bool __stdcall DllMain( void*, unsigned long r, void* )
{
	if ( r != 1 )
		return false;

	injector::inject( );

	return true;
}