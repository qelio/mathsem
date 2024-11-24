#pragma once

#include "Formula.h"

/**
 * @class Operation
 * @brief A template class that represents an operation with a specific entity type.
 *
 * This class provides basic functionality for operations of a given entity type.
 * The entity type is specified as a template parameter `Type`.
 *
 * @tparam Type The entity type associated with the operation.
 */
template<EntityBaseType Type>
class Operation
{
public:
	/**
	 * @brief Default constructor for the Operation class.
	 */
	Operation(void);

	/**
	 * @brief Destructor for the Operation class.
	 */
	~Operation(void);
};

/**
 * @brief Compares two Formula objects for identity.
 *
 * This function checks if two Formula objects are identical by comparing their contents.
 *
 * @param first The first Formula object to compare.
 * @param second The second Formula object to compare.
 * @return Returns true if the two Formula objects are identical, otherwise false.
 */
bool Identity(const Formula & first, const Formula & second);

/**
 * @brief Compares two Formula objects for equality.
 *
 * This operator compares two Formula objects for equality by checking if their contents are the same.
 *
 * @param first The first Formula object to compare.
 * @param second The second Formula object to compare.
 * @return Returns true if the two Formula objects are equal, otherwise false.
 */
bool operator == (const Formula & first, const Formula & second );
