/* Wei Luo */

#include <stdbool.h>

typedef void (* ActionFunction) (void *data);
typedef bool (* ComparisonFunction) (void *data1, void *data2);
typedef bool (* CriteriaFunction) (void *data);
