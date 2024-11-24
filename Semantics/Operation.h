// Заголовочный файл защиты от двойного включения
#pragma once

#include "Formula.h"

/**
 * @class Operation
 * @brief Шаблонный класс, представляющий операцию с определенным типом сущности.
 *
 * Этот класс предоставляет базовый функционал для операций с указанным типом сущности.
 * Тип сущности задается параметром шаблона `Type`.
 *
 * @tparam Type Тип сущности, связанной с операцией.
 */
template<EntityBaseType Type>
class Operation
{
public:
	/**
	 * @brief Конструктор по умолчанию для класса Operation.
	 */
	Operation(void);

	/**
	 * @brief Деструктор для класса Operation.
	 */
	~Operation(void);
};

/**
 * @brief Сравнивает два объекта Formula на идентичность.
 *
 * Эта функция проверяет, являются ли два объекта Formula идентичными, сравнивая их содержимое.
 *
 * @param first Первый объект Formula для сравнения.
 * @param second Второй объект Formula для сравнения.
 * @return Возвращает true, если два объекта Formula идентичны, иначе false.
 */
bool Identity(const Formula & first, const Formula & second);

/**
 * @brief Сравнивает два объекта Formula на равенство.
 *
 * Этот оператор сравнивает два объекта Formula на равенство, проверяя, одинаково ли их содержимое.
 *
 * @param first Первый объект Formula для сравнения.
 * @param second Второй объект Formula для сравнения.
 * @return Возвращает true, если два объекта Formula равны, иначе false.
 */
bool operator == (const Formula & first, const Formula & second);