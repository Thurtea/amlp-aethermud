#define Targeted       1
#define NoTarget       2
#define NoArgs         3
#define ForceAdverb    4
#define ExtraAdverbs   5
#define Locations      6
#define ForceLocation  7
#define Preposition    8
#define DisableAnd     9
 
#define SaveFile "/daemon/soul/soul"
#define FallBackFile "/daemon/soul/default.c"
#define SOUL_ADVERBS "/daemon/adverbs"
 
static string HelpPage = (
 "Most of the following emotes can be combined with 'and' in any "
 "order, which allows you to create some rather interesting "
 "sentences.  However, some are unique and cannot be combined with "
 "others.  Most emotes are set up to use adverbs, which you "
 "can substitute with other adverbs ('emotehelp adverbs' for list). "
 "Adverbs may be specified with a shortened prefix, but note that the "
 "first match found in the pool will be used. (example: 'h' would "
 "return handsomly, where 'hap' would return happily).  If you do not "
 "wish for the default adverb to be displayed, enter '.' as the "
 "adverb."
 "\n\n"
 "Syntax: smile br            : You smile broadly.\n"
 "        smile blitz         : You smile happily at Blitz.\n"
 "        smile blitz br      : You smile broadly at Blitz.\n"
 "        smile blitz and ack : You smile happily at Blitz and ack.\n"
 "\n");
