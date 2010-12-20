# DO NOT EDIT! GENERATED AUTOMATICALLY!
# Copyright (C) 2002-2010 Free Software Foundation, Inc.
#
# This file is free software, distributed under the terms of the GNU
# General Public License.  As a special exception to the GNU General
# Public License, this file may be distributed as part of a program
# that contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
#
# This file represents the compiled summary of the specification in
# gnulib-cache.m4. It lists the computed macro invocations that need
# to be invoked from configure.ac.
# In projects that use version control, this file can be treated like
# other built files.


# This macro should be invoked from ./configure.ac, in the section
# "Checks for programs", right after AC_PROG_CC, and certainly before
# any checks for libraries, header files, types and library functions.
AC_DEFUN([gl_EARLY],
[
  m4_pattern_forbid([^gl_[A-Z]])dnl the gnulib macro namespace
  m4_pattern_allow([^gl_ES$])dnl a valid locale name
  m4_pattern_allow([^gl_LIBOBJS$])dnl a variable
  m4_pattern_allow([^gl_LTLIBOBJS$])dnl a variable
  AC_REQUIRE([AC_PROG_RANLIB])
  # Code from module alloca-opt:
  # Code from module announce-gen:
  # Code from module arg-nonnull:
  # Code from module array-list:
  # Code from module autobuild:
  AB_INIT
  # Code from module btowc:
  # Code from module c++defs:
  # Code from module c-ctype:
  # Code from module clock-time:
  # Code from module cloexec:
  # Code from module close-stream:
  # Code from module closeout:
  # Code from module configmake:
  # Code from module dup2:
  # Code from module environ:
  # Code from module errno:
  # Code from module error:
  # Code from module execute:
  # Code from module exitfail:
  # Code from module extensions:
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])
  # Code from module fatal-signal:
  # Code from module fcntl:
  # Code from module fcntl-h:
  # Code from module float:
  # Code from module fpending:
  # Code from module fpieee:
  AC_REQUIRE([gl_FP_IEEE])
  # Code from module fpucw:
  # Code from module frexp-nolibm:
  # Code from module frexpl-nolibm:
  # Code from module gendocs:
  # Code from module getdate:
  # Code from module getdtablesize:
  # Code from module getopt-gnu:
  # Code from module getopt-posix:
  # Code from module gettext:
  # Code from module gettext-h:
  # Code from module gettime:
  # Code from module gettimeofday:
  # Code from module gnumakefile:
  # Code from module gnupload:
  # Code from module havelib:
  # Code from module include_next:
  # Code from module inline:
  # Code from module intprops:
  # Code from module isnand-nolibm:
  # Code from module isnanf-nolibm:
  # Code from module isnanl-nolibm:
  # Code from module langinfo:
  # Code from module list:
  # Code from module localcharset:
  # Code from module lstat:
  # Code from module maintainer-makefile:
  # Code from module malloc-gnu:
  # Code from module malloc-posix:
  # Code from module malloca:
  # Code from module math:
  # Code from module mbrtowc:
  # Code from module mbsinit:
  # Code from module memchr:
  # Code from module mkstemp:
  # Code from module mktime:
  # Code from module multiarch:
  # Code from module nl_langinfo:
  # Code from module nocrash:
  # Code from module open:
  # Code from module parse-datetime:
  # Code from module posix_spawn-internal:
  # Code from module posix_spawn_file_actions_addopen:
  # Code from module posix_spawn_file_actions_destroy:
  # Code from module posix_spawn_file_actions_init:
  # Code from module posix_spawnattr_destroy:
  # Code from module posix_spawnattr_init:
  # Code from module posix_spawnattr_setflags:
  # Code from module posix_spawnattr_setsigmask:
  # Code from module posix_spawnp:
  # Code from module printf-frexp:
  # Code from module printf-frexpl:
  # Code from module printf-safe:
  # Code from module quotearg:
  # Code from module quotearg-simple:
  # Code from module rawmemchr:
  # Code from module regex:
  # Code from module sched:
  # Code from module setenv:
  # Code from module sigaction:
  # Code from module signal:
  # Code from module signbit:
  # Code from module sigprocmask:
  # Code from module size_max:
  # Code from module spawn:
  # Code from module ssize_t:
  # Code from module stat:
  # Code from module stdbool:
  # Code from module stddef:
  # Code from module stdint:
  # Code from module stdio:
  # Code from module stdlib:
  # Code from module strchrnul:
  # Code from module streq:
  # Code from module strerror:
  # Code from module string:
  # Code from module strsep:
  # Code from module sys_stat:
  # Code from module sys_time:
  # Code from module sys_wait:
  # Code from module tempname:
  # Code from module time:
  # Code from module time_r:
  # Code from module timespec:
  # Code from module unistd:
  # Code from module unsetenv:
  # Code from module useless-if-before-free:
  # Code from module vasnprintf:
  # Code from module vasnprintf-posix:
  # Code from module vasprintf:
  # Code from module vc-list-files:
  # Code from module verify:
  # Code from module wait-process:
  # Code from module waitpid:
  # Code from module warn-on-use:
  # Code from module wchar:
  # Code from module wcrtomb:
  # Code from module wctype:
  # Code from module xalloc:
  # Code from module xalloc-die:
  # Code from module xsize:
])

# This macro should be invoked from ./configure.ac, in the section
# "Check for header files, types and library functions".
AC_DEFUN([gl_INIT],
[
  AM_CONDITIONAL([GL_COND_LIBTOOL], [true])
  gl_cond_libtool=true
  gl_m4_base='m4'
  m4_pushdef([AC_LIBOBJ], m4_defn([gl_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([gl_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([gl_LIBSOURCES]))
  m4_pushdef([gl_LIBSOURCES_LIST], [])
  m4_pushdef([gl_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='lib'
  # Code from module alloca-opt:
  gl_FUNC_ALLOCA
  # Code from module announce-gen:
  # Code from module arg-nonnull:
  # Code from module array-list:
  # Code from module autobuild:
  # Code from module btowc:
  gl_FUNC_BTOWC
  gl_WCHAR_MODULE_INDICATOR([btowc])
  # Code from module c++defs:
  # Code from module c-ctype:
  # Code from module clock-time:
  gl_CLOCK_TIME
  # Code from module cloexec:
  gl_CLOEXEC
  gl_MODULE_INDICATOR_FOR_TESTS([cloexec])
  # Code from module close-stream:
  gl_CLOSE_STREAM
  gl_MODULE_INDICATOR([close-stream])
  # Code from module closeout:
  gl_CLOSEOUT
  # Code from module configmake:
  gl_CONFIGMAKE_PREP
  # Code from module dup2:
  gl_FUNC_DUP2
  gl_UNISTD_MODULE_INDICATOR([dup2])
  # Code from module environ:
  gl_ENVIRON
  gl_UNISTD_MODULE_INDICATOR([environ])
  # Code from module errno:
  gl_HEADER_ERRNO_H
  # Code from module error:
  gl_ERROR
  m4_ifdef([AM_XGETTEXT_OPTION],
    [AM_][XGETTEXT_OPTION([--flag=error:3:c-format])
     AM_][XGETTEXT_OPTION([--flag=error_at_line:5:c-format])])
  # Code from module execute:
  gl_EXECUTE
  # Code from module exitfail:
  # Code from module extensions:
  # Code from module fatal-signal:
  gl_FATAL_SIGNAL
  # Code from module fcntl:
  gl_FUNC_FCNTL
  gl_FCNTL_MODULE_INDICATOR([fcntl])
  # Code from module fcntl-h:
  gl_FCNTL_H
  # Code from module float:
  gl_FLOAT_H
  # Code from module fpending:
  gl_FUNC_FPENDING
  # Code from module fpieee:
  # Code from module fpucw:
  # Code from module frexp-nolibm:
  gl_FUNC_FREXP_NO_LIBM
  gl_MATH_MODULE_INDICATOR([frexp])
  # Code from module frexpl-nolibm:
  gl_FUNC_FREXPL_NO_LIBM
  gl_MATH_MODULE_INDICATOR([frexpl])
  # Code from module gendocs:
  # Code from module getdate:
  # Code from module getdtablesize:
  gl_FUNC_GETDTABLESIZE
  gl_UNISTD_MODULE_INDICATOR([getdtablesize])
  # Code from module getopt-gnu:
  gl_FUNC_GETOPT_GNU
  gl_MODULE_INDICATOR_FOR_TESTS([getopt-gnu])
  # Code from module getopt-posix:
  gl_FUNC_GETOPT_POSIX
  # Code from module gettext:
  dnl you must add AM_GNU_GETTEXT([external]) or similar to configure.ac.
  AM_GNU_GETTEXT_VERSION([0.18.1])
  # Code from module gettext-h:
  AC_SUBST([LIBINTL])
  AC_SUBST([LTLIBINTL])
  # Code from module gettime:
  gl_GETTIME
  # Code from module gettimeofday:
  gl_FUNC_GETTIMEOFDAY
  gl_SYS_TIME_MODULE_INDICATOR([gettimeofday])
  # Code from module gnumakefile:
  # Autoconf 2.61a.99 and earlier don't support linking a file only
  # in VPATH builds.  But since GNUmakefile is for maintainer use
  # only, it does not matter if we skip the link with older autoconf.
  # Automake 1.10.1 and earlier try to remove GNUmakefile in non-VPATH
  # builds, so use a shell variable to bypass this.
  GNUmakefile=GNUmakefile
  m4_if(m4_version_compare([2.61a.100],
  	m4_defn([m4_PACKAGE_VERSION])), [1], [],
        [AC_CONFIG_LINKS([$GNUmakefile:$GNUmakefile], [],
  	[GNUmakefile=$GNUmakefile])])
  # Code from module gnupload:
  # Code from module havelib:
  # Code from module include_next:
  # Code from module inline:
  gl_INLINE
  # Code from module intprops:
  # Code from module isnand-nolibm:
  gl_FUNC_ISNAND_NO_LIBM
  # Code from module isnanf-nolibm:
  gl_FUNC_ISNANF_NO_LIBM
  # Code from module isnanl-nolibm:
  gl_FUNC_ISNANL_NO_LIBM
  # Code from module langinfo:
  gl_LANGINFO_H
  # Code from module list:
  gl_LIST
  # Code from module localcharset:
  gl_LOCALCHARSET
  LOCALCHARSET_TESTS_ENVIRONMENT="CHARSETALIASDIR=\"\$(top_builddir)/$gl_source_base\""
  AC_SUBST([LOCALCHARSET_TESTS_ENVIRONMENT])
  # Code from module lstat:
  gl_FUNC_LSTAT
  gl_SYS_STAT_MODULE_INDICATOR([lstat])
  # Code from module maintainer-makefile:
  AC_CONFIG_COMMANDS_PRE([m4_ifdef([AH_HEADER],
    [AC_SUBST([CONFIG_INCLUDE], m4_defn([AH_HEADER]))])])
  # Code from module malloc-gnu:
  gl_FUNC_MALLOC_GNU
  gl_MODULE_INDICATOR([malloc-gnu])
  # Code from module malloc-posix:
  gl_FUNC_MALLOC_POSIX
  gl_STDLIB_MODULE_INDICATOR([malloc-posix])
  # Code from module malloca:
  gl_MALLOCA
  # Code from module math:
  gl_MATH_H
  # Code from module mbrtowc:
  gl_FUNC_MBRTOWC
  gl_WCHAR_MODULE_INDICATOR([mbrtowc])
  # Code from module mbsinit:
  gl_FUNC_MBSINIT
  gl_WCHAR_MODULE_INDICATOR([mbsinit])
  # Code from module memchr:
  gl_FUNC_MEMCHR
  gl_STRING_MODULE_INDICATOR([memchr])
  # Code from module mkstemp:
  gl_FUNC_MKSTEMP
  gl_STDLIB_MODULE_INDICATOR([mkstemp])
  # Code from module mktime:
  gl_FUNC_MKTIME
  gl_TIME_MODULE_INDICATOR([mktime])
  # Code from module multiarch:
  gl_MULTIARCH
  # Code from module nl_langinfo:
  gl_FUNC_NL_LANGINFO
  gl_LANGINFO_MODULE_INDICATOR([nl_langinfo])
  # Code from module nocrash:
  # Code from module open:
  gl_FUNC_OPEN
  gl_FCNTL_MODULE_INDICATOR([open])
  # Code from module parse-datetime:
  gl_PARSE_DATETIME
  # Code from module posix_spawn-internal:
  # Code from module posix_spawn_file_actions_addopen:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawn_faction_addopen])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawn_file_actions_addopen])
  # Code from module posix_spawn_file_actions_destroy:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawn_faction_destroy])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawn_file_actions_destroy])
  # Code from module posix_spawn_file_actions_init:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawn_faction_init])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawn_file_actions_init])
  # Code from module posix_spawnattr_destroy:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnattr_destroy])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnattr_destroy])
  # Code from module posix_spawnattr_init:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnattr_init])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnattr_init])
  # Code from module posix_spawnattr_setflags:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnattr_setflags])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnattr_setflags])
  # Code from module posix_spawnattr_setsigmask:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnattr_setsigmask])
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnattr_setsigmask])
  # Code from module posix_spawnp:
  gl_POSIX_SPAWN
  if test $HAVE_POSIX_SPAWN = 0 || test $REPLACE_POSIX_SPAWN = 1; then
    gl_REPLACE_SPAWN_H
    AC_LIBOBJ([spawnp])
    gl_POSIX_SPAWN_INTERNAL
  fi
  gl_SPAWN_MODULE_INDICATOR([posix_spawnp])
  # Code from module printf-frexp:
  gl_FUNC_PRINTF_FREXP
  # Code from module printf-frexpl:
  gl_FUNC_PRINTF_FREXPL
  # Code from module printf-safe:
  m4_divert_text([INIT_PREPARE], [gl_printf_safe=yes])
  # Code from module quotearg:
  gl_QUOTEARG
  # Code from module quotearg-simple:
  # Code from module rawmemchr:
  gl_FUNC_RAWMEMCHR
  gl_STRING_MODULE_INDICATOR([rawmemchr])
  # Code from module regex:
  gl_REGEX
  # Code from module sched:
  gl_SCHED_H
  # Code from module setenv:
  gl_FUNC_SETENV
  gl_STDLIB_MODULE_INDICATOR([setenv])
  # Code from module sigaction:
  gl_SIGACTION
  gl_SIGNAL_MODULE_INDICATOR([sigaction])
  # Code from module signal:
  gl_SIGNAL_H
  # Code from module signbit:
  gl_SIGNBIT
  gl_MATH_MODULE_INDICATOR([signbit])
  # Code from module sigprocmask:
  gl_SIGNALBLOCKING
  gl_SIGNAL_MODULE_INDICATOR([sigprocmask])
  # Code from module size_max:
  gl_SIZE_MAX
  # Code from module spawn:
  gl_SPAWN_H
  # Code from module ssize_t:
  gt_TYPE_SSIZE_T
  # Code from module stat:
  gl_FUNC_STAT
  gl_SYS_STAT_MODULE_INDICATOR([stat])
  # Code from module stdbool:
  AM_STDBOOL_H
  # Code from module stddef:
  gl_STDDEF_H
  # Code from module stdint:
  gl_STDINT_H
  # Code from module stdio:
  gl_STDIO_H
  # Code from module stdlib:
  gl_STDLIB_H
  # Code from module strchrnul:
  gl_FUNC_STRCHRNUL
  gl_STRING_MODULE_INDICATOR([strchrnul])
  # Code from module streq:
  # Code from module strerror:
  gl_FUNC_STRERROR
  gl_STRING_MODULE_INDICATOR([strerror])
  # Code from module string:
  gl_HEADER_STRING_H
  # Code from module strsep:
  gl_FUNC_STRSEP
  gl_STRING_MODULE_INDICATOR([strsep])
  # Code from module sys_stat:
  gl_HEADER_SYS_STAT_H
  AC_PROG_MKDIR_P
  # Code from module sys_time:
  gl_HEADER_SYS_TIME_H
  AC_PROG_MKDIR_P
  # Code from module sys_wait:
  gl_SYS_WAIT_H
  AC_PROG_MKDIR_P
  # Code from module tempname:
  gl_FUNC_GEN_TEMPNAME
  # Code from module time:
  gl_HEADER_TIME_H
  # Code from module time_r:
  gl_TIME_R
  gl_TIME_MODULE_INDICATOR([time_r])
  # Code from module timespec:
  gl_TIMESPEC
  # Code from module unistd:
  gl_UNISTD_H
  # Code from module unsetenv:
  gl_FUNC_UNSETENV
  gl_STDLIB_MODULE_INDICATOR([unsetenv])
  # Code from module useless-if-before-free:
  # Code from module vasnprintf:
  gl_FUNC_VASNPRINTF
  # Code from module vasnprintf-posix:
  gl_FUNC_VASNPRINTF_POSIX
  # Code from module vasprintf:
  gl_FUNC_VASPRINTF
  gl_STDIO_MODULE_INDICATOR([vasprintf])
  m4_ifdef([AM_XGETTEXT_OPTION],
    [AM_][XGETTEXT_OPTION([--flag=asprintf:2:c-format])
     AM_][XGETTEXT_OPTION([--flag=vasprintf:2:c-format])])
  # Code from module vc-list-files:
  # Code from module verify:
  # Code from module wait-process:
  gl_WAIT_PROCESS
  # Code from module waitpid:
  gl_FUNC_WAITPID
  gl_SYS_WAIT_MODULE_INDICATOR([waitpid])
  # Code from module warn-on-use:
  # Code from module wchar:
  gl_WCHAR_H
  # Code from module wcrtomb:
  gl_FUNC_WCRTOMB
  gl_WCHAR_MODULE_INDICATOR([wcrtomb])
  # Code from module wctype:
  gl_WCTYPE_H
  # Code from module xalloc:
  gl_XALLOC
  # Code from module xalloc-die:
  # Code from module xsize:
  gl_XSIZE
  # End of code from modules
  m4_ifval(gl_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([gl_LIBSOURCES_DIR])[ ||
      for gl_file in ]gl_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([gl_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([gl_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([gl_LIBSOURCES_DIR])
  m4_popdef([gl_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    gl_libobjs=
    gl_ltlibobjs=
    if test -n "$gl_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $gl_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        gl_libobjs="$gl_libobjs $i.$ac_objext"
        gl_ltlibobjs="$gl_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([gl_LIBOBJS], [$gl_libobjs])
    AC_SUBST([gl_LTLIBOBJS], [$gl_ltlibobjs])
  ])
  gltests_libdeps=
  gltests_ltlibdeps=
  m4_pushdef([AC_LIBOBJ], m4_defn([gltests_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([gltests_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([gltests_LIBSOURCES]))
  m4_pushdef([gltests_LIBSOURCES_LIST], [])
  m4_pushdef([gltests_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='tests'
changequote(,)dnl
  gltests_WITNESS=IN_`echo "${PACKAGE-$PACKAGE_TARNAME}" | LC_ALL=C tr abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ | LC_ALL=C sed -e 's/[^A-Z0-9_]/_/g'`_GNULIB_TESTS
changequote([, ])dnl
  AC_SUBST([gltests_WITNESS])
  gl_module_indicator_condition=$gltests_WITNESS
  m4_pushdef([gl_MODULE_INDICATOR_CONDITION], [$gl_module_indicator_condition])
  m4_popdef([gl_MODULE_INDICATOR_CONDITION])
  m4_ifval(gltests_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([gltests_LIBSOURCES_DIR])[ ||
      for gl_file in ]gltests_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([gltests_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([gltests_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([gltests_LIBSOURCES_DIR])
  m4_popdef([gltests_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    gltests_libobjs=
    gltests_ltlibobjs=
    if test -n "$gltests_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $gltests_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        gltests_libobjs="$gltests_libobjs $i.$ac_objext"
        gltests_ltlibobjs="$gltests_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([gltests_LIBOBJS], [$gltests_libobjs])
    AC_SUBST([gltests_LTLIBOBJS], [$gltests_ltlibobjs])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into gl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gl_LIBOBJ], [
  AS_LITERAL_IF([$1], [gl_LIBSOURCES([$1.c])])dnl
  gl_LIBOBJS="$gl_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into gl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gl_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [gl_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([gl_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([gl_LIBSOURCES_DIR], [lib])
      m4_append([gl_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into gltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gltests_LIBOBJ], [
  AS_LITERAL_IF([$1], [gltests_LIBSOURCES([$1.c])])dnl
  gltests_LIBOBJS="$gltests_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into gltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gltests_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [gltests_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([gltests_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([gltests_LIBSOURCES_DIR], [tests])
      m4_append([gltests_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# This macro records the list of files which have been installed by
# gnulib-tool and may be removed by future gnulib-tool invocations.
AC_DEFUN([gl_FILE_LIST], [
  build-aux/announce-gen
  build-aux/arg-nonnull.h
  build-aux/c++defs.h
  build-aux/config.rpath
  build-aux/gendocs.sh
  build-aux/gnupload
  build-aux/useless-if-before-free
  build-aux/vc-list-files
  build-aux/warn-on-use.h
  doc/gendocs_template
  doc/getdate.texi
  doc/parse-datetime.texi
  lib/alloca.in.h
  lib/asnprintf.c
  lib/asprintf.c
  lib/btowc.c
  lib/c-ctype.c
  lib/c-ctype.h
  lib/cloexec.c
  lib/cloexec.h
  lib/close-stream.c
  lib/close-stream.h
  lib/closeout.c
  lib/closeout.h
  lib/config.charset
  lib/dup2.c
  lib/errno.in.h
  lib/error.c
  lib/error.h
  lib/execute.c
  lib/execute.h
  lib/exitfail.c
  lib/exitfail.h
  lib/fatal-signal.c
  lib/fatal-signal.h
  lib/fcntl.c
  lib/fcntl.in.h
  lib/float+.h
  lib/float.in.h
  lib/fpending.c
  lib/fpending.h
  lib/fpucw.h
  lib/frexp.c
  lib/frexpl.c
  lib/getdate.h
  lib/getdtablesize.c
  lib/getopt.c
  lib/getopt.in.h
  lib/getopt1.c
  lib/getopt_int.h
  lib/gettext.h
  lib/gettime.c
  lib/gettimeofday.c
  lib/gl_array_list.c
  lib/gl_array_list.h
  lib/gl_list.c
  lib/gl_list.h
  lib/intprops.h
  lib/isnan.c
  lib/isnand-nolibm.h
  lib/isnand.c
  lib/isnanf-nolibm.h
  lib/isnanf.c
  lib/isnanl-nolibm.h
  lib/isnanl.c
  lib/iswblank.c
  lib/langinfo.in.h
  lib/localcharset.c
  lib/localcharset.h
  lib/lstat.c
  lib/malloc.c
  lib/malloca.c
  lib/malloca.h
  lib/malloca.valgrind
  lib/math.in.h
  lib/mbrtowc.c
  lib/mbsinit.c
  lib/memchr.c
  lib/memchr.valgrind
  lib/mkstemp.c
  lib/mktime-internal.h
  lib/mktime.c
  lib/nl_langinfo.c
  lib/open.c
  lib/parse-datetime.h
  lib/parse-datetime.y
  lib/printf-args.c
  lib/printf-args.h
  lib/printf-frexp.c
  lib/printf-frexp.h
  lib/printf-frexpl.c
  lib/printf-frexpl.h
  lib/printf-parse.c
  lib/printf-parse.h
  lib/quotearg.c
  lib/quotearg.h
  lib/rawmemchr.c
  lib/rawmemchr.valgrind
  lib/ref-add.sin
  lib/ref-del.sin
  lib/regcomp.c
  lib/regex.c
  lib/regex.h
  lib/regex_internal.c
  lib/regex_internal.h
  lib/regexec.c
  lib/sched.in.h
  lib/setenv.c
  lib/sig-handler.h
  lib/sigaction.c
  lib/signal.in.h
  lib/signbitd.c
  lib/signbitf.c
  lib/signbitl.c
  lib/sigprocmask.c
  lib/size_max.h
  lib/spawn.in.h
  lib/spawn_faction_addopen.c
  lib/spawn_faction_destroy.c
  lib/spawn_faction_init.c
  lib/spawn_int.h
  lib/spawnattr_destroy.c
  lib/spawnattr_init.c
  lib/spawnattr_setflags.c
  lib/spawnattr_setsigmask.c
  lib/spawni.c
  lib/spawnp.c
  lib/stat.c
  lib/stdbool.in.h
  lib/stddef.in.h
  lib/stdint.in.h
  lib/stdio-write.c
  lib/stdio.in.h
  lib/stdlib.in.h
  lib/strchrnul.c
  lib/strchrnul.valgrind
  lib/streq.h
  lib/strerror.c
  lib/string.in.h
  lib/strsep.c
  lib/sys_stat.in.h
  lib/sys_time.in.h
  lib/sys_wait.in.h
  lib/tempname.c
  lib/tempname.h
  lib/time.in.h
  lib/time_r.c
  lib/timespec.h
  lib/unistd.in.h
  lib/unsetenv.c
  lib/vasnprintf.c
  lib/vasnprintf.h
  lib/vasprintf.c
  lib/verify.h
  lib/w32spawn.h
  lib/wait-process.c
  lib/wait-process.h
  lib/waitpid.c
  lib/wchar.in.h
  lib/wcrtomb.c
  lib/wctype.in.h
  lib/xalloc-die.c
  lib/xalloc.h
  lib/xmalloc.c
  lib/xsize.h
  m4/00gnulib.m4
  m4/alloca.m4
  m4/asm-underscore.m4
  m4/autobuild.m4
  m4/bison.m4
  m4/btowc.m4
  m4/clock_time.m4
  m4/cloexec.m4
  m4/close-stream.m4
  m4/closeout.m4
  m4/codeset.m4
  m4/configmake.m4
  m4/dos.m4
  m4/dup2.m4
  m4/eealloc.m4
  m4/environ.m4
  m4/errno_h.m4
  m4/error.m4
  m4/execute.m4
  m4/exponentd.m4
  m4/exponentf.m4
  m4/exponentl.m4
  m4/extensions.m4
  m4/fatal-signal.m4
  m4/fcntl-o.m4
  m4/fcntl.m4
  m4/fcntl_h.m4
  m4/float_h.m4
  m4/fpending.m4
  m4/fpieee.m4
  m4/frexp.m4
  m4/frexpl.m4
  m4/getdtablesize.m4
  m4/getopt.m4
  m4/gettext.m4
  m4/gettime.m4
  m4/gettimeofday.m4
  m4/gl_list.m4
  m4/glibc2.m4
  m4/glibc21.m4
  m4/gnulib-common.m4
  m4/iconv.m4
  m4/include_next.m4
  m4/inline.m4
  m4/intdiv0.m4
  m4/intl.m4
  m4/intldir.m4
  m4/intlmacosx.m4
  m4/intmax.m4
  m4/intmax_t.m4
  m4/inttypes-pri.m4
  m4/inttypes_h.m4
  m4/isnand.m4
  m4/isnanf.m4
  m4/isnanl.m4
  m4/langinfo_h.m4
  m4/lcmessage.m4
  m4/ldexpl.m4
  m4/lib-ld.m4
  m4/lib-link.m4
  m4/lib-prefix.m4
  m4/localcharset.m4
  m4/locale-fr.m4
  m4/locale-ja.m4
  m4/locale-zh.m4
  m4/lock.m4
  m4/longlong.m4
  m4/lstat.m4
  m4/malloc.m4
  m4/malloca.m4
  m4/math_h.m4
  m4/mbrtowc.m4
  m4/mbsinit.m4
  m4/mbstate_t.m4
  m4/memchr.m4
  m4/mkstemp.m4
  m4/mktime.m4
  m4/mmap-anon.m4
  m4/mode_t.m4
  m4/multiarch.m4
  m4/nl_langinfo.m4
  m4/nls.m4
  m4/nocrash.m4
  m4/onceonly.m4
  m4/open.m4
  m4/parse-datetime.m4
  m4/po.m4
  m4/posix_spawn.m4
  m4/printf-frexp.m4
  m4/printf-frexpl.m4
  m4/printf-posix.m4
  m4/printf.m4
  m4/progtest.m4
  m4/quotearg.m4
  m4/rawmemchr.m4
  m4/regex.m4
  m4/sched_h.m4
  m4/setenv.m4
  m4/sig_atomic_t.m4
  m4/sigaction.m4
  m4/signal_h.m4
  m4/signalblocking.m4
  m4/signbit.m4
  m4/size_max.m4
  m4/spawn_h.m4
  m4/ssize_t.m4
  m4/stat.m4
  m4/stdbool.m4
  m4/stddef_h.m4
  m4/stdint.m4
  m4/stdint_h.m4
  m4/stdio_h.m4
  m4/stdlib_h.m4
  m4/strchrnul.m4
  m4/strerror.m4
  m4/string_h.m4
  m4/strsep.m4
  m4/sys_stat_h.m4
  m4/sys_time_h.m4
  m4/sys_wait_h.m4
  m4/tempname.m4
  m4/threadlib.m4
  m4/time_h.m4
  m4/time_r.m4
  m4/timespec.m4
  m4/tm_gmtoff.m4
  m4/uintmax_t.m4
  m4/unistd_h.m4
  m4/vasnprintf-posix.m4
  m4/vasnprintf.m4
  m4/vasprintf.m4
  m4/visibility.m4
  m4/wait-process.m4
  m4/waitpid.m4
  m4/warn-on-use.m4
  m4/wchar_h.m4
  m4/wchar_t.m4
  m4/wcrtomb.m4
  m4/wctype_h.m4
  m4/wint_t.m4
  m4/xalloc.m4
  m4/xsize.m4
  top/GNUmakefile
  top/maint.mk
])
