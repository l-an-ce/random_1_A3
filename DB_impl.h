/* DB_impl.h
 *
 * Header to declare private functions that should not be visible to
 * public users of the database.
 *
 * Author: Lexis Tran, Aryan Mahendru, Marek Maisonneuve, Lance Malafu
 * Lab instructor: Salwa Abougamila
 * Lecture instructor: Dhara Wagh, Abdullah Mohiuddin
 */

#ifndef DB_IMPL_H
#define DB_IMPL_H


int countEntriesHelper(int member, const char *thing);

int editHelper(int member,const char *thing);

void resizeTable(int table, char *add);

#endif