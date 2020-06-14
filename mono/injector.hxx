#pragma once
#include <windows.h>
#include <string>
#include <thread>
#include "dll.hxx"

namespace injector
{
	typedef void mono_object;
	typedef void mono_domain;
	typedef void mono_assembly;
	typedef void mono_image;
	typedef void mono_class;
	typedef void mono_method;
	typedef void mono_image_open_status;

	void init( HMODULE module );
	void inject( );
}