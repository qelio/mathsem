#pragma once

#include "common_functions.h"
//#include <stdint.h>

/**
 * @enum EntityBaseType
 * @brief Enumeration for the types of entities used in logical formulas.
 */
enum EntityBaseType {
    NONE_FORMULA, ///< Undefined entity type.
    ATOMIC_FORMULA = 1, ///< Atomic formula type.
    NEGATIVE_OPERATION = 2, ///< Negation operation (NOT).
    QUANTIFIER1_OPERATION = 3, ///< Quantifier operation type 1 (e.g., for universal quantification).
    QUANTIFIER2_OPERATION = 4, ///< Quantifier operation type 2 (e.g., for existential quantification).
    AND_OPERATION = 5,  ///< AND logical operation.
    OR_OPERATION = 6,  ///< OR logical operation.
    FORMULA_SET = 7,  ///< Set of formulas.
    BELONGING_PREDICATE = 8, ///< Predicate for membership in a set.
    TUPLE = 9, ///< Tuple entity.
    SUBSET = 10, ///< Subset operation.
    REPLACE_VARIABLE = 11, ///< Variable replacement operation.
};

/**
 * @enum Formula_Feature
 * @brief Enumeration for the possible features or states of a formula.
 */
enum Formula_Feature {
    NONE_FEATURE,  ///< No specific feature.
    TRUTH_FEATURE = 1, ///< Formula is true.
    FALSE_FEATURE = 2, ///< Formula is false.
    PERFORMED_FEATURE = 3,  ///< Formula has been executed.
    ATOMARN_FEATURE = 4 ///< Formula is atomic.
};

/**
 * @enum VariableType
 * @brief Enumeration for the types of variables used in logical formulas.
 */
enum VariableType {
    NONE_VARIABLE, ///< Undefined variable type.
    VARIABLE = 1, ///< Standard variable type.
    SET = 2 ///< Set variable type.
};

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
// If libxml2 is enabled, handle XML serialization/deserialization here.
#else
// Classes representing variable and formula items if libxml is not used.
class CVariableItem;  ///< Class for variable item representing logical variables.
class CFormulaItem;  ///< Class for formula item, part of the logical formula representation.
class CSetItem;    ///< Class for set item representing formula sets.
#endif

/**
 * @class Level
 * @brief Class representing the level or context for a variable or formula.
 *
 * This class is used to encapsulate the level of a variable or formula, which can be used for comparison or contextual manipulation.
 */
class Level
{
protected:
    tstring level; ///< The string representing the level.

public:
    /**
     * @brief Default constructor, initializes the level to "0".
     */
    Level() { level = _T("0"); }

    /**
     * @brief Parameterized constructor, initializes the level with the given string.
     * @param tstr The level string to initialize.
     */
    Level(tstring & tstr) { level = tstr; }

    /**
     * @brief Destructor for cleaning up the Level object.
     */
    ~Level() {}

    /**
     * @brief Retrieves the current level string.
     * @return The level string.
     */
    tstring & GetLevel() { return level; }

    /**
     * @brief Sets the level to the specified string.
     * @param tstr The string to set as the level.
     */
    void SetLevel(tstring & tstr) { level = tstr; }

    /**
     * @brief Compares the current level with another level.
     * @param l The other level to compare.
     * @return True if levels are equal, otherwise false.
     */
    bool compare(const Level& l) { return !level.compare(l.level); }
};

/**
 * @class EntityVariable
 * @brief Class representing a variable entity within a logical formula.
 *
 * The class is used to handle variables, including their types, labels, and indices, and provides methods for manipulation and comparison.
 */
class EntityVariable: public Level
{
    VariableType type; ///< Type of the variable (standard variable or set).
    tstring label; ///< Label representing the variable.
    tstring index; ///< Index for distinguishing different instances of the same variable.
    tstring redefinition; ///< Redefinition of the variable (if any).
    tstring text; ///< Textual representation of the variable.

public:
    /**
     * @brief Default constructor, initializes the variable with default values.
     */
    EntityVariable() { type = VARIABLE; label = _T("x"); index = _T(""); SetText(); }

    /**
     * @brief Destructor for cleaning up the EntityVariable object.
     */
    ~EntityVariable() {}

    /**
     * @brief Constructor with initialization parameters for variable type, label, and index.
     * @param str The variable label.
     * @param index_ The index of the variable.
     * @param type_ The type of the variable (either VARIABLE or SET).
     */
    EntityVariable(const tstring & str, const tstring & index_, VariableType type_)
        { label = str; index = index_; type = type_; SetText(); }

    /**
     * @brief Copy constructor to create a new EntityVariable from an existing one.
     * @param ev The EntityVariable to copy.
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
    // XML serialization logic goes here if libxml2 is enabled.
#else
    /**
     * @brief Constructor from a variable item in the case where libxml2 is not used.
     * @param vi The variable item to initialize from.
     */
    EntityVariable(const CVariableItem& vi);
#endif
};























/**
 * Returns the text, considering redefinition if available.
 * If redefinition is set, it will return the redefined text,
 * otherwise, it will return the original text.
 *
 * @return A pointer to the current text (either redefined or original).
 */
tstring * GetText() { if(redefinition.length() > 0) return &redefinition; else return &text; };

/**
 * Returns the initial (original) text without considering redefinition.
 *
 * @return A pointer to the original text.
 */
tstring * GetInitialText() { return &text; };

/**
 * Sets the text for the label and appends the index with special formatting.
 * This method combines the label with the formatted index, if any.
 *
 * @note The method does not currently append the index, as the code is commented out.
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
 * Sets the redefinition text.
 *
 * @param new_text The new text to set as redefinition.
 */
void SetRedefinition(tstring & new_text) {redefinition = new_text; };

/**
 * Returns the redefinition text.
 *
 * @return A reference to the redefinition text.
 */
tstring & GetRedefinition() { return redefinition; };

/**
 * Compares the current variable with another one.
 *
 * @param ev The EntityVariable to compare with.
 * @return true if the variables are equal, false otherwise.
 */
bool compare(const EntityVariable&);

/**
 * Checks if the variable is set.
 *
 * @return true if the type is SET, false otherwise.
 */
bool isSet() { bool res = false; (type == SET) ? res=true : res = false; return res; };

/**
 * Checks if the variable is of type VARIABLE.
 *
 * @return true if the type is VARIABLE, false otherwise.
 */
bool isVariable() { bool res; (type == VARIABLE) ? res=true : res=false; return res; };

/**
 * Returns the label of the entity variable.
 *
 * @return A reference to the label.
 */
tstring & GetLabel() { return label; };

/**
 * Returns the index of the entity variable.
 *
 * @return A reference to the index.
 */
tstring & GetIndex() { return index; };

/**
 * Returns the type of the variable.
 *
 * @return The type of the variable as a VariableType.
 */
VariableType GetType() { return type; };

/**
 * Sets the index of the entity variable.
 *
 * @param ind The new index to set.
 */
void SetIndex(tstring & ind) { index = ind; };

/**
 * Sets the label of the entity variable.
 *
 * @param lab The new label to set.
 */
void SetLabel(tstring & lab) { label = lab; };

/**
 * Sets the type of the entity variable.
 *
 * @param type_ The new type to set.
 */
void SetType(VariableType type_) { type = type_; };

/**
 * Equality operator for comparing two EntityVariable objects.
 *
 * @param ev1 The first EntityVariable to compare.
 * @param ev2 The second EntityVariable to compare.
 * @return true if the variables are equal, false otherwise.
 */
bool operator == (EntityVariable& ev1, EntityVariable& ev2);

/**
 * Represents an entity with free and linked variables, a description, and additional information.
 * Provides accessors for free and linked variables, as well as the text and description of the entity.
 */
class EntityBase
{
protected:
    vector <EntityVariable *> freeVariables;  ///< List of free variables.
    vector <EntityVariable *> linkedVariables;  ///< List of linked variables.
    tstring description;  ///< Description of the entity.
    tstring addons;  ///< Addons related to the entity.
    tstring label; ///< Label associated with the entity.
    tstring text; ///< Text associated with the entity.
    EntityBaseType type; ///< Type of the entity, from EntityBaseType enum.
    tstring redefined_text; ///< Redefined text, if any.
    bool redefined; ///< Flag indicating if the entity has been redefined.
    EntityBase * replaced_base; ///< Pointer to the replaced base entity, or nullptr.
    EntityVariable * initial_variable; ///< Initial variable, or nullptr.
    EntityVariable * new_variable; ///< New variable, or nullptr.

public:
    /**
     * Default constructor for the EntityBase class.
     */
    EntityBase(void);

    /**
     * Destructor for the EntityBase class.
     */
    ~EntityBase(void);

    /**
     * Returns the list of free variables.
     *
     * @return A pointer to the vector of free variables.
     */
    vector <EntityVariable *> * getFreeVariables() { return &freeVariables; };

    /**
     * Returns the list of linked variables.
     *
     * @return A pointer to the vector of linked variables.
     */
    vector <EntityVariable *> * getLinkedVariables() { return &linkedVariables; };

    /**
     * Returns the text associated with the entity, considering redefinition if available.
     *
     * @return A reference to the current text (either redefined or original).
     */
    tstring & getText() { if(redefined_text.length() > 0) return redefined_text; else return text; };

    /**
     * Returns the description of the entity.
     *
     * @return A pointer to the description string.
     */
    tstring * getDescription() { return &description; };

    /**
     * Returns the addons related to the entity.
     *
     * @return A pointer to the addons string.
     */
    tstring * getAddOns() { return &addons; };

    /**
     * Sets the text for the entity.
     *
     * @param lpctstr The text to set.
     */
    void SetText(LPCTSTR lpctstr);

    /**
     * Sets the redefined text for the entity.
     *
     * @param lpctstr The redefined text to set.
     */
    //void SetIRedefinedText(LPCTSTR lpctstr) { redefined_text = lpctstr; };
};








/**
 * Sets the description of the entity.
 *
 * @param lpctstr The description text to set.
 */
void SetDescription(LPCTSTR lpctstr) { description = lpctstr; };

/**
 * Sets the addons for the entity.
 *
 * @param lpctstr The addon text to set.
 */
void SetAddons(LPCTSTR lpctstr) { addons = lpctstr; };

/**
 * Returns a pointer to the label of the entity.
 *
 * @return A pointer to the label string.
 */
tstring * getLabel() { return &label; };

/**
 * Returns a pointer to the initial text (before redefinition) of the entity.
 *
 * @return A pointer to the initial text.
 */
tstring * getInitialText() { return &text; };

/**
 * Returns a pointer to the redefined text of the entity.
 *
 * @return A pointer to the redefined text.
 */
tstring * getRedefinedText() { return &redefined_text; };

/**
 * Returns the type of the entity, considering redefinition.
 *
 * @return The type of the entity (may return ATOMIC_FORMULA if redefined).
 */
EntityBaseType getType() { if ((type != FORMULA_SET) && isRedefined()) return ATOMIC_FORMULA; else return type; };

/**
 * Returns the type of the entity if it has been replaced.
 *
 * @return The replaced type of the entity.
 */
EntityBaseType getReplacedType();

/**
 * Sets the type of the entity.
 *
 * @param type_ The new type to set.
 */
void setType(EntityBaseType type_) { type = type_; };

/**
 * Checks if the entity is a formula.
 *
 * @return true if the entity is a formula, false otherwise.
 */
bool isFormula() { return ((type != FORMULA_SET) && !((type == REPLACE_VARIABLE) && (replaced_base != nullptr) && replaced_base->isSet())); };

/**
 * Checks if the entity is a set.
 *
 * @return true if the entity is a set, false otherwise.
 */
bool isSet() { bool res = false; ((type == FORMULA_SET) || ((type == REPLACE_VARIABLE) && (replaced_base != nullptr) && replaced_base->isSet())) ? res = true : res = false; return res; };

/**
 * Checks if the entity is a subset.
 *
 * @return true if the entity is a subset, false otherwise.
 */
bool isSubset() { if (type == SUBSET) return true; else return false; };

/**
 * Checks if the entity has been redefined.
 *
 * @return true if the entity is redefined, false otherwise.
 */
bool isRedefined() { return redefined; };

/**
 * Marks the entity as redefined.
 */
void setRedefined() { redefined = true; };

/**
 * Marks the entity as temporarily unredefined.
 */
void setTemporarilyUnredefined() { redefined = false; };

/**
 * Sets the replacing entity, initial variable, and new variable for REPLACE_VARIABLE.
 *
 * @param base_ The entity to replace.
 * @param initial_ The initial variable.
 * @param new_ The new variable.
 */
void SetReplacing(EntityBase * base_, EntityVariable * initial_, EntityVariable * new_);

/**
 * Sets the replaced base entity.
 *
 * @param preplaced The entity to set as replaced.
 */
void setReplacedBase(EntityBase * preplaced) { replaced_base = preplaced; };

/**
 * Returns the replaced base entity.
 *
 * @return A pointer to the replaced base entity.
 */
EntityBase * getReplacedBase() { return replaced_base; };

/**
 * Returns the initial variable associated with the entity.
 *
 * @return A pointer to the initial variable.
 */
EntityVariable * getInitialVariable() { return initial_variable; };

/**
 * Returns the new variable associated with the entity.
 *
 * @return A pointer to the new variable.
 */
EntityVariable * getNewVariable() { return new_variable; };

/**
 * Checks if the entity is part of a set group.
 *
 * @param pentities The vector of entities to check.
 * @return A SetGroup indicating the group the entity belongs to.
 */
SetGroup isPartOfSetGroup(vector <EntityBase *> * pentities);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Class Formula, representing a formula entity.
class Formula: public EntityBase
{
private:
    /**
     * Sets the subset text for the formula.
     *
     * @param entities The entities to include in the subset.
     */
    void SetSubsetText(vector <EntityBase *> * entities);

    /**
     * Sets the subset label for the formula.
     *
     * @param entities The entities to include in the subset.
     */
    void SetSubsetLabel(vector <EntityBase *> * entities);

protected:
    Formula_Feature feature;  ///< Feature of the formula.

public:
    vector <ParentLink *> parents;  ///< List of parent links to other formulas.
    vector <EntityVariable *> possibleVariables; ///< List of possible variables in the formula.
    vector <Formula*> possibleFormulas; ///< List of possible formulas for further relationships.

public:
    /**
     * Default constructor for the Formula class.
     */
    Formula(void);

    /**
     * Destructor for the Formula class.
     */
    ~Formula(void);

    #if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
    #else
    /**
     * Constructor that initializes the formula from a CFormulaItem.
     *
     * @param cfi The CFormulaItem to initialize the formula.
     */
    Formula(const CFormulaItem& );
    #endif
};
/**
 * Unsets the free variables in the formula.
 *
 * This function clears and unsets all the variables that are no longer needed in the
 * current context and adds them to the unset list.
 *
 * @param unset A reference to the vector where the unset variables are added.
 */
void unsetFreeVariables(vector <EntityVariable *> * unset);

/**
 * Gets the feature of the formula.
 *
 * This method returns the current feature of the formula, which was set during its
 * creation or modification.
 *
 * @return The feature of the formula.
 */
Formula_Feature getFeature() { return feature; };

/**
 * Sets a new feature for the formula.
 *
 * This method allows changing the formula's feature, which might be necessary when
 * modifying the formula's structure.
 *
 * @param feature_ The new feature to set for the formula.
 */
void setFeature(Formula_Feature feature_) { feature = feature_; };

/**
 * Gets the quantifier prefix for the formula.
 *
 * The quantifier prefix is used to denote the type of quantifier in the formula,
 * and it may be required when processing or transforming the formula.
 *
 * @return A pointer to the quantifier prefix string.
 */
tstring * getQuantifierPrefix() { return &quantifierPrefix; };

/**
 * Joins all formulas of a specified type from a list of entities.
 *
 * This function processes all entities of the given type and combines them into
 * a single formula, which is returned as a result.
 *
 * @param entities A pointer to the list of entities to process.
 * @param type The type of the entities to join.
 */
friend void joinAllFormulas(vector <EntityBase *> * entities, EntityBaseType type);

/**
 * Joins two formulas of a specified type from a list of entities.
 *
 * This function processes two formulas of the specified type, merging them into
 * a single formula, and returns the result.
 *
 * @param entities A pointer to the list of entities to process.
 * @param type The type of the entities to join.
 * @param first The first formula to combine.
 * @param second The second formula to combine.
 * @return A pointer to the new combined formula.
 */
friend Formula * joinFormula(vector <EntityBase *> * entities, EntityBaseType type, Formula * first, Formula * second);

/**
 * Processes the quantifier formula of a specified type.
 *
 * This function generates the quantifier formula by processing the entities and
 * their respective types, taking into account free variables.
 *
 * @param entities A pointer to the list of entities to process.
 * @param type The type of quantifier to process.
 */
void quantifierFormula(vector <EntityBase *> * entities, EntityBaseType type);

/**
 * Sets an atomic formula using two entity variables.
 *
 * This function sets a simple atomic formula using the provided variables, which
 * are processed and transformed accordingly.
 *
 * @param ev1 The first entity variable to use in the atomic formula.
 * @param ev2 The second entity variable to use in the atomic formula.
 */
void setAtomFormula(const EntityVariable & ev1, const EntityVariable & ev2);

/**
 * Sets an atomic formula using two entity variables, and processes the entities.
 *
 * This function processes a list of entities and sets the atomic formula based
 * on the provided variables, returning true if the operation was successful.
 *
 * @param entities A pointer to the list of entities to process.
 * @param ev1 The first entity variable to use in the atomic formula.
 * @param ev2 The second entity variable to use in the atomic formula.
 * @return True if the formula was set successfully, otherwise false.
 */
bool setAtomFormula(vector <EntityBase *> * entities, const EntityVariable & ev1, const EntityVariable & ev2);

/**
 * Sets a quantifier formula with a free variable and returns the new formula.
 *
 * This function generates a quantifier formula based on the list of entities,
 * the quantifier type, and the free variable. It returns the resulting formula.
 *
 * @param entities A pointer to the list of entities to process.
 * @param type The type of quantifier.
 * @param freeVariable A pointer to the free variable.
 * @return A pointer to the generated quantifier formula.
 */
Formula* quantifierFormula(vector <EntityBase *> * entities, EntityBaseType type, EntityVariable * freeVariable);

/**
 * Creates a quantifier formula with a free variable and returns the result.
 *
 * This function generates and returns a quantifier formula, taking into account
 * the type of quantifier and the free variable provided.
 *
 * @param type The type of quantifier.
 * @param freeVariable A pointer to the free variable.
 * @return A pointer to the quantifier formula.
 */
Formula* quantifierFormula(EntityBaseType type, EntityVariable * freeVariable);

/**
 * Joins all formulas of a specified type from the entities.
 *
 * This function processes all entities of the given type and combines them into
 * a single formula, which is returned as the result.
 *
 * @param entities A pointer to the list of entities to process.
 * @param type The type of entities to join.
 */
friend void quantifierAllFormulas(vector <EntityBase *> * entities, EntityBaseType type);

/**
 * Applies a negative operation to all formulas in the list of entities.
 *
 * This function processes all formulas in the provided entities and applies a
 * negation operation to each one.
 *
 * @param entities A pointer to the list of entities to process.
 */
friend void negativeAllFormulas(vector <EntityBase *> * entities);

/**
 * Applies a negation operation to the formula.
 *
 * This function negates the formula and returns the result.
 *
 * @param entities A pointer to the list of entities to process.
 * @return A pointer to the negated formula.
 */
Formula*  negativeFormula(vector <EntityBase *> * entities);

/**
 * Applies a negation operation to a specific formula within the list of entities.
 *
 * This function applies negation to a specific formula in the list, identified by
 * the provided index, and returns the result.
 *
 * @param entities A pointer to the list of entities to process.
 * @param i The index of the formula to negate.
 * @return A pointer to the negated formula.
 */
Formula*  negativeFormula(vector <EntityBase *> * entities, int i);

/**
 * Determines if the formula belongs to a specific predicate.
 *
 * This function checks whether the given formula belongs to the specified predicate
 * and returns true if it does, otherwise false.
 *
 * @param entities A pointer to the list of entities to process.
 * @param parent A pointer to the parent formula.
 * @param set A pointer to the formula set.
 * @param ptvars Optional pointer to a string containing predicate variables.
 * @return True if the formula belongs to the predicate, otherwise false.
 */
bool predicateBelonging(vector <EntityBase *> * entities, Formula * parent, FormulaSet * set, tstring * ptvars = nullptr);

/**
 * Sets the predicate text for a given formula.
 *
 * This function assigns a textual representation for the predicate associated with
 * the parent formula.
 *
 * @param parent A pointer to the parent formula.
 * @param ptvars A pointer to a string containing predicate variables.
 */
void SetPredicateText(Formula * parent, tstring * ptvars);

/**
 * Sets the predicate text for the given formula set.
 *
 * This function generates and assigns the text representation for the predicate
 * of the formula set.
 *
 * @param set_text The text representation of the predicate.
 */
void SetPredicateText(tstring & set_text);

/**
 * Sets the subset text for the given formula set.
 *
 * This function generates and assigns the text representation for the subset
 * of the formula set.
 *
 * @param set_text The text representation of the subset.
 */
void SetSubsetText(tstring & set_text);

/**
 * Determines if the formula belongs to a specified subset.
 *
 * This function checks whether the formula belongs to the given set and
 * returns the result.
 *
 * @param entities A pointer to the list of entities to process.
 * @param set A pointer to the formula set.
 * @param variables A pointer to the list of variables.
 * @return True if the formula belongs to the subset, otherwise false.
 */
bool subset(vector <EntityBase *> * entities, FormulaSet * set, vector <EntityVariable *> * variables);

/**
 * Checks if the formula is atomic.
 *
 * This function checks whether the current formula is atomic.
 *
 * @return True if the formula is atomic, otherwise false.
 */
bool isAtom() { return (type == ATOMIC_FORMULA); };

/**
 * Checks if the formula is a negation.
 *
 * This function checks if the current formula is a negation operation.
 *
 * @return True if the formula is a negation, otherwise false.
 */
bool isNegative() { if( isRedefined()) return false; else return (type == NEGATIVE_OPERATION); };

/**
 * Checks if the formula is a quantifier.
 *
 * This function checks if the current formula is a quantifier operation.
 *
 * @return True if the formula is a quantifier, otherwise false.
 */
bool isQuantifier() { if( isRedefined()) return false; else if((type == QUANTIFIER1_OPERATION) || (type == QUANTIFIER2_OPERATION)) return true; return false; };

/**
 * Checks if the formula represents a belonging predicate.
 *
 * This function checks if the current formula represents a belonging predicate.
 *
 * @return True if the formula is a belonging predicate, otherwise false.
 */
bool isBelongingPredicate() { return (type == BELONGING_PREDICATE); };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  class FormulaSet - Represents a set of formulas, potentially nested, with variable-based and set-based properties
//
class FormulaSet : public EntityBase //, public Level
{
private:
    Formula *formula;               ///< Pointer to the parent Formula object
    FormulaSet *set;                ///< Pointer to a nested FormulaSet object
    vector <EntityVariable *> baseVariables;  ///< List of base variables for the FormulaSet
    EntityVariable *pnaming;        ///< Variable representing the naming of the FormulaSet

public:
    /**
     * @brief Default constructor for FormulaSet
     */
    FormulaSet(void);

    /**
     * @brief Destructor for FormulaSet
     */
    ~FormulaSet(void);

    /**
     * @brief Constructor to initialize FormulaSet with a parent Formula, a list of variables, and a naming variable.
     * @param parent Pointer to the parent Formula
     * @param variables Pointer to a vector of EntityVariable objects
     * @param naming Pointer to the naming EntityVariable
     */
    FormulaSet(Formula *parent, vector <EntityVariable *> *variables, EntityVariable *naming_);

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)
    // Additional constructors can be added here for XML-based initialization
#else
    /**
     * @brief Constructor that initializes FormulaSet from an XML item.
     * @param item The XML item representing the FormulaSet
     */
    FormulaSet(const CSetItem& item);
#endif

    /**
     * @brief Sets the text for the FormulaSet.
     */
    void setText();

    /**
     * @brief Sets the text for the FormulaSet using the provided variable string.
     * @param tvars String representing the variables to use in the text.
     */
    void setText(tstring tvars);

    /**
     * @brief Sets the text for the FormulaSet from a list of EntityBase objects.
     * @param entities Pointer to a vector of EntityBase objects.
     */
    void setText(vector <EntityBase *> *entities);

    /**
     * @brief Gets the parent Formula of the FormulaSet.
     * @return Pointer to the parent Formula object.
     */
    Formula *getParentFormula() { return formula; }

    /**
     * @brief Sets the parent Formula of the FormulaSet.
     * @param parent Pointer to the parent Formula object.
     */
    void setParentFormula(Formula *parent) { formula = parent; }

    /**
     * @brief Sets a label for the FormulaSet using a list of entities.
     * @param entities Pointer to a vector of EntityBase objects.
     */
    void SetLabel(vector <EntityBase *> *entities);

    /**
     * @brief Checks if the FormulaSet is based on variables.
     * @return True if based on variables, false otherwise.
     */
    bool isVariableBased();

    /**
     * @brief Checks if the FormulaSet is based on other sets.
     * @return True if based on sets, false otherwise.
     */
    bool isSetBased();

    /**
     * @brief Gets the list of base variables for the FormulaSet.
     * @return Pointer to the vector of base variables.
     */
    vector <EntityVariable *> *getBaseVariables() { return &baseVariables; }

    /**
     * @brief Gets the naming variable for the FormulaSet.
     * @return Pointer to the naming EntityVariable.
     */
    EntityVariable *getNaming() { return pnaming; }

    /**
     * @brief Sets the naming variable for the FormulaSet.
     * @param pev Pointer to the EntityVariable to set as the naming variable.
     */
    void setNaming(EntityVariable *pev) { pnaming = pev; }

    /**
     * @brief Checks if the FormulaSet is an exclusion formula.
     * @param parent Pointer to the parent Formula.
     * @return True if the FormulaSet is an exclusion, false otherwise.
     */
    bool isExclusion(Formula *parent);

    /**
     * @brief Processes exclusion for the FormulaSet.
     * @param parent Pointer to the parent Formula.
     * @param variables Pointer to a vector of variables.
     * @param tvars String to store text variables.
     * @param tlevel String to store the text level.
     * @param produceText Boolean flag to determine if text should be produced (default is true).
     */
    void proccessExclusion(Formula *parent, vector <EntityVariable *> *variables, tstring &tvars, tstring &tlevel, bool produceText = TRUE);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  class Tuple - Represents a tuple of variables within a formula
//
class Tuple: public Formula
{
private:
    int level;  ///< Level associated with the Tuple

public:
    /**
     * @brief Default constructor for Tuple
     */
    Tuple(void);

    /**
     * @brief Constructor to create a Tuple with a set of EntityVariables.
     * @param ev1 First EntityVariable
     * @param set The set EntityVariable
     */
    Tuple(EntityVariable &ev1, EntityVariable &set);

    /**
     * @brief Constructor to create a Tuple with two EntityVariables and a set.
     * @param ev1 First EntityVariable
     * @param ev2 Second EntityVariable
     * @param set The set EntityVariable
     */
    Tuple(EntityVariable &ev1, EntityVariable &ev2, EntityVariable &set);

    /**
     * @brief Constructor to create a Tuple from a vector of EntityVariables and a set.
     * @param pev Pointer to a vector of EntityVariables
     * @param set The set EntityVariable
     */
    Tuple(vector <EntityVariable *> *pev, EntityVariable &set);

    /**
     * @brief Constructor to create a Tuple from a CFormulaItem.
     * @param fi The CFormulaItem to initialize the Tuple.
     */
    Tuple(const CFormulaItem& fi);

    /**
     * @brief Destructor for Tuple
     */
    ~Tuple(void);

    /**
     * @brief Sets the level for the Tuple.
     * @param l The level to set.
     */
    void SetLevel(int l) { level = l; }

    /**
     * @brief Sets the text for the Tuple based on the provided variables.
     * @param depending Pointer to a vector of EntityVariables (optional)
     * @param ptvars Pointer to a string of variables (optional)
     */
    void SetTupleText(vector <EntityVariable *> *depending = nullptr, tstring *ptvars = nullptr);

    /**
     * @brief Sets the text for the Tuple directly from a string.
     * @param tstr The text to set.
     */
    void SetTupleText(tstring &tstr) { text = tstr; }

    /**
     * @brief Sets the label for the Tuple from a string.
     * @param tstr The label string to set.
     */
    void SetTupleLabel(tstring &tstr) { label = tstr; }

    /**
     * @brief Compares the Tuple to an EntityVariable.
     * @param ev The EntityVariable to compare with.
     * @return True if the Tuple matches the EntityVariable, false otherwise.
     */
    bool compare(const EntityVariable& ev);
};

// Auxiliary functions

/**
 * @brief Compares two EntityVariables to determine their order in a binary search.
 * @param ev The first EntityVariable
 * @param evcomp The second EntityVariable
 * @return True if ev is less than evcomp, false otherwise.
 */
bool myentity_compare(EntityVariable *ev, EntityVariable *evcomp);

/**
 * @brief Checks if a variable exists based on its symbol and index in a list of entities.
 * @param symbol The symbol of the variable
 * @param index The index of the variable
 * @param entities Pointer to a vector of EntityBase objects
 * @return True if the variable exists, false otherwise.
 */
bool isExistVariable(tstring &symbol, tstring &index, vector <EntityBase *> *entities);

/**
 * @brief Checks if a naming variable exists based on its symbol and index in a list of entities.
 * @param symbol The symbol of the naming variable
 * @param index The index of the naming variable
 * @param entities Pointer to a vector of EntityBase objects
 * @return True if the naming variable exists, false otherwise.
 */
bool isExistNaming(tstring &symbol, tstring &index, vector <EntityBase *> *entities);

/**
 * @brief Checks if a FormulaSet exists based on its symbol and index in a list of entities.
 * @param symbol The symbol of the FormulaSet
 * @param index The index of the FormulaSet
 * @param entities Pointer to a vector of EntityBase objects
 * @return Pointer to the matching FormulaSet if it exists, nullptr otherwise.
 */
FormulaSet *isExistFormulaSet(tstring &symbol, tstring &index, vector <EntityBase *> *entities);

/**
 * @brief Checks if the given text represents a variable part of a label.
 * @param text The text to check
 * @return True if the text is a valid variable part of a label, false otherwise.
 */
bool isTextOfVariable(tstring &text);

/**
 * @brief Creates a variable part of a label based on a vector of entities.
 * @param entities Pointer to a vector of EntityBase objects
 * @param base The EntityBase representing the base of the label
 * @return The string representing the variable part of the label.
 */
tstring makeVarPartOfLabel(vector <EntityBase *> *entities, EntityBase *base);

