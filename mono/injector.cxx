#include "injector.hxx"

namespace injector
{
	typedef void( __cdecl* t_mono_thread_attach )( mono_domain* );
	t_mono_thread_attach mono_thread_attach;

	typedef mono_domain* ( __cdecl* t_mono_get_root_domain )( void );
	t_mono_get_root_domain mono_get_root_domain;

	typedef mono_image* ( __cdecl* t_mono_assembly_get_image )( mono_assembly* );
	t_mono_assembly_get_image mono_assembly_get_image;

	typedef mono_class* ( __cdecl* t_mono_class_from_name )( mono_image*, const char*, const char* );
	t_mono_class_from_name mono_class_from_name;

	typedef mono_method* ( __cdecl* t_mono_class_get_method_from_name )( mono_class*, const char*, int );
	t_mono_class_get_method_from_name mono_method_from_name;

	typedef mono_object* ( __cdecl* t_mono_runtime_invoke )( mono_method*, void*, void**, mono_object** );
	t_mono_runtime_invoke mono_runtime_invoke;

	typedef mono_image* ( __cdecl* t_mono_image_open_from_data )( const char*, uint64_t, bool, mono_image_open_status* );
	t_mono_image_open_from_data  mono_image_open_from_data;

	typedef mono_assembly* ( __cdecl* t_mono_assembly_load_from_full )( mono_image_open_status*, const char*, mono_image_open_status*, bool );
	t_mono_assembly_load_from_full mono_assembly_load_from_full;

	void init( HMODULE module )
	{
		mono_thread_attach = ( t_mono_thread_attach )GetProcAddress( module, "mono_thread_attach" );
		mono_get_root_domain = ( t_mono_get_root_domain )GetProcAddress( module, "mono_get_root_domain" );
		mono_assembly_get_image = ( t_mono_assembly_get_image )GetProcAddress( module, "mono_assembly_get_image" );
		mono_class_from_name = ( t_mono_class_from_name )GetProcAddress( module, "mono_class_from_name" );
		mono_method_from_name = ( t_mono_class_get_method_from_name )GetProcAddress( module, "mono_class_get_method_from_name" );
		mono_runtime_invoke = ( t_mono_runtime_invoke )GetProcAddress( module, "mono_runtime_invoke" );
		mono_image_open_from_data = ( t_mono_image_open_from_data )GetProcAddress( module, "mono_image_open_from_data" );
		mono_assembly_load_from_full = ( t_mono_assembly_load_from_full )GetProcAddress( module, "mono_assembly_load_from_full" );
	}

	void inject( )
	{
		mono_image* raw_image;
		mono_image* image;
		mono_assembly* assembly;


		HMODULE mono_module = LoadLibraryW( L"mono-2.0-bdwgc.dll" );
		init( mono_module );

		mono_thread_attach( mono_get_root_domain( ) );

		raw_image = mono_image_open_from_data( ( char* )dll_array, sizeof( dll_array ), true, NULL );
		assembly = mono_assembly_load_from_full( raw_image, dll_array, NULL, false );
		image = mono_assembly_get_image( assembly );
		mono_runtime_invoke( mono_method_from_name( mono_class_from_name( image, "namespace", "class" ), "method", NULL ), NULL, NULL, NULL );
	}
}