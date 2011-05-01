/*
 
 Regular-expression matching library for Arduino.
 
 Written by Nick Gammon.
 Date: 30 April 2011
 
 Heavily based on the Lua regular expression matching library written by Roberto Ierusalimschy. 
 
 Adapted to run on the Arduino by Nick Gammon.
 
 
 VERSION
 
  Version 1.0  - 30th April 2011 : initial release.
  Version 1.1  - 1st May 2011    : added some helper functions, made more modular.


 */


// Maximum of captures we can return. 
// Increase if you need more, decrease to save memory.
#define MAXCAPTURES 32

// the "magic escape" character 
#define REGEXP_ESC		'%'

// special characters that have to be escaped
// (not used in the library, but you might need this)
#define REGEXP_SPECIALS	"^$*+?.([%-"

// Result codes from calling regexp:

// we got a match
#define REGEXP_MATCHED 1    

// no match, or not attempted to match yet
#define REGEXP_NOMATCH 0    

// errors when matching
#define ERR_INVALID_CAPTURE_INDEX -1
#define ERR_INVALID_PATTERN_CAPTURE -2
#define ERR_MALFORMED_PATTERN_ENDS_WITH_ESCAPE -3
#define ERR_MALFORMED_PATTERN_ENDS_WITH_RH_SQUARE_BRACKET -4
#define ERR_UNBALANCED_PATTERN -5
#define ERR_TOO_MANY_CAPTURES -6
#define ERR_MISSING_LH_SQUARE_BRACKET_AFTER_ESC_F -7
#define ERR_NO_TARGET_STRING -8


/* macro to `unsign' a character */
#define uchar(c)        ((unsigned char)(c))

// special capture "lengths"
#define CAP_UNFINISHED	(-1)
#define CAP_POSITION	(-2)

typedef class MatchState {
private:
  
  char result;  // result of last Match call
  
public:
  
  MatchState () : src (0), result (REGEXP_NOMATCH) {};  // constructor
  
  // supply these two:
  const char *src;  /* source string */
  unsigned int src_len;    /* length of source string */

  // used internally  
  const char *src_end;  /* end of source string */
 
  // returned fields:
  
  unsigned int MatchStart;    // zero-relative offset of start of match
  unsigned int MatchLength;   // length of match
  
  int level;  /* total number of captures in array below (finished or unfinished) */
  
  // capture addresses and lengths
  struct {
    const char *init;
    int len;              // might be CAP_UNFINISHED or CAP_POSITION
  } capture[MAXCAPTURES];
  
  // add target string, null-terminated
  void Target (const char * s);
  // add target string, with specified length
  void Target (const char * s, const unsigned int len);
  // do a match on a supplied pattern and zero-relative starting point
  char Match (const char * pattern, unsigned int index = 0);
  // return the matching string
  char * GetMatch (char * s);
  // return capture string n
  char * GetCapture (char * s, const int n);
  // get result of previous match
  char GetResult () { return result; }
  
} MatchState;

