#ifndef MACROS_H
# define MACROS_H

/*
** Special characters not defined in op.h
*/

# define QUOTE_CHAR 			'"'
# define EOL_CHAR 				'\n'

/*
** Allowed characters in numerical value
*/

# define NUMERIC_CHARS			"-0123456789"

/*
** Padding Flags
*/

# define PAD_RIGHT 				1
# define PAD_LEFT 				2

/*
** Masks to extract line and column from int64 during error reporting
*/

# define LINE_MASK 0x0000FFFF
# define COL_MASK 0xFFFF0000

/*
** Size Restrictions
** (Max is 10000 lines at 80 tokens / line without comments, max token length 512)
*/

# define MAX_TOKEN_STR_SIZE		512
# define MAX_TOKEN_LIST_SIZE 	10000 * 80
# define MAX_INPUT_FILE_SIZE	MAX_TOKEN_STR_SIZE * MAX_TOKEN_LIST_SIZE

#endif
