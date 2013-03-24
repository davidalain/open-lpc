/*
 * assert.h
 *
 *  Created on: Mar 5, 2013
 *      Author: David Alain
 */

#ifndef OPENLPC_ASSERT_H_
#define OPENLPC_ASSERT_H_

#ifdef USE_OPENLPC_ASSERT

void openlpc_assert(const char* msg, uint32_t exp);

#define ASSERT(msg, exp) 	openlpc_assert(msg, exp)
#else
#define ASSERT(msg, exp)
#endif


#endif /* ASSERT_H_ */
