#pragma once

#include "common_functions.h"
//#include <stdint.h>

/**
 * @enum EntityBaseType
 * @brief Перечисление типов сущностей, используемых в логических формулах.
 */
enum EntityBaseType {
    NONE_FORMULA, ///< Неопределенный тип сущности.
    ATOMIC_FORMULA = 1, ///< Тип атомарной формулы.
    NEGATIVE_OPERATION = 2, ///< Операция отрицания (НЕ).
    QUANTIFIER1_OPERATION = 3, ///< Операция квантора типа 1 (например, для всеобщей квантификации).
    QUANTIFIER2_OPERATION = 4, ///< Операция квантора типа 2 (например, для существующей квантификации).
    AND_OPERATION = 5,  ///< Логическая операция И.
    OR_OPERATION = 6,  ///< Логическая операция ИЛИ.
    FORMULA_SET = 7,  ///< Набор формул.
    BELONGING_PREDICATE = 8, ///< Предикат принадлежности множеству.
    TUPLE = 9, ///< Сущность кортежа.
    SUBSET = 10, ///< Операция подмножества.
    REPLACE_VARIABLE = 11, ///< Операция замены переменной.
};

/**
 * @enum Formula_Feature
 * @brief Перечисление возможных характеристик или состояний формулы.
 */
enum Formula_Feature {
    NONE_FEATURE,  ///< Без особых характеристик.
    TRUTH_FEATURE = 1, ///< Формула истинна.
    FALSE_FEATURE = 2, ///< Формула ложна.
    PERFORMED_FEATURE = 3,  ///< Формула выполнена.
    ATOMARN_FEATURE = 4 ///< Формула атомарная.
};

/**
 * @enum VariableType
 * @brief Перечисление типов переменных, используемых в логических формулах.
 */
enum VariableType {
    NONE_VARIABLE, ///< Неопределенный тип переменной.
    VARIABLE = 1, ///< Стандартный тип переменной.
    SET = 2 ///< Тип переменной множества.
};

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
// Если libxml2 включен, здесь обрабатывается сериализация/десериализация XML.
#else
// Классы, представляющие элементы переменных и формул, если libxml не используется.
class CVariableItem;  ///< Класс для элемента переменной, представляющий логические переменные.
class CFormulaItem;  ///< Класс для элемента формулы, часть представления логической формулы.
class CSetItem;    ///< Класс для элемента множества, представляющий множества формул.
#endif

/**
 * @class Level
 * @brief Класс, представляющий уровень или контекст для переменной или формулы.
 *
 * Этот класс используется для инкапсуляции уровня переменной или формулы, который может быть использован для сравнения или контекстной манипуляции.
 */
class Level
{
protected:
    tstring level; ///< Строка, представляющая уровень.

public:
    /**
     * @brief Конструктор по умолчанию, инициализирует уровень значением "0".
     */
    Level() { level = _T("0"); }

    /**
     * @brief Параметризованный конструктор, инициализирует уровень заданной строкой.
     * @param tstr Строка уровня для инициализации.
     */
    Level(tstring & tstr) { level = tstr; }

    /**
     * @brief Деструктор для очистки объекта Level.
     */
    ~Level() {}

    /**
     * @brief Получает текущую строку уровня.
     * @return Строка уровня.
     */
    tstring & GetLevel() { return level; }

    /**
     * @brief Задает уровень указанной строкой.
     * @param tstr Строка для установки в качестве уровня.
     */
    void SetLevel(tstring & tstr) { level = tstr; }

    /**
     * @brief Сравнивает текущий уровень с другим уровнем.
     * @param l Другой уровень для сравнения.
     * @return True, если уровни равны, иначе false.
     */
    bool compare(const Level& l) { return !level.compare(l.level); }
};

/**
 * @class EntityVariable
 * @brief Класс, представляющий переменную сущность в логической формуле.
 *
 * Этот класс используется для обработки переменных, включая их типы, метки и индексы, а также предоставляет методы для манипуляции и сравнения.
 */
class EntityVariable: public Level
{
    VariableType type; ///< Тип переменной (стандартная переменная или множество).
    tstring label; ///< Метка, представляющая переменную.
    tstring index; ///< Индекс для различения разных экземпляров одной и той же переменной.
    tstring redefinition; ///< Переопределение переменной (если необходимо).
    tstring text; ///< Текстовое представление переменной.

public:
    /**
     * @brief Конструктор по умолчанию, инициализирующий переменную значениями по умолчанию.
     */
    EntityVariable() { type = VARIABLE; label = _T("x"); index = _T(""); SetText(); }

    /**
     * @brief Деструктор для очистки объекта EntityVariable.
     */
    ~EntityVariable() {}

    /**
     * @brief Конструктор с параметрами для инициализации типа переменной, метки и индекса.
     * @param str Метка переменной.
     * @param index_ Индекс переменной.
     * @param type_ Тип переменной (либо VARIABLE, либо SET).
     */
    EntityVariable(const tstring & str, const tstring & index_, VariableType type_)
        { label = str; index = index_; type = type_; SetText(); }

    /**
     * @brief Конструктор копирования для создания новой EntityVariable из существующей.
     * @param ev EntityVariable, которую нужно скопировать.
     */
    EntityVariable(const EntityVariable & ev) {
        type = ev.type;
        label = ev.label;
        index = ev.index;
        SetText();
        Level * pl = (Level *)&ev;
        SetLevel(pl->GetLevel());
        redefinition = ev.redefinition;
    }

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
    // Логика сериализации XML здесь, если libxml2 включен.
#else
    /**
     * @brief Конструктор из элемента переменной в случае, если libxml2 не используется.
     * @param vi Элемент переменной для инициализации.
     */
    EntityVariable(const CVariableItem& vi);
#endif
};





















/**
 * Возвращает текст, учитывая переопределение, если оно доступно.
 * Если переопределение установлено, вернет переопределенный текст,
 * иначе вернет оригинальный текст.
 *
 * @return Указатель на текущий текст (либо переопределенный, либо оригинальный).
 */
tstring * GetText() { if(redefinition.length() > 0) return &redefinition; else return &text; };

/**
 * Возвращает начальный (оригинальный) текст, не учитывая переопределение.
 *
 * @return Указатель на оригинальный текст.
 */
tstring * GetInitialText() { return &text; };

/**
 * Устанавливает текст для метки и добавляет индекс с специальным форматированием.
 * Этот метод объединяет метку с отформатированным индексом, если он есть.
 *
 * @note Метод в настоящее время не добавляет индекс, так как код закомментирован.
 */
void SetText()
{
    text = label;
    for(size_t i = 0; i < index.length(); i++)
    {
        text += _T("<Symbol=/low>");
        text += index.at(i);
    }
};

/**
 * Устанавливает текст переопределения.
 *
 * @param new_text Новый текст для установки в качестве переопределения.
 */
void SetRedefinition(tstring & new_text) { redefinition = new_text; };

/**
 * Возвращает текст переопределения.
 *
 * @return Ссылка на текст переопределения.
 */
tstring & GetRedefinition() { return redefinition; };

/**
 * Сравнивает текущую переменную с другой.
 *
 * @param ev EntityVariable для сравнения.
 * @return true, если переменные равны, иначе false.
 */
bool compare(const EntityVariable&);

/**
 * Проверяет, является ли переменная множеством.
 *
 * @return true, если тип SET, иначе false.
 */
bool isSet() { bool res = false; (type == SET) ? res = true : res = false; return res; };

/**
 * Проверяет, является ли переменная типа VARIABLE.
 *
 * @return true, если тип VARIABLE, иначе false.
 */
bool isVariable() { bool res; (type == VARIABLE) ? res = true : res = false; return res; };

/**
 * Возвращает метку переменной сущности.
 *
 * @return Ссылка на метку.
 */
tstring & GetLabel() { return label; };

/**
 * Возвращает индекс переменной сущности.
 *
 * @return Ссылка на индекс.
 */
tstring & GetIndex() { return index; };

/**
 * Возвращает тип переменной.
 *
 * @return Тип переменной как VariableType.
 */
VariableType GetType() { return type; };

/**
 * Устанавливает индекс переменной сущности.
 *
 * @param ind Новый индекс для установки.
 */
void SetIndex(tstring & ind) { index = ind; };

/**
 * Устанавливает метку переменной сущности.
 *
 * @param lab Новая метка для установки.
 */
void SetLabel(tstring & lab) { label = lab; };

/**
 * Устанавливает тип переменной сущности.
 *
 * @param type_ Новый тип для установки.
 */
void SetType(VariableType type_) { type = type_; };

/**
 * Оператор равенства для сравнения двух объектов EntityVariable.
 *
 * @param ev1 Первая EntityVariable для сравнения.
 * @param ev2 Вторая EntityVariable для сравнения.
 * @return true, если переменные равны, иначе false.
 */
bool operator == (EntityVariable& ev1, EntityVariable& ev2);

/**
 * Представляет сущность со свободными и связанными переменными, описанием и дополнительной информацией.
 * Предоставляет методы для доступа к свободным и связанным переменным, а также к тексту и описанию сущности.
 */
class EntityBase
{
protected:
    vector <EntityVariable *> freeVariables;  ///< Список свободных переменных.
    vector <EntityVariable *> linkedVariables;  ///< Список связанных переменных.
    tstring description;  ///< Описание сущности.
    tstring addons;  ///< Дополнения, связанные с сущностью.
    tstring label; ///< Метка, связанная с сущностью.
    tstring text; ///< Текст, связанный с сущностью.
    EntityBaseType type; ///< Тип сущности по перечислению EntityBaseType.
    tstring redefined_text; ///< Переопределенный текст, если таков имеется.
    bool redefined; ///< Флаг, указывающий, было ли сущность переопределена.
    EntityBase * replaced_base; ///< Указатель на замененную сущность, или nullptr.
    EntityVariable * initial_variable; ///< Начальная переменная, или nullptr.
    EntityVariable * new_variable; ///< Новая переменная, или nullptr.

public:
    /**
     * Конструктор по умолчанию для класса EntityBase.
     */
    EntityBase(void);

    /**
     * Деструктор для класса EntityBase.
     */
    ~EntityBase(void);

    /**
     * Возвращает список свободных переменных.
     *
     * @return Указатель на вектор свободных переменных.
     */
    vector <EntityVariable *> * getFreeVariables() { return &freeVariables; };

    /**
     * Возвращает список связанных переменных.
     *
     * @return Указатель на вектор связанных переменных.
     */
    vector <EntityVariable *> * getLinkedVariables() { return &linkedVariables; };

    /**
     * Возвращает текст, связанный с сущностью, учитывая переопределение, если оно имеется.
     *
     * @return Ссылка на текущий текст (либо переопределенный, либо оригинальный).
     */
    tstring & getText() { if(redefined_text.length() > 0) return redefined_text; else return text; };

    /**
     * Возвращает описание сущности.
     *
     * @return Указатель на строку описания.
     */
    tstring * getDescription() { return &description; };

    /**
     * Возвращает дополнения, связанные с сущностью.
     *
     * @return Указатель на строку дополнений.
     */
    tstring * getAddOns() { return &addons; };

    /**
     * Устанавливает текст для сущности.
     *
     * @param lpctstr Текст для установки.
     */
    void SetText(LPCTSTR lpctstr);

    /**
     * Устанавливает переопределенный текст для сущности.
     *
     * @param lpctstr Переопределенный текст для установки.
     */
    //void SetIRedefinedText(LPCTSTR lpctstr) { redefined_text = lpctstr; };
};
/**
 * Устанавливает описание сущности.
 *
 * @param lpctstr Текст описания для установки.
 */
void SetDescription(LPCTSTR lpctstr) { description = lpctstr; };

/**
 * Устанавливает дополнения для сущности.
 *
 * @param lpctstr Текст дополнений для установки.
 */
void SetAddons(LPCTSTR lpctstr) { addons = lpctstr; };

/**
 * Возвращает указатель на метку сущности.
 *
 * @return Указатель на строку метки.
 */
tstring * getLabel() { return &label; };

/**
 * Возвращает указатель на начальный текст (до переопределения) сущности.
 *
 * @return Указатель на начальный текст.
 */
tstring * getInitialText() { return &text; };

/**
 * Возвращает указатель на переопределенный текст сущности.
 *
 * @return Указатель на переопределенный текст.
 */
tstring * getRedefinedText() { return &redefined_text; };

/**
 * Возвращает тип сущности, учитывая переопределение.
 *
 * @return Тип сущности (может вернуть ATOMIC_FORMULA, если переопределено).
 */
EntityBaseType getType() { if ((type != FORMULA_SET) && isRedefined()) return ATOMIC_FORMULA; else return type; };

/**
 * Возвращает тип сущности, если она была заменена.
 *
 * @return Замененный тип сущности.
 */
EntityBaseType getReplacedType();

/**
 * Устанавливает тип сущности.
 *
 * @param type_ Новый тип для установки.
 */
void setType(EntityBaseType type_) { type = type_; };

/**
 * Проверяет, является ли сущность формулой.
 *
 * @return true, если сущность является формулой, иначе false.
 */
bool isFormula() { return ((type != FORMULA_SET) && !((type == REPLACE_VARIABLE) && (replaced_base != nullptr) && replaced_base->isSet())); };

/**
 * Проверяет, является ли сущность множеством.
 *
 * @return true, если сущность является множеством, иначе false.
 */
bool isSet() { bool res = false; ((type == FORMULA_SET) || ((type == REPLACE_VARIABLE) && (replaced_base != nullptr) && replaced_base->isSet())) ? res = true : res = false; return res; };

/**
 * Проверяет, является ли сущность подмножеством.
 *
 * @return true, если сущность является подмножеством, иначе false.
 */
bool isSubset() { if (type == SUBSET) return true; else return false; };

/**
 * Проверяет, было ли сущность переопределена.
 *
 * @return true, если сущность переопределена, иначе false.
 */
bool isRedefined() { return redefined; };

/**
 * Помечает сущность как переопределенную.
 */
void setRedefined() { redefined = true; };

/**
 * Временно снимает пометку с сущности, что она переопределена.
 */
void setTemporarilyUnredefined() { redefined = false; };

/**
 * Устанавливает заменяемую сущность, начальную переменную и новую переменную для REPLACE_VARIABLE.
 *
 * @param base_ Заменяемая сущность.
 * @param initial_ Начальная переменная.
 * @param new_ Новая переменная.
 */
void SetReplacing(EntityBase * base_, EntityVariable * initial_, EntityVariable * new_);

/**
 * Устанавливает замененную базовую сущность.
 *
 * @param preplaced Сущность для установки в качестве замененной.
 */
void setReplacedBase(EntityBase * preplaced) { replaced_base = preplaced; };

/**
 * Возвращает замененную базовую сущность.
 *
 * @return Указатель на замененную базовую сущность.
 */
EntityBase * getReplacedBase() { return replaced_base; };

/**
 * Возвращает начальную переменную, связанную с сущностью.
 *
 * @return Указатель на начальную переменную.
 */
EntityVariable * getInitialVariable() { return initial_variable; };

/**
 * Возвращает новую переменную, связанную с сущностью.
 *
 * @return Указатель на новую переменную.
 */
EntityVariable * getNewVariable() { return new_variable; };

/**
 * Проверяет, является ли сущность частью группы множеств.
 *
 * @param pentities Вектор сущностей для проверки.
 * @return SetGroup, указывающая группу, к которой принадлежит сущность.
 */
SetGroup isPartOfSetGroup(vector <EntityBase *> * pentities);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Класс Formula, представляющий сущность формулы.
class Formula: public EntityBase
{
private:
    /**
     * Устанавливает текст для подмножества формулы.
     *
     * @param entities Сущности, включенные в подмножество.
     */
    void SetSubsetText(vector <EntityBase *> * entities);

    /**
     * Устанавливает метку для подмножества формулы.
     *
     * @param entities Сущности, включенные в подмножество.
     */
    void SetSubsetLabel(vector <EntityBase *> * entities);

protected:
    Formula_Feature feature;  ///< Характеристика формулы.

public:
    vector <ParentLink *> parents;  ///< Список связей с другими формулами.
    vector <EntityVariable *> possibleVariables; ///< Список возможных переменных в формуле.
    vector <Formula*> possibleFormulas; ///< Список возможных формул для дальнейших отношений.

public:
    /**
     * Конструктор по умолчанию для класса Formula.
     */
    Formula(void);

    /**
     * Деструктор для класса Formula.
     */
    ~Formula(void);

    #if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
    #else
    /**
     * Конструктор, инициализирующий формулу из CFormulaItem.
     *
     * @param cfi CFormulaItem для инициализации формулы.
     */
    Formula(const CFormulaItem& );
    #endif
};
/**
 * Сбрасывает свободные переменные в формуле.
 *
 * Эта функция очищает и сбрасывает все переменные, которые больше не нужны в текущем контексте,
 * и добавляет их в список сброшенных переменных.
 *
 * @param unset Вектор, куда добавляются сброшенные переменные.
 */
void unsetFreeVariables(vector <EntityVariable *> * unset);

/**
 * Возвращает характеристику формулы.
 *
 * Этот метод возвращает текущую характеристику формулы, которая была установлена во время ее создания или изменения.
 *
 * @return Характеристика формулы.
 */
Formula_Feature getFeature() { return feature; };

/**
 * Устанавливает новую характеристику для формулы.
 *
 * Этот метод позволяет изменить характеристику формулы, что может потребоваться при изменении структуры формулы.
 *
 * @param feature_ Новая характеристика для установки.
 */
void setFeature(Formula_Feature feature_) { feature = feature_; };

/**
 * Возвращает префикс квантора для формулы.
 *
 * Префикс квантора используется для обозначения типа квантора в формуле,
 * и он может быть необходим при обработке или преобразовании формулы.
 *
 * @return Указатель на строку префикса квантора.
 */
tstring * getQuantifierPrefix() { return &quantifierPrefix; };

/**
 * Объединяет все формулы указанного типа из списка сущностей.
 *
 * Эта функция обрабатывает все сущности данного типа и объединяет их в одну формулу,
 * которая возвращается в виде результата.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @param type Тип сущностей для объединения.
 */
friend void joinAllFormulas(vector <EntityBase *> * entities, EntityBaseType type);

/**
 * Объединяет две формулы указанного типа из списка сущностей.
 *
 * Эта функция обрабатывает две формулы указанного типа, объединяя их в одну формулу,
 * и возвращает результат.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @param type Тип сущностей для объединения.
 * @param first Первая формула для объединения.
 * @param second Вторая формула для объединения.
 * @return Указатель на новую объединенную формулу.
 */
friend Formula * joinFormula(vector <EntityBase *> * entities, EntityBaseType type, Formula * first, Formula * second);

/**
 * Обрабатывает формулу квантора указанного типа.
 *
 * Эта функция генерирует формулу квантора, обрабатывая сущности и
 * их типы, принимая во внимание свободные переменные.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @param type Тип квантора для обработки.
 */
void quantifierFormula(vector <EntityBase *> * entities, EntityBaseType type);
/**
 * Устанавливает атомарную формулу, используя две переменные сущности.
 *
 * Эта функция устанавливает простую атомарную формулу, используя предоставленные переменные,
 * которые обрабатываются и преобразуются соответствующим образом.
 *
 * @param ev1 Первая переменная сущности для использования в атомарной формуле.
 * @param ev2 Вторая переменная сущности для использования в атомарной формуле.
 */
void setAtomFormula(const EntityVariable & ev1, const EntityVariable & ev2);

/**
 * Устанавливает атомарную формулу, используя две переменные сущности и обрабатывая сущности.
 *
 * Эта функция обрабатывает список сущностей и устанавливает атомарную формулу на основе
 * предоставленных переменных, возвращая true, если операция была успешной.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @param ev1 Первая переменная сущности для использования в атомарной формуле.
 * @param ev2 Вторая переменная сущности для использования в атомарной формуле.
 * @return True, если формула была успешно установлена, иначе false.
 */
bool setAtomFormula(vector <EntityBase *> * entities, const EntityVariable & ev1, const EntityVariable & ev2);

/**
 * Устанавливает формулу квантора со свободной переменной и возвращает новую формулу.
 *
 * Эта функция генерирует формулу квантора на основе списка сущностей, типа квантора и свободной переменной.
 * Возвращает результирующую формулу.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @param type Тип квантора.
 * @param freeVariable Указатель на свободную переменную.
 * @return Указатель на сгенерированную формулу квантора.
 */
Formula* quantifierFormula(vector <EntityBase *> * entities, EntityBaseType type, EntityVariable * freeVariable);

/**
 * Создает формулу квантора со свободной переменной и возвращает результат.
 *
 * Эта функция генерирует и возвращает формулу квантора, учитывая тип квантора и предоставленную свободную переменную.
 *
 * @param type Тип квантора.
 * @param freeVariable Указатель на свободную переменную.
 * @return Указатель на формулу квантора.
 */
Formula* quantifierFormula(EntityBaseType type, EntityVariable * freeVariable);

/**
 * Объединяет все формулы указанного типа из списка сущностей.
 *
 * Эта функция обрабатывает все сущности данного типа и объединяет их в одну формулу,
 * которая возвращается в виде результата.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @param type Тип сущностей для объединения.
 */
friend void quantifierAllFormulas(vector <EntityBase *> * entities, EntityBaseType type);

/**
 * Применяет операцию отрицания ко всем формулам в списке сущностей.
 *
 * Эта функция обрабатывает все формулы в предоставленных сущностях и применяет
 * операцию отрицания к каждой из них.
 *
 * @param entities Указатель на список сущностей для обработки.
 */
friend void negativeAllFormulas(vector <EntityBase *> * entities);

/**
 * Применяет операцию отрицания к формуле.
 *
 * Эта функция выполняет отрицание формулы и возвращает результат.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @return Указатель на отрицательную формулу.
 */
Formula* negativeFormula(vector <EntityBase *> * entities);

/**
 * Применяет операцию отрицания к определенной формуле внутри списка сущностей.
 *
 * Эта функция применяет отрицание к определенной формуле в списке, идентифицированной
 * предоставленным индексом, и возвращает результат.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @param i Индекс формулы для отрицания.
 * @return Указатель на отрицательную формулу.
 */
Formula* negativeFormula(vector <EntityBase *> * entities, int i);

/**
 * Определяет, принадлежит ли формула определенному предикату.
 *
 * Эта функция проверяет, принадлежит ли данная формула указанному предикату,
 * и возвращает true, если это так, иначе false.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @param parent Указатель на основную формулу.
 * @param set Указатель на набор формул.
 * @param ptvars Необязательный указатель на строку, содержащую переменные предиката.
 * @return True, если формула принадлежит предикату, иначе false.
 */
bool predicateBelonging(vector <EntityBase *> * entities, Formula * parent, FormulaSet * set, tstring * ptvars = nullptr);

/**
 * Устанавливает текст предиката для заданной формулы.
 *
 * Эта функция назначает текстовое представление для предиката, связанного с
 * основной формулой.
 *
 * @param parent Указатель на основную формулу.
 * @param ptvars Указатель на строку, содержащую переменные предиката.
 */
void SetPredicateText(Formula * parent, tstring * ptvars);

/**
 * Устанавливает текст предиката для заданного набора формул.
 *
 * Эта функция генерирует и назначает текстовое представление для предиката
 * набора формул.
 *
 * @param set_text Текстовое представление предиката.
 */
void SetPredicateText(tstring & set_text);

/**
 * Устанавливает текст подмножества для заданного набора формул.
 *
 * Эта функция генерирует и назначает текстовое представление для подмножества
 * набора формул.
 *
 * @param set_text Текстовое представление подмножества.
 */
void SetSubsetText(tstring & set_text);

/**
 * Определяет, принадлежит ли формула заданному подмножеству.
 *
 * Эта функция проверяет, принадлежит ли формула заданному множеству, и
 * возвращает результат.
 *
 * @param entities Указатель на список сущностей для обработки.
 * @param set Указатель на набор формул.
 * @param variables Указатель на список переменных.
 * @return True, если формула принадлежит подмножеству, иначе false.
 */
bool subset(vector <EntityBase *> * entities, FormulaSet * set, vector <EntityVariable *> * variables);

/**
 * Проверяет, является ли формула атомарной.
 *
 * Эта функция проверяет, является ли текущая формула атомарной.
 *
 * @return True, если формула является атомарной, иначе false.
 */
bool isAtom() { return (type == ATOMIC_FORMULA); };

/**
 * Проверяет, является ли формула отрицанием.
 *
 * Эта функция проверяет, является ли текущая формула операцией отрицания.
 *
 * @return True, если формула является отрицанием, иначе false.
 */
bool isNegative() { if( isRedefined()) return false; else return (type == NEGATIVE_OPERATION); };

/**
 * Проверяет, является ли формула квантором.
 *
 * Эта функция проверяет, является ли текущая формула операцией квантора.
 *
 * @return True, если формула является квантором, иначе false.
 */
bool isQuantifier() { if( isRedefined()) return false; else if((type == QUANTIFIER1_OPERATION) || (type == QUANTIFIER2_OPERATION)) return true; return false; };

/**
 * Проверяет, представляет ли формула предикат принадлежности.
 *
 * Эта функция проверяет, представляет ли текущая формула предикат принадлежности.
 *
 * @return True, если формула является предикатом принадлежности, иначе false.
 */
bool isBelongingPredicate() { return (type == BELONGING_PREDICATE); };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Класс FormulaSet - Представляет набор формул, потенциально вложенных, с переменными и свойствами на основе множеств
//

class FormulaSet : public EntityBase //, public Level
{
private:
    Formula *formula;               ///< Указатель на основную формулу
    FormulaSet *set;                ///< Указатель на вложенный набор формул
    vector<EntityVariable *> baseVariables;  ///< Список базовых переменных для набора формул
    EntityVariable *pnaming;        ///< Переменная, представляющая наименование набора формул

public:
    /**
     * @brief Конструктор по умолчанию для FormulaSet
     */
    FormulaSet(void);

    /**
     * @brief Деструктор для FormulaSet
     */
    ~FormulaSet(void);

    /**
     * @brief Конструктор для инициализации FormulaSet с родительской формулой, списком переменных и переменной наименования.
     * @param parent Указатель на родительскую формулу
     * @param variables Указатель на вектор объектов EntityVariable
     * @param naming_ Указатель на переменную наименования EntityVariable
     */
    FormulaSet(Formula *parent, vector<EntityVariable *> *variables, EntityVariable *naming_);

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
    // Здесь можно добавить дополнительные конструкторы для инициализации на основе XML
#else
    /**
     * @brief Конструктор, который инициализирует FormulaSet из элемента XML.
     * @param item Элемент XML, представляющий FormulaSet
     */
    FormulaSet(const CSetItem& item);
#endif

    /**
     * @brief Устанавливает текст для FormulaSet.
     */
    void setText();

    /**
     * @brief Устанавливает текст для FormulaSet, используя предоставленную строку переменных.
     * @param tvars Строка, представляющая переменные для использования в тексте.
     */
    void setText(tstring tvars);

    /**
     * @brief Устанавливает текст для FormulaSet из списка объектов EntityBase.
     * @param entities Указатель на вектор объектов EntityBase.
     */
    void setText(vector<EntityBase *> *entities);

    /**
     * @brief Получает родительскую формулу для FormulaSet.
     * @return Указатель на объект родительской формулы.
     */
    Formula *getParentFormula() { return formula; }

    /**
     * @brief Устанавливает родительскую формулу для FormulaSet.
     * @param parent Указатель на объект родительской формулы.
     */
    void setParentFormula(Formula *parent) { formula = parent; }

    /**
     * @brief Устанавливает метку для FormulaSet, используя список сущностей.
     * @param entities Указатель на вектор объектов EntityBase.
     */
    void SetLabel(vector<EntityBase *> *entities);

    /**
     * @brief Проверяет, основан ли FormulaSet на переменных.
     * @return True если основан на переменных, иначе false.
     */
    bool isVariableBased();

    /**
     * @brief Проверяет, основан ли FormulaSet на других множествах.
     * @return True если основан на множествах, иначе false.
     */
    bool isSetBased();

    /**
     * @brief Получает список базовых переменных для FormulaSet.
     * @return Указатель на вектор базовых переменных.
     */
    vector<EntityVariable *> *getBaseVariables() { return &baseVariables; }

    /**
     * @brief Получает переменную для наименования FormulaSet.
     * @return Указатель на переменную наименования EntityVariable.
     */
    EntityVariable *getNaming() { return pnaming; }

    /**
     * @brief Устанавливает переменную для наименования FormulaSet.
     * @param pev Указатель на объект EntityVariable для установки в качестве переменной наименования.
     */
    void setNaming(EntityVariable *pev) { pnaming = pev; }

    /**
     * @brief Проверяет, является ли FormulaSet формулой исключения.
     * @param parent Указатель на родительскую формулу.
     * @return True если FormulaSet является исключением, иначе false.
     */
    bool isExclusion(Formula *parent);

    /**
     * @brief Обрабатывает исключение для FormulaSet.
     * @param parent Указатель на родительскую формулу.
     * @param variables Указатель на вектор переменных.
     * @param tvars Строка для хранения текстовых переменных.
     * @param tlevel Строка для хранения уровня текста.
     * @param produceText Логический флаг для определения, следует ли генерировать текст (по умолчанию true).
     */
    void proccessExclusion(Formula *parent, vector<EntityVariable *> *variables, tstring &tvars, tstring &tlevel, bool produceText = TRUE);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Класс Tuple - Представляет кортеж переменных в формуле
//
class Tuple: public Formula
{
private:
    int level;  ///< Уровень, связанный с кортежем

public:
    /**
     * @brief Конструктор по умолчанию для Tuple
     */
    Tuple(void);

    /**
     * @brief Конструктор для создания кортежа с набором переменных EntityVariable.
     * @param ev1 Первая переменная сущности
     * @param set Набор переменных EntityVariable
     */
    Tuple(EntityVariable &ev1, EntityVariable &set);

    /**
     * @brief Конструктор для создания кортежа с двумя переменными EntityVariable и набором.
     * @param ev1 Первая переменная сущности
     * @param ev2 Вторая переменная сущности
     * @param set Набор переменных EntityVariable
     */
    Tuple(EntityVariable &ev1, EntityVariable &ev2, EntityVariable &set);

    /**
     * @brief Конструктор для создания кортежа из вектора переменных EntityVariable и набора.
     * @param pev Указатель на вектор переменных EntityVariable
     * @param set Набор переменных EntityVariable
     */
    Tuple(vector<EntityVariable *> *pev, EntityVariable &set);

    /**
     * @brief Конструктор для создания кортежа из CFormulaItem.
     * @param fi CFormulaItem для инициализации кортежа.
     */
    Tuple(const CFormulaItem& fi);

    /**
     * @brief Деструктор для Tuple
     */
    ~Tuple(void);

    /**
     * @brief Устанавливает уровень для Tuple.
     * @param l Уровень для установки.
     */
    void SetLevel(int l) { level = l; }

    /**
     * @brief Устанавливает текст для Tuple на основе предоставленных переменных.
     * @param depending Указатель на вектор переменных EntityVariable (опционально)
     * @param ptvars Указатель на строку переменных (опционально)
     */
    void SetTupleText(vector<EntityVariable *> *depending = nullptr, tstring *ptvars = nullptr);

    /**
     * @brief Устанавливает текст для Tuple напрямую из строки.
     * @param tstr Текст для установки.
     */
    void SetTupleText(tstring &tstr) { text = tstr; }

    /**
     * @brief Устанавливает метку для Tuple из строки.
     * @param tstr Строка метки для установки.
     */
    void SetTupleLabel(tstring &tstr) { label = tstr; }

    /**
     * @brief Сравнивает Tuple с переменной EntityVariable.
     * @param ev Переменная EntityVariable для сравнения.
     * @return True если Tuple соответствует переменной EntityVariable, иначе false.
     */
    bool compare(const EntityVariable& ev);
};

// Вспомогательные функции

/**
 * @brief Сравнивает две переменные EntityVariable для определения их порядка в бинарном поиске.
 * @param ev Первая переменная EntityVariable
 * @param evcomp Вторая переменная EntityVariable
 * @return True если ev меньше чем evcomp, иначе false.
 */
bool myentity_compare(EntityVariable *ev, EntityVariable *evcomp);

/**
 * @brief Проверяет существование переменной на основе её символа и индекса в списке сущностей.
 * @param symbol Символ переменной
     * @param index Индекс переменной
 * @param entities Указатель на список объектов EntityBase
 * @return True если переменная существует, иначе false.
 */
bool isExistVariable(tstring &symbol, tstring &index, vector<EntityBase *> *entities);

/**
 * @brief Проверяет существование переменной наименования на основе её символа и индекса в списке сущностей.
 * @param symbol Символ переменной наименования
 * @param index Индекс переменной наименования
 * @param entities Указатель на список объектов EntityBase
 * @return True если переменная наименования существует, иначе false.
 */
bool isExistNaming(tstring &symbol, tstring &index, vector<EntityBase *> *entities);

/**
 * @brief Проверяет существование FormulaSet на основе её символа и индекса в списке сущностей.
 * @param symbol Символ FormulaSet
 * @param index Индекс FormulaSet
 * @param entities Указатель на список объектов EntityBase
 * @return Указатель на совпадающий FormulaSet если он существует, иначе nullptr.
 */
FormulaSet *isExistFormulaSet(tstring &symbol, tstring &index, vector<EntityBase *> *entities);

/**
 * @brief Проверяет, представляет ли данный текст переменную в метке.
 * @param text Текст для проверки
 * @return True если текст является допустимой переменной в метке, иначе false.
 */
bool isTextOfVariable(tstring &text);

/**
 * @brief Создает переменную в метке на основе вектора сущностей.
 * @param entities Указатель на вектор объектов EntityBase
 * @param base Объект EntityBase, представляющий основу метки
 * @return Строка, представляющая переменную в метке.
 */
tstring makeVarPartOfLabel(vector<EntityBase *> *entities, EntityBase *base);