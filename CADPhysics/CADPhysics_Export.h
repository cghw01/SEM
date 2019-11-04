
#ifndef CADPhysics_EXPORT_H
#define CADPhysics_EXPORT_H

#ifdef CADPhysics_BUILT_AS_STATIC
#  define CADPhysics_EXPORT
#  define CADPHYSICS_NO_EXPORT
#else
#  ifndef CADPhysics_EXPORT
#    ifdef CADPhysics_EXPORTS
        /* We are building this library */
#      define CADPhysics_EXPORT 
#    else
        /* We are using this library */
#      define CADPhysics_EXPORT 
#    endif
#  endif

#  ifndef CADPHYSICS_NO_EXPORT
#    define CADPHYSICS_NO_EXPORT 
#  endif
#endif

#ifndef CADPHYSICS_DEPRECATED
#  define CADPHYSICS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef CADPHYSICS_DEPRECATED_EXPORT
#  define CADPHYSICS_DEPRECATED_EXPORT CADPhysics_EXPORT CADPHYSICS_DEPRECATED
#endif

#ifndef CADPHYSICS_DEPRECATED_NO_EXPORT
#  define CADPHYSICS_DEPRECATED_NO_EXPORT CADPHYSICS_NO_EXPORT CADPHYSICS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CADPHYSICS_NO_DEPRECATED
#    define CADPHYSICS_NO_DEPRECATED
#  endif
#endif

#endif
