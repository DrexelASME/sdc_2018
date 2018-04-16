/** @file <file_name>.h
 *  @brief <file_description>
 *  @author <first_name> <last_name> - <email>
 *  @date Created: <date>
 */

#ifndef FILE_NAME_H_
#define FILE_NAME_H_

#include <includes_arent_commented.h>

#define <define_name> <define_value> /**< <define_description> */

/** @struct <struct_name>
 *  @brief <struct_description>
 *  @author <first_name> <last_name> - <email>
 *  @date Created: <date>
 */
struct StructName {
	double var_1; /**< <var_description> */
	double var_2; /**< <var_description> */
};

namespace namespace_name {
/** @namespace <namespace_name>
 *  @brief <namespace_description>
 *  @author <first_name> <last_name> - <email>
 *  @date Created: <date>
 */

	void function(int&, int*);
	/** @fn void function(int&, int*)
	 *  @brief <function_description>
	 *  @details <detailed_description>
	 *  @author <first_name> <last_name> - <email>
	 *  @date Created: <date>
	 */

}

class ClassName {
/** @class <class_name>
 *  @brief <class_description>
 *  @author <first_name> <last_name> - <email>
 *  @date Created: <date>
 */

public:
	void function(int&, int*);
	/** @fn void function(int&, int*)
	 *  @brief <function_description>
	 *  @details <detailed_description>
	 *  @author <first_name> <last_name> - <email>
	 *  @date Created: <date>
	 */

private:
	double _variable = 0.0; /**< <var_description> */

};

#endif /* FILE_NAME_H_ */


