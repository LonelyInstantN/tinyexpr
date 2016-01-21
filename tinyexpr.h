/*
 * TINYEXPR - Tiny recursive descent parser and evaluation engine in C
 *
 * Copyright (c) 2015, 2016 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgement in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef __TINYEXPR_H__
#define __TINYEXPR_H__



typedef double (*te_fun1)(double);
typedef double (*te_fun2)(double, double);


typedef struct te_expr {
    struct te_expr *left, *right;
    union {double value; te_fun1 f1; te_fun2 f2;};
    const double *bound;
} te_expr;


typedef struct {
    const char *name;
    const double *value;
} te_variable;


/* Note on error handling:
 * If the parser encounters an error, it will still return
 * an expression up to that point (which may be worthless or useful.
 * If the error pointer parameter is passed in and not null, the
 * parser will set it to roughly the index of the error in the
 * input expression. If there is no error, the parse sets
 * the error pointer to 0.
 */


/* Parses the input expression, evaluates it, and frees it. */
double te_interp(const char *expression, int *error);

/* Parses the input expression and binds variables. */
te_expr *te_compile(const char *expression, const te_variable *lookup, int lookup_len, int *error);

/* Evaluates the expression. */
double te_eval(te_expr *n);

/* Prints debugging information on the syntax tree. */
void te_print(const te_expr *n);

/* Frees the expression. */
void te_free(te_expr *n);



#endif /*__TINYEXPR_H__*/
