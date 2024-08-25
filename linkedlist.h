/* Wei Luo */

#include <stdbool.h>

typedef void (* ActionFunction) (void *data);
typedef bool (* ComparisonFunction) (void *data1, void *data2);
typedef bool (* CriteriaFunction) (void *data);

int deleteSome(void *p2head, CriteriaFunction mustGo, ActionFunction disposal, int text) ;
bool insert(void *p2head, void *data, ComparisonFunction goesInFrontOf, int text) ;
void iterate(void *head, ActionFunction doThis) ;
void sort(void *hptr, ComparisonFunction cf) ;
