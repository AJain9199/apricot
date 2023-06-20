/**
 * Contains macros that serve no functional purpose other than increasing code readability and making code easier to
 * understand.
 *
 * Macros in this file:
 * OUT: specifies that a parameter to a function serves as an output
 * concat: concatenates two tokens
 */

#ifndef APRICOT_SPEC_H
#define APRICOT_SPEC_H

#define OUT(x) x


#define concat2(X, Y) X##Y
#define concat(X, Y)  concat2(X, Y)

#endif //APRICOT_SPEC_H
