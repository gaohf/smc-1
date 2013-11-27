dnl $Id$
dnl config.m4 for extension smc

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(smc, for smc support,
dnl Make sure that the comment is aligned:
[  --with-smc             Include smc support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(smc, whether to enable smc support,
dnl Make sure that the comment is aligned:
dnl [  --enable-smc           Enable smc support])

if test "$PHP_SMC" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-smc -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/smc.h"  # you most likely want to change this
  dnl if test -r $PHP_SMC/$SEARCH_FOR; then # path given as parameter
  dnl   SMC_DIR=$PHP_SMC
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for smc files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SMC_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SMC_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the smc distribution])
  dnl fi

  dnl # --with-smc -> add include path
  dnl PHP_ADD_INCLUDE($SMC_DIR/include)

  dnl # --with-smc -> check for lib and symbol presence
  dnl LIBNAME=smc # you may want to change this
  dnl LIBSYMBOL=smc # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SMC_DIR/lib, SMC_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SMCLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong smc lib version or lib not found])
  dnl ],[
  dnl   -L$SMC_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(SMC_SHARED_LIBADD)

  PHP_NEW_EXTENSION(smc, smc.c, $ext_shared)
fi
