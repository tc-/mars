AC_INIT([mars], [0.1], [tommy.l.s.carlsson@gmail.com])
AC_CONFIG_AUX_DIR([build])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_CANONICAL_HOST

AC_LANG([C++])
AC_PROG_CXX

AC_CHECK_LIB([ncurses], [initscr], [NCURSESLIB=-lncurses])
AC_SUBST([NCURSESLIB])
AC_CHECK_HEADERS([curses.h])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
   Makefile
])
AC_OUTPUT
