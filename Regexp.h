/*
 
 Regular-expression matching library for Ardiuno.
 
 Written by Nick Gammon.
 Date: 30 April 2011
 
 Heavily based on the Lua regular expression matching library written by Roberto Ierusalimschy. 
 
 Adapted to run on the Arduino by Nick Gammon.
 
 
 VERSION
 
  Version 1.0  - 30th April 2011
 

 */


// Maximum of captures we can return. 
// Increase if you need more, decrease to save memory.
#define MAXCAPTURES 16

// Result codes from calling regexp
#define REGEXP_MATCHED 1    // we got a match, see MatchState structure for capture

#define REGEXP_NOMATCH 0    // no match

// errors when matching
#define ERR_INVALID_CAPTURE_INDEX -1
#define ERR_INVALID_PATTERN_CAPTURE -2
#define ERR_MALFORMED_PATTERN_ENDS_WITH_ESCAPE -3
#define ERR_MALFORMED_PATTERN_ENDS_WITH_RH_SQUARE_BRACKET -4
#define ERR_UNBALANCED_PATTERN -5
#define ERR_TOO_MANY_CAPTURES -6
#define ERR_MISSING_LH_SQUARE_BRACKET_AFTER_ESC_F -7


/* macro to `unsign' a character */
#define uchar(c)        ((unsigned char)(c))

#define CAP_UNFINISHED	(-1)
#define CAP_POSITION	(-2)

typedef struct MatchState {
  const char *src_end;  /* end of source string */
  
public:
  
  // supply these two:
  const char *src;  /* source string */
  unsigned int src_len;    /* length of source string */
  
  // returned:
  
  unsigned int match_start;  // zero-relative offset of start of match
  unsigned int match_len;    // length of match
  
  int level;  /* total number of captures in array below (finished or unfinished) */
  struct {
    const char *init;
    int len;  // might be CAP_UNFINISHED or CAP_POSITION
  } capture[MAXCAPTURES];
} MatchState;

// the "escape" character 
#define REGEXP_ESC		'%'

// special characters that have to be escaped
#define SPECIALS	"^$*+?.([%-"

// parse a regular expression
char regexp (MatchState & ms, const char * pattern, unsigned int index);